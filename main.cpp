#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQmlContext>
#include "PlayerController.h"
#include "AudioInfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/assets/icons/app_icon.png"));

    QQmlApplicationEngine engine;

    AudioInfo audioInfo;
    engine.rootContext()->setContextProperty("audioInfo", &audioInfo);
    
    qmlRegisterSingletonType<PlayerController>("com.company.PlayerController", 1, 0,
                                               "PlayerController", &PlayerController::create);

    engine.loadFromModule("AudioPlayer", "Main");

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() {QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    return app.exec();
}
