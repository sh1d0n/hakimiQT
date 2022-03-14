#include "alghoritmhakimi.h"
#include "graphwidget.h"
#include "edge.h"
#include "node.h"

void deikstra(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& matrixD)
{
    for(size_t startTop = 0; startTop < matrix.size(); startTop++)
    {
        std::vector<bool> used;
        used.assign(matrix.size(), false);
        std::vector<int> tops;
        tops.assign(matrix.size(), INT_MAX);
        tops[startTop] = 0;

        int z = 0;
        int s = startTop;

        while(z != used.size())
        {
            size_t v = 0;
            for(size_t j = 0; j < matrix.size(); j++)
            {
                if(matrix[s][j] == 0)
                {
                    continue;
                }

                int summ = tops[s] + matrix[s][j];
                if(summ < tops[j])
                {
                    tops[j] = summ;
                }

                int k = INT_MAX;

                for (size_t i = 0; i < tops.size(); i++)
                {
                    if (k > tops[i] && !used[i] && i != s)
                    {
                        v = i;
                        k = tops[i];
                    }
                }
            }

            used[s] = true;
            s = v;

            z = 0;
            for (size_t i = 0; i < used.size(); i++)
            {
                if (used[i] == true)
                {
                    z++;
                }
            }
        }

        for(size_t j = 0; j < matrixD.size(); j++)
        {
            matrixD[startTop][j] = tops[j];
        }
    }
}

void deikstra(std::vector<std::vector<int>> matrix, int matrixSize, std::pair<int,int>& topWithMax)
{
    std::vector<std::pair<int, int>> maxCounts;
    for(size_t startTop = matrixSize; startTop < matrix.size(); startTop++)
    {
        std::vector<bool> used;
        used.assign(matrix.size(), false);
        std::vector<int> tops;
        tops.assign(matrix.size(), INT_MAX);
        tops[startTop] = 0;

        int z = 0;
        int s = startTop;

        while(z != used.size())
        {
            size_t v = 0;
            for(size_t j = 0; j < matrix.size(); j++)
            {
                if(matrix[s][j] == 0)
                {
                    continue;
                }

                int summ = tops[s] + matrix[s][j];
                if(summ < tops[j])
                {
                    tops[j] = summ;
                }

                int k = INT_MAX;

                for (size_t i = 0; i < tops.size(); i++)
                {
                    if (k > tops[i] && !used[i] && i != s)
                    {
                        v = i;
                        k = tops[i];
                    }
                }
            }

            used[s] = true;
            s = v;

            z = 0;
            for (size_t i = 0; i < used.size(); i++)
            {
                if (used[i] == true)
                {
                    z++;
                }
            }
        }

        int k = 0;
        for(size_t j = 0; j < tops.size(); j++)
        {
            if(k < tops[j])
            {
                k = tops[j];
            }
        }

        maxCounts.push_back({startTop, k});
    }

    int k = INT_MAX;
    for(size_t i = 0; i < maxCounts.size(); i++)
    {
        if(k > maxCounts[i].second)
        {
            k = maxCounts[i].second;
            topWithMax.first = maxCounts[i].first;
            topWithMax.second = maxCounts[i].second;
        }
    }
}

int findMaxMin(std::vector<std::vector<int>> matrixD, int& index)
{
    std::vector<int> maxValues;

    int maxValue = 0;
    for(size_t i = 0; i < matrixD.size(); i++)
    {
        for(size_t j = 0; j < matrixD.size(); j++)
        {
            if(maxValue < matrixD[i][j])
            {
                maxValue = matrixD[i][j];
            }
        }

        maxValues.push_back(maxValue);
        maxValue = 0;
    }

    int minValue = INT_MAX;
    for(size_t i = 0; i < maxValues.size(); i++)
    {
        if(minValue > maxValues[i])
        {
            minValue = maxValues[i];
            index = i;
        }
    }

    return minValue;
}

void findExistingRibs(std::vector<std::vector<int>> matrix, std::vector<ribs>& availableRibs, std::vector<std::vector<int>> matrixD)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = i + 1; j < matrix.size(); j++)
        {
            if(matrix[i][j] != 0)
            {
                availableRibs.push_back({i, j, 0});
            }
        }
    }

    int z = 0;
    for(size_t i = 0; i < availableRibs.size(); i++)
    {
        for(size_t j = 0; j < matrixD.size(); j++)
        {
            if(matrixD[availableRibs[i].firstTop][j] > matrixD[availableRibs[i].secondTop][j])
            {
                z = matrixD[availableRibs[i].secondTop][j];
            }
            else
            {
                z = matrixD[availableRibs[i].firstTop][j];
            }

            if(z > availableRibs[i].edgeEvaluation)
            {
                availableRibs[i].edgeEvaluation = z;
            }
        }
    }
}

