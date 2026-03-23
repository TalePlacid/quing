#include "Test_TaskNavigationService.h"

#include "../../../NavigationState.h"
#include "../../../TaskController.h"
#include "../../../TaskNavigationService.h"
#include "../../../TaskPathTitleList.h"
#include "../AssertReporter.h"
#include "../Local8BitStringConverter.h"

#pragma warning(disable:4996)

Test_TaskNavigationService::Test_TaskNavigationService()
{
}

Test_TaskNavigationService::~Test_TaskNavigationService()
{
}

void Test_TaskNavigationService::Execute()
{
    TaskController taskController;
    NavigationState navigationState;
    TaskNavigationService taskNavigationService(&taskController, &navigationState);
    TaskPathTitleList pathTitles;
    Task& depth1Task = taskController.Attach(
        "11111111-1111-1111-1111-111111111111",
        "1단계",
        "1단계 설명",
        DateTime(2026, 3, 23, 19, 0, 0));
    Task& depth2Task = taskController.Attach(
        depth1Task,
        "22222222-2222-2222-2222-222222222222",
        "2단계",
        "2단계 설명",
        DateTime(2026, 3, 23, 19, 1, 0));
    Task& depth3Task = taskController.Attach(
        depth2Task,
        "33333333-3333-3333-3333-333333333333",
        "3단계",
        "3단계 설명",
        DateTime(2026, 3, 23, 19, 2, 0));
    Task& depth4Task = taskController.Attach(
        depth3Task,
        "44444444-4444-4444-4444-444444444444",
        "4단계",
        "4단계 설명",
        DateTime(2026, 3, 23, 19, 3, 0));
    Task& depth5Task = taskController.Attach(
        depth4Task,
        "55555555-5555-5555-5555-555555555555",
        "5단계",
        "5단계 설명",
        DateTime(2026, 3, 23, 19, 4, 0));
    Task& branchedDepth1Task = taskController.Attach(
        "66666666-6666-6666-6666-666666666666",
        "분기 1단계",
        "분기 1단계 설명",
        DateTime(2026, 3, 23, 19, 5, 0));
    Task& branchedDepth2Task = taskController.Attach(
        branchedDepth1Task,
        "77777777-7777-7777-7777-777777777777",
        "분기 2단계",
        "분기 2단계 설명",
        DateTime(2026, 3, 23, 19, 6, 0));
    Task& branchedDepth3Task = taskController.Attach(
        branchedDepth2Task,
        "88888888-8888-8888-8888-888888888888",
        "분기 3단계",
        "분기 3단계 설명",
        DateTime(2026, 3, 23, 19, 7, 0));

    // 1. 루트 위치에서는 빈 경로를 반환한다.
    pathTitles = taskNavigationService.GetCurrentPathTitles();
    AssertReporter::Assert(
        pathTitles.GetLength() == 0,
        Local8BitStringConverter::Convert("루트 위치 경로 반환 실패"));

    // 2. 루트 작업 위치에서는 자신의 제목만 반환한다.
    taskNavigationService.MoveTo(depth1Task.GetUUID());
    pathTitles = taskNavigationService.GetCurrentPathTitles();
    AssertReporter::Assert(
        pathTitles.GetLength() == 1
        && pathTitles.GetAt(0) == "1단계",
        Local8BitStringConverter::Convert("루트 작업 경로 반환 실패"));

    // 3. 하위 작업 위치에서는 루트부터 현재까지의 제목을 순서대로 반환한다.
    taskNavigationService.MoveTo(depth3Task.GetUUID());
    pathTitles = taskNavigationService.GetCurrentPathTitles();
    AssertReporter::Assert(
        pathTitles.GetLength() == 3
        && pathTitles.GetAt(0) == "1단계"
        && pathTitles.GetAt(1) == "2단계"
        && pathTitles.GetAt(2) == "3단계",
        Local8BitStringConverter::Convert("하위 작업 경로 반환 실패"));

    // 4. 4단계 작업 위치에서는 4단계 경로를 순서대로 반환한다.
    taskNavigationService.MoveTo(depth4Task.GetUUID());
    pathTitles = taskNavigationService.GetCurrentPathTitles();
    AssertReporter::Assert(
        pathTitles.GetLength() == 4
        && pathTitles.GetAt(0) == "1단계"
        && pathTitles.GetAt(1) == "2단계"
        && pathTitles.GetAt(2) == "3단계"
        && pathTitles.GetAt(3) == "4단계",
        Local8BitStringConverter::Convert("4단계 작업 경로 반환 실패"));

    // 5. 5단계 작업 위치에서는 5단계 경로를 순서대로 반환한다.
    taskNavigationService.MoveTo(depth5Task.GetUUID());
    pathTitles = taskNavigationService.GetCurrentPathTitles();
    AssertReporter::Assert(
        pathTitles.GetLength() == 5
        && pathTitles.GetAt(0) == "1단계"
        && pathTitles.GetAt(1) == "2단계"
        && pathTitles.GetAt(2) == "3단계"
        && pathTitles.GetAt(3) == "4단계"
        && pathTitles.GetAt(4) == "5단계",
        Local8BitStringConverter::Convert("5단계 작업 경로 반환 실패"));

    // 6. 분기 루트의 하위 작업 위치에서는 해당 분기 경로만 반환한다.
    taskNavigationService.MoveTo(branchedDepth3Task.GetUUID());
    pathTitles = taskNavigationService.GetCurrentPathTitles();
    AssertReporter::Assert(
        pathTitles.GetLength() == 3
        && pathTitles.GetAt(0) == "분기 1단계"
        && pathTitles.GetAt(1) == "분기 2단계"
        && pathTitles.GetAt(2) == "분기 3단계",
        Local8BitStringConverter::Convert("분기 루트 작업 경로 반환 실패"));
}

string Test_TaskNavigationService::GetName()
{
    return "Test_TaskNavigationService";
}
