#include "herowindow.h"
#include "ui_herowindow.h"

HeroWindow::HeroWindow(QVector<std::shared_ptr<Hero>>* vec, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeroWindow)
{
    ui->setupUi(this);
    model = new HeroModel(vec);
    ui->tableView->setModel(model);
}

HeroWindow::~HeroWindow()
{
    delete ui;
    delete model;
}

HeroModel *HeroWindow::receiveModel()
{
    return model;
}

void HeroWindow::on_pushButton_clicked()
{
    QModelIndex in,in1,in2,in3;
    if (ui->tableView->currentIndex().isValid())
    {
        model->insertRows(ui->tableView->currentIndex().row() + 1,1);
        in = model->index(ui->tableView->currentIndex().row() + 1,
                                      0,
                                      ui->tableView->currentIndex().parent());
        in1 = model->index(ui->tableView->currentIndex().row() + 1,
                                       1,
                                       ui->tableView->currentIndex().parent());
        in2 = model->index(ui->tableView->currentIndex().row() + 1,
                                       2,
                                       ui->tableView->currentIndex().parent());
        in3 = model->index(ui->tableView->currentIndex().row() + 1,
                                       3,
                                       ui->tableView->currentIndex().parent());
    } else {
        model->insertRows(model->rowCount(), 1);
        in = model->index(model->rowCount() - 1,
                                      0,
                                      ui->tableView->currentIndex().parent());
        in1 = model->index(model->rowCount() - 1,
                                       1,
                                       ui->tableView->currentIndex().parent());
        in2 = model->index(model->rowCount() - 1,
                                       2,
                                       ui->tableView->currentIndex().parent());
        in3 = model->index(model->rowCount() - 1,
                                       3,
                                       ui->tableView->currentIndex().parent());
    }

    model->setData(in,ui->lineEdit->text(),Qt::EditRole);
    model->setData(in1,ui->lineEdit_2->text() ,Qt::EditRole);
    model->setData(in2, /*bool positive =*/ ui->spinBox->value(), Qt::EditRole);
    model->setData(in3,ui->textEdit->toPlainText(),Qt::EditRole);

}

void HeroWindow::on_pushButton_3_clicked()
{
    if (ui->tableView->currentIndex().isValid())
        model->removeRows(ui->tableView->currentIndex().row(),1);
}

