/*
Назва дисципліни:   ПЗ ВПКС
Лабораторна робота: №1, Варіант 19
                    X = (R*MC)*MD + (B*Z)*E*d
Виконав:            Маковій Віктор Миколайович
Група:              ІП-05
Дата:               
*/


public class Lab1 {
    public static void main(String[] args) {
        T1 t1 = new T1();
        T2 t2 = new T2();
        T3 t3 = new T3();
        T4 t4 = new T4();


        if (Data.way == 0) {
          t1.enterDefault();  
          t2.enterDefault();
          t3.enterDefault();
          t4.enterDefault();
        } else {
        t1.enterData();
        t2.enterData();
        t3.enterData();
        t4.enterData();            
        }

        Data.start = System.currentTimeMillis(); // point start
        t1.start();
        t2.start();
        t3.start();
        t4.start();
    }
}