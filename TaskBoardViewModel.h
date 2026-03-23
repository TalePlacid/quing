#ifndef TASKBOARDVIEWMODEL_H
#define TASKBOARDVIEWMODEL_H

#include <QObject>

#include "NavigationState.h"
#include "TaskController.h"
#include "TaskNavigatorActionHandler.h"
#include "TaskNavigatorViewModel.h"
#include "TaskNavigationService.h"

class TaskBoardViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TaskNavigatorViewModel* taskNavigatorViewModel READ GetTaskNavigatorViewModel CONSTANT)

public:
    explicit TaskBoardViewModel(QObject* parent = 0);
    ~TaskBoardViewModel();

    TaskNavigatorViewModel* GetTaskNavigatorViewModel() const;

private:
    TaskController taskController;
    NavigationState navigationState;
    TaskNavigationService taskNavigationService;
    TaskNavigatorActionHandler taskNavigatorActionHandler;
    TaskNavigatorViewModel* taskNavigatorViewModel;
};

#endif // TASKBOARDVIEWMODEL_H
