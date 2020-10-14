#ifndef PLACEMODEL_H
#define PLACEMODEL_H

#include <QAbstractTableModel>
#include "place.h"
#include <memory>

class placeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit placeModel(QVector<std::shared_ptr<Place>>* vec = new QVector<std::shared_ptr<Place>>(), QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role =
            Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent =
            QModelIndex()) override;
     bool removeRows(int row, int count, const QModelIndex &parent =
             QModelIndex()) override;


private:
    QVector<std::shared_ptr<Place>>* Places;
};

#endif // PLACEMODEL_H
