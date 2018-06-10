#ifndef SHUTTERPROXYMODEL_H
#define SHUTTERPROXYMODEL_H

#include <QSortFilterProxyModel>


class ShutterModel; // forward declaration


class ShutterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ShutterProxyModel(ShutterModel* model = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const override;
};

#endif // SHUTTERPROXYMODEL_H
