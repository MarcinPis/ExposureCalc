#ifndef APERTUREPROXYMODEL_H
#define APERTUREPROXYMODEL_H

#include <QSortFilterProxyModel>


class ApertureModel; // forward declaration


class ApertureProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ApertureProxyModel(ApertureModel* model = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const override;
};

#endif // APERTUREPROXYMODEL_H
