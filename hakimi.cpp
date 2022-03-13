#include "hakimi.h"
#include "ui_hakimi.h"
#include "graphwidget.h"
#include "alghoritmhakimi.h"

Hakimi::Hakimi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hakimi)
{
    ui->setupUi(this);

    graph = new GraphWidget(this);
    ui->verticalLayout->addWidget(graph);
    connect(graph, &GraphWidget::selectionChange, this, &Hakimi::on_selectionChanged);
}

Hakimi::~Hakimi()
{
    delete ui;
}


void Hakimi::on_createNodeButton_clicked()
{
     graph->createNode();
}

void Hakimi::on_selectionChanged(Node *node)
{
    ui->activeNodeLine->setText(QString::number(node->GetID()));
}

void Hakimi::on_activeNodeLine_editingFinished()
{
    graph->GetSelectionNode()->SetID(ui->activeNodeLine->text().toInt());
}


void Hakimi::on_deleteButton_clicked()
{
    graph->DeleteNode(ui->activeNodeLine->text().toInt());
    ui->activeNodeLine->clear();
}


void Hakimi::on_createEdgeButton_clicked()
{
    graph->createEdge(ui->activeNodeLine->text().toInt(), ui->nearbyNodeLine->text().toInt());
    if(graph->GetCanCreate() == true)
    {
        ui->comboBox->addItem(graph->GetEdgeText());
    }
}


void Hakimi::on_deleteEdgeButton_clicked()
{
    graph->DeleteEdge(ui->comboBox->currentText());
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
}


void Hakimi::on_edgeWeightLine_editingFinished()
{
    int weight = ui->edgeWeightLine->text().toInt();
    graph->SetEdgeWeight(ui->comboBox->currentText(), weight);
}


void Hakimi::on_comboBox_currentTextChanged(const QString &arg1)
{
    int weight = graph->GetEdgeWeight(arg1);
    ui->edgeWeightLine->setText(QString::number(weight));
}


void Hakimi::on_startButton_clicked()
{
    QString result;
    result = mainAlghoritm();

    ui->resultLine->setText(result);
}

