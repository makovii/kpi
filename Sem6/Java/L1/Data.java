import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class Data {
  public static int N = 4;
  public static final int Part = N / 4; // 4 threads
  public static int way = 0; // 0 by default values - 1; 1 - using terminal
  public static long start = 0; // point start
  public static long end = 0; // point end

  public static int[] X = new int[N];
  public static int[] R = new int[N];
  public static int[] B = new int[N];
  public static int[] Z = new int[N];
  public static int[] E = new int[N];
  public static int[] A = new int[N];
  public static int[][] MC = new int[N][N];
  public static int[][] MD = new int[N][N];

  public static AtomicInteger a = new AtomicInteger();
  public static int d = 0;
  
  public static final Object object = new Object(); // monitor

  public static final Semaphore Sem1 = new Semaphore(0, true); // enter R,Z in T1 for T2
  public static final Semaphore Sem2 = new Semaphore(0, true); // enter R,Z in T1 for T3
  public static final Semaphore Sem3 = new Semaphore(0, true); // enter R,Z in T1 for T4
  public static final Semaphore Sem4 = new Semaphore(0, true); // end calculation-3 in T1
  public static final Semaphore Sem5 = new Semaphore(0, true); // end calculation-4 in T1

  public static final Semaphore Sem6 = new Semaphore(0, true); // enter MD in T2 for T1
  public static final Semaphore Sem7 = new Semaphore(0, true); // enter MD in T2 for T3
  public static final Semaphore Sem8 = new Semaphore(0, true); // enter MD in T2 for T4
  public static final Semaphore Sem9 = new Semaphore(0, true); // end calculation-3 in T2
  public static final Semaphore Sem10 = new Semaphore(0, true); // end calculation-4 in T2

  public static final Semaphore Sem11 = new Semaphore(0, true); // enter B,d in T3 for T1
  public static final Semaphore Sem12 = new Semaphore(0, true); // enter B,d in T3 for T2
  public static final Semaphore Sem13 = new Semaphore(0, true); // enter B,d in T3 for T4
  public static final Semaphore Sem14 = new Semaphore(0, true); // start calculation-4 in T1
  public static final Semaphore Sem15 = new Semaphore(0, true); // start calculation-4 in T2
  public static final Semaphore Sem16 = new Semaphore(0, true); // start calculation-4 in T4

  public static final Semaphore Sem17 = new Semaphore(0, true); // enter MC, E in T4 for T1
  public static final Semaphore Sem18 = new Semaphore(0, true); // enter MC, E in T4 for T2
  public static final Semaphore Sem19 = new Semaphore(0, true); // enter MC, E in T4 for T3
  public static final Semaphore Sem21 = new Semaphore(0, true); // end calculation-3 in T1
  public static final Semaphore Sem22 = new Semaphore(0, true); // end calculation-4 in T1


  // multiplication subMatrix and vector
  public static int[] multipleVectorAndSubMatrix(int[] Vector, int[][] Matrix, int start, int end) {

    int resVector[] = new int[Data.N];
    int k = -1;
    for (int i = start; i < N; ++i) {
      k++;
      for (int j = 0; j < end; ++j) {
        resVector[k] += Matrix[i][j] * Vector[k];  
      }        
    }
    return resVector;
  }

  // multiplication vector and vector
  public static int multipleSubVectorAndSubVector(int[] A, int[] B, int start, int end) {
    int resScalar = 0;
    for (int i = start; i < end; ++i) {
      resScalar += A[i] * B[i];  
    }        
    return resScalar;
  }

  // multiplication scalar, scalar and vector
  public static int[] multipleSubVectorAndTwoScalar(int[] E, int a, int d, int start, int end) {
    int resVector[] = new int[N];
    for (int i = start; i < end; ++i) {
      resVector[i] = a * d * E[i];  
    }        
    return resVector;
  }

  // sum vector and vector
  public static int[] sumVectorAndVector(int[] A, int[] B) {
    int resVector[] = new int[N];
    for (int i = 0; i < A.length; ++i) {
      resVector[i] = A[i] + B[i];  
    }        
    return resVector;
  }
  
  public static void insertPartVector(int[] PartVector, int[] AidVector, int start, int end) {
    int j = 0;
    for (int i = start; i < end; ++i) {
      AidVector[i] = PartVector[j];
      j++;
    }  
  }

  public static void printVector(int[] Vector) {
    for (int i = 0; i < N; ++i) {
      System.out.println(Vector[i]);
    }  
  }
}