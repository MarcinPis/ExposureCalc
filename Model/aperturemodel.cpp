#include "aperturemodel.h"
#include <algorithm>
#include <QSettings>

ApertureModel::ApertureModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mApertureList = {
        {0.0, 1, "1.0", 1},
        {0.33, 1.12246, "1.1", 3},
        {0.67, 1.25992, "1.2", 3},
        {1.0, 1.41421, "1.4", 1},
        {1.33, 1.5874, "1.6", 3},
        {1.67, 1.7818, "1.8", 3},
        {2.0, 2, "2.0", 1},
        {2.33, 2.24492, "2.2", 3},
        {2.67, 2.51984, "2.5", 3},
        {3.0, 2.82843, "2.8", 1},
        {3.33, 3.1748, "3.2", 3},
        {3.67, 3.56359, "3.5", 3},
        {4.0, 4, "4.0", 1},
        {4.33, 4.48985, "4.5", 3},
        {4.67, 5.03968, "5.0", 3},
        {5.0, 5.65685, "5.6", 1},
        {5.33, 6.3496, "6.3", 3},
        {5.67, 7.12719, "7.1", 3},
        {6.0, 8, "8.0", 1},
        {6.33, 8.9797, "9.0", 3},
        {6.67, 10.0794, "10", 3},
        {7.0, 11.3137, "11", 1},
        {7.33, 12.6992, "13", 3},
        {7.67, 14.2544, "14", 3},
        {8.0, 16, "16", 1},
        {8.33, 17.9594, "18", 3},
        {8.67, 20.1587, "20", 3},
        {9.0, 22.6274, "22", 1},
        {9.33, 25.3984, "25", 3},
        {9.67, 28.5088, "29", 3},
        {10.0, 32, "32", 1},
        {10.33, 35.9188, "36", 3},
        {10.67, 40.3175, "40", 3},
        {11.0, 45.2548, "45", 1},
        {11.33, 50.7968, "50", 3},
        {11.67, 57.0175, "60", 3},
        {12.0, 64, "64", 1},
        {12.33, 71.8376, "72", 3},
        {12.67, 80.6349, "80", 3},
        {13.0, 90.5097, "90", 1},
        {13.33, 101.594, "100", 3},
        {13.67, 114.035, "115", 3},
        {14.0, 128, "128", 1},
        {14.33, 143.675, "144", 3},
        {14.67, 161.27, "160", 3},
        {15.0, 181.019, "180", 1},
        {15.33, 203.187, "200", 3},
        {15.67, 228.07, "230", 3},
        {16.0, 256, "256", 1},
    };
}

int ApertureModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }

    return mApertureList.count();
}

QVariant ApertureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const ApertureSpeed item = mApertureList[index.row()];

    switch(role)
    {
    case aperatureRole_stopValue:
        return QVariant(item.stopValue);
    case apertureRole_preciseAperture:
        return QVariant(item.presiceAperture);
    case apertureRole_nominalAperture:
        return QVariant(item.nominalAperture);
    case apertureRole_stopInfo:
        return QVariant(item.stopInfo);
    }
    return QVariant();
}

QHash<int, QByteArray> ApertureModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[aperatureRole_stopValue] = "stopValue";
    names[apertureRole_preciseAperture] = "aperturePrecise";
    names[apertureRole_nominalAperture] = "apertureNominal";
    names[apertureRole_stopInfo] = "apertureInfo";

    return names;
}

QString ApertureModel::getNominalValue(const double &stopValue)
{
    auto result = std::find_if(mApertureList.begin(), mApertureList.end(),
                               // Make that lambada
                               [stopValue](ApertureSpeed& ap) { return ap.stopValue == stopValue; }
            );

    bool found = (result != std::end(mApertureList));

    if(found)
    {
        int indexArray = result - mApertureList.begin();
        return mApertureList[indexArray].nominalAperture;
    }
    else
    {
        return "error";
    }
}

void ApertureModel::dataChangedEmiter()
{
    emit dataChanged(index(0, 0), index(rowCount()-1, 0));
}
