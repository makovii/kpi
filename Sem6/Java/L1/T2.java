import java.util.Scanner;

public class T2 extends Thread {
  private int[][] MC2 = new int[Data.N][Data.N];
  private int[][] MD2 = new int[Data.N][Data.N];
  private int[] R2 = new int[Data.N];
  private int[] E2 = new int[Data.N];
  private int d2 = 0;

  public void enterDefault() {
    System.out.println("Enter MD");
    for (int i = 0; i < Data.N; i++) {
      for (int j = 0; j < Data.N; j++) {
        Data.MD[i][j] = 1;
      }
    }
  }
  
  public void enterData() {
    Scanner console = new Scanner(System.in);

    System.out.printf("Enter matrix MD (%d by %d): ", Data.N, Data.N);
    for (int i = 0; i < Data.N; i++) {
        System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
        for (int j = 0; j < Data.N; j++) {
            Data.MD[i][j] = console.nextInt();
        }
    }
  }


  public void run() {
    System.out.println("Start T2");



    System.out.println("T2 release Sem6");
    Data.Sem6.release(1);
    System.out.println("T2 release Sem7");
    Data.Sem7.release(1);
    System.out.println("T2 release Sem8");
    Data.Sem8.release(1);

    System.out.println("T2 waiting for Sem1,Sem12,Sem18 - calculation 1,2,3");
    try {
      Data.Sem1.acquire();
      Data.Sem12.acquire();
      Data.Sem18.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T2 got permission Sem1,Sem12,Sem18");

    synchronized (Data.object) {
      System.arraycopy(Data.R, 0, R2, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MC[i], 0, MC2[i], 0, Data.N);
      }
    }

    // A2 = R*MC2
    int[] A2 = Data.multipleVectorAndSubMatrix(R2, MC2, Data.Part * 1, Data.Part * 2);
    Data.insertPartVector(A2, Data.A, Data.Part * 1, Data.Part * 2);

    // a2 = (B2*Z2)
    int a2 = Data.multipleSubVectorAndSubVector(Data.B, Data.Z, Data.Part * 1, Data.Part * 2);
    Data.a.getAndAdd(a2);


    System.out.println("T2 release Sem9 - end calculating-3");
    Data.Sem9.release(1);

    System.out.println("T2 waiting for Sem15 - calculation-4");
    try {
      Data.Sem15.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T2 got permission for Sem15 - calculation-4");


    synchronized (Data.object) {
      System.arraycopy(Data.A, 0, A2, 0, Data.N);
      d2 = Data.d;
      System.arraycopy(Data.E, 0, E2, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MD[i], 0, MD2[i], 0, Data.N);
      }
    }
    a2 = Data.a.get();

    // X2 = А2*MDh + а2*Eh*d2
    int [] X2 = Data.sumVectorAndVector(
      Data.multipleVectorAndSubMatrix(A2, MD2, Data.Part * 1, Data.Part * 2),
      Data.multipleSubVectorAndTwoScalar(E2, a2, d2, Data.Part * 1, Data.Part * 2)
    );

    Data.insertPartVector(X2, Data.X, Data.Part * 1, Data.Part * 2);

    System.out.println("T2 release Sem10 - end calculating-4");
    Data.Sem10.release(1);
  }
}
