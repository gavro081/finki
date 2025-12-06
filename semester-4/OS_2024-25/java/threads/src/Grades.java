import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;


public class Grades {

    static double average = 0;
    static long total_sum = 0;
    // DEFINE OTHER GLOBAL VARIABLES
    static final BoundedRandomGenerator random = new BoundedRandomGenerator();

    private static final int ARRAY_LENGTH = 10000000;

    private static final int NUM_THREADS = 10;

    static Semaphore done = new Semaphore(0);

    static ReentrantLock sum_lock = new ReentrantLock();

    // TODO: Define sychronization elements

    static void init() {
        // TODO: Initialize synchronization elements
    }

    // DO NOT CHANGE
    public static int[] getSubArray(int[] array, int start, int end) {
        return Arrays.copyOfRange(array, start, end);
    }

    public static void main(String[] args) throws InterruptedException {

        init();

        int[] arr = ArrayGenerator.generate(ARRAY_LENGTH);

        // TODO: Make the CalculateThread class a thread and start 10 instances
        // Each instance should take a subarray from the original array with equal length
        int step = ARRAY_LENGTH / NUM_THREADS;
        List<CalculateThread> threads = new ArrayList<>(NUM_THREADS);
        int begin = 0;
        for (int i = 0; i < NUM_THREADS; i++) {
            threads.add(new CalculateThread(arr, begin, begin + step));
            begin = begin + step;
        }

        // TODO: Create and start 10 threads for calculating the average grade
        for (CalculateThread t : threads){
            t.start();
        }
        // Replace the call to calculateAverageGrade below with calculateAverageGradeParallel
//        average = calculateThread.calculateAverageGrade();

        done.acquire(NUM_THREADS);
        // TODO: Update the value of the global variable average

        average = (double) total_sum / ARRAY_LENGTH;

        // DO NOT CHANGE

        System.out.println("Your calculated average grade is: " + average);
        System.out.println("The actual average grade is: " + ArrayGenerator.actualAvg);

        SynchronizationChecker.checkResult();

    }


    // TO DO: Make the CalculateThread class a thread, you can add methods and attributes
    static class CalculateThread extends Thread{

        private int[] arr;
        int startSearch;
        int endSearch;

        public CalculateThread(int[] arr, int startSearch, int endSearch) {
            this.arr = arr;
            this.startSearch=startSearch;
            this.endSearch=endSearch;
        }

        public Double calculateAverageGrade() {
            return Arrays.stream(arr).average().getAsDouble();
        }

        public void run(){
            try{
                calculateAverageGradeParallel();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }

        public void calculateAverageGradeParallel() throws InterruptedException{
            // TO DO: Implement and run this method from the thread
            // The method should not return a result
            // Take care of the proper synchronization
            long local_sum = 0;
            for (int i = startSearch; i < endSearch; i++) {
                local_sum += arr[i];
            }
            sum_lock.lock();
            total_sum += local_sum;
            sum_lock.unlock();
            done.release();
        }
    }

    /******************************************************
     // DO NOT CHANGE THE CODE BELOW TO THE END OF THE FILE
     *******************************************************/

    static class BoundedRandomGenerator {
        static final Random random = new Random();
        static final int RANDOM_BOUND_UPPER = 10;
        static final int RANDOM_BOUND_LOWER = 6;

        public int nextInt() {
            return random.nextInt(RANDOM_BOUND_UPPER - RANDOM_BOUND_LOWER) + RANDOM_BOUND_LOWER;
        }

    }

    static class ArrayGenerator {

        private static double actualAvg = 0;

        static int[] generate(int length) {
            int[] array = new int[length];

            for (int i = 0; i < length; i++) {
                int grade = Grades.random.nextInt();
                actualAvg += grade;
                array[i] = grade;
            }

            actualAvg /= array.length;

            return array;
        }
    }

    static class SynchronizationChecker {
        public static void checkResult() {
            if (ArrayGenerator.actualAvg != average) {
                throw new RuntimeException("The calculated result is not equal to the actual average grade!");
            }
        }
    }
}