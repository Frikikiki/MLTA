/*
3.1. Заяц (5)
Имеется лестница, состоящая из N ступенек. При подъеме по лестнице заяц может прыгать на
любое количество ступенек от 1 до K. Сколько у зайца способов подъема по лестнице?
Ввод из файла INPUT.TXT. Единственная строка содержит целые положительные числа N и K.
Вывод в файл OUTPUT.TXT. Выводится единственное число - количество способов подъема
по лестнице.
Ограничения: 1 ≤ K ≤ N ≤ 100.
Пример
Ввод
3 2
Вывод
3

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> MultiplyLongNumberBySimple(std::vector <int> a, const int b)
{
    for(int i = 0; i < a.size(); i++)
    {
        a[i] *= b;
    }
    std::reverse(a.begin(), a.end());
    for(int i = 0; i < a.size() - 1; i++)
    {
        a[i+1] += a[i] / 10;
        a[i] = a[i] % 10;
    }
    int help = a[a.size() - 1] / 10;
    a[a.size() - 1] %= 10;
    while(help != 0)
    {
        a.push_back(help % 10);
        help /= 10;
    }
    std::reverse(a.begin(), a.end());
    return(a);
}

std::vector<int> Substract(std::vector <int> a, std::vector <int> b)
{
    int k;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++)
    {
        if (a[i] >= b[i])
            a[i] -= b[i];
        else
        {
            k = i + 1;
            while (a[k] == 0)
                k++;
            a[k]--;
            for(int j = k - 1; j > i; j--)
                a[j] = 9;
            a[i] = a[i] + 10 - b[i];
        }
    }
    while (a.back() == 0)
    {
        if(a.size() == 1)
            break;
        a.pop_back();
    }
    std::reverse(a.begin(), a.end());
    return a;
}

int main()
{
    std::ifstream inputFile;
    inputFile.open("input.txt");
    int N;
    int K;
    std::vector<int> newValue;
    inputFile >> N;
    inputFile >> K;
    std::vector<std::vector<int>> counts;
    counts.push_back({1});
    counts.push_back({1});
    while(counts.size() - 1 != N)
    {
        newValue = MultiplyLongNumberBySimple(counts.back(), 2);
        if((((int)counts.size()) - 1 - K) >= 0)
        {
            newValue = Substract(newValue, counts[((int)counts.size()) - 1 - K]);
        }
        counts.push_back(newValue);
    }
    std::ofstream outputFile;
    outputFile.open("output.txt");
    for(int i: counts.back())
    {
        outputFile << i;
    }
    return(0);
}