#ifndef TEST_CHILDARRAYFOREST_H
#define TEST_CHILDARRAYFOREST_H
#include <cstdint>
#include <string>
using namespace std;
#include "../Test.h"

typedef int64_t Int;

class Test_ChildArrayForest : public Test{
public:
    Test_ChildArrayForest();
    virtual ~Test_ChildArrayForest();

    virtual void Execute();
    virtual string GetName();
public:
    static bool MatchInt(const Int& object, const Int& key);
    static void AddOne(Int& element);
};

#endif // TEST_CHILDARRAYFOREST_H
