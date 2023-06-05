public class T4 extends Thread {
  Data Mon;

  int a4;
  int x4;
  int[][] ME4 = new int[Mon.N][Mon.N];
  int[] D4 = new int[Mon.N];

  int start = Mon.H * 3;
  int end = Mon.H * 4;

  public T4(Data X) {
      Mon = X;
  }

  public void run() {
    System.out.println("T4 start");

    // input B, E
    Mon.C = Mon.insertVecWithNum(1);
    Mon.Write_x(1);

    System.out.printf("T4 finish input\n");

    // Сигнал про введення даних
    Mon.sInput();
    // Чекати на введення даних в інших потоках
    Mon.wInput();

    // КД1
    ME4 = Mon.ReadME();
    // КД2
    D4 = Mon.ReadD();

    // Обчислення 1
    Mon.sortFirst(start, D4, ME4);

    System.out.printf("T4 finish 1 calc");

    // Сигнал про завершення обчислення1
    Mon.sOper1();

    // Чекати на завершення обчислення1 в потоках
    Mon.wOper1();

    // Обчислення 2
    Mon.mergeSort(Mon.A, Mon.A, Mon.A, Mon.H, Mon.H*3, Mon.H*2, Mon.H*4);

    // Сигнал про завершення обчислення2
    Mon.sOper2();

    // Чекати на завершення обчислення2 в потоці T1
    Mon.wOper2();

    System.out.printf("T3 finish 2 calc");


    // Обчислення 3
    Mon.mergeSort(Mon.A, Mon.A, Mon.A, 0, Mon.H*2, Mon.H*2, Mon.H*4);

    // Обчислення 4
    a4 = Mon.multipleSubVectorAndSubVector(Mon.B, Mon.C, start);

    System.out.printf("T4 finish 4 calc");

    // Обчислення 5 // КД3
    Mon.Write_a(a4);

    // Сигнал про завершення обчислення5
    Mon.sOper5();

    // Чекати на завершення обчислення5 в потоках
    Mon.wOper5();

    // КД4
    a4 = Mon.Read_a();
    // КД5
    x4 = Mon.Read_x();

    // Обчислення 6
    int[] Z4 = Mon.sumSubVectorAndSubVector(a4, x4, start);

    System.out.printf("T4 finish 6 calc");

    // Введеня Z
    Mon.WriteZ(Z4, start);

    // Чекати на завершення обчислення6 в потоках
    Mon.wOper6();

    System.out.println("T4 end");

    Mon.printZ();

    Mon.end = System.currentTimeMillis(); // point end 

    System.out.printf("spent time: %d\n", Mon.end - Mon.start);
    System.out.println("Runtime.getRuntime().availableProcessors() = " +
    Runtime.getRuntime().availableProcessors());

  }
}
