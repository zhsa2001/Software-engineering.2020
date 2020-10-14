#include "placewindow.h"
#include "ui_placewindow.h"

PlaceWindow::PlaceWindow(QVector<std::shared_ptr<Place> > *vec, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlaceWindow)
{
    ui->setupUi(this);
    model = new placeModel(vec);
    ui->tableView->setModel(model);
}

PlaceWindow::~PlaceWindow()
{
    delete ui;
    delete model;
}

placeModel *PlaceWindow::receiveModel()
{
    return model;
}

void PlaceWindow::on_pushButton_clicked()
{
    QModelIndex in,in1;
    if (ui->tableView->currentIndex().isValid())
    {
        model->insertRows(ui->tableView->currentIndex().row() + 1,1);
        in = model->index(ui->tableView->currentIndex().row() + 1,
                                      0,
                                      ui->tableView->currentIndex().parent());
        in1 = model->index(ui->tableView->currentIndex().row() + 1,
                                       1,
                                       ui->tableView->currentIndex().parent());
    } else {
        model->insertRows(model->rowCount(), 1);
        in = model->index(model->rowCount() - 1,
                                      0,
                                      ui->tableView->currentIndex().parent());
        in1 = model->index(model->rowCount() - 1,
                                       1,
                                       ui->tableView->currentIndex().parent());
    }

    model->setData(in,ui->lineEdit->text(),Qt::EditRole);
    model->setData(in1,ui->textEdit->toPlainText() ,Qt::EditRole);

}

void PlaceWindow::on_pushButton_3_clicked()
{
    if (ui->tableView->currentIndex().isValid())
        model->removeRows(ui->tableView->currentIndex().row(),1);
}
