//
// Created by 2003j on 9/28/2022.
//

#include "User.h"
#include <iostream>
using namespace std;
//setters
void User::setName(std::string n) {
    name = n;
}
void User::setAlias(string a) {
    alias = a;
}
void User::setPassword(std::string p) {
    password = p;
}
void User::setUserType(string u){
    if (u == "NORMAL"){
        userType = NORMAL;
    }
    else{
        userType = SUPERUSER;
    }
}
//getters
string User::getName() {
    return name;
}
string User::getAlias() {
    return alias;
}
string User::getPassword() {
    return password;
}
int User::getTypeUser(){
    return userType;
}
//constructors
User::User(std::string n, std::string a, std::string p) {
    name = n;
    alias = a;
    password = p;
    userType = NORMAL;
}
User::User() {
    name = "";
    alias = "";
    password = "";
    userType = NORMAL;
}
//virtual function
void User::viewReactions(int postId, const Area &a){
    cout << "You are not a Super User"<<endl;
}