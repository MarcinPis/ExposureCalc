#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>

#include <QSortFilterProxyModel>

#include "Controller/exposurecalcs.h"

#include "Model/shuttermodel.h"
#include "Model/shutterproxymodel.h"
#include "Model/isomodel.h"
#include "Model/isoproxymodel.h"
#include "Model/aperturemodel.h"
#include "Model/apertureproxymodel.h"

// Bring the settings
#include <QSettings>
// Bring the translation
#include <QTranslator>


int main(int argc, char *argv[])
{
    // Set app info
    QCoreApplication::setOrganizationName("Marcin Pisarski");
    QCoreApplication::setOrganizationDomain("pisarski.com");
    QCoreApplication::setApplicationName("Exposure Calc");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // Exposure calculator declaration
    ExposureCalcs myCalculator;

    // Declare that models
    auto myApertureModel = myCalculator.ptrApertureModel;
    auto myShutterModel = myCalculator.ptrShutterModel;
    auto myIsoModel = myCalculator.ptrIsoModel;
    auto myFilterModel = myCalculator.ptrFilterModel;

    // CustomProxyApertureModel
    auto customProxyAperture = new ApertureProxyModel(myApertureModel);

    // CustomProxyShuttereModel
    auto customProxyShutter = new ShutterProxyModel(myShutterModel);

    // CustomProxyShuttereModel
    auto customProxyIso = new IsoProxyModel(myIsoModel);

    // Check the settings
    QSettings settings;
    settings.beginGroup("scales");
    int filterSetup = settings.value("filterScaleIndex").toInt();

    if(filterSetup == 0)
    {
        // INITIALIZE SETTINGS
        settings.setValue("stopScaleIndex", 3);
        settings.setValue("filterScaleIndex", 3);
        settings.endGroup();

        settings.beginGroup("exposureTriangle");
        settings.setValue("aperMinStop", 8);
        settings.setValue("aperMaxStop", 0);
        settings.setValue("aperMinVal", "16");
        settings.setValue("aperMaxVal", "1.0");

        settings.setValue("isoMinStop", 0);
        settings.setValue("isoMaxStop", 7);
        settings.setValue("isoMinVal", "100");
        settings.setValue("isoMaxVal", "12800");

        settings.setValue("shutterMaxStop", -13);
        settings.setValue("shutterMaxVal", "8000");
        settings.endGroup();
    }

    // Start the QML engine
    QQmlApplicationEngine engine;

    // Install translations
    QTranslator translator;
    translator.load("translation_" + QLocale::system().name(), ":/i18n/");
    app.installTranslator(&translator);

    // Register models
    engine.rootContext()->setContextProperty("ShutterModel", myShutterModel);
    engine.rootContext()->setContextProperty("IsoModel", myIsoModel);
    engine.rootContext()->setContextProperty("ApertureModel", myApertureModel);

    // Filter model
    engine.rootContext()->setContextProperty("FilterModel", myFilterModel);

    // Custom aperture model
    engine.rootContext()->setContextProperty("CustomProxyAperture", customProxyAperture);

    // Custom shutter model
    engine.rootContext()->setContextProperty("CustomProxyShutter", customProxyShutter);

    // Custom ISO model
    engine.rootContext()->setContextProperty("CustomProxyIso", customProxyIso);

    // Register the c++ class
    engine.rootContext()->setContextProperty("myCalculatorTest", &myCalculator);

    // QML standard stuff
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
