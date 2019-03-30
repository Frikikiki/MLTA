/*
1.8. Шашки 2 (7)
На шахматном поле расположены N черных шашек и одна белая дамка. Требуется написать
программу, которая по заданному расположению шашек определяет, какое максимальное
количество шашек может взять белая дамка за один ход.
Ввод из файла INPUT.TXT. Задается 8 строк, каждая содержит 8 символов. Символом ‘0’
обозначается пустая клетка, символом ‘1’ положение черной шашки и символом ‘2’ - положение
белой дамки.
Вывод в файл OUTPUT.TXT. В первой строке вывести единственное число K – максимальное
количество черных шашек, которых можно взять за один ход. В последующих K + 1 строках
вывести координаты клеток, определяющих движение дамки. Если есть несколько решений,
вывести любое из них.
Пример
Ввод
00000001
00100000
00010100
00101000
00020000
00101010
00000000
00000000
Вывод
6
5 4
7 6
5 8
1 4
3 2
5 4
3 6

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <vector>
#include <algorithm>

using Field = std::vector<std::vector<char>>;

enum Direction {left_up, right_up, left_down, right_down};

const int SIDE_SIZE = 8;
const char QUEEN = '2';
const char CHECKER = '1';
const char FREE_PLACE = '0';

struct Way
{
    int CheckersCount = 0;
    std::vector<std::vector<int>> Steps;
};

bool Compare(const Way &left, const Way &right)
{
    return left.CheckersCount > right.CheckersCount;
}

Field GetBoard(std::ifstream &inputFile)
{
    Field board;
    std::vector<char> temp;
    char ch;
    for(int i = 0; i < SIDE_SIZE; i++)
    {
        for(int j = 0; j < SIDE_SIZE; j++)
        {
            inputFile >> ch;
            temp.push_back(ch);
        }
        board.push_back(temp);
        temp.clear();
    }
    return board;
}

void FindQueen(Field &board, int &iOfQueen, int &jOfQueen)
{
    for(int i = 0; i < SIDE_SIZE; i++)
        for(int j = 0; j < SIDE_SIZE; j++)
            if(board[i][j] == QUEEN)
            {
                iOfQueen = i;
                jOfQueen = j;
                board[i][j] = FREE_PLACE;
                break;
            }          
}

void NextStep(Field board, int i, int j, bool wasLastActionGetting, 
                const Direction direction, Way currentWay, std::vector<Way> &allWays)
{     
    if (wasLastActionGetting)
    {
        if (direction == left_up)
        {
            currentWay.Steps.push_back({i + 1, j + 1});
            allWays.push_back(currentWay);
            NextStep(board, i, j, false, left_up, currentWay, allWays);
            currentWay.Steps.pop_back();
            while (board[i][j] == FREE_PLACE && i >= 0 && j >= 0)
            {
                currentWay.Steps.push_back({i + 1, j + 1});
                NextStep(board, i, j, false, right_up, currentWay, allWays);
                NextStep(board, i, j, false, left_down, currentWay, allWays);
                currentWay.Steps.pop_back();
                i--;
                j--;
                if ( i < 0 || j < 0)
                    break;
            }
        }
        else if (direction == right_up)
        {
            currentWay.Steps.push_back({i + 1, j + 1});
            allWays.push_back(currentWay);
            NextStep(board, i, j, false, right_up, currentWay, allWays);
            currentWay.Steps.pop_back();
            while (board[i][j] == FREE_PLACE && i >= 0 && j <= SIDE_SIZE - 1)
            {
                currentWay.Steps.push_back({i + 1, j + 1});
                NextStep(board, i, j, false, left_up, currentWay, allWays);
                NextStep(board, i, j, false, right_down, currentWay, allWays);
                currentWay.Steps.pop_back();
                i--;
                j++;
                if (i < 0 || j > SIDE_SIZE - 1)
                    break;
            }
        }
        else if (direction == left_down)
        {
            currentWay.Steps.push_back({i + 1, j + 1});
            allWays.push_back(currentWay);
            NextStep(board, i, j, false, left_down, currentWay, allWays);
            currentWay.Steps.pop_back();
            while (board[i][j] == FREE_PLACE && i <= SIDE_SIZE - 1 && j >= 0)
            {
                currentWay.Steps.push_back({i + 1, j + 1});
                NextStep(board, i, j, false, left_up, currentWay, allWays);
                NextStep(board, i, j, false, right_down, currentWay, allWays);
                currentWay.Steps.pop_back();
                i++;
                j--;
                if (i > SIDE_SIZE - 1 || j < 0)
                    break;
            }
        }
        else if (direction == right_down)
        {
            currentWay.Steps.push_back({i + 1, j + 1});
            allWays.push_back(currentWay);
            NextStep(board, i, j, false, right_down, currentWay, allWays);
            currentWay.Steps.pop_back();
            while(board[i][j] == FREE_PLACE && i <= SIDE_SIZE - 1 && j <= SIDE_SIZE - 1)
            {
                currentWay.Steps.push_back({i + 1, j + 1});
                NextStep(board, i, j, false, right_up, currentWay, allWays);
                NextStep(board, i, j, false, left_down, currentWay, allWays);
                currentWay.Steps.pop_back();
                i++;
                j++;
                if (i > SIDE_SIZE - 1 || j > SIDE_SIZE - 1)
                    break;
            }
        }
    }
    else
    {
        if (direction == left_up)
        {
            while (board[i][j] == FREE_PLACE && i != 0 && j != 0)
            {
                i--;
                j--;
                if (i < 0 || j < 0)
                    break;
            }
            if (board[i][j] == CHECKER && i != 0 && j != 0 && board[i-1][j-1] == FREE_PLACE)
            {
                board[i][j] = FREE_PLACE;
                currentWay.CheckersCount++;
                NextStep(board, i - 1, j - 1, true, left_up, currentWay, allWays);
            }
        }
        else if (direction == right_up)
        {
            while (board[i][j] == FREE_PLACE && i != 0 && j != SIDE_SIZE - 1)
            {
                i--;
                j++;
                if (i < 0 || j > SIDE_SIZE - 1)
                    break;
            }
            if (board[i][j] == CHECKER && i != 0 && j != SIDE_SIZE - 1 && board[i-1][j+1] == FREE_PLACE)
            {
                board[i][j] = FREE_PLACE;
                currentWay.CheckersCount++;
                NextStep(board, i - 1, j + 1, true, right_up, currentWay, allWays);
            }
        }
        else if (direction == left_down)
        {
            while (board[i][j] == FREE_PLACE && i != SIDE_SIZE - 1 && j != 0)
            {
                i++;
                j--;
                if (i > SIDE_SIZE - 1 || j < 0)
                    break;
            }
            if (board[i][j] == CHECKER && i != SIDE_SIZE - 1 && j != 0 && board[i+1][j-1] == FREE_PLACE)
            {
                board[i][j] = FREE_PLACE;
                currentWay.CheckersCount++;
                NextStep(board, i + 1, j - 1, true, left_down, currentWay, allWays);
            }
        }
        else if (direction == right_down)
        {
            while (board[i][j] == FREE_PLACE && i != SIDE_SIZE - 1 && j != SIDE_SIZE - 1)
            {
                i++;
                j++;
                if (i > SIDE_SIZE - 1 || j > SIDE_SIZE - 1)
                    break;
            }
            if (board[i][j] == CHECKER && i != SIDE_SIZE - 1 && j != SIDE_SIZE - 1 && board[i+1][j+1] == FREE_PLACE)
            {
                board[i][j] = FREE_PLACE;
                currentWay.CheckersCount++;
                NextStep(board, i + 1, j + 1, true, right_down, currentWay, allWays);
            }
        }
    }
}


int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    Way currentWay;
    std::vector<Way> allWays;
    
    Field board = GetBoard(inputFile);

    int iOfQueen, jOfQueen;
    FindQueen(board, iOfQueen, jOfQueen);
    
    Way firstPoint;
    firstPoint.Steps.push_back({iOfQueen + 1, jOfQueen + 1});
    allWays.push_back(firstPoint);

    NextStep(board, iOfQueen, jOfQueen, false, left_up, currentWay, allWays);
    NextStep(board, iOfQueen, jOfQueen, false, right_up, currentWay, allWays);
    NextStep(board, iOfQueen, jOfQueen, false, left_down, currentWay, allWays);
    NextStep(board, iOfQueen, jOfQueen, false, right_down, currentWay, allWays);

    std::sort(allWays.begin(), allWays.end(), Compare);

    outputFile << allWays[0].CheckersCount << std::endl;
    outputFile << iOfQueen + 1 << " " << jOfQueen + 1 << std::endl;
    if (allWays[0].CheckersCount > 0)
    {
        for (auto i: allWays[0].Steps)
            outputFile << i[0] << " " << i[1] << std::endl;
    }
    return(0);
}
