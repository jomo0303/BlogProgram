//
// Created by 2003j on 9/28/2022.
//

#ifndef BLOG3_USER_H
#define BLOG3_USER_H
#include <iostream>
#include "Area.h"
using namespace std;
class User {
public:
    //enumeration
    enum userType {NORMAL, SUPERUSER};
    //setters
    void setName(string n);
    void setAlias(string a);
    void setPassword(string p);
    void setUserType(string u);
    //getters
    string getName();
    string getAlias();
    string getPassword();
    int getTypeUser();
    //constructor
    User(string n, string a, string p);
    User();
    //virtual function
    virtual void viewReactions(int postId, const Area &a);
private:
    //variables
    string name;
    string alias;
    string password;
    int userType;
};


#endif //BLOG3_USER_H
