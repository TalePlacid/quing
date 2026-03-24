#include "TestRegistrationHelper.h"
#include "Tester.h"
#include "application/Test_TaskNavigationService.h"
#include "domain/Test_Task.h"
#include "domain/Test_ChildArrayForest.h"
#include "domain/Test_TaskController.h"
#include "presentation/Test_TaskNavigatorViewModel.h"

#pragma warning(disable:4996)

TestRegistrationHelper::TestRegistrationHelper(){

}

TestRegistrationHelper::~TestRegistrationHelper(){

}

void TestRegistrationHelper::RegisterAll(Tester& tester){
    tester.Register(new Test_Task());
    tester.Register(new Test_ChildArrayForest());
    tester.Register(new Test_TaskController());
    tester.Register(new Test_TaskNavigationService());
    tester.Register(new Test_TaskNavigatorViewModel());
}
