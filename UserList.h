//
// Created by 2003j on 10/21/2022.
//

#ifndef BLOG3_USERLIST_H
#define BLOG3_USERLIST_H
using namespace std;
#include <vector>
#include <iostream>
#include "User.h"
template <class T> class UserList {
public:
    void addUser(T user);
    void displayUser(int i);
    int getUsersSize();
private:
    vector <User*> users;
};


#endif //BLOG3_USERLIST_H
