#include "shutterproxymodel.h"
#include "shuttermodel.h"

#include <QObject>
#include <QQmlComponent>
#include <QSettings>

ShutterProxyModel::ShutterProxyModel(ShutterModel* model)
{
    this->setSourceModel(model);
}

bool ShutterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const
{
    bool returnRecord(false);

    // Read settings
    QSettings shutterSettings;
    shutterSettings.beginGroup("exposureTriangle");
    int minShutter = shutterSettings.value("shutterMaxStop").toInt();
    shutterSettings.endGroup();

    QSettings stopScaleSettings;
    stopScaleSettings.beginGroup("scales");
    int stopScale = stopScaleSettings.value("stopScaleIndex").toInt();


    if (this->sourceModel() != nullptr)
    {
        auto index = this->sourceModel()->index(source_row, 0, sourceParent);
        if (index.isValid())
        {
            auto valueRole = index.data(ShutterModel::shutterRole_stopInfo);
            auto stopValue = index.data(ShutterModel::shutterRole_stopValue);
            if (valueRole.isValid() && stopValue.isValid())
            {
                if ((valueRole == 1 || valueRole == stopScale) && (stopValue >= minShutter))
                {
                    returnRecord = true;
                }
            }
        }
    }
    return returnRecord;
}
