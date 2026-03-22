#include "Test_TaskController.h"
#include "../../TaskController.h"
#include "../Local8BitStringConverter.h"
#include "../AssertReporter.h"

#pragma warning(disable:4996)

Test_TaskController::Test_TaskController(){

}

Test_TaskController::~Test_TaskController(){

}

void Test_TaskController::Execute(){
    TaskController taskController;
    Task task;
    Task task2("22222222-2222-2222-2222-222222222222", "제목 2", "세부 2", DateTime(2026, 3, 21, 9, 5, 0));
    Task task3("33333333-3333-3333-3333-333333333333", "제목 3", "세부 3", DateTime(2026, 3, 21, 9, 10, 0));
    Task task4("44444444-4444-4444-4444-444444444444", "제목 4", "세부 4", DateTime(2026, 3, 22, 0, 0, 0));
    Task* searchedTask = 0;

    // 1. task(기본 Task)를 붙인다.
    Task& attachedTask = taskController.Attach();
    AssertReporter::Assert(attachedTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && taskController.GetLength() == 1,
                           Local8BitStringConverter::Convert("기본 생성자 붙이다 실패"));

    // 2. 인자 생성 붙인다.
    Task& attachedTask1 = taskController.Attach("11111111-1111-1111-1111-111111111111", "제목1", "세부1", DateTime(2026, 3, 21, 9, 0, 0));
    AssertReporter::Assert(attachedTask1.GetUUID() == "11111111-1111-1111-1111-111111111111"
                   && attachedTask1.GetTitle() == "제목1"
                   && attachedTask1.GetDetail() == "세부1"
                   && attachedTask1.GetCreatedAt() == DateTime(2026, 3, 21, 9, 0, 0)
                   && attachedTask1.GetCategory() == PENDING
                   && attachedTask1.IsUrgent() == false
                   && attachedTask1.GetDueDate() == DateTime()
                   && attachedTask1.GetCompletedAt() == DateTime()
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(attachedTask1), vector<ChildArrayForest<Task>::OrderEntry>({{attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(attachedTask1), vector<ChildArrayForest<Task>::OrderEntry>({{attachedTask1, 0}}))
                   && taskController.GetLength() == 2,
                           Local8BitStringConverter::Convert("인자 생성 붙이다 실패"));

    // 3. task2를 붙인다.
    Task& attachedTask2 = taskController.Attach(task2);
    AssertReporter::Assert(attachedTask2.IsEqual(task2)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task2, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("task2 붙이다 실패"));

    // 4. task3를 task1의 자식으로 붙인다.
    Task& attachedTask3 = taskController.Attach(attachedTask1, task3);
    AssertReporter::Assert(attachedTask3.IsEqual(task3)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task3, 1}, {task2, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {task3, 1}, {attachedTask1, 0}, {task2, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(attachedTask1), vector<ChildArrayForest<Task>::OrderEntry>({{attachedTask1, 0}, {task3, 1}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(attachedTask1), vector<ChildArrayForest<Task>::OrderEntry>({{task3, 1}, {attachedTask1, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("task3를 task1의 자식으로 붙이다 실패"));

    // 5. task4를 task3의 자식으로 붙인다.
    Task& attachedTask4 = taskController.Attach(task3, task4);
    AssertReporter::Assert(attachedTask4.IsEqual(task4)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task3, 1}, {task4, 2}, {task2, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {task4, 2}, {task3, 1}, {attachedTask1, 0}, {task2, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(task3), vector<ChildArrayForest<Task>::OrderEntry>({{task3, 0}, {task4, 1}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(task3), vector<ChildArrayForest<Task>::OrderEntry>({{task4, 1}, {task3, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("task4를 task3의 자식으로 붙이다 실패"));

    // 6. ""으로 검색한다.
    searchedTask = taskController.Search("");
    AssertReporter::Assert(searchedTask != 0
                   && searchedTask->IsEqual(task)
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("빈 문자열로 검색하다 실패"));

    // 7. 검색된 task의 제목과 내용을 수정한다.
    Task& modifiedTask = taskController.Modify(*searchedTask, "제목0", "세부0");
    task.Modify("제목0", "세부0");
    searchedTask = &modifiedTask;
    AssertReporter::Assert(modifiedTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task3, 1}, {task4, 2}, {task2, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {task4, 2}, {task3, 1}, {attachedTask1, 0}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 제목과 내용을 수정하다 실패"));

    // 8. 검색된 task의 마감일자를 설정한다.
    Task& scheduledTask = taskController.ScheduleFor(*searchedTask, DateTime(2026, 3, 22, 0, 9, 30));
    task.ScheduleFor(DateTime(2026, 3, 22, 0, 9, 30));
    searchedTask = &scheduledTask;
    AssertReporter::Assert(scheduledTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(*searchedTask), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(*searchedTask), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 마감일자를 설정하다 실패"));

    // 9. 검색된 task의 마감일자를 비운다.
    Task& clearedDueDateTask = taskController.ClearDueDate(*searchedTask);
    task.ClearDueDate();
    searchedTask = &clearedDueDateTask;
    AssertReporter::Assert(clearedDueDateTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {task4, 2}, {task3, 1}, {attachedTask1, 0}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 마감일자를 비우다 실패"));

    // 10. 검색된 task의 완료일자를 기록한다.
    Task& recordedTask = taskController.RecordCompletionAt(*searchedTask, DateTime(2026, 3, 23, 18, 0, 0));
    task.RecordCompletionAt(DateTime(2026, 3, 23, 18, 0, 0));
    searchedTask = &recordedTask;
    AssertReporter::Assert(recordedTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task3, 1}, {task4, 2}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 완료일자를 기록하다 실패"));

    // 11. 검색된 task의 카테고리를 COMPLETED로 바꾼다.
    Task& completedTask = taskController.ChangeCategory(*searchedTask, COMPLETED);
    task.ChangeCategory(COMPLETED);
    searchedTask = &completedTask;
    AssertReporter::Assert(completedTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(*searchedTask), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 카테고리를 COMPLETED로 바꾸다 실패"));

    // 12. 검색된 task의 완료일자를 비운다.
    Task& clearedCompletionTask = taskController.ClearCompletionAt(*searchedTask);
    task.ClearCompletionAt();
    searchedTask = &clearedCompletionTask;
    AssertReporter::Assert(clearedCompletionTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {task4, 2}, {task3, 1}, {attachedTask1, 0}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 완료일자를 비우다 실패"));

    // 13. 검색된 task의 카테고리를 DEFERRED로 바꾼다.
    Task& deferredTask = taskController.ChangeCategory(*searchedTask, DEFERRED);
    task.ChangeCategory(DEFERRED);
    searchedTask = &deferredTask;
    AssertReporter::Assert(deferredTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(*searchedTask), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task의 카테고리를 DEFERRED로 바꾸다 실패"));

    // 14. 검색된 task를 긴급 체크한다.
    Task& markedTask = taskController.MarkUrgent(*searchedTask, true);
    task.MarkUrgent(true);
    searchedTask = &markedTask;
    AssertReporter::Assert(markedTask.IsEqual(task)
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(*searchedTask), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("검색된 task를 긴급 체크하다 실패"));

    // 15. taskController를 복사생성하여 copy를 만든다.
    TaskController copy(taskController);
    AssertReporter::Assert(this->IsSameOrderEntries(copy.GetPreOrderEntries(), taskController.GetPreOrderEntries())
                   && this->IsSameOrderEntries(copy.GetPostOrderEntries(), taskController.GetPostOrderEntries())
                   && copy.GetLength() == taskController.GetLength(),
                           Local8BitStringConverter::Convert("taskController를 복사생성하여 copy를 만들다 실패"));

    // 16. taskController의 루트들에서 task2를 0번 인덱스로 옮긴다.
    Task& movedTask2 = taskController.Move(task2, 0);
    AssertReporter::Assert(movedTask2.IsEqual(task2)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task2, 0}, {task, 0}, {attachedTask1, 0}, {task3, 1}, {task4, 2}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task2, 0}, {task, 0}, {task4, 2}, {task3, 1}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(copy.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}, {task3, 1}, {task4, 2}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("taskController의 루트들에서 task2를 0번 인덱스로 옮기다 실패"));

    // 17. task3를 task2의 자식으로 옮긴다.
    Task& movedTask3 = taskController.MoveAsChild(task2, task3);
    AssertReporter::Assert(movedTask3.IsEqual(task3)
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task2, 0}, {task3, 1}, {task4, 2}, {task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(task2), vector<ChildArrayForest<Task>::OrderEntry>({{task2, 0}, {task3, 1}, {task4, 2}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task4, 2}, {task3, 1}, {task2, 0}, {task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(task2), vector<ChildArrayForest<Task>::OrderEntry>({{task4, 2}, {task3, 1}, {task2, 0}}))
                   && taskController.GetLength() == 3,
                           Local8BitStringConverter::Convert("task3를 task2의 자식으로 옮기다 실패"));

    // 18. task4를 뗀다.
    taskController.Detach(task4);
    AssertReporter::Assert(this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task2, 0}, {task3, 1}, {task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task3, 1}, {task2, 0}, {task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPreOrderEntries(task2), vector<ChildArrayForest<Task>::OrderEntry>({{task2, 0}, {task3, 1}}))
                   && taskController.GetLength() == 3
                   && taskController.Search("44444444-4444-4444-4444-444444444444") == 0,
                           Local8BitStringConverter::Convert("task4를 떼다 실패"));

    // 19. task2를 뗀다.
    taskController.Detach(task2);
    AssertReporter::Assert(this->IsSameOrderEntries(taskController.GetPreOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}}))
                   && this->IsSameOrderEntries(taskController.GetPostOrderEntries(), vector<ChildArrayForest<Task>::OrderEntry>({{task, 0}, {attachedTask1, 0}}))
                   && taskController.GetLength() == 2
                   && taskController.Search("22222222-2222-2222-2222-222222222222") == 0
                   && taskController.Search("33333333-3333-3333-3333-333333333333") == 0,
                           Local8BitStringConverter::Convert("task2를 떼다 실패"));

    // 20. copy = taskController 로 치환연산한다.
    copy = taskController;
    AssertReporter::Assert(this->IsSameOrderEntries(copy.GetPreOrderEntries(), taskController.GetPreOrderEntries())
                   && this->IsSameOrderEntries(copy.GetPostOrderEntries(), taskController.GetPostOrderEntries())
                   && copy.GetLength() == taskController.GetLength(),
                           Local8BitStringConverter::Convert("copy에 치환연산하다 실패"));
}

string Test_TaskController::GetName(){
    return "Test_TaskController";
}

bool Test_TaskController::IsSameOrderEntries(
    const vector<ChildArrayForest<Task>::OrderEntry>& left,
    const vector<ChildArrayForest<Task>::OrderEntry>& right){
    bool isSame = left.size() == right.size();
    size_t i = 0;

    while (isSame == true && i < left.size())
    {
        isSame = left[i].level == right[i].level
                && left[i].element.IsEqual(right[i].element);
        i++;
    }

    return isSame;
}
