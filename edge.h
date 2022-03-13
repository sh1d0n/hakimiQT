#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

//! [0]
class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode);

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();
    void SetWeight(int weight){edgeWeight = weight;}
    void SetNodes(int nodeID1, int nodeID2){nodes.first = nodeID1; nodes.second = nodeID2;}

    QString edgeNodesText(){return ("(" + QString::number(nodes.first) + ";" + QString::number(nodes.second) + ")");}

    int edgeNode1(){return nodes.first;}
    int edgeNode2(){return nodes.second;}

    int GetWeight(){return edgeWeight;}

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    QPair<int, int> nodes;
    int edgeWeight;
    qreal arrowSize = 10;
};
//! [0]

#endif // EDGE_H
