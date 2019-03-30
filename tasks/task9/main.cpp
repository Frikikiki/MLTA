/*
9.2. Простоватые числа (4)
Студент Вася отыскивает простые числа в диапазоне от 1 до N (1 ≤  N ≤ 10 15 ). Если число M, не
превосходящее N, не делится на 2, 3 и 5, Вася называет его “простоватым”. По заданному
значению N найти количество простоватых чисел.
Ввод. В единственной строке файла INPUT.TXT находится число N.
Вывод. В единственную строку файла OUTPUT.TXT вывести количество простоватых чисел.
Пример
Ввод
10
Вывод
2

Оганнисян Григор, ПС-21, MinGW
*/

#include <fstream>

const long long LCM = 30;

long long getCountOfRustic(long long N)
{
    long long count = 0;
    for (int i = 1; i <= N; i += 2)
    {
        if ((i % 3 != 0) && (i % 5 != 0))
        {
            count++;
        }
    }
    return count;
}

int main()
{
	std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    long long N;
	long long count = 0;

	inputFile >> N;

	if (N < LCM)
		count = getCountOfRustic(N);
	else
		count = (N / LCM) * 8 + getCountOfRustic(N % LCM);

	outputFile << count;
}