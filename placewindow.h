#ifndef PLACEWINDOW_H
#define PLACEWINDOW_H

#include <QMainWindow>
#include "placemodel.h"

namespace Ui {
class PlaceWindow;
}

class PlaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaceWindow(QVector<std::shared_ptr<Place>>* vec = new QVector<std::shared_ptr<Place>>(), QWidget *parent = nullptr);
    ~PlaceWindow();

    placeModel *receiveModel();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::PlaceWindow *ui;
    placeModel* model;
};

#endif // PLACEWINDOW_H
