#include "isoproxymodel.h"
#include "isomodel.h"

#include <QObject>
#include <QQmlComponent>
#include <QSettings>

IsoProxyModel::IsoProxyModel(IsoModel* model)
{
    this->setSourceModel(model);
}

bool IsoProxyModel::filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const
{
    bool returnRecord(false);

    // Read settings
    QSettings isoSettings;
    isoSettings.beginGroup("exposureTriangle");
    int minIso = isoSettings.value("isoMinStop").toInt();
    int maxIso = isoSettings.value("isoMaxStop").toInt();
    isoSettings.endGroup();

    QSettings stopScaleSettings;
    stopScaleSettings.beginGroup("scales");
    int stopScale = stopScaleSettings.value("stopScaleIndex").toInt();


    if (this->sourceModel() != nullptr)
    {
        auto index = this->sourceModel()->index(source_row, 0, sourceParent);
        if (index.isValid())
        {
            auto valueRole = index.data(IsoModel::isoRole_stopInfo);
            auto stopValue = index.data(IsoModel::isoRole_stopValue);
            if (valueRole.isValid() && stopValue.isValid())
            {
                if ((valueRole == 1 || valueRole == stopScale) && (stopValue >= minIso && stopValue <= maxIso))
                {
                    returnRecord = true;
                }
            }
        }
    }
    return returnRecord;
}
