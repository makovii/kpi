import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Data {
  public static int N = 2;
  public static int way = 0;
  private static final Random ran = new Random();

  // calculate F1: d = MAX((A + B + C) *(MA*ME))
  public static int F1 (int[] A, int[] B, int[] C, int[][] MA, int[][] ME) {
    int[] newVector = new int[N];

    // adding three vectors
    for (int i = 0; i < N; i++) {
      newVector[i] = A[i] + B[i] + C[i];
    }

    // multiplication matrix and matrix
    int newMatrix[][] = new int[N][N];
     for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          for (int k = 0; k < N; k++) {
            newMatrix[i][j] += MA[i][k] * ME[k][j];
          } 
        }
    }

    // multiplication matrix and vector
    int resVector[] = new int[N];
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        resVector[i] += newMatrix[i][j] * newVector[j];  
      }        
    }

    // calculate maximum
    int result = resVector[0];
    for (int i = 1; i < N; ++i) {
      if (resVector[i] > result) result = resVector[i];
    }

    return result;
  }

  // calculate F2: ML = SORT(MF*MG)
  public static int[][] F2 (int[][] MF, int[][] MG) {
    // multiplication matrix and matrix
    int newMatrix[][] = new int[N][N];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          newMatrix[i][j] += MF[i][k] * MG[k][j];
        } 
      }
    }

    // sort matrix
    for (int i = 0; i < N; i++) {
      Arrays.sort(newMatrix[i]);
    }
    return newMatrix;
  }

  // calculate S = (O+P)*TRANS(MR * MT)
  public static int[] F3 (int[] O, int[] P, int[][] MR, int[][] MT) {
    // multiplication matrix and matrix
    int newMatrix[][] = new int[N][N];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          newMatrix[i][j] += MR[i][k] * MT[k][j];
        } 
      }
    }

    // transportation matrix
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        MR[j][i] = newMatrix[i][j];
      }
    }

    // adding two vectors
    int[] newVector = new int[N];
    for (int i = 0; i < N; i++) {
      newVector[i] = O[i] + P[i];
    }

    // multiplication matrix and vector
    int resVector[] = new int[N];
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        resVector[i] += MR[i][j] * newVector[j];  
      }        
    }
    return resVector;
  }

  public static int[][] insertMatrix (int value) {
      int matrix[][] = new int[N][N];
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          matrix[i][j] = value; 
        }          
      }
      return matrix;
  }

  public static int[] insertVector (int num) {
      int vector[] = new int[N];
      for (int i = 0; i < N; ++i) {
        vector[i] = num;
      }
        
      return vector;
  }

  public static int[][] generateRandMatrix () {
      int matrix[][] = new int[N][N];
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          matrix[i][j] = ran.nextInt();
        }
      }
      return matrix;
  }

  public static int[] generateRandVec () {
      int vector[] = new int[N];
      for (int i = 0; i < N; ++i) {
        vector[i] = ran.nextInt();  
      }
      return vector;
  }

  public static void writeMatrixToFile(String fileName, String matrixName) {
      try {
        FileWriter writer = new FileWriter(fileName, true);

        // int tempMtx[][] = new int[N][N];   delete this string
        writer.write(matrixName + "\n");
        for (int i = 0; i < N; i++) {
          for (int j = 0; j < N; j++) {
            if (j == N - 1) {
              writer.write(ran.nextInt(10) + "\n");
              break;
            }
            writer.write(ran.nextInt(10) + ", ");
          }
        }
        writer.close();

      } catch (IOException e) {
        System.out.println("An error occurred.");
        e.printStackTrace();
      }
  }

  public static void writeVectorToFile(String fileName, String vectorName) {
      try {
        FileWriter writer = new FileWriter(fileName, true);

        writer.write(vectorName + "\n");
        for (int j = 0; j < N; j++) {
            if (j == N - 1) {
              writer.write(ran.nextInt(10) + "\n");
              break;
            }
            writer.write(ran.nextInt(10) + ", ");
        }
        writer.close();

      } catch (IOException e) {
        System.out.println("An error occurred.");
        e.printStackTrace();
      }
  }

  public static int[][] readMatrixFromFile(String fileName, String matrixName) {
    int tempMtx[][] = new int[N][N];
    try {
      FileReader reader = new FileReader(fileName);
      Scanner scan = new Scanner(reader);
      boolean isMatrix = false;
      int rows = 0;

      while(scan.hasNextLine()) {
        String line = scan.nextLine();
        if (rows >= N) break;

        if (isMatrix) {
          String[] row = line.split(", ");
          for (int i = 0; i < row.length; i++) {
            tempMtx[rows][i] = Integer.parseInt(row[i]);
          }
          rows++;
        }

        if (line.equals(matrixName)) {
            isMatrix = true;
        }
      }
      reader.close();
      scan.close();

    } catch (Exception e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }
    return tempMtx;
  }

  public static int[] readVectorFromFile(String fileName, String vectorName) {
    int tempVec[] = new int[N];
    try {
      FileReader reader = new FileReader(fileName);
      Scanner scan = new Scanner(reader);
      boolean isVector = false;

      while(scan.hasNextLine()) {
        String line = scan.nextLine();
        if (isVector) {
          String[] row = line.split(", ");
          for (int i = 0; i < row.length; i++){
            tempVec[i] = Integer.parseInt(row[i]);
          }
          break;
        }
        if(line.equals(vectorName)){
          isVector = true;
        }
      }
      reader.close();
      scan.close();

    } catch (Exception e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }

    return tempVec;
  }
}