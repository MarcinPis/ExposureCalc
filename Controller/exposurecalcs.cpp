#include "exposurecalcs.h"

#include <cmath>
#include <QDebug>
#include <QtMath>
#include <algorithm>

#include <QVector>
#include <QSettings>

// Default constructor
ExposureCalcs::ExposureCalcs(QObject *parent) :
    QObject(parent)
{
    ptrApertureModel = new ApertureModel(this);
    ptrShutterModel = new ShutterModel(this);
    ptrIsoModel = new IsoModel(this);
    ptrFilterModel = new FilterModel(this);
}

void ExposureCalcs::calculateExposureValue(const double &aparature, const double &shutter, const double &iso)
{

//    double aparatureValue = log2(pow(aparature, 2));
//    double shutterValue = log2(1 / shutter);
//    double isoValue = log2(iso / 100);
//    double exposure = aparatureValue + shutterValue - isoValue;

    // Convert that from log2 to just logs because of android limitations
    double aparatureValue = log(pow(aparature, 2))/log(2);
    double shutterValue = log(1 / shutter)/log(2);
    double isoValue = log(iso / 100)/log(2);
    double exposure = aparatureValue + shutterValue - isoValue;

    mExposureValue = roundedStopValue(exposure);

    emit exposureValueChanged(mExposureValue);
}

void ExposureCalcs::calculateAparature(const double &stopShutter, const double &stopIso, const double &ndFilter)
{
    double apertureValue = mExposureValue + stopShutter + stopIso - ndFilter;
    double roundedAperture = roundedStopValue(apertureValue);

    QSettings apertureSettings;
    apertureSettings.beginGroup("exposureTriangle");
    int minStopAperture = apertureSettings.value("aperMinStop").toInt();
    int maxStopAperture = apertureSettings.value("aperMaxStop").toInt();
    QString minValAperture = apertureSettings.value("aperMinVal").toString();
    QString maxValAperture= apertureSettings.value("aperMaxVal").toString();
    apertureSettings.endGroup();

    QString apertureOutput;
    QString msg = "";
    // Check if the value is in acceptable range
    if(roundedAperture > minStopAperture)
    {
        double apertureDeficit = minStopAperture - roundedAperture;
        msg = tr("Exceeds the limit by ") + QString::number(apertureDeficit) + tr("EV");
        apertureOutput = minValAperture;
    }
    else if(roundedAperture < maxStopAperture)
    {
        double apertureDeficit = maxStopAperture - roundedAperture;
        msg = tr("Exceeds the limit by ") + QString::number(apertureDeficit) + tr("EV");
        apertureOutput = maxValAperture;
    }
    else
    {
        // if YES then do that lambada
        apertureOutput = ptrApertureModel->getNominalValue(roundedAperture);
    }

    emit apertureValueChanged(apertureOutput, msg);
}

void ExposureCalcs::calculateShutterValue(const double &stopAparature, const double &stopIso, const double &ndFilter)
{

    double shutterValue = -mExposureValue + stopAparature - stopIso + ndFilter;
    double roundedShutter = roundedStopValue(shutterValue);

    // Read settings
    QSettings shutterSettings;
    shutterSettings.beginGroup("exposureTriangle");
    int maxStopShutter = shutterSettings.value("shutterMaxStop").toInt();
    int minStopShutter = 5;
    QString maxValShutter = shutterSettings.value("shutterMaxVal").toString();
    shutterSettings.endGroup();

    QString shutterOutput;
    QString msg = "";
    // Check if the value is in acceptable range
    if(roundedShutter > minStopShutter)
    {
        quint32 result = static_cast<quint32>(pow(2, roundedShutter));
        if(result >= 86400)
        {
            shutterOutput = tr("Too long");
            msg = tr("Shutter time would exceed the limit of 24h");
        }
        else
        {
            // Convert the value to hh:ss
            if(result > 60 && result < 3600)
            {
                // Give result in mm:ss format
                quint32 minutes = result / 60;
                quint32 seconds = result - minutes * 60;
                shutterOutput = QString::number(minutes) + "m:" + QString::number(seconds) + "s";
            }
            else if(result > 3600)
            {
                // Give result in hh:mm format
                quint32 hours = result / 3600;
                quint32 minutes = (result - hours * 3600) / 60;
                shutterOutput = QString::number(hours) + "h:" + QString::number(minutes) + "m";
            }
            else if(result < 60)
            {
                // Give result in ss format
                shutterOutput = QString::number(result) + "s";
            }
        }
    }
    else if(roundedShutter < maxStopShutter)
    {
        shutterOutput = maxValShutter;
        double shutterDeficit = maxStopShutter - roundedShutter;
        msg = tr("Exceeds the limit by ") + QString::number(shutterDeficit) + tr("EV");
    }
    else
    {
        // if YES then do that lambada
        shutterOutput = ptrShutterModel->getNominalShutter(roundedShutter);
    }

    emit shutterValueChanged(shutterOutput, msg);
}

