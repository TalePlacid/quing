#include "TaskNavigatorActionHandler.h"

#include <QString>

TaskNavigatorActionHandler::TaskNavigatorActionHandler(TaskNavigationService* taskNavigationService)
{
    this->taskNavigationService = taskNavigationService;
}

TaskNavigatorActionHandler::~TaskNavigatorActionHandler()
{
}

void TaskNavigatorActionHandler::GetCurrentPathTitles(QStringList& titles, qint64& length) const
{
    const TaskPathTitleList pathTitles = this->taskNavigationService->GetCurrentPathTitles();

    titles.clear();
    Int i = 0;
    while (i < pathTitles.GetLength())
    {
        titles.append(QString::fromStdString(pathTitles.GetAt(i)));
        i++;
    }
    length = pathTitles.GetLength();
}
