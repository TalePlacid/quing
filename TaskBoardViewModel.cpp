#include "TaskBoardViewModel.h"

TaskBoardViewModel::TaskBoardViewModel(QObject* parent)
    : QObject(parent)
    , taskNavigationService(&this->taskController, &this->navigationState)
    , taskNavigatorActionHandler(&this->taskNavigationService)
{
    this->taskNavigatorViewModel = new TaskNavigatorViewModel(&this->taskNavigatorActionHandler, this);
}

TaskBoardViewModel::~TaskBoardViewModel()
{
}

TaskNavigatorViewModel* TaskBoardViewModel::GetTaskNavigatorViewModel() const
{
    return this->taskNavigatorViewModel;
}
