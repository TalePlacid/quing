#ifndef TASKNAVIGATORACTIONHANDLER_H
#define TASKNAVIGATORACTIONHANDLER_H

#include <QStringList>
#include <QtTypes>

#include "TaskNavigationService.h"

class TaskNavigatorActionHandler
{
public:
    explicit TaskNavigatorActionHandler(TaskNavigationService* taskNavigationService);
    ~TaskNavigatorActionHandler();

    void GetCurrentPathTitles(QStringList& titles, qint64& length) const;

private:
    TaskNavigationService* taskNavigationService;
};

#endif // TASKNAVIGATORACTIONHANDLER_H
