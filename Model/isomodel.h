#ifndef ISOMODEL_H
#define ISOMODEL_H

#include <QAbstractListModel>
#include <QVector>

struct IsoSpeed
{
    double stopValue;
    double presiceIso;
    QString nominalIso;
    int stopInfo;
};


class IsoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit IsoModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    enum {
        isoRole_stopValue = 100,
        isoRole_preciseIso,
        isoRole_nominalIso,
        isoRole_stopInfo,
    };

    virtual QHash<int, QByteArray> roleNames() const override;

    QString getNominalIso(const double& stopValue);

public slots:
    void dataChangedEmiter();

private:
    QVector<IsoSpeed> mIsoSpeedList;

};

#endif // ISOMODEL_H
