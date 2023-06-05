/*
ПЗ ВПКС
Лабораторна робота 3, Варіант 30
Завдання:
Z = sort(D*(ME*MM)) + (B*C)*E*x
T1 = B, E
T2 = D, MM
T3 = ME
T4 = C, Z, x

Маковій В, ІП-05
Дата 24.04.2023
*/


public class Lab3 {
    public static void main(String[] args) {
        Data Monitor = new Data();
        T1 thread1 = new T1(Monitor);
        T2 thread2 = new T2(Monitor);
        T3 thread3 = new T3(Monitor);
        T4 thread4 = new T4(Monitor);

        Data.start = System.currentTimeMillis(); // point start

        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();
    }
}
