#ifndef PLACE_H
#define PLACE_H

#include <QString>

class Place
{
    QString Name = "", Description = "";
public:
    Place();
    Place(QString name, QString description);
    Place(const Place&);

    ~Place();
    QString name() const;
    QString description() const;
    void setName(QString);
    void setDescription(QString);
    Place& operator =(const Place&);
    bool operator ==(const Place&) const;
};

#endif // PLACE_H
