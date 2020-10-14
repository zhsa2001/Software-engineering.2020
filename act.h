#ifndef ACT_H
#define ACT_H

#include "hero.h"
#include "place.h"
#include <QVector>
//#include <QString>
#include <memory>

class Act
{
    QVector<std::weak_ptr<Hero>> Heroes;
    QVector<std::weak_ptr<Place>> Places;
    QString Name = "", Description = "", Result = "";
    //int Number = 0;
public:
    Act();
    Act(QString name, QString description, QString result/*, int number*/);
    Act(const Act&);

    ~Act();
    void addPlace(std::shared_ptr<Place>);
    void addHero(std::shared_ptr<Hero>);
    void removePlace(int number);
    void removeHero(int number);
    int heroesQuantity() const;
    int placesQuantity() const;
    Hero hero(int number) const;
    Place place(int number) const;
    int heroNumber(const QString& name) const;
    int placeNumber(const QString& name) const;
    //QVector<std::weak_ptr<Hero>> heroes();
    //QVector<std::weak_ptr<Place>> places();
    QString name() const;
    QString description() const;
    QString result() const;
//    int number();
    void setName(QString);
    void setDescription(QString);
    void setResult(QString);
//    void setNumber(int);
    void setHeroes(const QVector<std::weak_ptr<Hero>>&);
    void setPlaces(const QVector<std::weak_ptr<Place>>&);
    bool operator ==(const Act&) const;
    Act& operator =(const Act&);
};

#endif // ACT_H
