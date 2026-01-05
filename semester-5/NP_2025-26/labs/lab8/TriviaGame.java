package labs.lab8;

import java.util.ArrayList;
import java.util.Scanner;

enum QUESTION_TYPE {
    TRUEFALSE,
    FREEFORM
}

class TriviaQuestionFactory {
    TriviaQuestion create(String question, String answer, int pointValue, QUESTION_TYPE type){
        switch (type) {
            case TRUEFALSE: return new TrueFalseTriviaQuestion(question, answer, pointValue);
            case FREEFORM: return new FreeFormTriviaQuestion(question, answer, pointValue);
            default: throw new IllegalArgumentException("Invalid question type:" + type);
        }
    }
}

abstract class TriviaQuestion {
    public final String question;
    public final String answer;
    public final int pointValue;
    public final QUESTION_TYPE type;

    public TriviaQuestion(String question, String answer, int pointValue, QUESTION_TYPE type) {
        this.question = question;
        this.answer = answer;
        this.pointValue = pointValue;
        this.type = type;
    }

    abstract void show();
}

class FreeFormTriviaQuestion extends TriviaQuestion {
    public FreeFormTriviaQuestion(String question, String answer, int pointValue) {
        super(question, answer, pointValue, QUESTION_TYPE.FREEFORM);
    }

    @Override
    void show() {
        System.out.println(this.question);
    }
}

class TrueFalseTriviaQuestion extends TriviaQuestion {
    public TrueFalseTriviaQuestion(String question, String answer, int pointValue) {
        super(question, answer, pointValue, QUESTION_TYPE.TRUEFALSE);
    }

    @Override
    void show() {
        System.out.println(this.question);
        System.out.println("Enter 'T' for true or 'F' for false.");
    }
}


class TriviaData {
    private final ArrayList<TriviaQuestion> questions;
    private final TriviaQuestionFactory factory = new TriviaQuestionFactory();

    public TriviaData() {
        questions = new ArrayList<>();
    }

    public void addQuestion(String question, String answer, int pointValue, QUESTION_TYPE type) {
        TriviaQuestion newQuestion = factory.create(question, answer, pointValue, type);
        questions.add(newQuestion);
    }

    public void showQuestion(int index) {
        TriviaQuestion q = questions.get(index);
        System.out.println("Question " + (index + 1) + ".  " + q.pointValue + " points.");
        q.show();
    }

    public int numQuestions() {
        return questions.size();
    }

    public TriviaQuestion getQuestion(int index) {
        return questions.get(index);
    }
}

public class TriviaGame {

    public TriviaData questions;	// Questions

    public TriviaGame() {
        // Load questions
        questions = new TriviaData();
        questions.addQuestion("The possession of more than two sets of chromosomes is termed?",
                "polyploidy", 3, QUESTION_TYPE.FREEFORM);
        questions.addQuestion("Erling Kagge skiied into the north pole alone on January 7, 1993.",
                "F", 1, QUESTION_TYPE.TRUEFALSE);
        questions.addQuestion("1997 British band that produced 'Tub Thumper'",
                "Chumbawumba", 2, QUESTION_TYPE.FREEFORM);
        questions.addQuestion("I am the geometric figure most like a lost parrot",
                "polygon", 2, QUESTION_TYPE.FREEFORM);
        questions.addQuestion("Generics were introducted to Java starting at version 5.0.",
                "T", 1, QUESTION_TYPE.TRUEFALSE);
    }
    // Main game loop

    public static void main(String[] args) {
        int score = 0;			// Overall score
        int questionNum = 0;	// Which question we're asking
        TriviaGame game = new TriviaGame();
        Scanner keyboard = new Scanner(System.in);
        // Ask a question as long as we haven't asked them all
        while (questionNum < game.questions.numQuestions()) {
            // Show question
            game.questions.showQuestion(questionNum);
            // Get answer
            String answer = keyboard.nextLine();
            // Validate answer
            TriviaQuestion q = game.questions.getQuestion(questionNum);
            if (q.type == QUESTION_TYPE.TRUEFALSE) {
                if (answer.charAt(0) == q.answer.charAt(0)) {
                    System.out.println("That is correct!  You get " + q.pointValue + " points.");
                    score += q.pointValue;
                } else {
                    System.out.println("Wrong, the correct answer is " + q.answer);
                }
            } else if (q.type == QUESTION_TYPE.FREEFORM) {
                if (answer.toLowerCase().equals(q.answer.toLowerCase())) {
                    System.out.println("That is correct!  You get " + q.pointValue + " points.");
                    score += q.pointValue;
                } else {
                    System.out.println("Wrong, the correct answer is " + q.answer);
                }
            }
            System.out.println("Your score is " + score);
            questionNum++;
        }
        System.out.println("Game over!  Thanks for playing!");
    }
}

