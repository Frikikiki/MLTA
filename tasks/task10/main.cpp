/*
10.5. Последовательность 3 (5)
Задана неубывающая последовательность целых чисел. Найти количество пар чисел с заданной
разностью D.
Ввод из файла INPUT.TXT. В первой строке задаются через пробел два целых числа:
количество членов последовательности N и разность D (2 ≤ N ≤ 10 6 , 1 ≤ D ≤ 10 6 ). Во второй строке
вводятся через пробел N натуральных чисел последовательности A 1 ≤ A 2 ≤ ...≤ A N (A i ≤ 10 9 ).
Вывод в файл OUTPUT.TXT. Вывести число пар (A i , A j ) таких, что A i – A j = D.
Ограничения. Время работы на одном тесте до 2 с. Объем используемой памяти до 1 Мгб.
Пример
Ввод
10 7
3 5 12 18 25 40 47 47 48 49
Вывод
4
Оганнисян Григор, ПС-21
*/

#include <fstream>

int main()
{
    std::ifstream inputFileOne("input.txt");
    std::ifstream inputFileTwo("input.txt");
    std::ofstream outputFile("output.txt");
    long long valueOne = 0, valueTwo = 0, tempValue;
    int countOne = 0, countTwo = 0, countTotal = 0;
    int controlOne = 0, controlTwo = 0;
    int N, D;
    inputFileOne >> N >> D;
    inputFileTwo.seekg(inputFileOne.tellg());
    while (controlOne <= N && controlTwo <= N)
    { 
        if (controlOne == 0 && controlTwo == 0)
        {
            inputFileOne >> valueOne;
            controlOne++;
            inputFileTwo >> valueTwo;
            controlTwo++;
        }
        if (valueTwo - valueOne == D || valueOne - valueTwo == D)
        {
            tempValue = valueOne;
            while (tempValue == valueOne && controlOne <= N)
            {
                countOne++;
                inputFileOne >> valueOne;
                controlOne++;
            }
            tempValue = valueTwo;
            while (tempValue == valueTwo && controlTwo <= N)
            {
                countTwo++;
                inputFileTwo >> valueTwo;
                controlTwo++;
            }
            countTotal += countOne * countTwo;
            countOne = 0;
            countTwo = 0;
        }
        else if (valueOne < valueTwo)
        {
            if (valueTwo - valueOne > D)
            {
                while (valueOne < valueTwo - D && controlOne <= N)
                {
                    inputFileOne >> valueOne;
                    controlOne++;
                }
            }
            else if (valueTwo - valueOne < D)
            {
                while(valueTwo - valueOne < D && controlTwo <= N)
                {
                    inputFileTwo >> valueTwo;
                    controlTwo++;
                }
            }
        }
        else if (valueOne > valueTwo)
        {
            if (valueOne - valueTwo > D)
            {
                while (valueTwo < valueOne - D && controlTwo <= N)
                {
                    inputFileTwo >> valueTwo;
                    controlTwo++;
                }
            }
            else if (valueOne - valueTwo < D)
            {
                while(valueOne - valueTwo < D && controlOne <= N)
                {
                    inputFileOne >> valueOne;
                    controlOne++;
                }
            }
        }
        else if (valueOne == valueTwo)
        {
            while((valueOne == valueTwo || valueOne - valueTwo < D) && controlOne <= N)
            {
                inputFileOne >> valueOne;
                controlOne++;
            }
        }
    }
    outputFile << countTotal;
}