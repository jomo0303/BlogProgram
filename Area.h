//
// Created by 2003j on 9/19/2022.
//
#include <iostream>
#include <vector>
using namespace std;
#include "Post.h"
#ifndef BLOG3_AREA_H
#define BLOG3_AREA_H
class Area {
public:
    // return the name of the Area
    const string getName() const;
    //return the description of the Area
    const string getDesc() const;
    //set the name of the Area
    void setName(string nm);

    // add post
    int AddPost(Post post);
    //edit post
    void EditPost(Post post, int i);
    // get post
    const bool getPost(int i, Post &p) const;
    // set Area Description
    void setDescription(string d);
    //get Posts array size
    const int getPostsSize() const;
    //friend << operator
    friend ostream& operator <<(ostream& outputStream, const Area& area);
    //delete post
    void DeletePost(int PostChoice);
    //react to post
    void reactToPost(int p, int r, string a);
    friend void viewReactions();
private:
    string Name; //name of Area
    vector<Post> Posts;//array of posts
    string AreaDescription; //description of area
};


#endif //BLOG3_AREA_H
