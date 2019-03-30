/*
8.3. Матрица (8)
В матрице A размера NxN числа от 1 до N 2 . Каждое число записано ровно один раз. Даны две
матрицы размера NxN: Top и Left. Значение Top i j определяет количество чисел, больших A i j и
расположенных выше по столбцу, Left i j - количество чисел, больших A i j и расположенных левее по
строке. Найти возможные значения матрицы A. Если решений несколько, вывести любое.
Ввод из файла INPUT.TXT. В первой строке N (1 ≤ N ≤100), затем N строк матрицы Top (числа
через пробел), затем N строк матрицы Left. Числа в обеих матрицах от 0 до N.
Вывод в файл OUTPUT.TXT матрицы A – N строк, числа в строке через пробел. Если решений
нет, вывести 0.
Пример
Ввод
3
0 0 0
0 0 0
0 0 2
0 0 0
0 1 0
0 1 2
Вывод
1 2 6
5 3 7
9 8 4

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <iostream>
#include <vector>

struct Info
{
    int i;
    int j;

    Info()
    {
        this -> i = 0;
        this -> j = 0;
    }
    Info(const int i, const int j)
    {
        this -> i = i;
        this -> j = j;
    }
};

using Matrix = std::vector<std::vector<int>>;
using InfoMatrix = std::vector<std::vector<Info>>;

InfoMatrix GetInfoMatrixFromFile(std::ifstream &inputFile, const std::string &type, int n, bool &wasError)
{
    InfoMatrix result;
    Matrix help(n, std::vector<int>(n));
    std::vector<int> D;
    std::vector<int> helpVec;
    std::vector<Info> anotherLine(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (type == "column")
                inputFile >> help[j][i];
            else if (type == "row")
                inputFile >> help[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        D = help[i];
        for (int j = 1; j <= n; j++)
            helpVec.push_back(j);
        for (int j = n - 1; j >= 0; j--)
        {
            if ((int)helpVec.size() - 1 - D[j] < 0)
            {
                wasError = true;
                return result;
            }
            if (type == "column")
                anotherLine[helpVec[helpVec.size() - 1 - D[j]] - 1] = Info(j, i);
            else if (type == "row")
                anotherLine[helpVec[helpVec.size() - 1 - D[j]] - 1] = Info(i, j);
            if (helpVec.size() > 1)
                helpVec.erase(helpVec.end() - D[j] - 1);
        }
        result.push_back(anotherLine);
        helpVec.clear();
    }
    return result;
}

bool InsertOneNumber(Matrix &outMatrix, InfoMatrix &topMatrix, InfoMatrix &leftMatrix, int n, int a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!topMatrix[i].empty() && !leftMatrix[j].empty())
                if (topMatrix[i][0].i == leftMatrix[j][0].i && topMatrix[i][0].j == leftMatrix[j][0].j)
                {
                    outMatrix[topMatrix[i][0].i][topMatrix[i][0].j] = a;
                    topMatrix[i].erase(topMatrix[i].begin());
                    leftMatrix[j].erase(leftMatrix[j].begin());
                    return true;
                }
        }
    }
    return false;
}

bool InsertAllNumbers(Matrix &outMatrix, InfoMatrix &topMatrix, InfoMatrix &leftMatrix, int n)
{
    for (int a = 1; a <= n*n; a++)
    {
        if (!InsertOneNumber(outMatrix, topMatrix, leftMatrix, n, a))
            return false;
    }
    return true;
}

void ShowResult(const Matrix &outMatrix, std::ofstream &outputFile, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {    
            outputFile << outMatrix[i][j];
            if (j < n - 1)
                outputFile << " ";
        }
        if (i < n - 1)
            outputFile << std::endl;
    }
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    
    int N;
    inputFile >> N;
    
    Matrix outMatrix(N, std::vector<int>(N));

    bool wasError = false;
    InfoMatrix top = GetInfoMatrixFromFile(inputFile, "column", N, wasError);
    if (wasError)
    {
        outputFile << "0";
        return 0;
    }  
    InfoMatrix left = GetInfoMatrixFromFile(inputFile, "row", N, wasError);
    if (wasError)
    {
        outputFile << "0";
        return 0;
    }

    if (InsertAllNumbers (outMatrix, top, left, N))
    {
        ShowResult(outMatrix, outputFile, N);
    }
    else
    {
        outputFile << "0";
    }

    return 0;
}