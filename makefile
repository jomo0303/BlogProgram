#Blog4 makefile

Blog8: BlogPart8.o Post.o Area.o User.o SuperUser.o UserList.o
	g++ -std=c++11 BlogPart8.o Post.o Area.o User.o SuperUser.o UserList.o -o BlogPart8

BlogPart8.o: BlogPart8.cpp
	g++ -std=c++11 -c BlogPart8.cpp

Post.o: Post.h Post.cpp 
	g++ -std=c++11 -c Post.h
	g++ -std=c++11 -c Post.cpp

Area.o: Area.cpp Area.h
	g++ -std=c++11 -c Area.h
	g++ -std=c++11 -c Area.cpp

User.o: User.cpp User.h
	g++ -std=c++11 -c User.cpp
	g++ -std=c++11 -c User.h

SuperUser.o: SuperUser.cpp SuperUser.h
	g++ -std=c++11 -c SuperUser.cpp
	g++ -std=c++11 -c SuperUser.h

UserList.o: UserList.h UserList.cpp
	g++ -std=c++11 -c UserList.cpp
	g++ -std=c++11 -c UserList.h
clean:
	rm -rf *o Blog8
