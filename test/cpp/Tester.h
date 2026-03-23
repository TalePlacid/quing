#ifndef TESTER_H
#define TESTER_H
#include <vector>
#include <cstdint>
using namespace std;

typedef int64_t Int;

class Test;

class Tester{
public:
    Tester();
    ~Tester();
    Tester(const Tester& source) = delete;
    Tester& operator=(const Tester& source) = delete;

    Int Register(Test* test);
    void Run();
private:
    vector<Test*> tests;
    Int length;
};

#endif // TESTER_H
