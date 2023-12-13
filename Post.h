//
// Created by 2003j on 9/19/2022.
//

//
// Created by 2003j on 9/19/2022.
//
#include <iostream>
#include <vector>
using namespace std;
#ifndef BLOG3_POST_H
#define BLOG3_POST_H


class Post {

public:
    //setters
    void SetTitle(string t);
    void SetUser(string u);
    void SetBody(string b);
    //getters
    const string getTitle();
    const string getUser();
    const string getBody();
    const int getReaction(int i);
    const string getReactor(int i);
    const int getNumReactions();
    //constructor
    Post(string t, string b, string u);
    Post();
    //friend function
    friend ostream& operator <<(ostream& outputStream, const Post& post);
    bool operator ==(Post p1);
    //adding reaction functions
    void addReaction(int c, string a);
    void seeReactions();

private:
    string title;
    string user;
    string body;
    int numLove = 0;
    int numLike = 0;
    int numDislike = 0;
    int numHate = 0;
    int numReactions = 0;
    //parallel vectors to store alias and what they reacted with
    vector<string> reactors;
    vector<int> reactions;
};


#endif //BLOG3_POST_H
