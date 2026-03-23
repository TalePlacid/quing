#ifndef TASKNAVIGATIONSERVICE_H
#define TASKNAVIGATIONSERVICE_H
#include <string>
using namespace std;
#include "NavigationState.h"
#include "TaskController.h"
#include "TaskPathTitleList.h"

class TaskNavigationService
{
public:
    TaskNavigationService(TaskController* taskController, NavigationState* navigationState);
    ~TaskNavigationService();

    void MoveRoot();
    void MoveTo(const string& uuid);
    TaskPathTitleList GetCurrentPathTitles() const;

private:
    TaskController* taskController;
    NavigationState* navigationState;
};

#endif // TASKNAVIGATIONSERVICE_H
