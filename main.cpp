#include "test/cpp/Tester.h"
#include "test/cpp/TestRegistrationHelper.h"
#include "TaskBoardViewModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    Tester tester;
    TestRegistrationHelper::RegisterAll(tester);
    tester.Run();

    TaskBoardViewModel taskBoardViewModel;
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("taskBoardViewModel", &taskBoardViewModel);
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
