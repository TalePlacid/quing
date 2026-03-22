#include "TaskNavigatorViewModel.h"

#include "TaskNavigatorActionHandler.h"

TaskNavigatorViewModel::TaskNavigatorViewModel(TaskNavigatorActionHandler* actionHandler, QObject* parent)
    : QObject(parent)
{
    this->actionHandler = actionHandler;
    this->titles = QStringList();
    this->length = 0;

    this->LoadCurrentPathTitles();
}

QStringList TaskNavigatorViewModel::GetTitles() const
{
    return this->titles;
}

qint64 TaskNavigatorViewModel::GetLength() const
{
    return this->length;
}

void TaskNavigatorViewModel::LoadCurrentPathTitles()
{
    this->actionHandler->GetCurrentPathTitles(this->titles, this->length);

    emit TitlesChanged();
    emit LengthChanged();
}
