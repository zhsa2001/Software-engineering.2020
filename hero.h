#ifndef HERO_H
#define HERO_H

#include <QString>

class Hero
{
    QString Name = "", Kind = "", Description = "";
    bool Positive = 1;
public:
    Hero();
    Hero(QString name, QString kind, bool positive, QString description);
    Hero(const Hero&);

    ~Hero();

    QString name() const;
    QString kind() const;
    QString description() const;
    bool isPositive() const;
    void setName(QString);
    void setKind(QString);
    void setDescription(QString);
    void setPositive(bool);
    Hero& operator =(const Hero&);
    bool operator ==(const Hero&) const;
};

#endif // HERO_H
