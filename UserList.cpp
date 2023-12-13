//
// Created by 2003j on 10/21/2022.
//

#include "UserList.h"
using namespace std;
template<class T>
void UserList<T>::addUser(T user) {
    users.push_back(user);
}

template<class T>
void UserList<T>::displayUser(int i) {
    cout << users.at(i)->getAlias() <<endl;
}
template<class T>
int UserList<T>::getUsersSize() {
    return users.size();
};