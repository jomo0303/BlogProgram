#include <iostream>
#include <vector>
#include "Area.h"
#include "Post.h"
#include "User.h"
#include "SuperUser.h"
#include <fstream>
#include "UserList.h"
#include "UserList.cpp"
/* Name: Joseph Bustamante
Date: 9/4/22
Section: COP3330
Assignment: 2
Due Date: 9/4/22
About this project: This project uses classes and functions to make a blog type program
Assumptions: User enters ints and chars when they are supposed to
All work below was performed by Joseph Bustamante */

using namespace std;
//maximum number of Posts
const int MAX_NUM_POSTS = 10;
template<class T>
void readUserData(vector<T>){

}
//display menu
void displayMenu();

//User selects an action
void promptAction(string &strCh);

//implement Action
void implementAction(vector<Area>* areas, const string &strCh, User *u, UserList<User*>& users);

//displays all blog areas names + descriptions
void DisplayBlogAreas(const vector<Area>& areas);

//displays all posts in a blog
void DisplayPostsABlog(const Area& a);

//get a valid blog area id
int getValidBlogArea(int numAreas);

//get a valid post id
int getValidPost(const Area& a);

//displays a post
void DisplayPost(vector<Area>& areas);

//Makes a new post
void NewUserPost(vector<Area>& areas, User u);

//edits a post
void EditPost(vector<Area>& areas, User u);

//gets valid title
Post getValidTitle(const Area &a);

//login process
template<class T>
User* login(vector<T*> users);

//reads file
void readData(vector<Area>* areas);

//reads to file
void storeData(vector<Area> areas);

//reads from user file to create a user
template<class T>
void readUserData(vector<T*>& users, UserList<T*>& dumb);

//add reaction function only for superusers
void reactPost(vector<Area>& areas, User u);
//delete function
void deleteArea(vector<Area>& areas, int c);
//see alias function
void viewAlias(UserList<User*> users);
//trim functions
string ltrim(const std::string &s);
string rtrim(const std::string &s);
string trim(const std::string &s);

int main() {
    //array of areas
    vector<Area> areas;
    vector<Area>* areaPointer = &areas;
    UserList<User*> dumb;
    vector<User*> users;

    //user initialization
    readData(areaPointer);
    readUserData(users, dumb);
    //starts login
    User *user = login(users);
    if (user->getTypeUser() == 1){
        cout << "----SUPERUSER----"<<endl;
    }
    cout << "Hello " << user->getName()<<endl;
    //initialize areas


    //welcome
    cout << "Welcome to my Blog " << endl;

    string UserAction;
    do {
        displayMenu();
        promptAction(UserAction);

        implementAction(areaPointer, UserAction, user, dumb);

    } while ((UserAction != "Q") && (UserAction != "q"));
    //continue until user decides to quit


    return 0;
}

// sets up areas
void readData(vector<Area>* areas) {
    //making empty area variables to read values into
    Area a1, a2, a3, a4, a5;
    //adding them to the array
    areas->push_back(a1);
    areas->push_back(a2);
    areas->push_back(a3);
    areas->push_back(a4);
    areas->push_back(a5);
    //opening file
    ifstream inputFile;
    inputFile.open("Blog.txt");
    //counter variable and bool for knowing when file is over
    bool end = false;
    int i = 0;
    while (!end){
        //bool variable for knowing when the area is over, used in next while loop
        bool areaEnd = false;
        //string vars to hold data from file
        string areaName;
        string areaDesc;
        //reading in line to areaName
        getline(inputFile, areaName);
        //if areaName isn't the end of file marker reads into areadesc and adds area to the vector
        if (areaName != "End All"){
            areas->at(i).setName(areaName);
            getline(inputFile, areaDesc);
            areas->at(i).setDescription(areaDesc);
        }
            //if it is end of file marker ends both loops
        else{
            end = true;
            areaEnd = true;
        }
        //while loop for getting the posts in each area
        while (!areaEnd){
            //string vars to hold data from file
            string postName;
            string postUser;
            string postBody;
            //marker for reaction loop
            bool reactionEnd = false;
            //reads line to postName
            getline(inputFile, postName);
            //if it isn't the end of area marker reads into user and body vars and adds post to the area
            if (postName != "End Area"){
                getline(inputFile, postBody);
                getline(inputFile, postUser);
                Post p(postName, postBody, postUser);
                //loop for getting reactions
                while(!reactionEnd){
                    string reaction;
                    string reactor;
                    getline(inputFile, reaction);
                    //if reaction isn't end of file marker adds reactions and who reacted
                    if (reaction != "End Reactions"){
                        getline(inputFile, reactor);
                        if (reaction == "1"){
                            p.addReaction(1, reactor);
                        }
                        else if (reaction == "2"){
                            p.addReaction(2, reactor);
                        }
                        else if (reaction == "3"){
                            p.addReaction(3, reactor);
                        }
                        else{
                            p.addReaction(4, reactor);
                        }
                    }
                    else{
                        reactionEnd = true;
                    }
                }
                areas->at(i).AddPost(p);
            }
                //if it is end of area marker ends this loop and adds to the counter variable
            else {
                areaEnd = true;
                i++;
            }
        }
    }
    //closes file
    inputFile.close();
}

