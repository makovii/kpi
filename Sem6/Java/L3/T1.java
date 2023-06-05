public class T1 extends Thread {
  Data Mon;

  int a1;
  int x1;
  int[][] ME1 = new int[Mon.N][Mon.N];
  int[] D1 = new int[Mon.N];

  int start = 0;
  int end = Mon.H;

  public T1(Data X) {
      Mon = X;
  }

  public void run() {
    System.out.println("T1 start");

    // input B, E
    Mon.B = Mon.insertVecWithNum(1);
    Mon.E = Mon.insertVecWithNum(1);


    System.out.printf("T1 finish input\n");

    // Сигнал про введення даних
    Mon.sInput();
    // Чекати на введення даних в інших потоках
    Mon.wInput();

    // КД1
    ME1 = Mon.ReadME();
    // КД2
    D1 = Mon.ReadD();

    // Обчислення 1
    Mon.sortFirst(start, D1, ME1);

    System.out.printf("T1 finish 1 calc");

    // Сигнал про завершення обчислення1
    Mon.sOper1();

    // Чекати на завершення обчислення1 в потоках
    Mon.wOper1();

    // Обчислення 2
    Mon.mergeSort(Mon.A, Mon.A, Mon.A, 0, Mon.H*2, Mon.H, Mon.H*3);

    // Сигнал про завершення обчислення2
    Mon.sOper2();

    System.out.printf("T1 finish 2 calc");

    // Обчислення 4
    a1 = Mon.multipleSubVectorAndSubVector(Mon.B, Mon.C, start);

    System.out.printf("T1 finish 4 calc");

    // Обчислення 5 // КД3
    Mon.Write_a(a1);

    // Сигнал про завершення обчислення5
    Mon.sOper5();

    // Чекати на завершення обчислення5 в потоках
    Mon.wOper5();

    // КД4
    a1 = Mon.Read_a();
    // КД5
    x1 = Mon.Read_x();

    // Обчислення 6
    int[] Z1 = Mon.sumSubVectorAndSubVector(a1, x1, start);

    System.out.printf("T1 finish 6 calc");

    // Введеня Z
    Mon.WriteZ(Z1, start);

    // Сигнал про завершення обчислення6
    Mon.sOper6();

    System.out.println("T1 end");
  }
}
