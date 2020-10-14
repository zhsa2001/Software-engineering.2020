#include "bookdialog.h"
#include "ui_bookdialog.h"

BookDialog::BookDialog(QString name, double number, int year, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDialog)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->number->setRange(0,100);
    ui->number->setValue(number);
    ui->year->setRange(0,2100);
    ui->year->setValue(year);
}

BookDialog::~BookDialog()
{
    delete ui;
}

QString BookDialog::name()
{
    return ui->name->text();
}

double BookDialog::number()
{
    return ui->number->value();
}

int BookDialog::year()
{
    return ui->year->value();
}
