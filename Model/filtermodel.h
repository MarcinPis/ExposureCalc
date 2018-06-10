#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QAbstractListModel>
#include <QVector>



struct FilterValues
{
    double stopValue;
    QString leeNotation;
    QString cokinNotation;
};


class FilterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FilterModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    enum {
        filterRole_stopValue = 100,
        filterRole_leeNotation,
        filterRole_cokinNotation,
    };

    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void filterSettingsChanged(QString Value);

public slots:
    void dataChangedEmiter();

private:
    QVector<FilterValues> mFilterSpeedList;
};

#endif // FILTERMODEL_H
