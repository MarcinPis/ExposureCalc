#ifndef SHUTTERMODEL_H
#define SHUTTERMODEL_H

#include <QAbstractListModel>
#include <QVector>


struct ShutterSpeed
{
    double stopValue;
    double preciseSeconds;
    QString nominalSeconds;
    int stopInfo;
};


class ShutterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ShutterModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    enum {
        shutterRole_stopValue = 100,
        shutterRole_preciseSeconds,
        shutterRole_nominalSeconds,
        shutterRole_stopInfo,
    };

    virtual QHash<int, QByteArray> roleNames() const override;

    QString getNominalShutter(const double& stopValue);

public slots:
    void dataChangedEmiter();

private:
    QVector<ShutterSpeed> mShutterSpeedList;

};

#endif // SHUTTERMODEL_H
