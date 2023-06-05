import java.util.Scanner;

public class T1 extends Thread {
  private int[][] MC1 = new int[Data.N][Data.N];
  private int[][] MD1 = new int[Data.N][Data.N];
  private int[] R1 = new int[Data.N];
  private int[] E1 = new int[Data.N];
  private int d1 = 0;

  public void enterDefault() {
  System.out.println("Enter R");
    for (int i = 0; i < Data.N; i++) {
      Data.R[i] = 1;
    }

    System.out.println("Enter Z");
    for (int i = 0; i < Data.N; i++) {
      Data.Z[i] = 1;
    }
  }

  public void enterData() {
    Scanner console = new Scanner(System.in);

    System.out.printf("Enter vector R (%d integers): ", Data.N);
    for (int i = 0; i < Data.N; i++) {
        Data.R[i] = console.nextInt();
    }

    System.out.printf("Enter vector Z (%d integers): ", Data.N);
    for (int i = 0; i < Data.N; i++) {
        Data.Z[i] = console.nextInt();
    }
  }

  public void run() {
    System.out.println("Start T1");

    System.out.println("T1 release Sem1");
    Data.Sem1.release(1);
    System.out.println("T1 release Sem2");
    Data.Sem2.release(1);
    System.out.println("T1 release Sem3");
    Data.Sem3.release(1);

    System.out.println("T1 waiting for Sem6,Sem11,Sem17 - calculation 1,2,3");
    try {
      Data.Sem6.acquire();
      Data.Sem11.acquire();
      Data.Sem17.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T1 got permission Sem6,Sem11,Sem17");

    synchronized (Data.object) {
      System.arraycopy(Data.R, 0, R1, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MC[i], 0, MC1[i], 0, Data.N);
      }
    }

    // A1 = R*MC1
    int[] A1 = Data.multipleVectorAndSubMatrix(R1, MC1, 0, Data.Part * 1);
    Data.insertPartVector(A1, Data.A, 0, Data.Part * 1);

    // a1 = (B1*Z1)
    int a1 = Data.multipleSubVectorAndSubVector(Data.B, Data.Z, 0, Data.Part * 1);
    Data.a.getAndAdd(a1);


    System.out.println("T1 release Sem4 - end calculating-3");
    Data.Sem4.release(1);

    System.out.println("T1 waiting for Sem14 - calculation-4");
    try {
      Data.Sem14.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T1 got permission for Sem14 - calculation-4");


    synchronized (Data.object) {
      System.arraycopy(Data.A, 0, A1, 0, Data.N);
      d1 = Data.d;
      System.arraycopy(Data.E, 0, E1, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MD[i], 0, MD1[i], 0, Data.N);
      }
    }
    a1 = Data.a.get();

    // X1 = А1*MDh + а1*Eh*d1
    int [] X1 = Data.sumVectorAndVector(
      Data.multipleVectorAndSubMatrix(A1, MD1, 0, Data.Part * 1),
      Data.multipleSubVectorAndTwoScalar(E1, a1, d1, 0, Data.Part * 1)
    );

    Data.insertPartVector(X1, Data.X, 0, Data.Part * 1);

    System.out.println("T1 release Sem5 - end calculating-4");
    Data.Sem5.release(1);

  }
}
