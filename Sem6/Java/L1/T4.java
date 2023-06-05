import java.util.Scanner;

public class T4 extends Thread {
  private int[][] MC4 = new int[Data.N][Data.N];
  private int[][] MD4 = new int[Data.N][Data.N];
  private int[] R4 = new int[Data.N];
  private int[] E4 = new int[Data.N];
  private int d4 = 0;

  public void enterDefault() {
    System.out.println("Enter MC");
    for (int i = 0; i < Data.N; i++) {
      for (int j = 0; j < Data.N; j++) {
        Data.MC[i][j] = 1;
      }
    }

    System.out.println("Enter E");
    for (int i = 0; i < Data.N; i++) {
      Data.E[i] = 1;
    }
  }

  public void enterData() {
    Scanner console = new Scanner(System.in);

    System.out.printf("Enter matrix MC (%d by %d): ", Data.N, Data.N);
    for (int i = 0; i < Data.N; i++) {
        System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
        for (int j = 0; j < Data.N; j++) {
            Data.MC[i][j] = console.nextInt();
        }
    }

    System.out.printf("Enter vector E (%d integers): ", Data.N);
    for (int i = 0; i < Data.N; i++) {
        Data.E[i] = console.nextInt();
    }
  }

  public void run() {
    System.out.println("Start T4");



    System.out.println("T4 release Sem17");
    Data.Sem17.release(1);
    System.out.println("T4 release Sem18");
    Data.Sem18.release(1);
    System.out.println("T4 release Sem19");
    Data.Sem19.release(1);


    System.out.println("T4 waiting for Sem3,Sem8,Sem13 - calculation 1,2,3");
    try {
      Data.Sem3.acquire();
      Data.Sem8.acquire();
      Data.Sem13.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T4 got permission Sem3,Sem8,Sem13");


    synchronized (Data.object) {
      System.arraycopy(Data.R, 0, R4, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MC[i], 0, MC4[i], 0, Data.N);
      }
    }
    // A4 = R*MC4
    int[] A4 = Data.multipleVectorAndSubMatrix(R4, MC4, Data.Part * 3, Data.Part * 4);
    Data.insertPartVector(A4, Data.A, Data.Part * 3, Data.Part * 4);

    // a4 = (B4*Z4)
    int a4 = Data.multipleSubVectorAndSubVector(Data.B, Data.Z, Data.Part * 3, Data.Part * 4);
    Data.a.getAndAdd(a4);


    System.out.println("T4 release Sem21 - end calculating-3");
    Data.Sem21.release(1);

    System.out.println("T4 waiting for Sem16 - calculation-4");
    try {
      Data.Sem16.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T4 got permission for Sem16 - calculation-4");


    synchronized (Data.object) {
      System.arraycopy(Data.A, 0, A4, 0, Data.N);
      d4 = Data.d;
      System.arraycopy(Data.E, 0, E4, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MD[i], 0, MD4[i], 0, Data.N);
      }
    }
    a4 = Data.a.get();

    // X4 = А4*MDh + а4*Eh*d4
    int [] X4 = Data.sumVectorAndVector(
      Data.multipleVectorAndSubMatrix(A4, MD4, Data.Part * 3, Data.Part * 4),
      Data.multipleSubVectorAndTwoScalar(E4, a4, d4, Data.Part * 3, Data.Part * 4)
    );

    Data.insertPartVector(X4, Data.X, Data.Part * 3, Data.Part * 4);

    System.out.println("T4 release Sem22 - end calculating-4");
    Data.Sem22.release(1);

  }
}
