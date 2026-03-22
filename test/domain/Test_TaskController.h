#ifndef TEST_TASKCONTROLLER_H
#define TEST_TASKCONTROLLER_H
#include "../Test.h"
#include "../../TaskController.h"

class Test_TaskController : public Test{
public:
    Test_TaskController();
    virtual ~Test_TaskController();

    virtual void Execute();
    virtual string GetName();
private:
    static bool IsSameOrderEntries(
        const vector<ChildArrayForest<Task>::OrderEntry>& left,
        const vector<ChildArrayForest<Task>::OrderEntry>& right);
};

#endif // TEST_TASKCONTROLLER_H
