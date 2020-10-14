#include "placemodel.h"

placeModel::placeModel(QVector<std::shared_ptr<Place>>* vec, QObject *parent)
    : QAbstractTableModel(parent), Places(vec)
{
}

QVariant placeModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            }
    return QVariant();
}

int placeModel::rowCount(const QModelIndex &parent) const
{
    return Places->length();
}

int placeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant placeModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return Places->at(index.row())->name();
            break;
        case 1:
            return Places->at(index.row())->description();
            break;
        }
    }
    return QVariant();
}

bool placeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        // m_gridData[index.row()][index.column()] = value.toString();
        switch (index.column()) {
        case 0:
            Places->at(index.row())->setName(value.toString());
            break;
        case 1:
            Places->at(index.row())->setDescription(value.toString());
            break;
        }
        return true;
    }
}

Qt::ItemFlags placeModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool placeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row, row + count - 1);
    Place* i = new Place;
    std::shared_ptr<Place> p(i);
    Places->insert(row, count, p);
    endInsertRows();
}

bool placeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent,row, row + count - 1);
    Places->remove(row, count);
    endRemoveRows();
}


