/*
6.3. Счастливые билеты (8). Номера автобусных билетов состоят из 2N цифр, включая
незначащие нули (1 ≤ N ≤ 500). Минимальный возможный номер состоит из 2N нулей, а
максимальный – из 2N девяток. Студент Вася ездит в университет на автобусе и коллекционирует
счастливые билеты, в которых сумма первых N цифр совпадает с суммой последних N цифр. Как и
всякий настоящий коллекционер, Вася готов пойти на все для пополнения своей коллекции.
Вместе с тем ему пока приходится учитывать свои финансовые возможности.
Каждый раз после приобретения билета Вася определяет, какое минимальное количество
билетов нужно купить еще, чтобы среди них обязательно оказался счастливый билет. Если у него
оказывается достаточно денег, он тут же покупает необходимое число билетов. Иногда он не
успевает закончить расчеты, проезжает свою остановку и опаздывает на занятия. Помогите Васе.
Ввод из файла INPUT.TXT. В первой строке находится число N. Во второй строке задан номер
первого билета Васи из 2N цифр.
Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальное число следующих
билетов, необходимое для гарантированного получения счастливого билета.
Примеры
Ввод 1  Ввод 2  Ввод 3
2       2       2
3817    0839    0000
Вывод 1 Вывод 2 Вывод 3
12      5       0

Оганнисян Григор, ПС-21
MinGW, 8.1.0
*/
#include <fstream>
#include <vector>
#include <algorithm>

using BigInt = std::vector<int>;

int CharToDigit(const char ch)
{
    switch (ch)
    {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        default:
            return 0;
            break;
    }
}

BigInt operator- (BigInt a, BigInt b)
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

BigInt GetBigIntFromFile(std::ifstream &inputFile, int N)
{
    BigInt number;
    char ch;
    for (int i = 0; i < N; i++)
    {
        inputFile >> ch;
        number.push_back(CharToDigit(ch));
    }
    return number;
}

void OutputBigInt(const BigInt &number, std::ofstream &outputFile)
{
    for (int i = 0; i < number.size(); i++)
        outputFile << number[i];
}

int GetSumOfDigits(const BigInt &number, std::string whatHalf)
{
    int sum = 0;
    int b, e; 
    if (whatHalf == "left")
    {
        b = 0;
        e = number.size() / 2;
    }
    else if (whatHalf == "right")
    {
        b = number.size() / 2;
        e = number.size();
    }
    for (b; b < e; b++)
    {
        sum += number[b];
    }
    return sum;
}

BigInt AlgorithmOne(BigInt number)
{
    int currentPosition = number.size() - 1;
    int firstHalfSum = GetSumOfDigits(number, "left");
    int secondHalfSum = GetSumOfDigits(number, "right");
    int digit;

    while (firstHalfSum != secondHalfSum)
    {
        digit = number[currentPosition];
        while (digit == 9)
        {
            currentPosition--;
            digit = number[currentPosition];
        }
        if (digit < 9)
        {
            digit++;
            number[currentPosition] = digit;
            secondHalfSum = GetSumOfDigits(number, "right");
        }
    }
    return number;
}

BigInt AlgorithmTwo(BigInt number)
{
    int currentPosition = number.size() - 1;
    int firstHalfSum = GetSumOfDigits(number, "left");
    int secondHalfSum = GetSumOfDigits(number, "right");
    int digit;

    while (firstHalfSum < secondHalfSum)
    {
        digit = number[currentPosition];
        while (digit == 9)
        {
            digit = 0;
            number[currentPosition] = 0;
            currentPosition--;
            digit = number[currentPosition];
        }
        digit++;
        number[currentPosition] = digit;
        firstHalfSum = GetSumOfDigits(number, "left");
        secondHalfSum = GetSumOfDigits(number, "right");
    }
    if (firstHalfSum == secondHalfSum)
        return number;
    else 
        return AlgorithmOne(number);
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    
    int N;
    inputFile >> N;

    BigInt ticketNumber = GetBigIntFromFile(inputFile, 2*N);
    int firstHalfSum = GetSumOfDigits(ticketNumber, "left");
    int secondHalfSum = GetSumOfDigits(ticketNumber, "right");

    if (firstHalfSum == secondHalfSum)
    {
        outputFile << 0;
    }
    else if (firstHalfSum > secondHalfSum)
    {
       OutputBigInt(AlgorithmOne(ticketNumber) - ticketNumber, outputFile);
    }
    else
    {
       OutputBigInt(AlgorithmTwo(ticketNumber) - ticketNumber, outputFile);
    }
    return 0;
}