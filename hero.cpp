#include "hero.h"

Hero::Hero()
{

}

Hero::Hero(QString name, QString kind, bool positive, QString description)
    :Name(name), Kind(kind), Description(description), Positive(positive)
{

}

Hero::Hero(const Hero& v)
    :Name(v.Name), Kind(v.Kind), Description(v.Description), Positive(v.Positive)
{

}

Hero::~Hero()
{
    Name.clear();
    Kind.clear();
    Description.clear();
}

QString Hero::name() const
{
    return Name;
}

QString Hero::kind() const
{
    return Kind;
}

QString Hero::description() const
{
    return Description;
}

bool Hero::isPositive() const
{
    return Positive;
}

void Hero::setName(QString name)
{
    Name = name;
}

void Hero::setKind(QString kind)
{
    Kind = kind;
}

void Hero::setDescription(QString description)
{
    Description = description;
}

void Hero::setPositive(bool positive)
{
    Positive = positive;
}

Hero& Hero::operator =(const Hero& v)
{
    this->Name = v.Name;
    this->Kind = v.Kind;
    this->Description = v.Description;
    this->Positive = v.Positive;
    return *this;
}

bool Hero::operator ==(const Hero &v) const
{
    return this->Kind == v.Kind && this->Name == v.Name && this->Positive
            == v.Positive && this->Description == v.Description;
}
