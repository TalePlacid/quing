#ifndef ASSERTREPORTER_H
#define ASSERTREPORTER_H
#include <string>
using namespace std;

class AssertReporter{
public:
    AssertReporter();
    ~AssertReporter();

    static void Assert(bool condition, string message);
};

#endif // ASSERTREPORTER_H
