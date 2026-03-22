#include "test/Tester.h"
#include "test/TestRegistrationHelper.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    Tester tester;
    TestRegistrationHelper::RegisterAll(tester);
    tester.Run();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("quing", "TaskBoard");
    int ret = app.exec();

    return ret;
}
