#include "heromodel.h"

HeroModel::HeroModel(QVector<std::shared_ptr<Hero>>* vec,QObject *parent)
    : QAbstractTableModel(parent), Heroes(vec)
{
}

QVariant HeroModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        if (orientation == Qt::Horizontal)
            switch (section){
            case 0:
                return tr("Имя");
                break;
            case 1:
                return tr("Вид");
                break;
            case 2:
                return tr("Положительный");
                break;
            case 3:
                return tr("Описание");
                break;
            }
    return QVariant();
}

int HeroModel::rowCount(const QModelIndex &parent) const
{
    return Heroes->length();
}

int HeroModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant HeroModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return Heroes->at(index.row())->name();
            break;
        case 1:
            return Heroes->at(index.row())->kind();
            break;
        case 2:
            return Heroes->at(index.row())->isPositive();
            break;
        case 3:
            return Heroes->at(index.row())->description();
            break;
        }
    }
    return QVariant();
}

bool HeroModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        // m_gridData[index.row()][index.column()] = value.toString();
        switch (index.column()) {
        case 0:
            Heroes->at(index.row())->setName(value.toString());
            break;
        case 1:
            Heroes->at(index.row())->setKind(value.toString());
            break;
        case 2:
            Heroes->at(index.row())->setPositive(value.toBool());
//            Heroes->at(index.row())->setPositive((value.toString()==NULL)? 0:1);
            break;
        case 3:
            Heroes->at(index.row())->setDescription(value.toString());
            break;
        }
        return true;
    }
}

Qt::ItemFlags HeroModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool HeroModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row, row + count - 1);
    Hero* i = new Hero;
    std::shared_ptr<Hero> p(i);
    Heroes->insert(row, count, p);
    endInsertRows();
}

bool HeroModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent,row, row + count - 1);
    Heroes->remove(row, count);
    endRemoveRows();
}