//display menu
void displayMenu() {
    // display menu options to user
    cout << "Please select from the following options..." << endl;
    cout << " A  - Display Blog areas" << endl;
    cout << " B  - Display all posts for a blog" << endl;
    cout << " C  - Add new post to an area" << endl;
    cout << " D  - Display a post" << endl;
    cout << " E  - Edit a post" << endl;
    cout << " F  - Delete a post"<<endl;
    cout << " G  - React to a post" <<endl;
    cout << " H  - View who reacted to a post"<<endl;
    cout << " X  - Delete an Area"<<endl;
    cout << " Z  - View all Aliases"<<endl;
    cout << " Q  - Quit" << endl;

}

//User Action
void promptAction(string &strCh) {
    //display menu options to screen

    //prompt user for choice
    cout << "What would you like to do?" << endl;
    cin >> strCh;
}

//implement Users Action
void implementAction(vector<Area>* areas, const string &strCh, User *u, UserList<User*>& users) {
    // if user selected A
    if ((strCh == "A") || (strCh == "a")) {
        DisplayBlogAreas(*areas);
    } else if ((strCh == "B") || (strCh == "b")) {
        cout << "Display all posts for a blog..." << endl;
        int blogId = getValidBlogArea(areas->size());
        DisplayPostsABlog(areas->at(blogId));
    }
        //user selects C
    else if ((strCh == "C") || (strCh == "c")){
        cout << "Add new post to an area..." <<endl;
        NewUserPost(*areas, *u);
    }
        //user selects D
    else if ((strCh == "D") || (strCh == "d")) {
        cout << "Display a post..." << endl;
        DisplayPost(*areas);
    }
        // user selects E
    else if ((strCh == "E") || (strCh == "e")) {
        cout << "Edit a post..." << endl;
        EditPost(*areas, *u);
    }
    else if ((strCh == "F") || (strCh == "f")) {
        //user has selected to quit
        cout << "Delete a post..." << endl;
        int blogID = getValidBlogArea(areas->size());
        int postID = getValidPost(areas->at(blogID));
        areas->at(blogID).DeletePost(postID);
    }
    else if ((strCh == "G") || (strCh == "g")) {
        //user has selected to quit
        cout << "React to a post..." << endl;
        reactPost(*areas, *u);
    }
    else if ((strCh == "H") || (strCh == "h")) {
        //user has selected to quit
        cout << "View who reacted to a post..." << endl;
        int a = getValidBlogArea(areas->size());
        int p = getValidPost(areas->at(a));
        u->viewReactions(p, areas->at(a));
    }
    else if (((strCh == "Z") || (strCh == "z")) && (u->getTypeUser() == 1))  {
        //user has selected to quit
        cout << "View all aliases..." << endl;
        viewAlias(users);
    }
    else if (((strCh == "X") || (strCh == "x")) && (u->getTypeUser() == 1)) {
        //user has selected to quit
        cout << "Delete an area..." << endl;
        int c = getValidBlogArea(areas->size());
        deleteArea(*areas, c);
    }
        //user selected Q
    else if ((strCh == "Q") || (strCh == "q")) {
        //user has selected to quit
        storeData(*areas);
        cout << "Bye..." << endl;
    }
    else {
        //user has selected an invalid option
        cout << strCh << " is not a valid option or no permissions loser :p" << endl;
    }
}

////////////////////////////
void DisplayBlogAreas(const vector<Area>& areas) {
    cout << "Display Blog areas..." << endl;
    //user has selected to display blog areas
    for (int i = 0; i < areas.size(); i++) {
        cout << "Area Index: " << i << endl;
        cout <<(areas[i]);
    }

}

