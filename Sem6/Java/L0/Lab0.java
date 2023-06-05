/*
Назва дисципліни:   ПЗ ВПКС
Лабораторна робота: №0, Варіант 15
                F1: d = MAX((A + B + C) *(MA*ME))
                F2: ML = SORT(MF*MG)
                F3: S = (O+P)*TRANS(MR * MT)
Виконав:            Маковій Віктор Миколайович
Група:              ІП-05
Дата:               20.02.2023
*/

import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Lab0 {
    public static void main(String[] args) {
        T1 T1 = new T1();
        T2 T2 = new T2();
        T3 T3 = new T3();

        if (Data.N > 1000) {
            System.out.print("Your amount too big !!!\nThere are several ways to execute:\n");
            System.out.print("\t1 - Generating files -> paste random data -> reading files\n");
            System.out.print("\t2 - Insert a value corresponding to the thread\n");
            System.out.print("\t3 - Insert data with random integers");
            System.out.print("\nEnter execution way: ");

            Scanner inputWay = new Scanner(System.in);
            int way = inputWay.nextInt();
            inputWay.close();

            if (way > 0 && way < 4) Data.way = way;
            else {
                System.out.println("An error occurred.");
            }

            if (way == 1) {
                try {
                    new FileWriter("data1.txt", false).close();
                    new FileWriter("data2.txt", false).close();
                    new FileWriter("data3.txt", false).close();

                } catch (IOException e) {
                    System.out.println("An error occurred.");
                    e.printStackTrace();
                }
            }
            T1.setPriority(Thread.MAX_PRIORITY);
            T2.setPriority(Thread.NORM_PRIORITY);
            T3.setPriority(Thread.MIN_PRIORITY);
            
            T2.start();
            T1.start();
            T3.start();
        } else {

            T1.setPriority(Thread.MAX_PRIORITY);
            T2.setPriority(Thread.NORM_PRIORITY);
            T3.setPriority(Thread.MIN_PRIORITY);

            T1.enterData();
            T2.enterData();
            T3.enterData();

            T1.start();
            T2.start();     
            T3.start();
        }
    }
}