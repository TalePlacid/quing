#ifndef TEST_TASKNAVIGATIONSERVICE_H
#define TEST_TASKNAVIGATIONSERVICE_H
#include <string>
using namespace std;
#include "../Test.h"

class Test_TaskNavigationService : public Test
{
public:
    Test_TaskNavigationService();
    virtual ~Test_TaskNavigationService();

    virtual void Execute();
    virtual string GetName();
};

#endif // TEST_TASKNAVIGATIONSERVICE_H
