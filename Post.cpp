//
// Created by 2003j on 9/19/2022.
//

#include "Post.h"
#include <iostream>
#include <iomanip>
using namespace std;
//implementing setters
void Post::SetTitle(string t) {
    title = t;
}

void Post::SetBody(string b) {
    body = b;
}

void Post::SetUser(string u) {
    user = u;
}
const string Post::getTitle(){
    return this->title;
}
const string Post::getUser() {
    return this->user;
}
const string Post::getBody() {
    return this->body;
}

bool Post::operator==(Post p1) {
    if (title == p1.title) {
        return true;
    }
    else {
        return false;
    }
}
//friend operator definitions
ostream &operator<<(ostream &outputStream, const Post &post) {
    outputStream<<"Title: " << post.title<<endl;
    outputStream<<"By: " << post.user<<endl;
    outputStream<<"Text: "<<post.body<<endl;
    if (post.numReactions > 0){
        outputStream<<"Num Love: "<<setw(15) << post.numLove<<endl;
        outputStream<<"Num Like: "<<setw(15) << post.numLike<<endl;
        outputStream<<"Num Dislike: "<<setw(12) << post.numDislike<<endl;
        outputStream<<"Num Hate: "<<setw(15) << post.numHate<<endl;
    }
    return outputStream;
}
//constructors
Post::Post(string t, string b, string u){
    title =t;
    body = b;
    user = u;
}
Post::Post(){
    title = "";
    user = "";
    body = "";
}
//adding reactions
void Post::addReaction(int c, string a){
    //increments variable depending on value sent in
    switch (c) {
        case 1:
            numLove++;
            numReactions++;
            reactors.push_back(a);
            reactions.push_back(c);
            break;
        case 2:
            numLike++;
            numReactions++;
            reactors.push_back(a);
            reactions.push_back(c);
            break;
        case 3:
            numDislike++;
            numReactions++;
            reactors.push_back(a);
            reactions.push_back(c);
            break;
        case 4:
            numHate++;
            numReactions++;
            reactors.push_back(a);
            reactions.push_back(c);
            break;
        default:
            break;
    }
}
//seeing reactions
void Post::seeReactions(){
    //loops through the reactions and reactors and outputs them
        for (int i = 0; i < reactors.size(); ++i) {
            //switch statement that converts ints to love, like ...
            switch (reactions[i]) {
                case 1:
                    cout << reactors[i] << " reacted with " << "Love" << endl;
                    break;
                case 2:
                    cout << reactors[i] << " reacted with " << "Like" << endl;
                    break;
                case 3:
                    cout << reactors[i] << " reacted with " << "Dislike" << endl;
                    break;
                case 4:
                    cout << reactors[i] << " reacted with " << "Hate" << endl;
            }

        }
}
//more getters
const int Post::getReaction(int i) {
    return reactions[i];
}
const string Post::getReactor(int i) {
    return reactors[i];
}
const int Post::getNumReactions(){
    return numReactions;
}
