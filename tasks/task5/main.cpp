/*
5.3. Число цифр (5)
Найти суммарное число цифр во всех целых числах от M до N включительно.
Ввод из файла INPUT.TXT. В единственной строке находятся целые числа M и N (1 ≤ M ≤
N ≤ 10 15 ).
Вывод в файл OUTPUT.TXT. В единственную строку вывести суммарное число цифр.
Примеры
Ввод 1 Ввод 2
1 2 2 11
Вывод 1 Вывод 2
2 12
Оганнисян Григор, ПС-21
*/

#include <fstream>
#include <cmath>

int getSize(long long number)
{
    int result = 0;
    while(number > 0)
    {
        result++;
        number /= 10;
    }
    return result;
}

long long getSumOfDigitsCounts(long long number)
{
    long long result = 0;
    int size = getSize(number);
    for(int i = 1; i < size; i++)
    {
        result += 9 * (long long)pow(10, i - 1) * i;
    }
    result += (number - (long long)pow(10, size - 1) + 1) * size;
    return result;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    long long firstNumber ;
    long long secondNumber;
    inputFile >> firstNumber;
    inputFile >> secondNumber;
    long long count = getSumOfDigitsCounts(secondNumber) - getSumOfDigitsCounts(firstNumber - 1);
    outputFile << count;
}