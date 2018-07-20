#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include <glog/logging.h>

#include "SignalSource.h"

#include "ui/GeneralTimeImpl.h"
#include "ui/GeneralSpectrumImpl.h"
#include "ui/BleRxImpl.h"
#include "ui/BleDutImpl.h"

int main(int argc, char* argv[])
{
    // Initialize Google's logging library.
    FLAGS_logtostderr = true;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Compiled Date: " << __DATE__;
    LOG(INFO) << "Compiled Time: " << __TIME__;

    qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray("qrc:/layouts"));
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);


    QQmlApplicationEngine engine;

    QString extraImportPath(QStringLiteral("%1/../../../../%2"));

    engine.addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
        QString::fromLatin1("qml")));

    //engine.rootContext()->setContextProperty("signalSource", &signalSource);

    qmlRegisterType<GeneralTimeImpl>("GeneralTimeImpl", 1, 1, "GeneralTimeImpl");
    qmlRegisterType<FreqDisplayForm>("GeneralSpectrumImpl", 1, 1, "GeneralSpectrumImpl");
    qmlRegisterType<BleRxImpl>("BleRxImpl", 1, 1, "BleRxImpl");
    qmlRegisterType<BleDutControl>("BleDutImpl", 1, 1, "BleDutImpl");


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
