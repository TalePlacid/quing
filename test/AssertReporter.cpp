#include <stdexcept>
using namespace std;
#include "AssertReporter.h"

#pragma warning(disable:4996)

AssertReporter::AssertReporter(){

}

AssertReporter::~AssertReporter(){

}

void AssertReporter::Assert(bool condition, string message){
    if(!condition)
    {
        throw runtime_error(message);
    }
}
