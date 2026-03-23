#ifndef TESTREGISTRATIONHELPER_H
#define TESTREGISTRATIONHELPER_H

class Tester;

class TestRegistrationHelper{
public:
    TestRegistrationHelper();
    ~TestRegistrationHelper();

    static void RegisterAll(Tester& tester);
};

#endif // TESTREGISTRATIONHELPER_H
