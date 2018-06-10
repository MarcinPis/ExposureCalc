#ifndef ISOPROXYMODEL_H
#define ISOPROXYMODEL_H

#include <QSortFilterProxyModel>


class IsoModel; // forward declaration


class IsoProxyModel : public QSortFilterProxyModel
{
        Q_OBJECT
public:
    IsoProxyModel(IsoModel* model = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const override;
};


#endif // ISOPROXYMODEL_H
