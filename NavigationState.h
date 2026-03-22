#ifndef NAVIGATIONSTATE_H
#define NAVIGATIONSTATE_H
#include <string>
using namespace std;

class NavigationState{
public:
    NavigationState();
    ~NavigationState();

    void MoveRoot();
    void MoveTo(const string& uuid);

    const string& GetCurrentUUID() const;
private:
    string currentUUID;
};

#endif // NAVIGATIONSTATE_H
