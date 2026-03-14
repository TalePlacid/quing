#include "Task.h"

#pragma warning(disable:4996)

Task::Task()
    :uuid(""), title(""), detail(""){
    category = PENDING;
    isUrgent = false;
    completedAt = DateTime();
    dueDate = DateTime();
}

Task::Task(string uuid, string title, string detail, DateTime createdAt)
    :uuid(uuid), title(title), detail(detail), createdAt(createdAt){
    category = PENDING;
    isUrgent = false;
    completedAt = DateTime();
    dueDate = DateTime();
}

Task::~Task(){

}

Task::Task(const Task& source)
    :uuid(source.uuid), title(source.title), detail(source.detail), category(source.category), isUrgent(source.isUrgent), createdAt(source.createdAt),
    completedAt(source.completedAt), dueDate(source.dueDate){

}

Task& Task::operator=(const Task& source){
    this->uuid = source.uuid;
    this->title = source.title;
    this->detail = source.detail;
    this->category = source.category;
    this->isUrgent = source.isUrgent;
    this->createdAt = source.createdAt;
    this->completedAt = source.completedAt;
    this->dueDate = source.dueDate;

    return *this;
}

Task& Task::ModifyContents(string title, string detail){
    this->title = title;
    this->detail = detail;

    return *this;
}

Task& Task::ScheduleFor(DateTime dueDate){
    this->dueDate = dueDate;

    return *this;
}

void Task::ClearDueDate(){
    this->dueDate = DateTime();
}

Category Task::ChangeCategory(Category category){
    this->category = category;

    return this->category;
}

Task& Task::RecordCompletionAt(DateTime completedAt){
    this->completedAt = completedAt;

    return *this;
}

bool Task::MarkUrgent(bool isUrgent){
    this->isUrgent = isUrgent;

    return this->isUrgent;
}

Task* Task::Clone() const{
    return new Task(*this);
}

bool Task::EqualsByUUID(const Task& other) const{
    return this->uuid == other.uuid;
}

bool Task::IsEqual(const Task& other){
    return this->uuid == other.uuid
            && this->title == other.title
            && this->detail == other.detail
            && this->category == other.category
            && this->isUrgent == other.isUrgent
            && this->createdAt == other.createdAt
            && this->completedAt == other.completedAt
            && this->dueDate == other.dueDate;
}

bool Task::IsNotEqual(const Task& other){
    return this->uuid != other.uuid
            || this->title != other.title
            || this->detail != other.detail
            || this->category != other.category
            || this->isUrgent != other.isUrgent
            || this->createdAt != other.createdAt
            || this->completedAt != other.completedAt
            || this->dueDate != other.dueDate;
}

bool Task::operator==(const Task& other){
    return this->uuid == other.uuid
            && this->title == other.title
            && this->detail == other.detail
            && this->category == other.category
            && this->isUrgent == other.isUrgent
            && this->createdAt == other.createdAt
            && this->completedAt == other.completedAt
            && this->dueDate == other.dueDate;
}

bool Task::operator!=(const Task& other){
    return this->uuid != other.uuid
            || this->title != other.title
            || this->detail != other.detail
            || this->category != other.category
            || this->isUrgent != other.isUrgent
            || this->createdAt != other.createdAt
            || this->completedAt != other.completedAt
            || this->dueDate != other.dueDate;
}
