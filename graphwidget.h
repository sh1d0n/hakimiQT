#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;
class Edge;

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);

    void itemMoved();
    void createNode();
    void createEdge(int nodeID1, int nodeID2);
    void SetSelection(Node *node);
    Node* GetSelectionNode(){return currentSelection;}
    Edge* GetEdge(){return edges.back();}
    void DeleteNode(int nodeID);
    QString GetEdgeText(){return forEdge;}
    void DeleteEdge(QString edgeText);
    void SetEdgeWeight(QString edgeText, int weight);
    int GetEdgeWeight(const QString &edgeText);
    bool GetCanCreate(){return canCreate;}


    //for alghoritm
    QVector<Node*> GetNodes(){return nodes;}
    QVector<Edge*> GetEdges(){return edges;}
    Edge* GetNeedEdge(int i){return edges[i];}

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

signals:
    void selectionChange(Node *node);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    //void drawBackground(QPainter *painter, const QRectF &rect) override;

    void resizeEvent(QResizeEvent *event) override;

    void scaleView(qreal scaleFactor);



private:
    int timerId = 0;
    QVector<Node*> nodes;
    QVector<Edge*> edges;
    Node *centerNode;
    QGraphicsScene *scene;
    Node *currentSelection;
    QString forEdge;
    bool canCreate = false;
};
//! [0]

#endif // GRAPHWIDGET_H
