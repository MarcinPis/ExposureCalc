#ifndef APERTUREMODEL_H
#define APERTUREMODEL_H

#include <QAbstractListModel>
#include <QVector>


struct ApertureSpeed
{
    double stopValue;
    double presiceAperture;
    QString nominalAperture;
    int stopInfo;
};


class ApertureModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ApertureModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    enum {
        aperatureRole_stopValue = 100,
        apertureRole_preciseAperture,
        apertureRole_nominalAperture,
        apertureRole_stopInfo,
    };

    virtual QHash<int, QByteArray> roleNames() const override;

    QString getNominalValue(const double& stopValue);

public slots:
    void dataChangedEmiter();

private:
    QVector<ApertureSpeed> mApertureList;

};

#endif // APERTUREMODEL_H
