#include "act.h"

Act::Act()
{

}

Act::Act(QString name, QString description, QString result/*, int number*/)
    :Name(name), Description(description), Result(result)/*, Number(number)*/
{

}

Act::Act(const Act& v)
    :Name(v.Name), Description(v.Description), Result(v.Result)/*, Number(v.Number)*/
{
    setPlaces(v.Places);
    setHeroes(v.Heroes);
}

Act::~Act()
{
    Name.clear();
    Description.clear();
    Result.clear();
    QVector<std::weak_ptr<Hero>>().swap(Heroes);
    QVector<std::weak_ptr<Place>>().swap(Places);
}

void Act::addPlace(std::shared_ptr<Place> v)
{
    Places.push_back(std::weak_ptr<Place>(v));
}

void Act::addHero(std::shared_ptr<Hero> v)
{
    Heroes.push_back(std::weak_ptr<Hero>(v));
}

void Act::removePlace(int number)
{
    if (!(number < 1 || number > Places.size()))
        Places.erase(Places.begin()+number-1);
}

void Act::removeHero(int number)
{
    if (!(number < 1 || number > Heroes.size()))
        Heroes.erase(Heroes.begin()+number-1);
}

int Act::heroesQuantity() const
{
    return Heroes.length();
}

int Act::placesQuantity() const
{
    return Places.length();
}

Hero Act::hero(int number) const
{
    if (!(number < 1 || number > Heroes.size()))
        if (Heroes[number - 1].lock() != nullptr)
            return *Heroes[number - 1].lock();
    return Hero();
}

Place Act::place(int number) const
{
    if (!(number < 1 || number > Places.size()))
        if (Places[number - 1].lock() != nullptr)
            return *Places[number - 1].lock();
    return Place();
}

int Act::heroNumber(const QString &name) const
{
    for (int i = 0; i < Heroes.length(); i++) {
        if (Heroes.at(i).lock() != nullptr)
            if (Heroes.at(i).lock()->name() == name)
                return i+1;
    }
    return -1;
}

int Act::placeNumber(const QString &name) const
{
    for (int i = 0; i < Places.length(); i++) {
        if (Places.at(i).lock() != nullptr)
            if (Places.at(i).lock()->name() == name)
                return i+1;
    }
    return -1;
}


QString Act::name() const
{
    return Name;
}

QString Act::description() const
{
    return Description;
}

QString Act::result() const
{
    return Result;
}

//int Act::number()
//{
//    return Number;
//}

void Act::setName(QString name)
{
    Name = name;
}

void Act::setDescription(QString description)
{
    Description = description;
}

void Act::setResult(QString result)
{
    Result = result;
}

//void Act::setNumber(int number)
//{
//    Number = number;
//}

void Act::setHeroes(const QVector<std::weak_ptr<Hero> > &v)
{
    Heroes.clear();
    Heroes.squeeze();
    Heroes.append(v);
}

void Act::setPlaces(const QVector<std::weak_ptr<Place> > &v)
{
    Places.clear();
    Places.squeeze();
    Places.append(v);
}

bool Act::operator ==(const Act &v) const
{
    bool p = 1;
    //if ()
    for (int i = 0; i < this->Heroes.length();i++) {
        p &= (this->hero(1) == v.hero(i))? 1:0;
    }
    for (int i = 0; i < this->Heroes.length();i++) {
        p &= (this->place(1) == v.place(i))? 1:0;
    }
    return this->Name == v.Name && p && this->Description == v.Description;
}

Act &Act::operator =(const Act &v)
{
    this->Name = v.Name;
    this->Heroes = v.Heroes;
    this->Places = v.Places;
    this->Description = v.Description;
    return *this;
}
