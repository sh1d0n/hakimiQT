#ifndef ALGHORITMHAKIMI_H
#define ALGHORITMHAKIMI_H

#include <vector>
#include <QGraphicsView>
#include "graphwidget.h"

struct ribs
{
    int firstTop;
    int secondTop;
    int edgeEvaluation;
};

struct neededRibs
{
    int firstTop;
    int secondTop;
    int minTop;
    int value;
};

/*bool ready;
QString result;
QString result1;
QString result2;
QString result3;*/

void deikstra(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& matrixD);
void deikstra(std::vector<std::vector<int>> matrix, int matrixSize, std::pair<int,int>& topWithMax);
int findMaxMin(std::vector<std::vector<int>> matrixD, int& index);
void findExistingRibs(std::vector<std::vector<int>> matrix, std::vector<ribs>& availableRibs, std::vector<std::vector<int>> matrixD);
void findAvailableRibs(std::vector<ribs>& ribs, int upperBound);
void fillNewMatrix(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& newMatrix, ribs activeRib);
QString mainAlghoritm();

/*bool GetReadyAlghoritm(){return ready;}
QString GetResult(){return result;}
QString GetResult2(){return result2;}
QString GetResult3(){return result3;}*/


#endif // ALGHORITMHAKIMI_H
