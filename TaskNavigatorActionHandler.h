#ifndef TASKNAVIGATORACTIONHANDLER_H
#define TASKNAVIGATORACTIONHANDLER_H

#include <QStringList>
#include <QtTypes>

#include "TaskPathService.h"

class TaskNavigatorActionHandler
{
public:
    explicit TaskNavigatorActionHandler(TaskPathService* taskPathService);
    ~TaskNavigatorActionHandler();

    void GetCurrentPathTitles(QStringList& titles, qint64& length) const;

private:
    TaskPathService* taskPathService;
};

#endif // TASKNAVIGATORACTIONHANDLER_H
