#ifndef TASKPATHTITLELIST_H
#define TASKPATHTITLELIST_H

#include <string>
#include <vector>
using namespace std;

#include "Task.h"

class TaskPathTitleList
{
public:
    TaskPathTitleList();
    ~TaskPathTitleList();

    void Append(const string& title);

    const string& GetAt(Int index) const;
    Int GetLength() const;

private:
    vector<string> titles;
    Int length;
};

#endif // TASKPATHTITLELIST_H
