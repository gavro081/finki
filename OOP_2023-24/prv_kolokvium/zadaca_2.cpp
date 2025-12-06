#include <iostream>
#include <cstring>




using namespace std;




class List{
   int *nums;
   int N;
public:
   List(){}
   List(int *nums, int N) : N(N){
       this->nums = new int[N];
       for (int i = 0; i < N; ++i) {
           this->nums[i] = nums[i];
       }
   }




   ~List(){
       delete[] nums;
   }




   List (const List& ob) {
       this->N = ob.N;
       this->nums = new int[ob.N];
       for (int i = 0; i < N; ++i) {
           this->nums[i] = ob.nums[i];
       }
   }




   List& operator=(const List& ob){
       this->N = ob.N;
       this->nums = new int[ob.N];
       for (int i = 0; i < N; ++i) {
           this->nums[i] = ob.nums[i];
       }
       return *this;
   }




   int sum(){
       int sum = 0;
       for (int i = 0; i < N; ++i) {
           sum += nums[i];
       }
       return sum;
   }




   double average(){
       return (double)sum() / N;
   }




   void pecati() {
       cout << N << ": ";
       for (int i = 0; i < N; ++i) {
           cout << nums[i] << ' ';
       }
       cout << "sum: " << sum() << " average: " << average() << '\n';
   }




   int getN(){return N;}
};




class ListContainer{
   List *lists;
   int N;
   int tries;
public:
   ListContainer(){N = 0; tries = 0; lists= nullptr;}




   ListContainer(List *lists, int N, int tries) : N(N), tries(tries){
       this->lists = new List[N];
       this->lists = lists;
   }




   ~ListContainer(){
       delete [] lists;
   }




   ListContainer (const ListContainer& ob) {
       this->N = ob.N;
       this->lists = new List[ob.N];
       this->lists = ob.lists;
       this->tries = ob.tries;
   }




   ListContainer& operator=(const ListContainer& ob){
       this->N = ob.N;
       this->lists = new List[ob.N];
       for (int i = 0; i < N; i++){
           this->lists[i] = ob.lists[i];
       }
       this->tries = ob.tries;
       return *this;
   }




   int sum(){
       int sum = 0;
       for (int i = 0; i < N; ++i) {
           sum += lists[i].sum();
       }
       return sum;
   }




   double average(){
       int vkN = 0;
       for (int i = 0; i < N; ++i) {
           vkN += lists[i].getN();
       }
       return (double)sum() / vkN;
   }








   void print(){
       if (N==0) {
           cout << "The list is empty\n";
           return;
       }
       for (int i = 0; i < N; ++i) {
           cout << "List number: " << i+1 << " List info: ";
           lists[i].pecati();




       }
       cout << "Sum: " << sum() << " Average: " << average() << '\n';
       cout << "Successful attempts: "<< N << " Failed attempts: "
            << tries - N << '\n';
   }




   void addNewList(List l){
       for (int i = 0; i < N; ++i) {
           if (l.sum() == lists[i].sum()) {
               tries++;
               return;
           }
       }




       List *temp = new List[N+1];
       for (int i = 0; i < N; ++i) {
           temp[i] = lists[i];
       }
       temp[N] = l;
       delete [] lists;
       lists = new List[N+1];
       tries++;N++;
       lists = temp;
   }




};


int main() {




   ListContainer lc;
   int N;
   cin>>N;




   for (int i=0;i<N;i++) {
       int n;
       int niza[100];




       cin>>n;




       for (int j=0;j<n;j++){
           cin>>niza[j];




       }




       List l=List(niza,n);




       lc.addNewList(l);
   }








   int testCase;
   cin>>testCase;




   if (testCase==1) {
       cout<<"Test case for operator ="<<endl;
       ListContainer lc1;
       lc1.print();
       cout<<lc1.sum()<<" "<<lc.sum()<<endl;
       lc1=lc;
       lc1.print();
       cout<<lc1.sum()<<" "<<lc.sum()<<endl;
       lc1.sum();
       lc1.average();




   }
   else {
       lc.print();
   }
}

