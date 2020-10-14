#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>

namespace Ui {
class BookDialog;
}

class BookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookDialog(QString name = "", double number = 0, int year = 0, QWidget *parent = nullptr);
    ~BookDialog();

    QString name();
    double number();
    int year();

private:
    Ui::BookDialog *ui;
};

#endif // BOOKDIALOG_H
