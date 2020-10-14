#ifndef HEROWINDOW_H
#define HEROWINDOW_H

#include <QMainWindow>
#include "heromodel.h"

namespace Ui {
class HeroWindow;
}

class HeroWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeroWindow(QVector<std::shared_ptr<Hero>>* vec = new QVector<std::shared_ptr<Hero>>(),QWidget *parent = nullptr);
    ~HeroWindow();

    HeroModel *receiveModel();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::HeroWindow *ui;
    HeroModel* model;
};

#endif // HEROWINDOW_H
