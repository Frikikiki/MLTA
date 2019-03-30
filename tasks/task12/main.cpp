/*
12.1. Дороги Прима (4)
В государстве Прим имеется ряд населенных пунктов, связанных грунтовыми дорогами.
Между любыми двумя пунктами может быть не более одной дороги. Решено заасфальтировать
некоторые дороги. Стоимость асфальтирования каждой дороги известна. Требуется выбрать
дороги для асфальтирования так, чтобы можно было проехать из каждого населенного пункта в
любой другой по асфальту, а общая стоимость работы была минимальной. Использовать алгоритм
Прима.
Ввод из файла INPUT.TXT. В первой строке вводятся значение N (1 ≤ N ≤ 1000) и M –
количество населенных пунктов и дорог. В каждой из следующих M строк вводится через пробел
пара номеров пунктов в порядке возрастания в паре и стоимость асфальтирования дороги между
ними.
Вывод в файл OUTPUT.TXT. В первой строке выводится общая стоимость работы. В
следующих N -1 строках содержатся пары населенных пунктов, определяющие выбранные дороги.
В каждой паре меньший номер должен быть первым. Список дорог должен быть отсортирован по
возрастанию первого в паре номера, а при равном первом номере – по второму. В случае
нескольких ответов выдать любой из них.
Пример
Ввод
4 5
2 3 5
1 4 5
1 2 6
1 3 1
3 4 3
Вывод
9
1 3
2 3
3 4

Оганнисян Григор, ПС-21
MinGW 8.1.0
*/

#include <fstream>
#include <vector>
#include <algorithm>

struct Relation
{
    int firstName;
    int secondName;
    int cost;
    Relation(int firstName, int secondName, int cost)
    {
        this -> firstName = firstName;
        this -> secondName = secondName;
        this -> cost = cost;
    }
    Relation()
    {
        this -> firstName = -1;
        this -> secondName = -1;
        this -> cost = -1;
    }
};

struct Node
{
    int name;
    bool isVisited = false;
    std::vector<Relation> relations;
};

bool CompareRelations(const Relation &left, const Relation &right)
{
    return left.cost < right.cost;
}

bool CompareNodes(const int &left, const int &right)
{
    return left < right;
}

bool CompareSteps(const std::vector<int> &left, const std::vector<int> &right)
{
    if (left[0] != right[0])
        return left[0] < right[0];
    else
        return left[1] < right[1];
}

Relation WhatIsTheNextNode(const std::vector<Node> &graph)
{
    std::vector<Relation> variants;
    for (int i = 1; i < graph.size(); i++)
    {
        if (graph[i].isVisited)
        {
            for (Relation const &j: graph[i].relations)
            {
                if (!graph[j.secondName].isVisited)
                {
                    variants.push_back(j);
                }
            }
        }
    }
    std::sort(variants.begin(), variants.end(), CompareRelations);
    return variants[0];
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    
    int a, b, c;
    int N, M;
    inputFile >> N >> M;

    std::vector<Node> graph(M + 1);
    
    std::vector<std::vector<int>> steps;
    Relation tempRelation;
    int costSum = 0;

    for (int i = 1; i <= M; i++)
    {
        inputFile >> a >> b >> c;
        graph[a].relations.push_back(Relation(a, b, c));
        graph[b].relations.push_back(Relation(b, a, c));
    }
    
    graph[1].isVisited = true;
    for (int i = 1; i < N; i++)
    {
        tempRelation = WhatIsTheNextNode(graph);
        steps.push_back({tempRelation.firstName, tempRelation.secondName});
        costSum += tempRelation.cost;
        graph[tempRelation.secondName].isVisited = true;
    }
    
    for (std::vector<int> &i: steps)
    {
        std::sort(i.begin(), i.end(), CompareNodes);
    }
    std::sort(steps.begin(), steps.end(), CompareSteps);

    outputFile << costSum << std::endl;
    for (std::vector<int> &i: steps)
    {
        outputFile << i[0] << " " << i[1] << std::endl;
    }

    return 0;
}