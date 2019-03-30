/*
2.2. Путь коня (6)
Дана шахматная доска, состоящая из N  N  клеток (2 ≤ N ≤ 300), несколько из них вырезано.
Провести ходом коня через невырезанные клетки путь минимальной длины из одной заданной
клетки в другую.
Ввод из файла INPUT.TXT. В первой строке задано число N. В следующих N строках
содержится по N символов. Символом # обозначена вырезанная клетка, точкой - невырезанная
клетка, @ - заданные клетки (таких символов два).
Вывод в файл OUTPUT.TXT. Если путь построить невозможно, вывести "Impossible", в
противном случае вывести такую же карту, как и на входе, но пометить все промежуточные
положения коня символом @.
Примеры
Ввод 1 Ввод 2 Ввод 3
5 5 5
..... @..@. @....
.@@.. ..##. ..#..
..... ..... .#...
..... ..... .....
..... ..... ....@
Вывод 1 Вывод 2 Вывод 3
...@.   @..@.   Impossible
.@@..   ..##.
....@   .@..@
.....   ..@..
.....   @....

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <vector>
#include <queue>

const int UNDEFIND = -1;

struct Position
{
    int i;
    int j;
    Position(const int iOfVar, const int jOfVar)
    {
        i = iOfVar;
        j = jOfVar;
    }
};

using Field = std::vector<std::vector<char>>;
using MatrixOfPositions = std::vector<std::vector<Position>>;

void getOutput(std::ofstream &outputFile, Field board, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            outputFile << board[i][j];
        }
        if(i != N - 1)
            outputFile << std::endl;
    }
}

int main()
{    
    int N;
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    inputFile >> N;
    Field board(N, std::vector<char>(N));
    MatrixOfPositions previousStates(N, std::vector<Position>(N, Position(UNDEFIND, UNDEFIND)));   
    Position startPoint(UNDEFIND, UNDEFIND);
    Position finishPoint(UNDEFIND, UNDEFIND);

    for (int i = 0; i < N; i++) //Заполнение массива и определение начала и конца
    {
        for (int j = 0; j < N; j++)
        {
            inputFile >> board[i][j];
            if (board[i][j] == '@')
            {
                if (startPoint.i == UNDEFIND)
                {
                    startPoint = Position(i, j);
                }
                else
                {
                    finishPoint = Position(i, j);
                    board[i][j] = '.';
                } 
            }
        }
    }
    std::queue<Position> positions;
    positions.push(startPoint);
    while (!positions.empty())
    {
        Position current = positions.front();
        positions.pop();
        for (int di = -2; di <= 2; di++)
            for (int dj = -2; dj <= 2; dj++)
                if (di * di + dj * dj == 5)
                {
                    int iNext = current.i + di;
                    int jNext = current.j + dj;
                    if (0 <= iNext && iNext < N && 0 <= jNext && jNext < N &&
                        board[iNext][jNext] == '.' && previousStates[iNext][jNext].i == UNDEFIND)
                    {
                        positions.push(Position(iNext, jNext));
                        previousStates[iNext][jNext] = current;
                    }
                }
    }
    
    if (previousStates[finishPoint.i][finishPoint.j].i == UNDEFIND)
    {
        outputFile << "Impossible";
        return(0);
    }
    
    Position current = finishPoint;
    do {
        board[current.i][current.j] = '@';
        current = previousStates[current.i][current.j];
    } while (!(current.i == startPoint.i && current.j == startPoint.j));
    
    getOutput(outputFile, board, N);
    
    return(0);
}
