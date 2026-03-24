#ifndef TEST_TASKNAVIGATORVIEWMODEL_H
#define TEST_TASKNAVIGATORVIEWMODEL_H
#include <string>
using namespace std;
#include "ViewModelTest.h"

class Test_TaskNavigatorViewModel : public ViewModelTest
{
public:
    Test_TaskNavigatorViewModel();
    virtual ~Test_TaskNavigatorViewModel();

    virtual void Execute();
    virtual string GetName();
};

#endif // TEST_TASKNAVIGATORVIEWMODEL_H
