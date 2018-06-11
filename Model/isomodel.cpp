#include "isomodel.h"
#include <algorithm>
#include <QSettings>

IsoModel::IsoModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mIsoSpeedList = {
        {-7, 0.78125, "0.8", 1},
        {-6.67, 0.98431, "1", 3},
        {-6.5, 1.10485, "1.1", 2},
        {-6.33, 1.24016, "1.2", 3},
        {-6, 1.5625, "1.6", 1},
        {-5.67, 1.96863, "2", 3},
        {-5.5, 2.20971, "2.2", 2},
        {-5.33, 2.48031, "2.5", 3},
        {-5, 3.125, "3", 1},
        {-4.67, 3.93725, "4", 3},
        {-4.5, 4.41942, "4.5", 2},
        {-4.33, 4.96063, "5", 3},
        {-4, 6.25, "6", 1},
        {-3.67, 7.87451, "8", 3},
        {-3.5, 8.83883, "9", 2},
        {-3.33, 9.92126, "10", 3},
        {-3, 12.5, "12", 1},
        {-2.67, 15.749, "16", 3},
        {-2.5, 17.6777, "18", 2},
        {-2.33, 19.8425, "20", 3},
        {-2, 25, "25", 1},
        {-1.67, 31.498, "32", 3},
        {-1.5, 35.3553, "35", 2},
        {-1.33, 39.685, "40", 3},
        {-1, 50, "50", 1},
        {-0.67, 62.9961, "64", 3},
        {-0.5, 70.7107, "70", 2},
        {-0.33, 79.3701, "80", 3},
        {0, 100, "100", 1},
        {0.33, 125.992, "125", 3},
        {0.5, 141.421, "140", 2},
        {0.67, 158.74, "160", 3},
        {1, 200, "200", 1},
        {1.33, 251.984, "250", 3},
        {1.5, 282.843, "280", 2},
        {1.67, 317.48, "320", 3},
        {2, 400, "400", 1},
        {2.33, 503.968, "500", 3},
        {2.5, 565.685, "560", 2},
        {2.67, 634.96, "640", 3},
        {3, 800, "800", 1},
        {3.33, 1007.94, "1000", 3},
        {3.5, 1131.37, "1100", 2},
        {3.67, 1269.92, "1250", 3},
        {4, 1600, "1600", 1},
        {4.33, 2015.87, "2000", 3},
        {4.5, 2262.74, "2200", 2},
        {4.67, 2539.84, "2500", 3},
        {5, 3200, "3200", 1},
        {5.33, 4031.75, "4000", 3},
        {5.5, 4525.48, "4400", 2},
        {5.67, 5079.68, "5000", 3},
        {6, 6400, "6400", 1},
        {6.33, 8063.49, "8000", 3},
        {6.5, 9050.97, "8800", 2},
        {6.67, 10159.4, "10000", 3},
        {7, 12800, "12800", 1},
        {7.33, 16127, "16000", 3},
        {7.5, 18101.9, "17600", 2},
        {7.67, 20318.7, "20000", 3},
        {8, 25600, "25600", 1},
        {8.33, 32254, "32000", 3},
        {8.5, 36203.9, "35200", 2},
        {8.67, 40637.5, "40000", 3},
        {9, 51200, "51200", 1},
        {9.33, 64508, "64000", 3},
        {9.5, 72407.7, "70400", 2},
        {9.67, 81274.9, "80000", 3},
        {10, 102400, "102K", 1},
        {10.33, 129016, "128K", 3},
        {10.5, 144815, "140K", 2},
        {10.67, 162550, "160K", 3},
        {11, 204800, "204K", 1},
        {11.33, 258032, "256K", 3},
        {11.5, 289631, "280K", 2},
        {11.67, 325100, "320K", 3},
        {12, 409600, "409K", 1},
        {12.33, 516064, "512K", 3},
        {12.5, 579262, "560K", 2},
        {12.67, 650199, "640K", 3},
        {13, 819200, "820K", 1},
        {13.33, 1032127.32, "1.0M", 3},
        {13.5, 1158523.75, "1.1M", 2},
        {13.67, 1300398.94, "1.28M", 3},
        {14, 1638400, "1.6M", 1},
        {14.33, 2064254.65, "2.0M", 3},
        {14.5, 2317047.5, "2.2M", 2},
        {14.67, 2600797.88, "2.5M", 3},
        {15, 3276800, "3.2M", 1},
    };
}

int IsoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return mIsoSpeedList.count();
}

QVariant IsoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const IsoSpeed item = mIsoSpeedList[index.row()];

    switch (role)
    {
    case isoRole_stopValue:
        return QVariant(item.stopValue);
    case isoRole_preciseIso:
        return QVariant(item.presiceIso);
    case isoRole_nominalIso:
        return QVariant(item.nominalIso);
    case isoRole_stopInfo:
        return QVariant(item.stopInfo);
    }
    return QVariant();
}

QHash<int, QByteArray> IsoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[isoRole_stopValue] = "stopValue";
    names[isoRole_preciseIso] = "isoPrecise";
    names[isoRole_nominalIso] = "isoNominal";
    names[isoRole_stopInfo] = "isoInfo";

    return names;
}

QString IsoModel::getNominalIso(const double &stopValue)
{
    auto result = std::find_if(mIsoSpeedList.begin(), mIsoSpeedList.end(),
                               // Make that lambada
                               [stopValue](IsoSpeed& iso) { return iso.stopValue == stopValue; }
            );

    bool found = (result != std::end(mIsoSpeedList));

    if(found)
    {
        int indexArray = result - mIsoSpeedList.begin();
        return mIsoSpeedList[indexArray].nominalIso;
    }
    else
    {
        return "error";
    }
}

void IsoModel::dataChangedEmiter()
{
    this->beginResetModel();

//    this->modelReset(dataChanged(index(0, 0), index(rowCount()-1, 0)));
    //emit dataChanged(index(0, 0), index(rowCount()-1, 0));
    this->endResetModel();
    //this->modelReset(dataChanged);
}