//////////////////
void DisplayPostsABlog(const Area& a) {
    cout << "Posts for " << a.getName() << endl;

    //user has selected to display blog areas
    for (int i = 0; i < a.getPostsSize(); i++) {
        Post p;
        bool found = a.getPost(i, p);
        if (found) {
            cout << "Post Index:" << i << endl;
            cout <<(p);
        }
    }

}

//////////////
int getValidBlogArea(int numAreas) {
    int area = -1;
    //input validation loop
    while ((area < 0) || (area >= numAreas)) {
        cout << "Please enter in a Blog Area Index" << endl;
        cin >> area;
        while (cin.fail()){
            cin.clear(); cin.ignore(512, '\n');
            cout << "invalid input try again" << endl;
            cin >> area;
        }
    }
    //return valid Blog Area Index
    return area;
}
int getValidPost(const Area& a) {
    int valid = -1;
    int PostChoice = -1;
    Post p;
    while (valid != 1){
        cout << "Please enter a valid post id" << endl;
        cin >> PostChoice;
        while (cin.fail()){
            cin.clear(); cin.ignore(512, '\n');
            cout << "invalid input try again" << endl;
            cin >> PostChoice;
        }
        valid = a.getPost(PostChoice, p);
    }
    return PostChoice;
}
////////////////////////
void NewUserPost(vector<Area>& areas, User u){
    string PostTitle;
    string PostBody;
    int AreaChoice;
    Post NewPost;
    //input validation for Area choice, Post title, user, and, description
    AreaChoice = getValidBlogArea(areas.size());
    NewPost = getValidTitle(areas[AreaChoice]);
    NewPost.SetUser(u.getAlias());
    while ((PostBody.length() <= 0) || (PostBody.length() > 500)){
        cout << "Enter post body"<<endl;
        getline(cin, PostBody);
        PostBody = trim(PostBody);
    }
    NewPost.SetBody(PostBody);
    //tries to add new post to the area if full it tells the user
    areas[AreaChoice].AddPost(NewPost);
    if (areas.size() >= MAX_NUM_POSTS){
        cout << "This area is full please try posting elsewhere." << endl;
    }
    else {
        cout << "Your post is now in the chosen area" << endl;
    }
}
void DisplayPost(vector<Area>& areas){


    //creates variable to hold post value for getpost
    Post p;
    //input validation for area and post choice
    int AreaChoice = getValidBlogArea(areas.size());
    int PostChoice = getValidPost(areas[AreaChoice]);
    //gets post
    areas[AreaChoice].getPost(PostChoice, p);
    cout << "Post Index:" << PostChoice << endl;
    cout <<(p);
}
void EditPost(vector<Area>& areas, User u){


    //creates variable to hold post value for getpost
    Post p;
    //input validation for area and post choice
    int AreaChoice = getValidBlogArea(areas.size());
    int PostChoice = getValidPost(areas[AreaChoice]);
    //gets post
    areas[AreaChoice].getPost(PostChoice, p);
    cout << "Post Index:" << PostChoice << endl;
    cout <<(p);

    string PostBody;
    //input validation for Post title, user, and, description
    p = getValidTitle(areas[AreaChoice]);
    p.SetUser(u.getAlias());
    while ((PostBody.length() <= 0) || (PostBody.length() > 500)){
        cout << "Enter new post body"<<endl;
        getline(cin, PostBody);
        PostBody = trim(PostBody);
    }
    p.SetBody(PostBody);

    areas[AreaChoice].EditPost(p, PostChoice);
}
//Valid post title function
Post getValidTitle(const Area &a){
    //string var to hold post title
    string PostTitle;
    Post p1;
    //while loop for valid length of post
    while ((PostTitle.length() <= 0) || (PostTitle.length() > 20)) {
        getline(cin, PostTitle);
        PostTitle = trim(PostTitle);
        p1.SetTitle(PostTitle);
        if ((PostTitle.length() <= 0) || (PostTitle.length() > 20)){
            cout << "Enter a valid post title"<<endl;
        }
        //for loop to check if post has the same title as any other post in the area
        for (int i = 0; i < a.getPostsSize(); ++i) {
            Post p2;
            a.getPost(i, p2);
            if (p1 == p2) {
                //tells the user if title is in use and resets PostTitle var
                cout << "Title already in use try again" << endl;
                PostTitle = "";
                p1.SetTitle(PostTitle);
            }
        }
    }
    return p1;
}
//Login function
template<class T>
User* login(vector<T*> users){
    bool loggedIn = false;
    string newName;
    string newPass;
    User *u;


    while (!loggedIn){
        cout<< "Enter Username" <<endl;
        cin >> newName;
        cout<< "Enter Password"<<endl;
        cin>>newPass;
        for (int i = 0; i < users.size(); ++i) {
            if((newName == users[i]->getName()) && (newPass == users[i]->getPassword())&& (users[i]->getTypeUser() != 1)) {
                loggedIn = true;
                u = users[i];
            }
            else if((newName == users[i]->getName()) && (newPass == users[i]->getPassword()) && (users[i]->getTypeUser() == 1)) {
                loggedIn = true;
                u = users[i];
            }
        }
        if (!loggedIn){
            cout << "Invalid Username or Password" <<endl;
        }
    }
    return u;
}

