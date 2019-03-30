/*
4.2. Треугольник (5)
Ниже изображен пример треугольника из чисел. Найти наибольшую сумму чисел,
расположенных на пути из верхней точки треугольника до основания.

7
3 8
8 1 6
4 2 3 0
Каждый шаг на пути происходит в направлении вниз по диагонали (влево или вправо).
Треугольник составлен из целых чисел от -10 5 до 10 5 .
Ввод из файла INPUT.TXT. Первое число определяет количество строк треугольника N
(N ≤ 300). Далее задаются строки треугольника.
Вывод в файл OUTPUT.TXT. В первой строке выводится единственное число – наибольшая
сумма. Во второй строке выдаются через пробел числа от вершины треугольника до основания,
дающие наибольшую сумму. Если решений несколько, вывести любое из них.
Пример
Ввод
4
7
3 8
8 1 6
4 2 3 0
Вывод
24
7 8 6 3

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <array>

const int MAX = 300;

void WriteOneNumber(const std::array<std::array<long, MAX>, MAX> &matrix, 
                        std::ofstream &output, int N, int i, int j, std::string lastTo = "right")
{    
    if(i < N - 1)
    {
        if(matrix[i + 1][j] > matrix[i + 1][j + 1])
        {
            output << matrix[i][j] - matrix[i + 1][j] << " ";
            WriteOneNumber(matrix, output, N, i + 1, j, "right");
        }
        else
        {
            output << matrix[i][j] - matrix[i + 1][j + 1] << " ";
            WriteOneNumber(matrix, output, N, i + 1, j + 1, "left");
        }
    }
    else if(i == N - 1)
    {
        if(lastTo == "right")
            output << std::max(matrix[i][j], matrix[i][j + 1]);
        else
            output << std::max(matrix[i][j], matrix[i][j - 1]);
    }
}

int main()
{
    std::array<std::array<long, MAX>, MAX> matrixD;
    std::array<std::array<long, MAX>, MAX> matrixR;
    std::ifstream inputFile("input.txt");
    int N;
    inputFile >> N;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            inputFile >> matrixD[i][j];
            if(i == N - 1)
                matrixR[i][j] = matrixD[i][j];
        }
    }

    for(int i = N - 2; i >= 0; i--)
    {
        for(int j = 0; j <= i; j++)
        {
            matrixR[i][j] = std::max(matrixD[i][j] + matrixR[i + 1][j], matrixD[i][j] + matrixR[i + 1][j + 1]);
        }
    }

    std::ofstream outputFile("output.txt");
    outputFile << matrixR[0][0] << std:: endl;
    WriteOneNumber(matrixR, outputFile, N, 0, 0);

    return(0);
}