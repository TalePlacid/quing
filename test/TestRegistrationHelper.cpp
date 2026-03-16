#include "TestRegistrationHelper.h"
#include "Tester.h"
#include "domain/Test_Task.h"

#pragma warning(disable:4996)

TestRegistrationHelper::TestRegistrationHelper(){

}

TestRegistrationHelper::~TestRegistrationHelper(){

}

void TestRegistrationHelper::RegisterAll(Tester& tester){
    tester.Register(new Test_Task());
}
