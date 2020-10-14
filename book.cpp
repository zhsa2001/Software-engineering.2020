#include "book.h"
#include <iostream>

Book::Book()
{

}

Book::Book(QString name, double number, int year)
    :Name(name), Number(number), Year(year)
{

}

Book::Book(const Book& v)
    :Name(v.Name), Number(v.Number), Year(v.Year)
{
    setActs(v.Acts);
}

Book::~Book()
{
    Name.clear();
    QVector<Act>().swap(Acts);
}

void Book::addAct(const Act v, int number)
{
    if (!(number < 1 || number > Acts.size() + 1)){
        Acts.insert(number - 1,v);
    }

}

void Book::removeAct(int number)
{
    if (!(number < 1 || number > Acts.size() + 1))
        Acts.erase(Acts.begin()+number-1);
}

QVector<Act> Book::acts()
{
    return Acts;
}

void Book::setActs(const QVector<Act> v)
{
    QVector<Act>().swap(Acts);
    Acts.append(v);
}

QString Book::name() const
{
    return Name;
}

void Book::setName(QString name)
{
    Name = name;
}

double Book::number() const
{
    return Number;
}

void Book::setNumber(double number)
{
    Number = number;
}

int Book::year() const
{
    return Year;
}

void Book::setYear(int year)
{
    Year = year;
}
