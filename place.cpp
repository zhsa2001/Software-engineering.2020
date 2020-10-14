#include "place.h"

Place::Place()
{

}

Place::Place(QString name, QString description)
    :Name(name), Description(description)
{

}

Place::Place(const Place& v)
    :Name(v.Name), Description(v.Description)
{

}

Place::~Place()
{
    Name.clear();
    Description.clear();
}

QString Place::name() const
{
    return Name;
}

QString Place::description() const
{
    return Description;
}

void Place::setName(QString name)
{
    Name = name;
}

void Place::setDescription(QString description)
{
    Description = description;
}

Place& Place::operator =(const Place& v)
{
    this->Name = v.Name;
    this->Description = v.Description;
    return *this;
}

bool Place::operator ==(const Place &v) const
{
    return this->Name == v.Name && this->Description == v.Description;
}

