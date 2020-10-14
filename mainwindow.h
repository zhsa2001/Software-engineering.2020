#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "book.h"
#include "actmodel.h"
#include "placewindow.h"
#include "herowindow.h"
#include "bookdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_forward_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_back_clicked();

    void on_actionAddBook_triggered();

    void on_actionDeleteBook_triggered();

    void on_actionEditBook_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Book> books;
    QVector<std::shared_ptr<Place>> Places;
    QVector<std::shared_ptr<Hero>> Heroes;
    PlaceWindow* placeWindow;
    HeroWindow* heroWindow;
    ActModel* model;
    int currentBook = 0;
    //ActModel* acts;

    void showBook();
};

#endif // MAINWINDOW_H
