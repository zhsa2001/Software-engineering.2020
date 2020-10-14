#include "actmodel.h"

ActModel::ActModel(QVector<Act> acts, QObject *parent)
    : QAbstractTableModel(parent), Acts(acts)
{
}

QVariant ActModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        if (orientation == Qt::Horizontal)
            switch (section){
            case 0:
                return tr("Название");
                break;
            case 1:
                return tr("Описание");
                break;
            case 2:
                return tr("Участники");
                break;
            case 3:
                return tr("Места");
                break;
            case 4:
                return tr("Итог");
                break;
            }
    else if (orientation == Qt::Vertical)
            return QString::number(section + 1);
    return QVariant();
}

int ActModel::rowCount(const QModelIndex &parent) const
{
    return Acts.length();
}

int ActModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant ActModel::data(const QModelIndex &index, int role) const
{
    QStringList heroes;
    QStringList places;
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return Acts.at(index.row()).name();
            break;
        case 1:
            return Acts.at(index.row()).description();
            break;
        case 2:
            for (int i = 0; i < Acts.at(index.row()).heroesQuantity();i++) {
                if (Acts.at(index.row()).hero(i + 1).name() != "")
                    heroes << Acts.at(index.row()).hero(i + 1).name();
            }
            return heroes.join(",");
            break;
        case 3:
            for (int i = 0; i < Acts.at(index.row()).placesQuantity();i++) {
                if (Acts.at(index.row()).place(i + 1).name() != "")
                    places << Acts.at(index.row()).place(i + 1).name();
            }
            return places.join(",");
            break;
        case 4:
            return Acts.at(index.row()).result();
            break;
        }
    }
    return QVariant();
}

bool ActModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        // m_gridData[index.row()][index.column()] = value.toString();
        switch (index.column()) {
        case 0:
            Acts[index.row()].setName(value.toString());
            return true;
        case 1:
            Acts[index.row()].setDescription(value.toString());
            return true;
        case 4:
            Acts[index.row()].setResult(value.toString());
            return true;
        }
        return false;
    }
}

void ActModel::addPlace(const QModelIndex &index, std::shared_ptr<Place> place, int role)
{
    if (role == Qt::EditRole)
    {
        Acts[index.row()].addPlace(place);
    }
}

void ActModel::addHero(const QModelIndex &index, std::shared_ptr<Hero> hero, int role)
{
    if (role == Qt::EditRole)
    {
        Acts[index.row()].addHero(hero);
    }
}

void ActModel::removeHero(const QModelIndex &index, QString hero, int role)
{
    if (role == Qt::EditRole)
    {
        if (hero == "all")
            for (int i = 0; i < Acts.at(index.row()).heroesQuantity(); i++) {
                Acts[i].removeHero(i+1);
            }
        else {
            int num = Acts[index.row()].heroNumber(hero);
            Acts[index.row()].removeHero(num);
        }
    }
}

void ActModel::removePlace(const QModelIndex &index, QString place, int role)
{
    if (role == Qt::EditRole)
    {
        if (place == "all")
            for (int i = 0; i < Acts.at(index.row()).placesQuantity(); i++) {
                Acts[i].removePlace(i+1);
            }
        else {
            int num = Acts[index.row()].placeNumber(place);
            Acts[index.row()].removePlace(num);
        }
    }
}

Qt::ItemFlags ActModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool ActModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row, row + count - 1);
    Acts.insert(row, count, Act());
    endInsertRows();
}

bool ActModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent,row, row + count - 1);
    Acts.remove(row, count);
    endRemoveRows();
}

QVector<Act> ActModel::acts()
{
    return Acts;
}
