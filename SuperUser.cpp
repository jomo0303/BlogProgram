//
// Created by 2003j on 10/6/2022.
//

#include "SuperUser.h"
#include <string>
using namespace std;
SuperUser::SuperUser() : User(){
    setUserType("SUPERUSER");
}
SuperUser::SuperUser(std::string n, std::string a, std::string p){
    setUserType("SUPERUSER");
    setName(n);
    setAlias(a);
    setPassword(p);
}
//virtual function that shows reactions and who reacted
void SuperUser::viewReactions(int postId, const Area &a) {
    //creates post
    Post p;
    //gets post
    a.getPost(postId, p);
    //calls see reactions for the post
    cout << p;
    p.seeReactions();
}