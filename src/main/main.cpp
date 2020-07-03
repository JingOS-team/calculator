#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>

#include "historymanager.h"
#include "typemodel.h"
#include "unitmodel.h"
int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    auto *historyManager = new HistoryManager();
    auto *typeModel = new TypeModel();
    auto *unitModel = new UnitModel();
    QObject::connect(typeModel, &TypeModel::categoryChanged, unitModel, &UnitModel::changeUnit);
    // create qml app engine
    QQmlApplicationEngine engine;
    KLocalizedString::setApplicationDomain("kalk");
    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));

    engine.rootContext()->setContextProperty("historyManager", historyManager);
    engine.rootContext()->setContextProperty("typeModel", typeModel);
    engine.rootContext()->setContextProperty("unitModel", unitModel);
    KAboutData aboutData("kalk", "Calculator", "0.1", "Calculator in Kirigami", KAboutLicense::GPL, i18n("© 2020 KDE Community"));
    KAboutData::setApplicationData(aboutData);

#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty(QStringLiteral("debug"), true);
#else
    engine.rootContext()->setContextProperty(QStringLiteral("debug"), false);
#endif
    // setup qml imports
    engine.addImportPath(QStringLiteral("qrc:/"));

    // load main ui
    engine.load(QUrl(QStringLiteral("qrc:/ui/Main.qml")));

    return app.exec();
}
