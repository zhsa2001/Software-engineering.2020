#ifndef HEROMODEL_H
#define HEROMODEL_H

#include <QAbstractTableModel>
#include "hero.h"
#include <memory>

class HeroModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HeroModel(QVector<std::shared_ptr<Hero>>* vec = new QVector<std::shared_ptr<Hero>>(), QObject *parent = nullptr);

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
    QVector<std::shared_ptr<Hero>>* Heroes;
};

#endif // HEROMODEL_H
