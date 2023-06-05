import java.util.Scanner;

public class T2 extends Thread {
    int MF[][] = new int[Data.N][Data.N];
    int MG[][] = new int[Data.N][Data.N];
    int ML[][] = new int[Data.N][Data.N];

    public void enterData () {
        Scanner console = new Scanner(System.in);

        System.out.printf("F2: Enter matrix MF (%d by %d): ", Data.N, Data.N);
        for (int i = 0; i < Data.N; i++) {
            System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
            for (int j = 0; j < Data.N; j++) {
                MF[i][j] = console.nextInt();
            }
        }

        System.out.printf("F2: Enter matrix MG (%d by %d): ", Data.N, Data.N);
        for (int i = 0; i < Data.N; i++) {
            System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
            for (int j = 0; j < Data.N; j++) {
                MG[i][j] = console.nextInt();
            }
        }
    }

    synchronized public void run() {
        System.out.println("\nT2 started");
        
        if (Data.way == 1) {
            Data.writeMatrixToFile("data2.txt", "MF");
            Data.writeMatrixToFile("data2.txt", "MG");
            MF = Data.readMatrixFromFile("data2.txt", "MF");
            MG = Data.readMatrixFromFile("data2.txt", "MG");
        }            
        if (Data.way == 2) {
            MF = Data.insertMatrix(2);
            MG = Data.insertMatrix(2);
        }
        if (Data.way == 3) {
            MF = Data.generateRandMatrix();
            MG = Data.generateRandMatrix();
        }

        //  calculate F2: ML = SORT(MF*MG)
        ML = Data.F2(MF, MG);

        System.out.println("T2 finished. Resulting Matrix:\n");
        for (int i = 0; i < Data.N; i++) {
            for (int j = 0; j < Data.N; j++)
                System.out.print(ML[i][j] + " ");
            System.out.println();
        }
    }
}