#ifndef TASKPATHSERVICE_H
#define TASKPATHSERVICE_H

#include <string>

#include "NavigationState.h"
#include "TaskController.h"
#include "TaskPathTitleList.h"

class TaskPathService
{
public:
    TaskPathService(TaskController* taskController, NavigationState* navigationState);
    ~TaskPathService();

    TaskPathTitleList GetCurrentPathTitles() const;

private:
    TaskController* taskController;
    NavigationState* navigationState;
};

#endif // TASKPATHSERVICE_H