void findAvailableRibs(std::vector<ribs>& ribs, int upperBound)
{

    for(size_t i = 0; i < ribs.size(); )
    {
        if(ribs[i].edgeEvaluation >= upperBound)
        {
            ribs.erase(ribs.begin() + i);
            i = 0;
        }
        else
        {
            i++;
        }
    }
}

void fillNewMatrix(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& newMatrix, ribs activeRib)
{
    for(size_t i = 0; i < matrix.size(); i++)
    {
        for(size_t j = 0; j < matrix.size(); j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    newMatrix[matrix.size()][activeRib.firstTop] = 1;
    newMatrix[activeRib.firstTop][matrix.size()] = 1;
    newMatrix[matrix.size()][matrix.size() + 1] = 1;
    newMatrix[matrix.size() + 1][matrix.size()] = 1;

    for(size_t i = matrix.size() + 1; i < newMatrix.size() - 1; i++)
    {
        newMatrix[i][i+1] = 1;
        newMatrix[i+1][i] = 1;
    }

    newMatrix[newMatrix.size() - 1][activeRib.secondTop] = 1;
    newMatrix[activeRib.secondTop][newMatrix.size() - 1] = 1;
}

QString mainAlghoritm(GraphWidget* graph)
{
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> matrixD;
    int matrixSize = graph->GetNodes().size();

    QString result;
    QString result1;
    QString result2;
    QString result3;

    matrix.assign(matrixSize, std::vector<int>(matrixSize));
    matrixD.assign(matrixSize, std::vector<int>(matrixSize));

    for(size_t i = 0; i < matrix.size(); i++)
    {
        for(size_t j = i + 1; j < matrix.size(); j++)
        {
            bool make = false;
            int p = 0;
            for(; p < graph->GetEdges().size(); p++)
            {
                int node1 = graph->GetNeedEdge(p)->edgeNode1();
                int node2 = graph->GetNeedEdge(p)->edgeNode2();
                if(node1 == i && node2 == j)
                {
                    make = true;
                    break;
                }
            }

            if(make)
            {
                matrix[i][j] = graph->GetNeedEdge(p)->GetWeight();
            }
            else
            {
                matrix[i][j] = 0;
            }
            matrix[j][i] = matrix[i][j];
        }
    }

    deikstra(matrix, matrixD);


    int upperBoundIndex;
    int upperBound = findMaxMin(matrixD, upperBoundIndex);

    std::vector<ribs> availableRibs;
    findExistingRibs(matrix, availableRibs, matrixD);

    findAvailableRibs(availableRibs, upperBound);

    std::vector<neededRibs> nRibs;
    if(availableRibs.empty())
    {
        result = "The absolute center of the graph is at the apex - " + QString::number(upperBoundIndex + 1);
    }
    else
    {
        for(size_t i = 0; i < availableRibs.size(); i++)
        {
            std::vector<std::vector<int>> newMatrix;
            newMatrix.assign(matrixSize + matrix[availableRibs[i].firstTop][availableRibs[i].secondTop] - 1, std::vector<int>(matrixSize + matrix[availableRibs[i].firstTop][availableRibs[i].secondTop] - 1));

            fillNewMatrix(matrix, newMatrix, availableRibs[i]);
            std::pair<int,int> topWithMax;
            deikstra(newMatrix, matrixSize, topWithMax);
            nRibs.push_back({availableRibs[i].firstTop, availableRibs[i].secondTop, topWithMax.first, topWithMax.second});
        }
        int needTop = 0;
        int k = INT_MAX;
        for(size_t i = 0; i < nRibs.size(); i++)
        {
            if(k > nRibs[i].value)
            {
                k = nRibs[i].value;
                needTop = i;
            }
        }

        result1 = "Place on(" + QString::number(nRibs[needTop].firstTop + 1) + "," + QString::number(nRibs[needTop].secondTop  + 1) + ")";
        result2 = "\r\nIn the distance = " + QString::number(nRibs[needTop].minTop - matrixSize + 1);
        result3 = "\r\nThe smallest distance to the farthest = " + QString::number(nRibs[needTop].value);
        result = result1 + result2 + result3;
    }

    return result;
}
