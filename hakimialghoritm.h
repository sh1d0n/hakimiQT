#ifndef HAKIMIALGHORITM_H
#define HAKIMIALGHORITM_H

#include <QGraphicsView>

class hakimiAlghoritm
{
public:
    hakimiAlghoritm();

    bool GetReadyAlghoritm(){return ready;}
    QString GetResult(){return result;}
    QString GetResult2(){return result2;}
    QString GetResult3(){return result3;}
    hakimiAlghoritm* hakimi;

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

    void deikstra(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& matrixD);
    void deikstra(std::vector<std::vector<int>> matrix, int matrixSize, std::pair<int,int>& topWithMax);
    int findMaxMin(std::vector<std::vector<int>> matrixD, int& index);
    void findExistingRibs(std::vector<std::vector<int>> matrix, std::vector<ribs>& availableRibs, std::vector<std::vector<int>> matrixD);
    void findAvailableRibs(std::vector<ribs>& ribs, int upperBound);
    void fillNewMatrix(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>>& newMatrix, ribs activeRib);

protected:
    bool ready;
    QString result;
    QString result2;
    QString result3;
};

#endif // HAKIMIALGHORITM_H
