/*
7.5. Волки и овцы (8)
На координатной плоскости заданы отрезками N волков и M овец.
Пастух с ружьем находится в начале координат. Выстрел поражает всех животных по
направлению полета пули. Найти наименьшее число выстрелов для того, чтобы убить всех
волков и не тронуть овец.
Ввод из файла INPUT.TXT. В первой строке задаются через пробел значения N и M
(1 ≤ N, M ≤ 10 3 ). В следующих N строках - целочисленные координаты начала (X 1 , Y 1 ) и
конца (X 2 , Y 2 ) отрезка, соответствующего волку (-1000 ≤ X 1 , X 2 ≤ 1000; 1 ≤Y 1 , Y 2 ≤ 1000).
Аналогично в следующих M строках указывается положение овец.

Вывод в файл OUTPUT.TXT единственного целого числа либо сообщения “No
solution”.
Пример
Ввод
2 1
1 1 2 3
-5 4 2 2
999 1000 1000 9993
Вывод
2
Оганнисян Григор, ПС-21
*/

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Point
{
    double X;
    double beginX = 0;
    double endX = 0;
    int indexOfEnd = -1;
    bool isIndexOfEndDefined = false;
    std::string Type;
    std::string Sort;
    Point()
    {
        Type = "UNDEFINED";
        Sort = "UNDEFINED";
        X = 0;
    }
    Point(const std::string Type, const std::string Sort, const double X)
    {
        this -> Type = Type;
        this -> Sort = Sort;
        this -> X = X;
    }
};

using Axis = std::vector<Point>;

bool Compare (const Point &left, const Point &right)
{
    if (left.X != right.X)
        return left.X < right.X;
    else
    {
        if (left.Type != right.Type)
        {
            return left.Type == "begin";
        }
        else
            if (left.Type == "begin")
                return left.Sort == "sheep";
            else
                return left.Sort == "wolf";
    }
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    int wolfsCount, sheepsCount;
    int sheepsInQuestion = 0, shotsCount = 0;
    int indexOfZeroSheep;
    double pointOfZeroSheep;
    bool isPossible = true;
    double XOnei, YOnei, XTwoi, YTwoi;
    inputFile >> wolfsCount >> sheepsCount;
    Axis axis;

    for (int i = 0; i < wolfsCount; i++)
    {
        inputFile >> XOnei >> YOnei >> XTwoi >> YTwoi;
        axis.push_back(Point("begin", "wolf", std::min(XOnei/YOnei, XTwoi/YTwoi)));
        axis.push_back(Point("end", "wolf", std::max(XOnei/YOnei, XTwoi/YTwoi)));
        axis[axis.size() - 2].endX = axis[axis.size() - 1].X;
        axis[axis.size() - 1].beginX = axis[axis.size() - 2].X;
    }
    for (int i = 0; i < sheepsCount; i++)
    {
        inputFile >> XOnei >> YOnei >> XTwoi >> YTwoi;
        axis.push_back(Point("begin", "sheep", std::min(XOnei/YOnei, XTwoi/YTwoi)));
        axis.push_back(Point("end", "sheep", std::max(XOnei/YOnei, XTwoi/YTwoi)));
    }
    
    std::sort(axis.begin(), axis.end(), Compare);
    for (int i = 0; i < 2*(sheepsCount + wolfsCount); i++)
    {
        if (axis[i].Sort == "wolf" && axis[i].Type == "begin")
            for (int j = 0; j < 2*(sheepsCount + wolfsCount); j++)
            {
                if (axis[j].Sort == "wolf" && axis[j].Type == "end" && axis[i].X == axis[j].beginX && 
                                        axis[i].endX == axis[j].X && !axis[j].isIndexOfEndDefined)
                {
                    axis[i].indexOfEnd = j;
                    axis[j].isIndexOfEndDefined = true;
                    break;
                }
            }
    }

    for (int i = 0; i < axis.size(); i++)
    {
        if (axis[i].Sort == "sheep" && axis[i].Type == "begin")
        {
            if (sheepsInQuestion == 0)
            {
                indexOfZeroSheep = i;
                pointOfZeroSheep = axis[i].X;
            }
            sheepsInQuestion++;
        }
        else if (axis[i].Sort == "sheep" && axis[i].Type == "end")
            sheepsInQuestion--;
        else if (axis[i].Sort == "wolf" && axis[i].Type == "end")
        {
            if (sheepsInQuestion == 0)
            {
                for (int j = i; j >= 0; j--)
                {
                    if (axis[j].Sort == "wolf" && axis[j].Type == "begin")
                        axis[axis[j].indexOfEnd].Type = "DEAD";
                }
                shotsCount++;
            }
            else
            {
                if (axis[i].beginX < pointOfZeroSheep)
                {
                    for (int j = indexOfZeroSheep - 1; j >= 0; j--)
                    {
                        if (axis[j].Sort == "wolf" && axis[j].Type == "begin")
                            axis[axis[j].indexOfEnd].Type = "DEAD";
                    }
                    shotsCount++;
                }
                else
                {
                    isPossible = false;
                    break;
                }
            }
        }
    }

    if (isPossible)
        outputFile << shotsCount;
    else
        outputFile << "No solution";

    return 0;
}