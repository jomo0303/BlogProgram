//
// Created by 2003j on 9/19/2022.
//
#include <iostream>
using namespace std;
#include "Area.h"


const int MAX_NUM_POSTS = 10;
// add post
int Area::AddPost(Post p) {
    //validate that less than MAX_NUM_POSTS have been added
    // to this blog
    if (Posts.size() < MAX_NUM_POSTS) {
        this->Posts.push_back(p);
        return 1;
    } else
        //invalid no room for new post
        return -1;
}

//edit post
void Area::EditPost(Post post, int i) {
    this->Posts[i] = post;
}
const bool Area::getPost(int i, Post &p) const {
    if (i < Posts.size()) // i is valid
    {
        p = this->Posts[i]; //set post
        return true; //return true
    } else { //i is not valid
        return false; //return false
    }
}
// set Area Description
void Area::setDescription(string d){
    AreaDescription = d;
}

//get Posts array size
const int Area::getPostsSize() const {
    return this->Posts.size();
}
// return the name of the Area
const string Area::getName() const {
    return this->Name;
};

//set the name of the Area
void Area::setName(string nm) {
    Name = nm;
};
//deletes a post
void Area::DeletePost(int PostChoice){
    Posts.erase(Posts.begin()+PostChoice);
    cout << "Post deleted"<<endl;
}
//returns description
const string Area::getDesc() const {
    return AreaDescription;
}
ostream &operator<<(ostream &outputStream, const Area &area) {
    outputStream << "Area Name: " << area.Name << endl;
    outputStream << "Area Description: " << area.AreaDescription<<endl;
    return outputStream;
}
void Area::reactToPost(int p, int r, string a){
    //switch statement to know which reaction to add
    switch (r) {
        case 1:
            Posts[p].addReaction(1, a);
            break;
        case 2:
            Posts[p].addReaction(2, a);
            break;
        case 3:
            Posts[p].addReaction(3, a);
            break;
        case 4:
            Posts[p].addReaction(4, a);
            break;
        default:
            break;
    }
}
