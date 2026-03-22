#include "NavigationState.h"

NavigationState::NavigationState()
    :currentUUID("") {

}

NavigationState::~NavigationState(){

}

void NavigationState::MoveRoot(){
    this->currentUUID = "";
}

void NavigationState::MoveTo(const string& uuid){
    this->currentUUID = uuid;
}

const string& NavigationState::GetCurrentUUID() const{
    return this->currentUUID;
}
