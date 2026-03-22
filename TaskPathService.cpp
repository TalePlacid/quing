#include "TaskPathService.h"

#include <vector>
using namespace std;

TaskPathService::TaskPathService(TaskController* taskController, NavigationState* navigationState)
{
    this->taskController = taskController;
    this->navigationState = navigationState;
}

TaskPathService::~TaskPathService()
{
}

TaskPathTitleList TaskPathService::GetCurrentPathTitles() const
{
    TaskPathTitleList pathTitles;
    const string& currentUUID = this->navigationState->GetCurrentUUID();
    Task* currentTask = 0;
    vector<string> reversedPathTitles;

    if (currentUUID != "")
    {
        currentTask = this->taskController->Search(currentUUID);
    }

    while (currentTask != 0)
    {
        reversedPathTitles.push_back(currentTask->GetTitle());
        currentTask = this->taskController->GetParentTask(*currentTask);
    }

    Int i = static_cast<Int>(reversedPathTitles.size()) - 1;
    while (i >= 0)
    {
        pathTitles.Append(reversedPathTitles[static_cast<size_t>(i)]);
        i--;
    }

    return pathTitles;
}
