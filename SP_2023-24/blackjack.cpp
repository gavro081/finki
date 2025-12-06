//
// Created by Filip on 29.12.24.
//
#include <iostream>
#include <ctime>

using namespace std;
void PrintGameRules();
int CardPicked(int x);
string PrintCard(int Card);
char BetChoice (string choice);
bool ChoiceInput (string choice);
bool CheckBust(int Sum);
int SumOfCards (int (&PlayersCards)[20],int &counter);
void HIT (int (&PlayersCards)[20], int &counter);
bool CheckBlackJack (int (&PlayerCards)[20], int &counter);
void ShowDealersCards(int (&DealersCards)[20],int &counter);
void FindWinner (int PlayersCards, int DealersCards, float &moneyCurrent, float &BettingAmount, int &chipTypeI, bool &HandOver);
int main() {
    string ime, chipTypeS, choice;
    float ChipsBuyIn, ChipsNumber, moneyCurrent = 0.0, BettingAmount=0.0;
    int chipTypeI, DealersCards[20], PlayersCards[20],PlayersCards2[20], counterP = 2,counterD=2,SplitAmount=0;
    char BettingChoice;
    bool DontAsk = false,HasSplit = false,GameOver=false;
    cout << "Please enter your name: ";
    cin >> ime;
    cout << "Hello, " << ime << ". Welcome to the C++ Casino.\n";
    cout << "This casino is new so the only game that is currently available is Blackjack.\n";
    cout << "There are 25,50 and 100$ chips. What type of chips would you like to buy? (25,50,100)\n";
    do {
        bool IsNumber = true;
        cin >> chipTypeS;
        for (int i = 0; i < chipTypeS.size(); i++) {
            if (isdigit(chipTypeS[i])) continue;
            else {
                IsNumber = false;
                break;
            }
        }
        if (IsNumber) {
            chipTypeI = stoi(chipTypeS);
            if (chipTypeI != 25 && chipTypeI != 50 && chipTypeI != 100 && chipTypeI > 0)
                cout << "Oops. We don't have " << chipTypeI << "$ chips yet. Please enter a valid value (25,50,100)\n";
            if (chipTypeI != 25 && chipTypeI != 50 && chipTypeI != 100 && chipTypeI < 0)
                cout << "Oops. Please enter a positive integer. (25,50,100)\n";
        } else cout << "Please enter a positive integer. (25,50,100)\n";
    } while (chipTypeS != "25" && chipTypeS != "50" && chipTypeS != "100");
    const int chips = chipTypeI;
    bool LotOfChips = false;
    do {
        cout << "How many chips would you like to buy?\n";
        char answer;
        cin >> ChipsNumber;
        if (ChipsNumber*chipTypeI>1000000){
            cout<<"The maximum amount of money allowed is 1.000.000$\n";
            cout<<"That is "<<1000000/chipTypeI<<" "<<chipTypeI<<"$ chips.";
        }
        else if (ChipsNumber<1) {
            cout<<"You need to buy at least one chip!\n";
        }
        else {
            cout << "That's great. Good luck!\n\n";
            LotOfChips = true;
        }
    } while (!LotOfChips);
    moneyCurrent += chipTypeI * ChipsNumber;
    PrintGameRules();
    do {
        cin >> choice;
        for (int i = 0; i < choice.size(); i++)
            choice[i] = toupper(choice[i]);
        if (choice != "START" && choice != "S") cout << "Type START or click S to begin!\n";
    } while (choice != "START" && choice != "S"); // pocnuva igrata
    if (moneyCurrent>chipTypeI){
        do {
            cout << "How many chips would you like to wager? (type 0 to end game)\n";
            cin >> ChipsBuyIn;
            if ((ChipsBuyIn-int (ChipsBuyIn))!=0) cout<<"Invalid chip amount!\n";
            if (ChipsBuyIn > moneyCurrent / chipTypeI) cout << "You don't have enough chips!\n";
            else if (ChipsBuyIn < 0) cout << "You can't buy a negative number of chips!\n";
        } while (ChipsBuyIn > moneyCurrent / chipTypeI || ChipsBuyIn < 0 || (ChipsBuyIn-int (ChipsBuyIn)!=0));
    }
    do {
        bool CanSplit = false;
        counterD = 2;
        bool HandOver = false;
        DontAsk = false;
        if (chipTypeI > moneyCurrent) {
            cout << "YOU DON'T HAVE ANY CHIPS LEFT!\n";
            GameOver = true;
            break;
        }
        if (!HasSplit) {
            for (int i = 0; i < 20; i++) {
                PlayersCards[i] = 0;
                PlayersCards2[i] = 0;
            }
        }


        for (int i = 0; i < 20; i++) DealersCards[i]=0;
        if (ChipsBuyIn==0) {
            GameOver=true;
            break;
        }
        if (!HasSplit) {
            BettingAmount = ChipsBuyIn * chipTypeI;
            cout << "Current Balance: " << moneyCurrent << "$ (" << moneyCurrent / chipTypeI << " chips)\n";
        }
        DealersCards[0] = CardPicked(time(0));
        DealersCards[1] = CardPicked(time(0)+25);
        PlayersCards[0] = CardPicked(time(0)-25);
        PlayersCards[1] = CardPicked(time(0)+30);

        if (HasSplit){
            for (int i=0;i<10; i++){
                PlayersCards[i]=0;
            }
            PlayersCards[0]=PlayersCards2[0];
            PlayersCards[1]=0;
            counterP--;
            HIT(PlayersCards, counterP);
            SplitAmount=0;
        }
        HasSplit = false;
        if (PlayersCards[0]==PlayersCards[1] && moneyCurrent >= BettingAmount * 2){
            PlayersCards2[0]=PlayersCards[0];
            CanSplit = true;
        }
        for (int i = 0; i < counterD + 1; i++) {
            SumOfCards(DealersCards, counterD);
        }
        cout << "Dealer's Deck: " << PrintCard(DealersCards[0]) << ", ?\n";
        cout << "Your deck: " << PrintCard(PlayersCards[0]) << ", " << PrintCard(PlayersCards[1]) << "\t\t\t" << "Bet: "
             << BettingAmount << "$\n";
        bool input = ChoiceInput(" ");
        bool BlackJack = false;
        do { // pocnuva rakata
            int SumOfCardsP = 0;
            int SumOfCardsD = 0;
            bool CanQuit = true;

            if (CheckBlackJack(PlayersCards, counterP)) {
                ShowDealersCards(DealersCards, counterD);
                if (SumOfCards(DealersCards, counterD) < 21) {
                    cout << "BLACKJACK!\nYOU WIN!\n\n";
                    moneyCurrent += 1.5 * BettingAmount;
                    cout << "Current Balance: " << moneyCurrent << "$/"<<moneyCurrent/chipTypeI<<" chips\n";
                    HandOver=true;
                    break;
                } else {
                    cout << "IT'S A TIE!\n\n";
                    HandOver = true;
                    break;
                }
            }
            do {
                if (counterP>2){
                    cout<<"HIT, STAND\n";
                }
                else {
                    if (!CanSplit) {
                        if (moneyCurrent < BettingAmount * 2) cout << "HIT, STAND, QUIT\n";
                        else cout << "HIT, STAND, DOUBLE, QUIT\n";
                    }
                    if (CanSplit){
                        if (moneyCurrent < BettingAmount * 2) cout << "HIT, STAND, SPLIT, QUIT\n";
                        else cout<<"HIT, STAND, DOUBLE, SPLIT, QUIT\n";
                    }
                }
                cin >> choice;
                if (ChoiceInput(choice)) {
                    input = true;
                    BettingChoice = BetChoice(choice);
                }
            } while (!input);//dobivam bukva betting choice
            if (BettingChoice == 'l' && CanSplit){
                PlayersCards[1]=0;
                counterP--;
                HIT(PlayersCards,counterP);
                cout << "Your deck: " << PrintCard(PlayersCards[0]) << ", " << PrintCard(PlayersCards[1])<<"\n";
                SplitAmount=BettingAmount;
                HasSplit=true;
                DontAsk = true;
                CanQuit = false;
            }
            if (BettingChoice == 'q' && CanQuit) {
                ShowDealersCards(DealersCards, counterD);
                moneyCurrent -= BettingAmount / 2;
                cout << "YOU SURRENDERED YOUR HAND!\n";
                cout << "Current Balance: " << moneyCurrent << "$ ("<<moneyCurrent/chipTypeI<<" chips)\n";
                HandOver=true;
                continue;
            }
            if (BettingChoice == 'd' && counterP != 2) {
                cout << "You can only double on the first hand!\n";
                continue;
            } else if (BettingChoice == 'd' && moneyCurrent < BettingAmount * 2) {
                cout << "You don't have enough money!\n";
                continue;
            }
            else if (BettingChoice == 'd' && counterP == 2 && moneyCurrent >= BettingChoice * 2) {
                CanQuit = false;
                HIT(PlayersCards, counterP);
                cout<<"Your deck: ";
                for (int i = 0; i < counterP; i++) {
                    SumOfCards(PlayersCards, counterP);
                    cout << PrintCard(PlayersCards[i]);
                    if (i < counterP - 1) cout << ", ";
                }
                cout << "\n";
                if (CheckBust(SumOfCards(PlayersCards, counterP))) {
                    cout << "YOU LOST!\n\n";
                    ShowDealersCards(DealersCards, counterD);
                    moneyCurrent -= 2 * BettingAmount;
                    break;
                } else {
                    if ((SumOfCards(DealersCards, counterD)) < 17) {
                        do {
                            HIT(DealersCards, counterD);
                            SumOfCards(DealersCards, counterD);
                        } while (SumOfCards(DealersCards, counterD) < 17);
                    } else counterD = 2;
                    ShowDealersCards(DealersCards, counterD);
                    SumOfCardsP=SumOfCards(PlayersCards,counterP);
                    SumOfCardsD=SumOfCards(DealersCards,counterD);
                    FindWinner(SumOfCardsP, SumOfCardsD, moneyCurrent, BettingAmount, chipTypeI, HandOver);
                    break;
                }
            }
            if (BettingChoice == 'h') {
                CanQuit = false;
                CanSplit = false;
                HIT(PlayersCards, counterP);
                cout << "Your deck: ";
                for (int i = 0; i < counterP; i++) {
                    cout << PrintCard(PlayersCards[i]);
                    if (i < counterP - 1) cout << ", ";
                }
                cout << "\n";
                if (SumOfCards(PlayersCards, counterP) == 21) {
                    if ((SumOfCards(DealersCards, counterD)) < 17) {
                        do {
                            HIT(DealersCards, counterD);
                            SumOfCards(DealersCards, counterD);
                        } while (SumOfCards(DealersCards, counterD) < 17);
                    } else counterD = 2;
                    ShowDealersCards(DealersCards, counterD);
                    SumOfCardsP= SumOfCards(PlayersCards,counterP);
                    SumOfCardsD= SumOfCards(DealersCards,counterD);
                    FindWinner(SumOfCardsP, SumOfCardsD, moneyCurrent, BettingAmount, chipTypeI, HandOver);
                    break;
                }
                if (CheckBust(SumOfCards(PlayersCards, counterP))) {
                    cout << "YOU LOST!\n\n";
                    ShowDealersCards(DealersCards, counterD);
                    moneyCurrent -= BettingAmount;
                    cout << "Current Balance: " << moneyCurrent << "$ ("<<moneyCurrent/chipTypeI<<" chips)\n";
                    HandOver = true;
                    break;
                }
            }
            if (BettingChoice == 's') {
                if ((SumOfCards(DealersCards, counterD)) < 17) {
                    do {
                        HIT(DealersCards, counterD);
                        SumOfCards(DealersCards, counterD);
                    } while (SumOfCards(DealersCards, counterD) < 17);
                } else counterD = 2;
                ShowDealersCards(DealersCards, counterD);
                SumOfCardsP = SumOfCards(PlayersCards,counterP);
                SumOfCardsD = SumOfCards(DealersCards, counterD);
                FindWinner(SumOfCardsP, SumOfCardsD, moneyCurrent, BettingAmount, chipTypeI, HandOver);
                break;
            }
        } while (!HandOver);
        counterP = 2;
        if (!HasSplit && moneyCurrent>chipTypeI) {
            do {
                cout << "How many chips would you like to wager? (type 0 to end game)\n";
                cin >> ChipsBuyIn;
                if (ChipsBuyIn > moneyCurrent / chipTypeI) cout << "You don't have enough chips!\n";
                else if (ChipsBuyIn < 0) cout << "You can't buy a negative number of chips!\n";
            } while (ChipsBuyIn > moneyCurrent / chipTypeI || ChipsBuyIn < 0);
        }
    }while(!GameOver);
    cout<<"\nThanks for playing!\n";
}

