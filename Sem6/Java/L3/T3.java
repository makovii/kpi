public class T3 extends Thread {
  Data Mon;

  int a3;
  int x3;
  int[][] ME3 = new int[Mon.N][Mon.N];
  int[] D3 = new int[Mon.N];

  int start = Mon.H * 2;
  int end = Mon.H * 3;

  public T3(Data X) {
      Mon = X;
  }

  public void run() {
    System.out.println("T3 start");

    // input ME
    Mon.WriteME(1);

    System.out.printf("T3 finish input\n");

    // Сигнал про введення даних
    Mon.sInput();
    // Чекати на введення даних в інших потоках
    Mon.wInput();

    // КД1
    ME3 = Mon.ReadME();
    // КД2
    D3 = Mon.ReadD();

    // Обчислення 1
    Mon.sortFirst(start, D3, ME3);

    System.out.printf("T3 finish 1 calc");

    // Сигнал про завершення обчислення1
    Mon.sOper1();


    // Обчислення 4
    a3 = Mon.multipleSubVectorAndSubVector(Mon.B, Mon.C, start);

    System.out.printf("T3 finish 4 calc");

    // Обчислення 5 // КД3
    Mon.Write_a(a3);

    // Сигнал про завершення обчислення5
    Mon.sOper5();

    // Чекати на завершення обчислення5 в потоках
    Mon.wOper5();

    // КД4
    a3 = Mon.Read_a();
    // КД5
    x3 = Mon.Read_x();

    // Обчислення 6
    int[] Z3 = Mon.sumSubVectorAndSubVector(a3, x3, start);

    System.out.printf("T3 finish 6 calc");

    // Введеня Z
    Mon.WriteZ(Z3, start);

    // Сигнал про завершення обчислення6
    Mon.sOper6();

    System.out.println("T3 end");
  }
}
