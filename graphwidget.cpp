#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-width()*5, -height()*5, width()*5, height()*5);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));
//! [0]

//! [1]
    /*scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));
    scene->addItem(new Edge(node2, centerNode));
    scene->addItem(new Edge(node3, node6));
    scene->addItem(new Edge(node4, node1));
    scene->addItem(new Edge(node4, centerNode));
    scene->addItem(new Edge(centerNode, node6));
    scene->addItem(new Edge(centerNode, node8));
    scene->addItem(new Edge(node6, node9));
    scene->addItem(new Edge(node7, node4));
    scene->addItem(new Edge(node8, node7));
    scene->addItem(new Edge(node9, node8));*/
}
//! [1]

//! [2]
void GraphWidget::itemMoved()
{
    /*if (!timerId)
        timerId = startTimer(1000 / 25);*/
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    /*Q_UNUSED(event);

    QList<Node *> nodes;
    const QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    for (Node *node : qAsConst(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (Node *node : qAsConst(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }*/
}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}
//! [5]
#endif

//! [6]
/*void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}*/
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]
void GraphWidget::shuffle()
{
    const QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::resizeEvent(QResizeEvent *event)
{

    //fitInView(sceneRect(), Qt::KeepAspectRatio);

    QGraphicsView::resizeEvent(event);
}

void GraphWidget::createNode()
{
    int max = 0;
    for(Node* node : nodes)
    {
        if(max < node->GetID())
        {
            max = node->GetID();
        }
    }
    nodes.push_back(new Node(this));
    nodes.back()->SetID(max + 1);
    scene->addItem(nodes[nodes.size()-1]);
    nodes[nodes.size()- 1]->setPos(0, 0);
}

void GraphWidget::createEdge(int nodeID1, int nodeID2)
{
    scene->addItem(new Edge(nodes[nodeID1 - 1], nodes[nodeID2 - 1]));
    int i = 0;
    if(!edges.empty())
    {
        for(Edge* edge : edges)
        {
            if((edge->edgeNode1() != nodeID1 || edge->edgeNode2() != nodeID2)&&(edge->edgeNode1() != nodeID2 || edge->edgeNode2() != nodeID1))
            {

            }
            else
            {
                i++;
            }
        }
    }

    if(i == 0)
    {
        edges.push_back(currentSelection->GetEdge());
        edges.back()->SetNodes(nodeID1, nodeID2);
        forEdge = edges.back()->edgeNodesText();
        edges.back()->SetWeight(0);
        canCreate = true;
    }
    else
    {
        scene->removeItem(currentSelection->GetEdge());
        canCreate = false;
    }
}

void GraphWidget::SetSelection(Node *node)
{
    currentSelection = node;
    emit selectionChange(currentSelection);
}

void GraphWidget::DeleteNode(int nodeID)
{
    scene->removeItem(nodes[nodeID - 1]);
    nodes.erase(nodes.begin() + nodeID - 1);

    int ID = 0;
    for(Node* node : nodes)
    {
        if(ID + 2 == node->GetID())
        {
            node->SetID(ID + 1);
        }
        ID++;
    }
}

void GraphWidget::DeleteEdge(QString edgeText)
{
    int i = 0;
    for(Edge* edge : edges)
    {
        if(edgeText == edge->edgeNodesText())
        {
            scene->removeItem((edge));
            edges.erase(edges.begin() + i);
        }
        i++;
    }
}

void GraphWidget::SetEdgeWeight(QString edgeText, int weight)
{
    for(Edge* edge : edges)
    {
        if(edgeText == edge->edgeNodesText())
        {
            edge->SetWeight(weight);
        }
    }
}

int GraphWidget::GetEdgeWeight(const QString &edgeText)
{
    for(Edge* edge: edges)
    {
        if(edgeText == edge->edgeNodesText())
        {
            return edge->GetWeight();
        }
    }
}

