#include "Test_Task.h"
#include "../../Task.h"
#include "../Local8BitStringConverter.h"
#include "../AssertReporter.h"

#pragma warning(disable:4996)

Test_Task::Test_Task(){

}

Test_Task::~Test_Task(){

}

void Test_Task::Execute(){
    Task task1;
    AssertReporter::Assert(task1.GetUUID() == ""
                   && task1.GetTitle() == ""
                   && task1.GetDetail() == ""
                   && task1.GetCategory() == PENDING
                   && task1.IsUrgent() == false
                   && task1.GetCreatedAt() == DateTime()
                   && task1.GetDueDate() == DateTime()
                   && task1.GetCompletedAt() == DateTime(),
                           Local8BitStringConverter::Convert("기본생성자 테스트 실패"));

    Task task2("12345678-1234-5678-9abc-1234567890ab", "작업 제목", "세부 내용 점검", DateTime(2026, 3, 15, 9, 30, 15));
    AssertReporter::Assert(task2.GetUUID() == "12345678-1234-5678-9abc-1234567890ab"
                   && task2.GetTitle() == "작업 제목"
                   && task2.GetDetail() == "세부 내용 점검"
                   && task2.GetCategory() == PENDING
                   && task2.IsUrgent() == false
                   && task2.GetCreatedAt() == DateTime(2026, 3, 15, 9, 30, 15)
                   && task2.GetDueDate() == DateTime()
                   && task2.GetCompletedAt() == DateTime(),
                           Local8BitStringConverter::Convert("인자생성자 테스트 실패"));

    Task task3(task2);
    AssertReporter::Assert(task3 == task2,
                           Local8BitStringConverter::Convert("복사생성자 테스트 실패"));

    Task task4;
    task4 = task2;
    AssertReporter::Assert(task4 == task2,
                           Local8BitStringConverter::Convert("치환연산자 테스트 실패"));

    task2.Modify("수정된 제목", "수정된 세부 내용");
    AssertReporter::Assert(task2.GetTitle() == "수정된 제목"
                   && task2.GetDetail() == "수정된 세부 내용",
                           Local8BitStringConverter::Convert("Modify 테스트 실패"));

    task2.ScheduleFor(DateTime(2026, 3, 17, 18, 45, 0));
    AssertReporter::Assert(task2.GetDueDate() == DateTime(2026, 3, 17, 18, 45, 0),
                           Local8BitStringConverter::Convert("ScheduleFor 테스트 실패"));

    task2.ClearDueDate();
    AssertReporter::Assert(task2.GetDueDate() == DateTime(),
                           Local8BitStringConverter::Convert("ClearDueDate 테스트 실패"));

    task2.ChangeCategory(IN_PROGRESS);
    AssertReporter::Assert(task2.GetCategory() == IN_PROGRESS,
                           Local8BitStringConverter::Convert("ChangeCategory 테스트 실패"));

    task2.RecordCompletionAt(DateTime(2026, 3, 18, 22, 10, 5));
    AssertReporter::Assert(task2.GetCompletedAt() == DateTime(2026, 3, 18, 22, 10, 5),
                           Local8BitStringConverter::Convert("RecordCompletionAt 테스트 실패"));

    task2.MarkUrgent(true);
    AssertReporter::Assert(task2.IsUrgent() == true,
                           Local8BitStringConverter::Convert("MarkUrgent 테스트 실패"));

    Task* task7 = 0;
    task7 = task2.Clone();
    AssertReporter::Assert(*task7 == task2,
                           Local8BitStringConverter::Convert("Clone 테스트 실패"));

    Task task5("12345678-1234-5678-9abc-1234567890ab", "다른 제목", "다른 내용", DateTime(2026, 3, 14, 10, 0, 0));
    Task task6("abcdef12-3456-7890-abcd-ef1234567890", "비교 제목", "비교 내용", DateTime(2026, 3, 19, 11, 5, 30));
    AssertReporter::Assert(task2.EqualsByUUID(task5) == true,
                           Local8BitStringConverter::Convert("EqualsByUUID 테스트 실패"));

    AssertReporter::Assert(task2.IsEqual(*task7) == true,
                           Local8BitStringConverter::Convert("IsEqual 테스트 실패"));

    AssertReporter::Assert(task2.IsNotEqual(task6) == true,
                           Local8BitStringConverter::Convert("IsNotEqual 테스트 실패"));

    AssertReporter::Assert((task2 == *task7) == true,
                           Local8BitStringConverter::Convert("operator== 테스트 실패"));

    AssertReporter::Assert((task2 != task6) == true,
                           Local8BitStringConverter::Convert("operator!= 테스트 실패"));

    delete task7;
}

string Test_Task::GetName(){
    return "Test_Task";
}
