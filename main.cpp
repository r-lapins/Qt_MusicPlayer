#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "PlayerController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    app.setWindowIcon(QIcon(":/assets/icons/app_icon.png"));
    
    QQmlApplicationEngine engine;
    
    PlayerController *playerController = new PlayerController(&app);
    qmlRegisterSingletonInstance("com.company.PlayerController", 1, 0, "PlayerController", playerController);

    engine.loadFromModule("AudioPlayer", "Main");
    
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() {QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    return app.exec();
}
