#ifndef TEST_H
#define TEST_H
#include <string>
using namespace std;

class Test{
public:
    Test();
    virtual ~Test() = 0;

    virtual bool Setup();
    virtual void Execute() = 0;
    virtual void Teardown();

    virtual string GetName() = 0;
};

#endif // TEST_H
