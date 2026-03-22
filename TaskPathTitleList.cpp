#include "TaskPathTitleList.h"

TaskPathTitleList::TaskPathTitleList()
    : titles(0)
{
    this->length = 0;
}

TaskPathTitleList::~TaskPathTitleList()
{
}

void TaskPathTitleList::Append(const string& title)
{
    this->titles.push_back(title);
    this->length++;
}

const string& TaskPathTitleList::GetAt(Int index) const
{
    return this->titles[static_cast<size_t>(index)];
}

Int TaskPathTitleList::GetLength() const
{
    return this->length;
}