// output function
void storeData(vector<Area> areas){
    //opens output file
    ofstream outputFile;
    outputFile.open("Blog.txt");
    //loops through areas adding their names, descriptions, and posts to the file
    for (int i = 0; i < areas.size(); ++i) {
        outputFile << areas[i].getName()<<endl;
        outputFile << areas[i].getDesc()<<endl;
        for (int j = 0; j < areas[i].getPostsSize(); ++j) {
            Post p;
            areas[i].getPost(j, p);
            outputFile << p.getTitle()<<endl;
            outputFile << p.getBody()<<endl;
            outputFile << p.getUser()<<endl;
            //another for loop for reactions and reactors
            for (int k = 0; k < p.getNumReactions(); ++k) {
                outputFile << p.getReaction(k)<<endl;
                outputFile << p.getReactor(k)<<endl;
            }
            outputFile << "End Reactions" <<endl;

        }
        //adds end of area marker so readData can use the same file
        outputFile << "End Area"<<endl;
    }
    //adds end of file marker so readData can use the same file
    outputFile << "End All"<<endl;
}

template<class T>
void readUserData(vector<T*>& users, UserList<T*>& dumb){
    //makes variables to hold data
    string userName;
    string userAlias;
    string userPass;
    string a;
    //opens file
    ifstream inputFile;
    inputFile.open("Users.txt");
    while(inputFile >> userName >>userAlias>>userPass>>a){
        //sets values for user and adds to the vector
        //creates a pointer to user type
        User *u;
        if(a == "SUPERUSER"){
            //if file says it is superuser creates pointer to SuperUser variable
            SuperUser *s;
            //creates dynamic variable for s to point to
            s = new SuperUser;
            //sets user data
            s->setName(userName);
            s->setAlias(userAlias);
            s->setPassword(userPass);
            s->setUserType(a);
            //has pointer to user point to superuser
            u = s;
        }
        else{
            //creates dynamic variable for u to point to if user is not super
            u = new User;
            u->setName(userName);
            u->setAlias(userAlias);
            u->setPassword(userPass);
            u->setUserType(a);
        }
        //adds u to a vector of pointers
        users.push_back(u);
        dumb.addUser(u);
    }
}
//react to post function
void reactPost(vector<Area>& areas, User u){
    //gets choices for what user wants to react to
    int AreaChoice = getValidBlogArea(areas.size());
    int PostChoice = getValidPost(areas[AreaChoice]);
    Post p;
    areas[AreaChoice].getPost(PostChoice, p);
    cout << p;
    //bool for while loop
    bool validReact = false;
    //var to hold reaction choice
    int reaction;
    while (!validReact){
        cout << "Please select a reaction" << endl;
        cout <<"1. Love"<<endl;
        cout <<"2. Like"<<endl;
        cout <<"3. Dislike"<<endl;
        cout <<"4. Hate"<<endl;
        cin >> reaction;
        //input validation
        while (cin.fail()){
            cin.clear(); cin.ignore(512, '\n');
            cout << "invalid input try again" << endl;
            cin >> reaction;
        }
        if ((reaction != 1) &&(reaction != 2) &&(reaction != 3) &&(reaction != 4)){
            validReact = false;
        }
        else{
            validReact = true;
        }
    }
    //calls member function to react to post
    areas[AreaChoice].reactToPost(PostChoice, reaction, u.getAlias());
}
//delete an Area
void deleteArea(vector<Area>& areas, int c){
    areas.erase(areas.begin()+c);
}
void viewAlias(UserList<User*> users){
    for (int i = 0; i < users.getUsersSize(); ++i) {
        users.displayUser(i);
    }
}
const std::string WHITESPACE = " \n\r\t\f\v";
///////////////////////////
//Left trim - remove all white space characters on the left
string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

//Right trim - remove all white space characters on the right
string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

//Trim - remove all white space characters on the left or right
string trim(const std::string &s) {
    return rtrim(ltrim(s));
}