void ExposureCalcs::calculateIsoValue(const double &stopAparature, const double &stopShutter, const double &ndFilter)
{
    double isoValue = -mExposureValue + stopAparature - stopShutter + ndFilter;
    double roundedIso = roundedStopValue(isoValue);

    QSettings isoSettings;
    isoSettings.beginGroup("exposureTriangle");
    int minStopIso = isoSettings.value("isoMinStop").toInt();
    int maxStopIso = isoSettings.value("isoMaxStop").toInt();
    QString minValIso = isoSettings.value("isoMinVal").toString();
    QString maxValIso = isoSettings.value("isoMaxVal").toString();
    isoSettings.endGroup();

    QString isoOutput;
    QString msg = "";
    // Check if the value is in acceptable range
    if(roundedIso > maxStopIso)
    {
        // Need higher iso
        isoOutput = maxValIso;
        double isoDeficit = maxStopIso - roundedIso;
        msg = tr("Exceeds the limit by ") + QString::number(isoDeficit) + tr("EV");
    }
    else if(roundedIso < minStopIso)
    {
        // Need lower iso
        isoOutput = minValIso;
        double isoDeficit = minStopIso - roundedIso;
        msg = tr("Exceeds the limit by ") + QString::number(isoDeficit) + tr("EV");
    }
    else
    {
        // if YES then do that lambada
        isoOutput = ptrIsoModel->getNominalIso(roundedIso);
    }

    emit isoValueChanged(isoOutput, msg);
}

double ExposureCalcs::roundedStopValue(const double &value) const
{
    // takes input in stop value
    // returns output in rounded stop value: .0 , .5, .33, .67

    QSettings filterSettings;
    filterSettings.beginGroup("scales");
    int stopPrecision = filterSettings.value("stopScaleIndex").toInt();
    filterSettings.endGroup();

    // cast double to int
    int intPart = static_cast<int>(value);

    // cast reminder to double
    double reminderValue = qFabs(value - intPart);

    if(stopPrecision == 1)
    {
        if(reminderValue < 0.5)
        {
            reminderValue = 0;
        }
        else if(reminderValue >= 0.5)
        {
            reminderValue = 1;
        }
    }
    else if(stopPrecision == 2)
    {
        if(reminderValue <= 0.25)
        {
            reminderValue = 0;
        }
        else if(reminderValue > 0.25 && reminderValue < 0.75)
        {
            reminderValue = 0.5;
        }
        else if(reminderValue >= 0.75)
        {
            reminderValue = 1;
        }
    }
    else if(stopPrecision == 3)
    {
        if(reminderValue < 0.165)
        {
            reminderValue = 0;
        }
        else if(reminderValue >= 0.165 && reminderValue < 0.495)
        {
            reminderValue = 0.33;
        }
        else if(reminderValue >= 0.495 && reminderValue < 0.825)
        {
            reminderValue = 0.67;
        }
        else if(reminderValue >= 0.0825)
        {
            reminderValue = 1;
        }
    }

    if (value >= 0)
    {
        return intPart + reminderValue;
    }
    else
    {
        return intPart - reminderValue;
    }
}
