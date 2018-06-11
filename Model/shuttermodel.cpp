#include "shuttermodel.h"
#include <algorithm>
#include <QSettings>

ShutterModel::ShutterModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mShutterSpeedList = {
        {5.0, 32, "30\"", 1},
        {4.67, 25.3984, "25\"", 3},
        {4.5, 22.6274, "22\"", 2},
        {4.33, 20.1587, "20\"", 3},
        {4.0, 16, "15\"", 1},
        {3.67, 12.6992, "13\"", 3},
        {3.5, 11.3137, "11\"", 2},
        {3.33, 10.0794, "10\"", 3},
        {3.0, 8, "8\"", 1},
        {2.67, 6.3496, "6\"", 3},
        {2.5, 5.65685, "6\"", 2},
        {2.33, 5.03968, "5\"", 3},
        {2.0, 4, "4\"", 1},
        {1.67, 3.1748, "3\"2", 3},
        {1.5, 2.82843, "3\"", 2},
        {1.33, 2.51984, "2\"5", 3},
        {1.0, 2, "2\"", 1},
        {0.67, 1.5874, "1\"6", 3},
        {0.5, 1.41421, "1\"5", 2},
        {0.33, 1.25992, "1\"3", 3},
        {0.0, 1, "1\"", 1},
        {-0.33, 0.793701, "0\"8", 3},
        {-0.5, 0.707107, "0\"7", 2},
        {-0.67, 0.629961, "0\"6", 3},
        {-1.0, 0.5, "0\"5", 1},
        {-1.33, 0.39685, "0\"4", 3},
        {-1.5, 0.353553, "0\"3", 2},
        {-1.67, 0.31498, "0\"3", 3},
        {-2.0, 0.25, "4", 1},
        {-2.33, 0.198425, "5", 3},
        {-2.5, 0.176777, "6", 2},
        {-2.67, 0.15749, "6", 3},
        {-3.0, 0.125, "8", 1},
        {-3.33, 0.0992126, "10", 3},
        {-3.5, 0.0883883, "11", 2},
        {-3.67, 0.0787451, "13", 3},
        {-4.0, 0.0625, "15", 1},
        {-4.33, 0.0496063, "20", 3},
        {-4.5, 0.0441942, "23", 2},
        {-4.67, 0.0393725, "25", 3},
        {-5.0, 0.03125, "30", 1},
        {-5.33, 0.0248031, "40", 3},
        {-5.5, 0.0220971, "45", 2},
        {-5.67, 0.0196863, "50", 3},
        {-6.0, 0.015625, "60", 1},
        {-6.33, 0.0124016, "80", 3},
        {-6.5, 0.0110485, "90", 2},
        {-6.67, 0.00984313, "100", 3},
        {-7.0, 0.0078125, "125", 1},
        {-7.33, 0.00620079, "160", 3},
        {-7.5, 0.00552427, "180", 2},
        {-7.67, 0.00492157, "200", 3},
        {-8.0, 0.00390625, "250", 1},
        {-8.33, 0.00310039, "320", 3},
        {-8.5, 0.00276214, "350", 2},
        {-8.67, 0.00246078, "400", 3},
        {-9.0, 0.00195313, "500", 1},
        {-9.33, 0.0015502, "640", 3},
        {-9.5, 0.00138107, "750", 2},
        {-9.67, 0.00123039, "800", 3},
        {-10.0, 0.000976563, "1000", 1},
        {-10.33, 0.000775098, "1250", 3},
        {-10.5, 0.000690534, "1500", 2},
        {-10.67, 0.000615196, "1600", 3},
        {-11.0, 0.000488281, "2000", 1},
        {-11.33, 0.000387549, "2500", 3},
        {-11.5, 0.000345267, "3000", 2},
        {-11.67, 0.000307598, "3200", 3},
        {-12.0, 0.000244141, "4000", 1},
        {-12.33, 0.000193775, "5000", 3},
        {-12.5, 0.000172633, "6000", 2},
        {-12.67, 0.000153799, "6400", 3},
        {-13.0, 0.00012207, "8000", 1},
        {-13.33, 0.0000968873, "10000", 3},
        {-13.5, 0.0000863167, "12000", 2},
        {-13.67, 0.0000768995, "12800", 3},
        {-14.0, 0.0000610352, "16000", 1},
        {-14.33, 0.0000484436, "20000", 3},
        {-14.5, 0.0000431584, "24000", 2},
        {-14.67, 0.0000384497, "25600", 3},
        {-15.0, 0.0000305176, "32000", 1},
    };
}

int ShutterModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return mShutterSpeedList.count();
}

QVariant ShutterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const ShutterSpeed item = mShutterSpeedList[index.row()];

    switch (role)
    {
    case shutterRole_stopValue:
        return QVariant(item.stopValue);
    case shutterRole_preciseSeconds:
        return QVariant(item.preciseSeconds);
    case shutterRole_nominalSeconds:
        return QVariant(item.nominalSeconds);
    case shutterRole_stopInfo:
        return QVariant(item.stopInfo);
    }
    return QVariant();
}

QHash<int, QByteArray> ShutterModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[shutterRole_stopValue] = "stopValue";
    names[shutterRole_preciseSeconds] = "shutterPrecise";
    names[shutterRole_nominalSeconds] = "shutterNominal";
    names[shutterRole_stopInfo] = "shutterInfo";

    return names;
}

QString ShutterModel::getNominalShutter(const double &stopValue)
{
    auto result = std::find_if(mShutterSpeedList.begin(), mShutterSpeedList.end(),
                               // Make that lambada
                               [stopValue](ShutterSpeed& sh) { return sh.stopValue == stopValue; }
            );

    bool found = (result != std::end(mShutterSpeedList));

    if(found)
    {
        int indexArray = result - mShutterSpeedList.begin();
        return mShutterSpeedList[indexArray].nominalSeconds;
    }
    else
    {
        return "below scale";
    }
}

void ShutterModel::dataChangedEmiter()
{
    emit dataChanged(index(0, 0), index(rowCount()-1, 0));
}
