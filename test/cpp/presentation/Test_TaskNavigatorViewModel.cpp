#include <QSignalSpy>
#include "Test_TaskNavigatorViewModel.h"
#include "../../../NavigationState.h"
#include "../../../TaskController.h"
#include "../../../TaskNavigationService.h"
#include "../../../TaskNavigatorActionHandler.h"
#include "../../../TaskNavigatorViewModel.h"
#include "../AssertReporter.h"
#include "../Local8BitStringConverter.h"

#pragma warning(disable:4996)

Test_TaskNavigatorViewModel::Test_TaskNavigatorViewModel()
{
}

Test_TaskNavigatorViewModel::~Test_TaskNavigatorViewModel()
{
}

void Test_TaskNavigatorViewModel::Execute()
{
    TaskController taskController;
    NavigationState navigationState;

    // 1. 계층 경로를 검증할 테스트 데이터를 준비한다.
    Task& depth1Task = taskController.Attach(
        "11111111-1111-1111-1111-111111111111",
        "Depth1",
        "Depth1 detail",
        DateTime(2026, 3, 23, 19, 0, 0));
    Task& depth2Task = taskController.Attach(
        depth1Task,
        "22222222-2222-2222-2222-222222222222",
        "Depth2",
        "Depth2 detail",
        DateTime(2026, 3, 23, 19, 1, 0));
    Task& depth3Task = taskController.Attach(
        depth2Task,
        "33333333-3333-3333-3333-333333333333",
        "Depth3",
        "Depth3 detail",
        DateTime(2026, 3, 23, 19, 2, 0));
    TaskNavigationService taskNavigationService(&taskController, &navigationState);
    TaskNavigatorActionHandler taskNavigatorActionHandler(&taskNavigationService);

    // 2. 생성자 초기 로드를 검증하기 위해 현재 위치를 2단계로 이동한다.
    taskNavigationService.MoveTo(depth2Task.GetUUID());

    TaskNavigatorViewModel taskNavigatorViewModel(&taskNavigatorActionHandler);
    AssertReporter::Assert(
        taskNavigatorViewModel.GetLength() == 2,
        Local8BitStringConverter::Convert("생성자 초기 길이 로드 실패"));
    AssertReporter::Assert(
        taskNavigatorViewModel.GetTitles() == QStringList({"Depth1", "Depth2"}),
        Local8BitStringConverter::Convert("생성자 초기 제목 로드 실패"));

    // 3. 명시적 재로드 시 시그널 발생과 상태 갱신을 검증한다.
    QSignalSpy titlesChangedSignalSpy(&taskNavigatorViewModel, &TaskNavigatorViewModel::TitlesChanged);
    QSignalSpy lengthChangedSignalSpy(&taskNavigatorViewModel, &TaskNavigatorViewModel::LengthChanged);

    taskNavigationService.MoveTo(depth3Task.GetUUID());

    taskNavigatorViewModel.LoadCurrentPathTitles();

    AssertReporter::Assert(
        titlesChangedSignalSpy.count() == 1,
        Local8BitStringConverter::Convert("TitlesChanged 시그널 발생 실패"));
    AssertReporter::Assert(
        lengthChangedSignalSpy.count() == 1,
        Local8BitStringConverter::Convert("LengthChanged 시그널 발생 실패"));
    AssertReporter::Assert(
        taskNavigatorViewModel.GetLength() == 3,
        Local8BitStringConverter::Convert("재로드 길이 갱신 실패"));
    AssertReporter::Assert(
        taskNavigatorViewModel.GetTitles() == QStringList({"Depth1", "Depth2", "Depth3"}),
        Local8BitStringConverter::Convert("재로드 제목 갱신 실패"));
}

string Test_TaskNavigatorViewModel::GetName()
{
    return "Test_TaskNavigatorViewModel";
}
