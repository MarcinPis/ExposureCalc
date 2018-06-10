#include "filtermodel.h"
#include <QSettings>

FilterModel::FilterModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mFilterSpeedList = {
        {0, "0", "0"},
        {1, "0.3 ND", "ND2"},
        {2, "0.6 ND", "ND4"},
        {3, "0.9 ND", "ND8"},
        {4, "1.2 ND", "ND16"},
        {5, "1.5 ND", "ND32"},
        {6, "1.8 ND", "ND64"},
        {6.67, "2.0 ND", "ND100"},
        {7, "2.1 ND", "ND128"},
        {8, "2.4 ND", "ND256"},
        {8.67, "2.6 ND", "ND400"},
        {9, "2.7 ND", "ND512"},
        {10, "3.0 ND", "ND1024"},
        {11, "3.3 ND", "ND2048"},
        {12, "3.6 ND", "ND4096"},
        {12.67, "3.8 ND", "ND6310"},
        {13, "3.9 ND", "ND8192"},
        {13.33, "4.0 ND", "ND10000"},
        {16.67, "5.0 ND", "ND100000"},
    };
}

int FilterModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mFilterSpeedList.count();
}

QVariant FilterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const FilterValues item = mFilterSpeedList[index.row()];

    switch (role)
    {
    case filterRole_stopValue:
        return QVariant(item.stopValue);
    case filterRole_leeNotation:
        return QVariant(item.leeNotation);
    case filterRole_cokinNotation:
        return QVariant(item.cokinNotation);
    }

    return QVariant();
}

QHash<int, QByteArray> FilterModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[filterRole_stopValue] = "stopValue";
    names[filterRole_leeNotation] = "filterLee";
    names[filterRole_cokinNotation] = "filterCokin";

    return names;
}

void FilterModel::dataChangedEmiter()
{
    QSettings filterSettings;
    filterSettings.beginGroup("scales");
    int filterScaleIndex = filterSettings.value("filterScaleIndex").toInt();
    filterSettings.endGroup();


    QString filterScaleSetup;
    if(filterScaleIndex == 1)
    {
        filterScaleSetup = "filterCokin";
    }
    else if(filterScaleIndex == 2)
    {
        filterScaleSetup = "filterLee";
    }
    else if(filterScaleIndex == 3)
    {
        filterScaleSetup = "stopValue";
    }

    emit filterSettingsChanged(filterScaleSetup);
}
