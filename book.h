#ifndef BOOK_H
#define BOOK_H

#include "act.h"

class Book
{
    QVector<Act> Acts;
    QString Name = "";
    double Number;
    int Year;
public:
    Book();
    Book(QString name, double number, int year);
    Book(const Book&);

    ~Book();
    void addAct(const Act, int number);
    void removeAct(int number);
    QVector<Act> acts();
    void setActs(const QVector<Act>);
    QString name() const;
    void setName(QString name);
    double number() const;
    void setNumber(double number);
    int year() const;
    void setYear(int year);
};

#endif // BOOK_H
