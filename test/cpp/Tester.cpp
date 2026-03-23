#include <iostream>
using namespace std;
#include "Tester.h"
#include "Test.h"
#include "TestRegistrationHelper.h"

#pragma warning(disable:4996)

Tester::Tester(){
    this->length = 0;
}

Tester::~Tester(){
    Int i = 0;
    while (i < this->length)
    {
        delete this->tests[i];
        i++;
    }
}

Int Tester::Register(Test* test){
    this->tests.push_back(test);
    this->length++;

    return this->length - 1;
}

void Tester::Run(){
    bool isSetupDone;
    bool isTeardownStarted;
    Test *test = 0;
    Int i = 0;
    while (i < this->tests.size())
    {
        test = this->tests[i];
        isSetupDone = false;
        isTeardownStarted = false;
        try
        {
            isSetupDone = test->Setup();
            test->Execute();
            if (isSetupDone)
            {
                isTeardownStarted = true;
                test->Teardown();
            }
            cout << "[PASS] " << test->GetName() << endl;
        }
        catch (const exception& error)
        {
            cerr << "[FAIL] " << test->GetName() << endl;
            cerr << error.what() << endl;
            if (isSetupDone && !isTeardownStarted)
            {
                try
                {
                    isTeardownStarted = true;
                    test->Teardown();
                }
                catch (const exception& error)
                {
                    cerr << "[FAIL] " << test->GetName() << endl;
                    cerr << error.what() << endl;
                }
            }
        }
        i++;
    }
}
