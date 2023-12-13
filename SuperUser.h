//
// Created by 2003j on 10/6/2022.
//

#ifndef BLOG3_SUPERUSER_H
#define BLOG3_SUPERUSER_H
#include "User.h"
#include <iostream>
#include "Area.h"
using namespace std;
class SuperUser : public User{
public:
    SuperUser();
    SuperUser(string n, string a, string p);
    void viewReactions(int postId, const Area &a);
private:

};


#endif //BLOG3_SUPERUSER_H
