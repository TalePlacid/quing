#include "test/Tester.h"
#include "test/TestRegistrationHelper.h"
#if 0
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#endif

int main(int argc, char *argv[])
{
    Tester tester;
    TestRegistrationHelper::RegisterAll(tester);
    tester.Run();
#if 0
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
#endif
    return 0; //ret;
}
