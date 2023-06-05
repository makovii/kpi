import java.util.Arrays;

public class Data {
  public static long start;
  public static long end;
  public static int N = 500;
  private final static int P = 4;
  public static int H = N/P;

  private int a = 0; // --СР
  private int x = 0; // --СР
  private int[] D = new int[N]; // --СР
  private int[][] ME = new int[N][N]; // --СР

  static int[] A = new int[N];
  static int[] E = new int[N];
  static int[] Z = new int[N];
  static int[] C = new int[N];
  int[] B = new int[N];
  static int[][] MM = new int[N][N];

  // Прапори для синхронізації
  private int Flag1 = 0;
  private int Flag2 = 0;
  private int Flag3 = 0;
  private int Flag4 = 0;
  private int Flag5 = 0;

  // Взаємодія зі СР
  public synchronized int[] ReadD() {
    return D;
  }
  public synchronized void WriteD(int input) {
    for (int i = 0; i < N; ++i)
      D[i] = input; 
  }
  
  public synchronized int[][] ReadME() {
    return ME;
  }
  public synchronized void WriteME(int input) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        ME[i][j] = input;
      }
    }
            
  }

  public synchronized int Read_a() {
    return a;
  }
  public synchronized void Write_a(int input) {
    a = a + input;
  }

  public synchronized int Read_x() {
    return x;
  }
  public synchronized void Write_x(int input) {
    x = input;
  }

  // для виводу
  public synchronized void WriteZ(int[] Vec, int start ) {
    int j = 0;
    int end = start + H;
    for (int i = start; i < end; ++i) {
        Z[i] = Vec[j];
        j++;
    }
  }
  public synchronized void printZ() {
      for (int i = 0; i < N; ++i) {
          System.out.print(Z[i] + " ");
      }
      System.out.print("\n");
  }

  // для синхронізації
  public synchronized void wInput() {
    try{
        if (Flag1 < 4) wait();
    } catch(Exception e) {}
  }
  public synchronized void sInput() {
      Flag1 += 1;
      if (Flag1 == 4) {
          notifyAll();
      }
  }

  public synchronized void wOper1() {
      try{
          if (Flag2 < 4) wait();
      } catch(Exception e) {}
  }
  public synchronized void sOper1() {
      Flag2 += 1;
      if (Flag2 == 4) {
          notifyAll();
      }
  }

  public synchronized void wOper2() {
    try{
        if (Flag3 < 2) wait();
    } catch(Exception e) {}
  }
  public synchronized void sOper2() {
      Flag3 += 1;
      if (Flag3 == 2) {
          notifyAll();
      }
  }

  public synchronized void wOper5() {
    try{
        if (Flag4 < 4) wait();
    } catch(Exception e) {}
  }
  public synchronized void sOper5() {
      Flag4 += 1;
      if (Flag4 == 4) {
          notifyAll();
      }
  }

  public synchronized void wOper6() {
    try{
        if (Flag5 < 3) wait();
    } catch(Exception e) {}
  }
  public synchronized void sOper6() {
      Flag5 += 1;
      if (Flag5 == 3) {
          notifyAll();
      }
  }


  // Секція обчислень

  // Ah = sort(D*(ME*MM))
  public static void sortFirst(int start, int[] D, int[][] ME) {
    // Обчислення6 Ah = p1 * X1 * (MX * MTh) + a1 * Zh
    int end = start + H;
    for (int i = start; i < end; i++) {
        int part = 0;
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
              //System.out.printf("*");
                part += D[k] * (ME[i][j] * MM[i][j]);
            }
        }
        A[i] = part;
        
    }
    Arrays.sort(A, start, end);
  }

  // sort*(X, Y)
  public static void mergeSort(int[] R, int[] X, int[] Y, int startX, int startY, int endX, int endY) {
    int[] buffer = new int[endX - startX + endY - startY];
    int i = startX, j = startY, k = 0;
    while (i < endX && j < endY) {
        if (X[i] <= Y[j]) {
            buffer[k] = X[i++];
        } else {
            buffer[k] = Y[j++];
        }
        k++;
    }
    while (i < endX) {
        buffer[k++] = X[i++];
    }
    while (j < endY) {
        buffer[k++] = Y[j++];
    }
    System.arraycopy(buffer, 0, R, startX * 2, k);
  }

  // ai = Bh * Ch
  public static int multipleSubVectorAndSubVector(int[] A, int[] B, int start) {
    int end = start + H;
    int resScalar = 0;
    for (int i = start; i < end; ++i) {
      resScalar += A[i] * B[i];  
    }        
    return resScalar;
  }


  // result operation: Zh = Ah + a*Eh*x
  public static int[] sumSubVectorAndSubVector(int a, int x, int start) {
    int resVector[] = new int[N];
    int end = start + H;
    for (int i = 0; i < end; ++i) {
      resVector[i] = A[i] + a * E[i] * x;  
    }        
    return resVector;
  }


  // Допоміжні функції
  public static int[][] insertMtxWithNum (int num) {
      int tempMtx[][] = new int[N][N];
      for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j)
              tempMtx[i][j] = num;
      return tempMtx;
  }

  public static int[] insertVecWithNum (int num) {
      int tempVec[] = new int[N];
      for (int i = 0; i < N; ++i)
          tempVec[i] = num;
      return tempVec;
  }
}
