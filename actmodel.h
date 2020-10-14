#ifndef ACTMODEL_H
#define ACTMODEL_H

#include <QAbstractTableModel>
#include "act.h"

class ActModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ActModel(QVector<Act> acts,QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role =
            Qt::EditRole) override;
    void addPlace(const QModelIndex &index, std::shared_ptr<Place>, int role =
            Qt::EditRole);
    void addHero(const QModelIndex &index, std::shared_ptr<Hero>, int role =
            Qt::EditRole);
    void removeHero(const QModelIndex &index, QString hero = "all", int role = Qt::EditRole);
    void removePlace(const QModelIndex &index, QString place = "all",int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent =
            QModelIndex()) override;
     bool removeRows(int row, int count, const QModelIndex &parent =
             QModelIndex()) override;
     QVector<Act> acts();

private:
    QVector<Act> Acts;
};

#endif // ACTMODEL_H
