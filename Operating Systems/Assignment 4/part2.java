import java.util.Arrays;
import java.util.Random;

public class MultithreadSort extends Thread{
    public static void main(String[] args) throws InterruptedException {

        // Checks the number of arguments when running the java program
        if (args.length < 1) {
            System.out.println("Usage: java MultithreadSort <size of Array>");
            return;
        }
        int n = Integer.parseInt(args[0]);
        double[] arr = generateArray(n);

        // Sorting using 2 threads
        double[] firstArray = Arrays.copyOfRange(arr, 0, n/2);
        double[] secondArray = Arrays.copyOfRange(arr, n/2, n);

        double startTime = System.currentTimeMillis();

        Thread t1 = new Thread(() -> {selectSort(firstArray);});
        Thread t2 = new Thread(() -> {selectSort(secondArray);});

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        double[] result = mergeArrays(firstArray, secondArray);
        double endTime = System.currentTimeMillis();
        double elapsed = endTime - startTime;
        System.out.printf("Sorting is done in %.1fms when two threads are used\n", elapsed);

        // Sort using one thread
        startTime = System.currentTimeMillis();
        selectSort(arr);
        endTime = System.currentTimeMillis();
        elapsed = endTime - startTime;
        System.out.printf("Sorting is done in %.1fms when one thread is used\n", elapsed);
    }

    // Generates a random array of doubles between 1.0 and 1000.0
    public static double[] generateArray(int n) {
        double[] arr = new double[n];
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            arr[i] = random.nextDouble() * 1000.0;
        }
        return arr;
    }

    // performs the selection sort for the threads
    public static void selectSort(double[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            double temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }

    // Method for merging the two subarrays into a single array
    public static double[] mergeArrays(double[] firstArray, double[] secondArray) {
        double[] result = new double[firstArray.length + secondArray.length];
        int i = 0, j = 0, k = 0;
        while (i < firstArray.length && j < secondArray.length) {
            if (firstArray[i] < secondArray[j]) {
                result[k++] = firstArray[i++];
            } else {
                result[k++] = secondArray[j++];
            }
        }

        while (i < firstArray.length) {
            result[k++] = firstArray[i++];
        }

        while (j < secondArray.length) {
            result[k++] = secondArray[j++];
        }

        return result;
    }
}