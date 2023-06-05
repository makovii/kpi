public class T2 extends Thread {
  Data Mon;

  int a2;
  int x2;
  int[][] ME2 = new int[Mon.N][Mon.N];
  int[] D2 = new int[Mon.N];

  int start = Mon.H;
  int end = Mon.H * 2;

  public T2(Data X) {
      Mon = X;
  }

  public void run() {
    System.out.println("T2 start");

    // input D, MM
    Mon.WriteD(1);
    Mon.MM = Mon.insertMtxWithNum(1);

    System.out.printf("T2 finish input\n");

    // Сигнал про введення даних
    Mon.sInput();
    // Чекати на введення даних в інших потоках
    Mon.wInput();

    // КД1
    ME2 = Mon.ReadME();
    // КД2
    D2 = Mon.ReadD();

    // Обчислення 1
    Mon.sortFirst(start, D2, ME2);

    System.out.printf("T2 finish 1 calc");

    // Сигнал про завершення обчислення1
    Mon.sOper1();


    // Обчислення 4
    a2 = Mon.multipleSubVectorAndSubVector(Mon.B, Mon.C, start);

    System.out.printf("T2 finish 4 calc");

    // Обчислення 5 // КД3
    Mon.Write_a(a2);

    // Сигнал про завершення обчислення5
    Mon.sOper5();

    // Чекати на завершення обчислення5 в потоках
    Mon.wOper5();

    // КД4
    a2 = Mon.Read_a();
    // КД5
    x2 = Mon.Read_x();

    // Обчислення 6
    int[] Z2 = Mon.sumSubVectorAndSubVector(a2, x2, start);

    System.out.printf("T2 finish 6 calc");

    // Введеня Z
    Mon.WriteZ(Z2, start);
        
    // Сигнал про завершення обчислення6
    Mon.sOper6();

    System.out.println("T2 end");
  }
}
