import java.util.Scanner;

public class T3 extends Thread {
  private int[][] MC3 = new int[Data.N][Data.N];
  private int[][] MD3 = new int[Data.N][Data.N];
  private int[] R3 = new int[Data.N];
  private int[] E3 = new int[Data.N];
  private int d3 = 0;

  public void enterDefault() {
    System.out.println("Enter B");
    for (int i = 0; i < Data.N; i++) {
      Data.R[i] = 1;
    }

    System.out.println("Enter d");
    Data.d = 1;   
  }
  
  public void enterData() {
    Scanner console = new Scanner(System.in);

    System.out.printf("Enter vector B (%d integers): ", Data.N);
    for (int i = 0; i < Data.N; i++) {
        Data.B[i] = console.nextInt();
    }

    System.out.printf("Enter scalar d: ");
    Data.d = console.nextInt(); 
  }


  public void run() {
    System.out.println("Start T3");



    System.out.println("T3 release Sem11");
    Data.Sem11.release(1);
    System.out.println("T3 release Sem12");
    Data.Sem12.release(1);
    System.out.println("T3 release Sem13");
    Data.Sem13.release(1);


    System.out.println("T3 waiting for Sem2,Sem7,Sem19 - calculation 1,2,3");
    try {
      Data.Sem2.acquire();
      Data.Sem7.acquire();
      Data.Sem19.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T3 got permission Sem2,Sem7,Sem19");

    synchronized (Data.object) {
      System.arraycopy(Data.R, 0, R3, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MC[i], 0, MC3[i], 0, Data.N);
      }
    }

    // A3 = R*MC3
    int[] A3 = Data.multipleVectorAndSubMatrix(R3, MC3, Data.Part * 2, Data.Part * 3);
    Data.insertPartVector(A3, Data.A, Data.Part * 2, Data.Part * 3);

    // a3 = (B3*Z3)
    int a3 = Data.multipleSubVectorAndSubVector(Data.B, Data.Z, Data.Part * 2, Data.Part * 3);
    Data.a.getAndAdd(a3);

    System.out.println("T3 waiting for Sem4, Sem9, Sem21 - end calculation-3");
    try {
      Data.Sem4.acquire();
      Data.Sem9.acquire();
      Data.Sem21.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T3 got permission Sem4, Sem9, Sem21");
    
    System.out.println("T3 release Sem14 - calculation-4");
    Data.Sem14.release(1);
    System.out.println("T3 release Sem15 - calculation-4");
    Data.Sem15.release(1);
    System.out.println("T3 release Sem16 - calculation-4");
    Data.Sem16.release(1);


    synchronized (Data.object) {
      System.arraycopy(Data.A, 0, A3, 0, Data.N);
      d3 = Data.d;
      System.arraycopy(Data.E, 0, E3, 0, Data.N);
      for (int i = 0; i < Data.N; i++) {
        System.arraycopy(Data.MD[i], 0, MD3[i], 0, Data.N);
      }
    }
    a3 = Data.a.get();

    // X3 = А3*MDh + а3*Eh*d3
    int [] X3 = Data.sumVectorAndVector(
      Data.multipleVectorAndSubMatrix(A3, MD3, Data.Part * 2, Data.Part * 3),
      Data.multipleSubVectorAndTwoScalar(E3, a3, d3, Data.Part * 2, Data.Part * 3)
    );
    
    Data.insertPartVector(X3, Data.X, Data.Part * 2, Data.Part * 3);


    System.out.println("T3 waiting for Sem5, Sem10, Sem22 - end calculation 4");
    try {
      Data.Sem5.acquire();
      Data.Sem10.acquire();
      Data.Sem22.acquire();
    } catch (InterruptedException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    System.out.println("T3 got permission Sem5, Sem10, Sem22");

    System.out.println("Result X:");
    Data.printVector(Data.X);
    Data.end = System.currentTimeMillis(); // point end 
    //System.out.printf("start: \t %d\n", Data.start);
    System.out.printf("spent time: %d\n", Data.end - Data.start);
    System.out.println("Runtime.getRuntime().availableProcessors() = " +
    Runtime.getRuntime().availableProcessors());
  }
}
