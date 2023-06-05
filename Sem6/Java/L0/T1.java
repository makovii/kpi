import java.util.Scanner;

public class T1 extends Thread {

    int A[] = new int[Data.N];
    int B[] = new int[Data.N];
    int C[] = new int[Data.N];
    int MA[][] = new int[Data.N][Data.N];
    int ME[][] = new int[Data.N][Data.N];

    int d;

    public void enterData() {
        Scanner console = new Scanner(System.in);

        System.out.printf("F1: Enter vector A (%d integers): ", Data.N);
        for (int i = 0; i < Data.N; i++) {
            A[i] = console.nextInt();
        }

        
        System.out.printf("F1: Enter vector B (%d integers): ", Data.N);
        for (int i = 0; i < Data.N; i++) {
            B[i] = console.nextInt();
        }
        System.out.printf("F1: Enter vector C (%d integers): ", Data.N);
        for (int i = 0; i < Data.N; i++) {
            C[i] = console.nextInt();
        }

        System.out.printf("F1: Enter matrix MA (%d by %d): ", Data.N, Data.N);
        for (int i = 0; i < Data.N; i++) {
            System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
            for (int j = 0; j < Data.N; j++) {
                MA[i][j] = console.nextInt();
            }
        }

        System.out.printf("\nF1: Enter matrix ME (%d by %d): ", Data.N, Data.N);
        for (int i = 0; i < Data.N; i++) {
            System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
            for (int j = 0; j < Data.N; j++) {
                ME[i][j] = console.nextInt();
            }
        }
    }

    public void run() {
        System.out.println("\nT1 started");

            if (Data.way == 1) {
                Data.writeVectorToFile("data1.txt", "A");
                Data.writeVectorToFile("data1.txt", "B");
                Data.writeVectorToFile("data1.txt", "C");
                Data.writeMatrixToFile("data1.txt", "MA");
                Data.writeMatrixToFile("data1.txt", "ME");

                A = Data.readVectorFromFile("data1.txt", "A");
                B = Data.readVectorFromFile("data1.txt", "B");
                C = Data.readVectorFromFile("data1.txt", "C");
                MA = Data.readMatrixFromFile("data1.txt", "MA");
                ME = Data.readMatrixFromFile("data1.txt", "ME");
            }           
            if (Data.way == 2) {
                A = Data.insertVector(1);
                B = Data.insertVector(1);
                C = Data.insertVector(1);
                MA = Data.insertMatrix(1);
                ME = Data.insertMatrix(1);
            }
            if (Data.way == 3) {
                A = Data.generateRandVec();
                B = Data.generateRandVec();
                C = Data.generateRandVec();
                MA = Data.generateRandMatrix();
                ME = Data.generateRandMatrix();
            }

        // calculate F1: d = MAX((A + B + C) *(MA*ME))
        d = Data.F1(A, B, C, MA, ME);

        
        System.out.printf("\nT1 finished. Scalar:");
        System.out.printf("%d  ", d);
    }
}