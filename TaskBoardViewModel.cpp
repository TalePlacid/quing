#include "TaskBoardViewModel.h"

TaskBoardViewModel::TaskBoardViewModel(QObject* parent)
    : QObject(parent)
    , taskPathService(&this->taskController, &this->navigationState)
    , taskNavigatorActionHandler(&this->taskPathService)
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
