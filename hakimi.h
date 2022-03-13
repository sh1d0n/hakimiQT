#ifndef HAKIMI_H
#define HAKIMI_H

#include <QMainWindow>
#include "graphwidget.h"
#include "node.h"
#include "alghoritmhakimi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Hakimi; }
QT_END_NAMESPACE

class Hakimi : public QMainWindow
{
    Q_OBJECT

public:
    Hakimi(QWidget *parent = nullptr);
    ~Hakimi();

private slots:

    void on_createNodeButton_clicked();
    void on_selectionChanged(Node *node);

    void on_activeNodeLine_editingFinished();

    void on_deleteButton_clicked();

    void on_createEdgeButton_clicked();

    void on_deleteEdgeButton_clicked();

    void on_edgeWeightLine_editingFinished();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_startButton_clicked();

private:
    Ui::Hakimi *ui;
    GraphWidget *graph;
};
#endif // HAKIMI_H
