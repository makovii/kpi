import java.util.Scanner;

public class T3 extends Thread {
    int S[] = new int[Data.N];
    int O[] = new int[Data.N];
    int P[] = new int[Data.N];
    int MR[][]=new int[Data.N][Data.N];
    int MT[][]=new int[Data.N][Data.N];

    public void enterData () {
        Scanner console = new Scanner(System.in);

        System.out.printf("F3: Enter vector O (%d integers): ", Data.N);
        for (int i = 0; i < Data.N; i++) {
            P[i] = console.nextInt();
        }

        System.out.printf("F3: Enter vector P (%d integers): ", Data.N);
        for (int i = 0; i < Data.N; i++) {
            P[i] = console.nextInt();
        }

        System.out.printf("F3: Enter matrix MR (%d by %d): ", Data.N, Data.N);
        for (int i = 0; i < Data.N; i++) {
            System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
            for (int j = 0; j < Data.N; j++) {
                MR[i][j] = console.nextInt();
            }
        }

        System.out.printf("F3: Enter matrix MT (%d by %d): ", Data.N, Data.N);
        for (int i = 0; i < Data.N; i++) {
            System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
            for (int j = 0; j < Data.N; j++) {
                MT[i][j] = console.nextInt();
            }
        }
    }

    synchronized public void run() {
        System.out.println("\nT3 started");

        if (Data.way == 1) {
            Data.writeVectorToFile("data3.txt", "O");
            Data.writeVectorToFile("data3.txt", "P");
            Data.writeMatrixToFile("data3.txt", "MR");
            Data.writeMatrixToFile("data3.txt", "MT");

            O = Data.readVectorFromFile("data3.txt", "O");
            P = Data.readVectorFromFile("data3.txt", "P");
            MR = Data.readMatrixFromFile("data3.txt", "MR");
            MT = Data.readMatrixFromFile("data3.txt", "MT");
        }            
        if (Data.way == 2) {
            O = Data.insertVector(3);
            P = Data.insertVector(3);
            MR = Data.insertMatrix(3);
            MT = Data.insertMatrix(3);
        }
        if (Data.way == 3) {
            O = Data.generateRandVec();
            P = Data.generateRandVec();
            MR = Data.generateRandMatrix();
            MT = Data.generateRandMatrix();
        }

        //  calculate F3: S = (O+P)*TRANS(MR * MT)
        S = Data.F3(O, P, MR, MT);

        System.out.printf("T3 finished. Vector: ");
        for (int i = 0; i < Data.N; ++i)
            System.out.printf("%d  ", S[i]);
    }
}