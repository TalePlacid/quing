#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H
#include <string>
#include <vector>
using namespace std;
#include "Task.h"
#include "ChildArrayForest.h"

class TaskController{
public:
    TaskController();
    ~TaskController();

    Task& Attach();
    Task& Attach(const string& uuid, const string& title, const string& detail, const DateTime& createdAt);
    Task& Attach(const Task& task);
    Task& Attach(const Task& parent, const Task& task);
    Task& Attach(const Task& parent, const string& uuid, const string& title, const string& detail, const DateTime& createdAt);
    void Detach(const Task& task);

    Task* Search(const string& uuid);

    Task& Modify(const Task& task, const string& title, const string& detail);
    Task& ScheduleFor(const Task& task, const DateTime& dueDate);
    Task& ClearDueDate(const Task& task);
    Task& ChangeCategory(const Task& task, Category category);
    Task& RecordCompletionAt(const Task& task, const DateTime& completedAt);
    Task& ClearCompletionAt(const Task& task);
    Task& MarkUrgent(const Task& task, bool isUrgent);

    Task& Move(const Task& task, Int index);
    Task& MoveAsChild(const Task& parent, const Task& task);
    Task& MoveAsChild(const Task& parent, Int index, const Task& task);

    Task* GetParentTask(const Task& task, Int level = 1);
    vector<ChildArrayForest<Task>::OrderEntry> GetPreOrderEntries();
    vector<ChildArrayForest<Task>::OrderEntry> GetPreOrderEntries(const Task& task);
    vector<ChildArrayForest<Task>::OrderEntry> GetPostOrderEntries();
    vector<ChildArrayForest<Task>::OrderEntry> GetPostOrderEntries(const Task& task);
    Int GetLength() const;
public:
    static bool MatchUUID(const Task& task, const string& uuid);
    static bool MatchTask(const Task& element, const Task& task);
private:
    ChildArrayForest<Task> tasks;
};

#endif // TASKCONTROLLER_H
