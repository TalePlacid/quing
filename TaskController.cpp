#include "TaskController.h"

#pragma warning(disable:4996)

TaskController::TaskController(){

}

TaskController::~TaskController(){

}

Task& TaskController::Attach(){
    return this->Attach(Task());
}

Task& TaskController::Attach(const string& uuid, const string& title, const string& detail, const DateTime& createdAt){
    return this->Attach(Task(uuid, title, detail, createdAt));
}

Task& TaskController::Attach(const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Insert(task);

    return node->GetElement();
}

Task& TaskController::Attach(const Task& parent, const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(parent, this->MatchTask);
    node = this->tasks.Insert(node, task);

    return node->GetElement();
}

Task& TaskController::Attach(const Task& parent, const string& uuid, const string& title, const string& detail, const DateTime& createdAt){
    return this->Attach(parent, Task(uuid, title, detail, createdAt));
}

void TaskController::Detach(const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    if (node != 0)
    {
        this->tasks.Delete(node);
    }
}

Task* TaskController::Search(const string& uuid){
    Task* task = 0;
    ChildArrayForest<Task>::Node* node = this->tasks.Search(uuid, this->MatchUUID);
    if (node != 0)
    {
        task = &node->GetElement();
    }

    return task;
}

Task& TaskController::Modify(const Task& task, const string& title, const string& detail){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& modifiedTask = node->GetElement();
    modifiedTask.Modify(title, detail);

    return modifiedTask;
}

Task& TaskController::ScheduleFor(const Task& task, const DateTime& dueDate){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& scheduledTask = node->GetElement();
    scheduledTask.ScheduleFor(dueDate);

    return scheduledTask;
}

Task& TaskController::ClearDueDate(const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& clearedTask = node->GetElement();
    clearedTask.ClearDueDate();

    return clearedTask;
}

Task& TaskController::ChangeCategory(const Task& task, Category category){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& changedTask = node->GetElement();
    changedTask.ChangeCategory(category);

    return changedTask;
}

Task& TaskController::RecordCompletionAt(const Task& task, const DateTime& completedAt){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& recordedTask = node->GetElement();
    recordedTask.RecordCompletionAt(completedAt);

    return recordedTask;
}

Task& TaskController::ClearCompletionAt(const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& clearedTask = node->GetElement();
    clearedTask.ClearCompletionAt();

    return clearedTask;
}

Task& TaskController::MarkUrgent(const Task& task, bool isUrgent){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& markedTask = node->GetElement();
    markedTask.MarkUrgent(isUrgent);

    return markedTask;
}

Task& TaskController::Move(const Task& task, Int index){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    Task& movedTask = node->GetElement();
    this->tasks.MoveNode(node, index);

    return movedTask;
}

Task& TaskController::MoveAsChild(const Task& parent, const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    ChildArrayForest<Task>::Node* parentNode = this->tasks.Search(parent, this->MatchTask);
    Task& movedTask = node->GetElement();

    this->tasks.MoveAsChild(node, parentNode);

    return movedTask;
}

Task& TaskController::MoveAsChild(const Task& parent, Int index, const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);
    ChildArrayForest<Task>::Node* parentNode = this->tasks.Search(parent, this->MatchTask);
    Task& movedTask = node->GetElement();
    this->tasks.MoveAsChild(node, parentNode, index);

    return movedTask;
}

Task* TaskController::GetParentTask(const Task& task, Int level){
    Task* parentTask = 0;
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);

    Int i = 0;
    while (i < level && node != 0)
    {
        node = node->GetParent();
        i++;
    }

    if (node != 0)
    {
        parentTask = &node->GetElement();
    }

    return parentTask;
}

vector<ChildArrayForest<Task>::OrderEntry> TaskController::GetPreOrderEntries(){
    return this->tasks.GetPreOrderEntries(0);
}

vector<ChildArrayForest<Task>::OrderEntry> TaskController::GetPreOrderEntries(const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);

    return this->tasks.GetPreOrderEntries(node);
}

vector<ChildArrayForest<Task>::OrderEntry> TaskController::GetPostOrderEntries(){
    return this->tasks.GetPostOrderEntries(0);
}

vector<ChildArrayForest<Task>::OrderEntry> TaskController::GetPostOrderEntries(const Task& task){
    ChildArrayForest<Task>::Node* node = this->tasks.Search(task, this->MatchTask);

    return this->tasks.GetPostOrderEntries(node);
}

Int TaskController::GetLength() const{
    return this->tasks.GetLength();
}

bool TaskController::MatchUUID(const Task& task, const string& uuid){
    return task.GetUUID() == uuid;
}

bool TaskController::MatchTask(const Task& element, const Task& task){
    return element.EqualsByUUID(task);
}