void PrintGameRules(){
    cout<<"RULES OF THE GAME\nThe computer hits until 17, after it stands.\n";
    cout<<"You have 5 options (To choose each option write down the word or the first letter of the option that you want to choose)(sp for split):\n";
    cout<<"1. HIT (Take a card)\n2. STAND (Don't take a card and end your turn)\n";
    cout<<"3. DOUBLE (Double your wager, take a single card and end your turn.)\n";
    cout<<"4. SPLIT (If the two cards have the same value, separate them to make two hands, each with the original wager)\n";
    cout<<"5. QUIT (Give up half of your wager and pull back from the game)\n";
    cout<<"You may type R at any time to see the rules of the game again.\n";
    cout<<"Type START or click 'S' to begin the game\n";
}
int CardPicked(int x){
    srand(x);
    int a = rand() % 13 + 1;
    if (a==11 || a==12 || a==13) a++;
    return a;
}
string PrintCard(int card) {
    if (card == 1) return "A";
    else if (card <= 10) return to_string(card);
    else if (card == 12) return "J";
    else if (card == 13) return "Q";
    else return "K";
}
char BetChoice (string choice){
    for (int i=0;i < choice.size(); i++) {
        choice[i]= tolower(choice[i]);
    }
    if (choice=="hit" || choice=="h") return 'h';
    else if (choice=="stand" || choice=="s") return 's';
    else if (choice=="split" || choice=="sp") return 'l';
    else if (choice=="double" || choice=="d") return 'd';
    else if (choice=="quit" || choice=="q") return 'q';
    else return 'P';
}
bool ChoiceInput (string choice){
    for (int i=0;i< choice.length();i++) {
        choice[i]= tolower(choice[i]);
    }
    if (choice == "hit" || choice == "h" || choice == "stand" || choice == "s" || choice == "split" ||
        choice == "sp" || choice == "double" || choice == "d" || choice == "quit" || choice == "q")
        return true;
    else return false;
}
void HIT (int (&PlayersCards)[20], int &counter){ //treba da stavam karti na igrac vo niza
    for (int i=0; i<(counter+1); i++) {
        if (PlayersCards[i]==0) {
            PlayersCards[i] = CardPicked(time(0) * 10 * counter);
            counter++;
            break;
        }
    }
}
void ShowDealersCards(int (&DealersCards)[20],int &counter){
    cout<<"Dealer's deck: ";
    for (int i=0; i<counter; i++) {
        if (DealersCards[i] != 0) cout << PrintCard(DealersCards[i]);
        if (i < counter - 1) cout << ", ";
    }
    cout<<"\n";
}
bool CheckBust(int Sum){
    if (Sum>21) return true;
    else return false;
}
int SumOfCards (int (&PlayersCards)[20],int &counter){
    int sum=0;
    bool hasAce=false;
    for (int i=0;i<counter;i++)
    {
        if (PlayersCards[i]==1 && hasAce){
            sum+=1;
        }
        else if (PlayersCards[i]==1 && !hasAce) {
            sum+=11;
            hasAce=true;
        }
        else if (PlayersCards[i]>=10) sum+=10;
        else sum+=PlayersCards[i];
    }
    if (sum>21 && hasAce) sum-=10;
    return sum;
}
bool CheckBlackJack (int (&PlayerCards)[20], int &counter) {
    bool HasTen = false;
    bool HasAce = false;
    if (counter > 2) return false;
    else {
        for (int i = 0; i < counter; i++) {
            if (PlayerCards[i]==1) HasAce = true;
            else if (PlayerCards[i]>=10) HasTen = true;
        }
    }
    if (HasAce && HasTen) return true;
    else return false;
}
void FindWinner (int PlayersCards, int DealersCards, float &moneyCurrent, float &BettingAmount, int &chipTypeI, bool &HandOver ){
    if (PlayersCards > DealersCards ||
        DealersCards > 21) {
        cout << "YOU WIN!\n\n";
        moneyCurrent += BettingAmount;
        cout << "Current Balance: " << moneyCurrent << "$ ("<<moneyCurrent/chipTypeI<<" chips)\n";
        HandOver = true;
    } else if (PlayersCards == DealersCards) {
        cout << "IT'S A TIE!\n\n";
        cout << "Current Balance: " << moneyCurrent << "$ ("<<moneyCurrent/chipTypeI<<" chips)\n";
        HandOver = true;
    } else {
        cout << "YOU LOST!\n\n";
        moneyCurrent -= BettingAmount;
        cout << "Current Balance: " << moneyCurrent << "$ ("<<moneyCurrent/chipTypeI<<" chips)\n";
        HandOver = true;
    }
}