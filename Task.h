#ifndef TASK_H //guard
#define TASK_H
#include <string>
#include <cstdint>
using namespace std;
#include "DateTime.h"

typedef int64_t Int;

enum Category : Int{
    PENDING,
    IN_PROGRESS,
    PARTIAL_COMPLETED,
    COMPLETED,
    DEFERRED,
    CANCELLED
};

class Task{
public:
    Task();
    Task(string uuid, string title, string detail, DateTime createdAt);
    virtual ~Task();
    Task(const Task& source);
    Task& operator=(const Task& source);

    void ModifyContents(string title, string detail);
    void ScheduleFor(DateTime dueDate);
    void ClearDueDate();
    void ChangeCategory(Category category);
    void RecordCompletionAt(DateTime completedAt);
    void MarkUrgent(bool isUrgent);

    Task* Clone() const;

    bool EqualsByUUID(const Task& other) const;
    bool IsEqual(const Task& other);
    bool IsNotEqual(const Task& other);

    bool operator==(const Task& other);
    bool operator!=(const Task& other);

    const string& GetUUID() const;
    const string& GetTitle() const;
    const string& GetDetail() const;
    Category GetCategory() const;
    bool IsUrgent() const;
    const DateTime& GetCreatedAt() const;
    const DateTime& GetCompletedAt() const;
    const DateTime& GetDueDate() const;
private:
    string uuid; //XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
    string title;
    string detail;
    Category category;
    bool isUrgent;
    DateTime createdAt;
    DateTime completedAt;
    DateTime dueDate;
};

inline const string& Task::GetUUID() const{
    return this->uuid;
}

inline const string& Task::GetTitle() const{
    return this->title;
}

inline const string& Task::GetDetail() const{
    return this->detail;
}

inline Category Task::GetCategory() const{
    return this->category;
}

inline bool Task::IsUrgent() const{
    return this->isUrgent;
}

inline const DateTime& Task::GetCreatedAt() const{
    return this->createdAt;
}

inline const DateTime& Task::GetCompletedAt() const{
    return this->completedAt;
}

inline const DateTime& Task::GetDueDate() const{
    return this->dueDate;
}

#endif // TASK_H
