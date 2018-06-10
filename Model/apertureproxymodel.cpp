#include "apertureproxymodel.h"
#include "aperturemodel.h"

#include <QObject>
#include <QQmlComponent>
#include <QSettings>

ApertureProxyModel::ApertureProxyModel(ApertureModel* model)
{
    this->setSourceModel(model);
}

bool ApertureProxyModel::filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const
{
    bool returnRecord(false);

    // Read settings
    QSettings apertureSettings;
    apertureSettings.beginGroup("exposureTriangle");
    int minAperture = apertureSettings.value("aperMinStop").toInt();
    int maxAperture = apertureSettings.value("aperMaxStop").toInt();
    apertureSettings.endGroup();

    QSettings stopScaleSettings;
    stopScaleSettings.beginGroup("scales");
    int stopScale = stopScaleSettings.value("stopScaleIndex").toInt();

    if (this->sourceModel() != nullptr)
    {
        auto index = this->sourceModel()->index(source_row, 0, sourceParent);
        if (index.isValid())
        {
            auto valueRole = index.data(ApertureModel::apertureRole_stopInfo);
            auto stopValue = index.data(ApertureModel::aperatureRole_stopValue);
            if (valueRole.isValid() && stopValue.isValid())
            {
                if ((valueRole == 1 || valueRole == stopScale) && (stopValue >= maxAperture && stopValue <= minAperture))
                {
                    returnRecord = true;
                }
            }
        }
    }
    return returnRecord;
}
