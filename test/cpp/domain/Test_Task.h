#ifndef TEST_TASK_H
#define TEST_TASK_H
#include <string>
using namespace std;
#include "../Test.h"

class Test_Task : public Test{
public:
    Test_Task();
    virtual ~Test_Task();

    virtual void Execute();
    virtual string GetName();
};

#endif // TEST_TASK_H
