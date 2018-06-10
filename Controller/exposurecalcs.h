#ifndef EXPOSURECALCS_H
#define EXPOSURECALCS_H

#include <QObject>

#include "Model/aperturemodel.h"
#include "Model/shuttermodel.h"
#include "Model/isomodel.h"
#include "Model/filtermodel.h"


class ExposureCalcs : public QObject
{
    Q_OBJECT

public:
    explicit ExposureCalcs(QObject *parent = nullptr);

    // Getters
    double getExposureValue() const { return mExposureValue; }

    // Models
    ApertureModel *ptrApertureModel;
    ShutterModel *ptrShutterModel;
    IsoModel *ptrIsoModel;
    FilterModel *ptrFilterModel;

signals:
    void exposureValueChanged(double Value);
    void apertureValueChanged(QString Value, QString Msg);
    void shutterValueChanged(QString Value, QString Msg);
    void isoValueChanged(QString Value, QString Msg);

public slots:
    void calculateExposureValue(const double& aparature, const double& shutter, const double& iso);
    void calculateAparature(const double &stopShutter, const double &stopIso, const double &ndFilter);
    void calculateShutterValue(const double &stopAparature, const double &stopIso, const double &ndFilter);
    void calculateIsoValue(const double &stopAparature, const double &stopShutter, const double &ndFilter);

private:
    double roundedStopValue(const double& value) const;

    double mExposureValue;
};

#endif // EXPOSURECALCS_H
