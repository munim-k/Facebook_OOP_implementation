#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
class Helper
{
public:
	static void intro()
	{
		cout << "                                           Welcome to SocialBee" << endl;
		cout << "Commands List: " << endl << endl << "output" << endl <<"view home"<<endl<< "set current user" << endl;
		cout << "View Friend List" << endl << "View Liked Pages" << endl << "Exit" << endl << "View timeline" << endl << "view likedlist" << endl << "see your memories" << endl << "share memory" << endl;
	}
	static int StringLength(const char* str)            //strlen alternative
	{
		int count = 0;
		for (int i = 0; str[i] != 0; i++)
		{
			count++;
		}
		return count;
	}
	static char lower(char letter)
	{
		if (letter >= 65 && letter <= 90)
		{
			return letter + 32;
		}
		else
		{
			return letter;
		}
	}
	static void StringCopy(char*& dest, char*& src)          //strncpy alternative
	{
		int count = 0;
		for (int i = 0; dest[i] != 0 && src[i] != 0; i++)
		{
			dest[i] = src[i];
			count++;
		}
		dest[count] = 0;
	}
	static char* GetStringFromBuffer(char* str)
	{
		int size = StringLength(str) + 1;
		char* temp = new char[size + 1];

		StringCopy(temp, str);
		temp[size] = '\0';
		return temp;
	}
	static int CompareString(const char* cstring1, const char* cstring2)            //strncmp alternative
	{
		int result = 0;
		int length1 = StringLength(cstring1);
		int length2 = StringLength(cstring2);
		int minLength = min(length1, length2);

		for (int i = 0; i < minLength && result == 0; i++) {
			if (lower(cstring1[i]) < lower(cstring2[i])) {
				result = -1;

			}
			else if (lower(cstring1[i]) > lower(cstring2[i])) {
				result = 1;

			}
		}

		if (result == 0) {
			if (length1 < length2) {
				result = -1;
			}
			else if (length1 > length2) {
				result = 1;
			}
		}

		return result;
	}
};
class SocialBee;
class Hives;
class Bees;
class Post;
class Date;
class Comment;
class Activity
{
	int Type;
	char* value;
public:
	Activity()
	{
		value = 0;
		Type = 0;
	}
	void settype(int a)
	{
		Type = a;
	}
	void setvalue(char* a)
	{
		value = new char[Helper::StringLength(a) + 1];
		Helper::StringCopy(value, a);
	}
	int gettype()
	{
		return Type;
	}
	char* getvalue()
	{
		return value;
	}
	~Activity()
	{
		delete[] value;
	}
};
class Object
{
protected:
	char* id;
public:
	virtual void output()
	{
		cout << id << "  ";
	}
	Object()
	{
		id = new char[4];
	}
	Object(char* a)
	{
		Helper::StringCopy(id, a);
	}
	void setid(char* a)
	{
		Helper::StringCopy(id, a);
	}
	char* getid()
	{
		return id;
	}
	void print()
	{
		cout << id << " " << endl;
	}
	
	virtual ~Object()
	{
		delete[] id;
	}
	virtual void getname()
	{
	};
	
	const Object& operator=(Object& obj)             //assignment operator
	{
		if (&obj != this)
		{
			if (obj.id != 0)
			{
				if (Helper::StringLength(id) == Helper::StringLength(obj.id))
				{
					Helper::StringCopy(id, obj.id);
				}
				else if (id == 0)
				{

					id = new char[Helper::StringLength(obj.id) + 1];
					Helper::StringCopy(id, obj.id);
				}
				else
				{
					delete[] id;
					int len = Helper::StringLength(obj.id);
					id = new char[len + 1];
					strcpy_s(id, len + 1, obj.id);
				}
			}
			else
				id = obj.id;
		}
		return *this;
	}
};
class Comment
{
	char* id;
	char* text;
	Object* commentby;
	static int totalcomments;
public:
	void print()
	{
		cout << "(" << commentby->getid() << ")";
	}
	static void Settotalcomments(int a)
	{
		totalcomments = a;
	}
	Comment()
	{
		id = new char[7];
		commentby = 0;
		text = new char[1];

	}
	void printComment()
	{
		if (commentby != nullptr)
			commentby->getname(); cout << "\t\t\t" << " wrote:\" " << text << "\"" << endl;
	}
	void Setvalues(char* idname, char* textname, Object* objname)
	{
		delete[] text;
		text = new char[Helper::StringLength(textname) + 1];
		Helper::StringCopy(text, textname);
		commentby = objname;

		Helper::StringCopy(id, idname);
	}
	void postcomment(const char* idname, const char* textname, Object* objname)
	{
		delete[] text;
		int len = Helper::StringLength(textname) + 1;
		text = new char[len];
		strcpy_s(text, len, textname);
		commentby = objname;

		strcpy_s(id, len, idname);
	}
	static int gettotalcomments()
	{
		return totalcomments;
	}
	void setcomment(char* a)
	{
		delete[] text;
		text = new char[Helper::StringLength(a) + 1];
		Helper::StringCopy(text, a);
	}
	void setobject(Object* a)
	{
		commentby = a;
	}
	char* getcomment()
	{
		return text;
	}
	Object* getobject()
	{
		return commentby;
	}
	void setcommentby(Object* obj)
	{
		if (commentby == 0)
		{
			commentby = new Object;
		}
		commentby = obj;
	}
	~Comment()
	{
		if (id != nullptr)
		{
			delete[] id;
		}
		if (text != nullptr)
		{
			delete[] text;
		}
		if (commentby != nullptr)
		{
			commentby = nullptr;
		}
	}
};
int Comment::totalcomments = 0;
class Date
{
	int date;
	int month;
	int year;

public:

	Date(int a = 15, int b = 11, int c = 2017)
	{

		date = a;
		month = b;
		year = c;

	}

	void setdate(int a, int b, int c)
	{
		if (this != 0)
		{
			date = a;
			month = b;
			year = c;
		}
	}
	void printDate()
	{
		cout << date << "/" << month << "/" << year;
	}
	int getdate()
	{
		return date;
	}
	int getmonth()
	{
		return month;
	}
	int getyear()
	{
		return year;
	}
	bool operator ==(Date& rhs)                //overloaded operator for checking last 24 hours
	{
		if (date == rhs.date && month == rhs.month && year == rhs.year)
		{
			return 1;
		}
		else if (date == rhs.date + 1 && month == rhs.month && year == rhs.year)
		{
			return 1;
		}
		else return 0;
	}
};


class Post
{
protected:
	char* id;
	char* text;
	Date SharedDate;
	Activity* activity;
	Object* SharedBy;
	Object** LikedBy;
	int type = 0;
	Comment** comments;
	int totallikes = 0;
	int commentcount = 0;
	static int totalposts;
	static int totalcomments;
public:
	static void settotalposts(int a)
	{
		totalposts = a;
	}
	~Post()
	{
		delete[] id;
		delete[] text;
		activity = nullptr;
		SharedBy = nullptr;
	}

	static void settotalcomments(int a)
	{
		totalcomments = a;
	}
	static int gettotalposts()
	{
		return totalposts;
	}
	static int gettotalcomments()
	{
		return totalcomments;
	}
	char* getid()
	{
		return id;
	}
	Post()
	{


		id = new char[7];
		LikedBy = 0;
		SharedBy = 0;
		comments = new Comment * [10];
		for (int i = 0; i < 10; i++)
		{
			comments[i] = new Comment;
		}
		activity = 0;

	}
	void setid(char* idname)
	{
		Helper::StringCopy(id, idname);
	}
	void setdate(int a, int b, int c)
	{
		SharedDate.setdate(a, b, c);
	}
	void settext(char* data)
	{
		text = new char[Helper::StringLength(data) + 1];
		Helper::StringCopy(text, data);
	}
	void setactivity(int a, char* b)
	{
		type = 2;
		activity = new Activity();
		activity->settype(a);
		activity->setvalue(b);
	}
	void settype(int t)
	{
		type = t;
	}
	void getlikedby()
	{
		for (int i = 0; i < totallikes; i++)
		{
			LikedBy[i]->getname(); cout << endl;
		}
	}
	void setsharedby(Object* user)
	{
		SharedBy = new Object;
		SharedBy = user;
	}
	void Addlikedby(Object*& ptr)
	{
		if (totallikes == 0)
		{
			LikedBy = new Object * [10];
		}
		LikedBy[totallikes] = new Object;
		LikedBy[totallikes] = ptr;
		totallikes++;
	}
	int getday()
	{
		return SharedDate.getdate();
	}
	int getmonth()
	{
		return SharedDate.getmonth();
	}
	int getyear()
	{
		return SharedDate.getyear();
	}
	void printListView()
	{
		if (activity != nullptr)
		{
			SharedBy->getname(); cout << "is  ";
			if (activity->gettype() == 1)
			{
				cout << "feeling  " << activity->getvalue() << endl;
			}
			else if (activity->gettype() == 2)
			{
				cout << "thinking about  " << activity->getvalue() << endl;
			}
			else if (activity->gettype() == 3)
			{
				cout << "Making  " << activity->getvalue() << endl;
			}
			else cout << "Celebrating  " << activity->getvalue() << endl;
		}
		cout << "\"" << text;
		cout << " \"...( ";
		SharedDate.printDate();
		cout << ")" << endl;

	}
	void AddComments(Comment* comment)
	{

		if (comments == 0)
		{
			comments = new Comment * [10];
		}
		comments[commentcount] = new Comment;
		comments[commentcount] = comment;
		commentcount++;
	}
	void printComments()
	{
		int i = 0;
		if (comments != 0)
		{
			for (int i = 0; i < commentcount; i++)
			{
				comments[i]->printComment();
			}

		}
	}
	virtual void print()
	{
		this->printListView();
		this->printComments();
	}
	int returnptryear()
	{
		return SharedDate.getyear();
	}
	int returnptrdate()
	{
		return SharedDate.getdate();
	}
	int returnptrmonth()
	{
		return SharedDate.getmonth();
	}
	bool comparedates();
};
int Post::totalposts = 0;
int Post::totalcomments = 0;
class Memory :public Post
{
	Post* originalpost;
	char* caption;
	int years = 0;
public:
	
	Memory()
	{

	}
	void setvalues(Post* ptr, const char* text, Bees* user);
	void print()
	{
		cout <<"\u001b[31m"<< text << " ...("; SharedDate.printDate(); cout << ")" << endl;
		cout << "(" << years << "years ago)" << endl<<"\u001b[0m";
		originalpost->print();
	}

	~Memory()
	{
		originalpost = nullptr;
		delete[] caption;
	}
	void setyears(Post* ptr);
};
class Hives :public Object
{
	char* id;
	char* title;
	Post** timeline;
	int postcount = 0;
public:
	static int totalpages;
	char* getid() { return id; }
	char* gettitle() { return title; }
	static int gettotalpages() { return totalpages; }
	static void settotalpages(int a) { totalpages = a; }

	Hives()
	{
		id = new char[4];
		title = new char[1];
		title[0] = '\0';
		timeline = 0;
	}
	~Hives()
	{
		delete[] id;
		delete[] title;
	}
	void getname()
	{
		cout << id << "-" << title;
	}
	void readdatafromfile(ifstream& fin)
	{
		fin >> id;
		char* temp = new char[1000];
		fin.getline(temp, 100);

		title = new char[Helper::StringLength(temp)];
		Helper::StringCopy(title, temp);
		delete[] temp;
	}
	void Print()
	{
		cout << id << "-" << title << endl;
	}
	void Addpost(Post* ptr)
	{
		if (postcount == 0)
		{
			timeline = new Post * [10];
		}
		timeline[postcount] = new Post;
		timeline[postcount] = ptr;
		postcount++;
	}
	void printTimeLine()
	{
		if (timeline != 0)
		{
			int i = 0;
			while (i < postcount)
			{
				if (timeline[i] != 0)
				{
					cout << "---";
					timeline[i]->print();
				}
				i++;
				cout << endl;
			}
		}
	}
	void printrecent()
	{
		for (int i = 0; i < postcount; i++)
		{
			if (timeline[i] != nullptr)
			{
				if (timeline[i]->comparedates() == 1)
				{
					timeline[i]->print();
				}
			}
		}
		cout << endl;
	}
};
int Hives::totalpages = 0;
class Bees :public Object
{
	char* id;
	char* fname ;
	char* lname ;
	Hives** likedpages;
	Bees** friendlist;
	static int totalusers;
	int friendcount = 0;
	int pagescount = 0;
	int postcount = 0;
	Post** timeline;
public:
	static int gettotalusers() { return totalusers; }
	static void settotalusers(int a) { totalusers = a; }
	char* getid() { return id; }

	Bees()
	{
		fname = 0;
		lname = 0;
		likedpages = new Hives * [10];
		friendlist = new Bees * [10];
		timeline = new Post * [10];
		id = new char[4];

	}
	void getname()
	{
		cout << id << "-" << fname << " " << lname;
	}
	~Bees()
	{
		delete[] id;
		delete[] fname;
		delete[] lname;
		delete[] friendlist;
		delete[] likedpages;
		delete[] timeline;
	}
	void readdatafromfile(ifstream& fin)
	{
		char* buffer = new char[100];
		fin >> id;
		fin >> buffer;
		fname = new char[Helper::StringLength(buffer)];
		Helper::StringCopy(fname, buffer);
		fin >> buffer;
		lname = new char[Helper::StringLength(buffer)];
		Helper::StringCopy(lname, buffer);
		delete[] buffer;
	}
	void seeyourmemories();

	void LikePage(Hives* page)
	{
		likedpages[pagescount] = new Hives;
		likedpages[pagescount] = page;
		pagescount++;
	}
	void AddFriend(Bees* user)
	{
		friendlist[friendcount] = new Bees;
		friendlist[friendcount] = user;
		friendcount++;
	}
	void ViewFriendList()
	{
		for (int i = 0; i < friendcount; i++)
		{
			cout << friendlist[i]->id << "-      " << friendlist[i]->fname << " " << friendlist[i]->lname << endl;
		}
	}
	void ViewPagesList()
	{
		for (int i = 0; i < pagescount; i++)
		{
			likedpages[i]->Print(); cout << endl;
		}
	}
	void Print()
	{
		cout << id << " " << fname << "  " << lname << endl;
	}
	void Addpost(Post*& ptr)
	{
		timeline[postcount] = new Post;
		timeline[postcount] = ptr;
		postcount++;
	}
	void sharememory(Post*& ptr, const char* text)
	{
		Memory* memory = new Memory();
		memory->setvalues(ptr, text,this);
		timeline[postcount] = new Post;
		timeline[postcount] = memory;
		postcount++;
	}
	void printTimeLine()
	{
		if (timeline != 0)
		{
			int i = 0;
			while (i < postcount)
			{
				if (timeline[i] != nullptr)
				{
					cout << "---";
					timeline[i]->print();
				}
				i++;
				cout << endl;
			}
		}
	} 
	void printrecent()
	{
		for (int i = 0; i < postcount; i++)
		{
			if (timeline[i] != nullptr)
			{
				if (timeline[i]->comparedates() == 1)
				{
					timeline[i]->print();
				}
			}
		}
		cout << endl;
	}
	void ViewHomePage()
	{
		cout << endl << fname << " " << lname << "-Home Page\n\n";

		if (friendlist != 0)
		{
			int i = 0;
			while (i < friendcount)
			{
				if (friendlist[i] != 0)
				{
					friendlist[i]->printrecent();
				}
				i++;
			}
		}
		if (likedpages != 0)
		{
			int i = 0;
			while (i < pagescount)
			{
				if (likedpages[i] != 0)
				{
					likedpages[i]->printrecent();
				}
				i++;
			}
		}
		
	}
};
int Bees::totalusers = 0;
class SocialBee
{
	Hives** pages;
	Bees** users;
	Post** posts;
public:
	static Date currentdate;
	
	~SocialBee()
	{
		for (int i = 0; i < Bees::gettotalusers(); i++)
		{
			if (users[i] != nullptr)
				delete[] users[i];
		}
		delete[] users;
		for (int i = 0; i < Hives::gettotalpages(); i++)
		{
			if (pages[i] != nullptr)
				delete[] pages[i];
		}
		delete[] pages;
		for (int i = 0; i < Post::gettotalposts(); i++)
		{
			if (posts[i] != nullptr)
				delete[] posts[i];
		}
		delete[] posts;
	}
	void getusers(Bees* ptr)
	{
		cout << ptr;
	}
	void LoadPagesFromFile()
	{
		int pagescount = 0;
		ifstream fin;
		fin.open("pages.txt");

		fin >> pagescount;
		Hives::settotalpages(pagescount);
		pages = new Hives * [pagescount];
		for (int i = 0; i < pagescount; i++)
		{
			pages[i] = new Hives;
			pages[i]->readdatafromfile(fin);
		}
		fin.close();
	}
	void LoadUsersFromFile()
	{
		int userscount = 0;
		ifstream fin;
		fin.open("users.txt");
		fin >> userscount;
		Bees::settotalusers(userscount);
		users = new Bees * [userscount];
		char* buffer = new char[100];

		char*** list = new char** [userscount];
		for (int i = 0; i < userscount; i++)
		{
			users[i] = new Bees;
			users[i]->readdatafromfile(fin);
			list[i] = new char* [12];
			int count = 0;
			fin >> buffer;
			if (buffer[0] == '-')
			{
				list[i][count] = 0;
			}
			else
			{

				while (buffer[0] != '-' && count < 10)
				{
					list[i][count] = new char[4];
					list[i][count] = Helper::GetStringFromBuffer(buffer);
					count++;
					fin >> buffer;

				}
				list[i][count] = 0;
			}

			fin >> buffer;
			Hives* Hptr = 0;
			while (buffer[0] != '-')
			{
				Hptr = SearchPageById(buffer);
				if (Hptr)
					users[i]->LikePage(Hptr);
				fin >> buffer;
			}
		}
		delete[] buffer;

		for (int i = 0; i < userscount; i++)
		{
			if (list[i][0] != 0)
			{
				int j = 0;
				while (list[i][j] != nullptr)
				{
					Bees* Bptr = SearchUserById(list[i][j]);
					users[i]->AddFriend(Bptr);
					j++;
				}
			}
		}

		fin.close();
		for (int j = 0; j < userscount; j++)
		{
			for (int k = 0; list[j][k] != 0; k++)
			{
				delete[] list[j][k];
			}
			delete[] list[j];
		}
		delete[] list;
	}

	Hives* SearchPageById(const char* name)
	{
		int index = -1;
		if (name)
		{
			for (int i = 0; i < Hives::gettotalpages() && index == -1; i++)
			{
				if (Helper::CompareString(pages[i]->getid(), name) == 0)
					index = i;
			}
		}
		if (index != -1)
			return &(*pages[index]);
		else return 0;
	}
	Bees* SearchUserById(const char* name)
	{
		if (name[0] == '-')
		{
			return 0;
		}
		int index = -1;
		if (name)
		{
			for (int i = 0; i < Bees::gettotalusers() && index == -1; i++)
			{
				if (Helper::CompareString(users[i]->getid(), name) == 0)
				{
					index = i;
				}
			}
		}
		if (index != -1)
		{
			return &*users[index];
		}
		else return 0;
	}
	void LoadPostsFromFile()
	{
		ifstream fin;
		fin.open("posts.txt");
		if (fin.is_open())
		{
			int totalposts = 0;
			fin >> totalposts;
			Post::settotalposts(totalposts);
			posts = new Post * [totalposts + 1];
			char* buffer = new char[100];

			for (int i = 0; i < totalposts; i++)
			{

				posts[i] = new Post;
				int type = 0;
				fin >> type;
				fin >> buffer;
				posts[i]->setid(buffer);
				int day = 0, month = 0, year = 0;
				fin >> day;
				fin >> month;
				fin >> year;
				posts[i]->setdate(day, month, year);
				fin.ignore();
				fin.getline(buffer, 100);
				posts[i]->settext(buffer);
				if (type == 2)
				{
					int a = 0;
					fin >> a;
					fin.getline(buffer, 100);
					posts[i]->settype(2);
					posts[i]->setactivity(a, buffer);
				}
				else
				{
					posts[i]->settype(1);
				}
				fin >> buffer;
				if (buffer[0] == 'u')
				{
					Bees* user = SearchUserById(buffer);
					user->Addpost(posts[i]);
					Object* ptr = static_cast<Object*>(user);
					posts[i]->setsharedby(ptr);
				}
				else if (buffer[0] == 'p')
				{
					Hives* page = SearchPageById(buffer);
					page->Addpost(posts[i]);
					Object* ptr = static_cast<Object*>(page);
					posts[i]->setsharedby(ptr);
				}
				fin >> buffer;
				while (buffer[0] != '-')
				{
					if (buffer[0] == 'u')
					{
						Bees* user = SearchUserById(buffer);

						Object* ptr = static_cast<Object*>(user);
						posts[i]->Addlikedby(ptr);
					}
					else if (buffer[0] == 'p')
					{
						Hives* page = SearchPageById(buffer);
						Object* ptr = static_cast<Object*>(page);
						posts[i]->Addlikedby(ptr);
					}
					fin >> buffer;
				}
			}
		}
		fin.close();

	}
	Post* SearchPostById(const char* name)
	{
		if (name[0] == '-')
		{
			return 0;
		}
		int index = -1;
		if (name)
		{
			for (int i = 0; i < Post::gettotalposts() && index == -1; i++)
			{
				if (Helper::CompareString(posts[i]->getid(), name) == 0)
				{
					index = i;
				}
			}
		}
		if (index != -1)
		{
			return &*posts[index];
		}
		else return 0;
	}
	void LoadCommentsFromFile()
	{
		int totalcomments = 0;
		ifstream fin;
		fin.open("comments.txt");
		fin >> totalcomments;
		Comment::Settotalcomments(totalcomments);
		for (int i = 0; i < totalcomments; i++)
		{
			char* id = new char[4];
			char* postid = new char[7];
			char* commentby = new char[4];
			Comment* com = new Comment;
			fin >> id;
			fin >> postid;
			fin >> commentby;
			if (i == 8)
			{
				int donothing = 0;
			}
			Post* ptr = SearchPostById(postid);
			ptr->AddComments(com);
			Object* objptr = 0;
			if (commentby[0] == 'u')
			{
				Bees* userptr = SearchUserById(commentby);
				Object* objptr = userptr;
			}
			else if (commentby[0] == 'p')
			{
				Hives* pageptr = SearchPageById(commentby);
				Object* objptr = pageptr;
			}
			char* text = new char[100];
			fin.getline(text, 100);
			com->Setvalues(id, text, objptr);
			delete[]id;
			delete[] postid;
			delete[] commentby;
			delete[] text;
		}
		fin.close();
	}
	void load()
	{
		LoadPagesFromFile();
		LoadUsersFromFile();
		LoadPostsFromFile();
		LoadCommentsFromFile();
	}
	void setcurrentdate()
	{
		currentdate.setdate(15,11,2017);
	}
	void commands()
	{
		int end = 0; char* userid = new char[5];
		Bees* curruser = 0;
		Post* currpage = 0;
		char* input = new char[50];
		setcurrentdate();
		int flag = 0;
		while (end == 0)
		{
			Helper::intro();
			if (flag != 0)
			{
				cout << "command:       ";
				cin.clear();
				cin.getline(input, 50);
			}
			if (flag==0 || Helper::CompareString(input, "output") == 0)
			{
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:                \u001b[31m Set current System Date 15 11 2017 \u001b[0m" << endl;


				cout << "current date set to 15 11 2017" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:               \u001b[31m Set current user u7 \u001b[0m" << endl;
				curruser = SearchUserById("u7");
				if (curruser != nullptr)
				{
					cout << endl << "User Successfully selected   " << endl;
				}
				else cout << endl << "invalid user id" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:                \u001b[31mView Friend List\u001b[0m " << endl;
				curruser->ViewFriendList();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Comand:                 \u001b[31m View Liked Pages \u001b[0m" << endl;
				curruser->ViewPagesList();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:              \u001b[31m  View Home \u001b[0m" << endl; 
				curruser->ViewHomePage();
				cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:                 \u001b[31m  ViewLikedList(post5) \u001b[0m" << endl;
				Post* ptr = SearchPostById("post5");
				Object* objptr = curruser;
				ptr->Addlikedby(objptr);
				ptr->getlikedby();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:                \u001b[31m   PostComment(post8, Thanks for the wishes) \u001b[0m" << endl;
				ptr = SearchPostById("post8");
				Comment* comptr = new Comment;
				const char* id = new char[4];
				id = "c14";
				const char* text = new char[50];
				text = "Thanks for the wishes";
				comptr->postcomment(id, text, objptr);
				ptr->AddComments(comptr);
				cout << "Command:                 \u001b[31m  ViewPost(post8)  \u001b[0m" << endl;
				ptr->print();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "command:               \u001b[31m  seeyourmemories() \u001b[0m" << endl;

				curruser->seeyourmemories();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:                \u001b[31m  ShareMemory(post10, Never thought I will be specialist in this field) \u001b[0m" << endl;
				ptr = SearchPostById("post10");
				text = "Never thought I will be specialist in this field";
				curruser->sharememory(ptr, text);
				cout << "view timeline" << endl;
				curruser->printTimeLine();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:                  \u001b[31m  ViewPage(p1)   \u001b[0m" << endl;
				Hives* currpage = SearchPageById("p1");
				currpage->printTimeLine();
				curruser = 0;
				curruser = SearchUserById("u11");
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "Command:               \u001b[31m  Set current user (u11)   \u001b[0m" << endl;
				if (curruser != nullptr)
					cout << "Ahsan Ali successfully set as Current User" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "command:     \u001b[31m view homepage   \u001b[0m" << endl;
				curruser->ViewHomePage();
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cout << "command:     \u001b[31m view timeline   \u001b[0m " << endl;
				curruser->printTimeLine();
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
				flag = 1;
			}
			else if (Helper::CompareString(input, "set current user") == 0)
			{
				cout << "Enter User id" << endl;
				cin.getline(userid, 5);
				curruser = SearchUserById(userid);
				if (curruser != nullptr)
				{
					cout << endl << "User Successfully selected   " << userid << endl;
				}
				else cout << endl << "invalid user id" << endl;
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			else if (Helper::CompareString(input, "view likedlist") == 0)
			{
				cout << "enter post id";
				cin.getline(userid, 5);
				currpage = SearchPostById(userid);
				currpage->getlikedby();
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			else if (Helper::CompareString(input, "see your memories") == 0)
			{
				if (curruser != nullptr)
				{
					curruser->seeyourmemories();
				}
				else cout << "no user selected" << endl;
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			else if (Helper::CompareString(input, "share memory") == 0)
			{
				cout << "enter post id";
				char* postid = new char[7];
				cin >> postid;
				Post* ptr = SearchPostById(postid);
				cout << "enter caption" << endl;
				cin.ignore();
				char* text = new char[50];
				cin.getline(text, 50);
				curruser->sharememory(ptr, text);
				delete[] postid;
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			
			else if (Helper::CompareString(input, "View Friend List") == 0)
			{
				if (curruser != nullptr)
				{
					curruser->ViewFriendList();
				}
				else cout << "Please Select user then try again" << endl;
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}

			else if (Helper::CompareString(input, "View Liked pages") == 0)
			{
				if (curruser != nullptr)
				{
					curruser->ViewPagesList();
				}
				else cout << "Please Select user then try again" << endl;
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			else if (Helper::CompareString(input, "Exit") == 0)
			{
				end = 1;
				cout << "Exiting SocialBee" << endl;
			}
			else if (Helper::CompareString(input, "View timeline") == 0)
			{
				curruser->printTimeLine();
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			else if (Helper::CompareString(input, "View home") == 0)
			{
				curruser->ViewHomePage();
				cout << "press enter to continue";
				char ch = _getch();
				system("CLS");
			}
			else
			{
				cout << "invalid command" << endl;
				cout << "Press enter to continue";
				char ch = _getch();
				system("CLS");
			}


		}
		delete[] input;
	}	
};
void Bees::seeyourmemories()
{
	for (int i = 0; i < postcount; i++)
	{
		if (timeline[i]->getday() == SocialBee::currentdate.getdate() && timeline[i]->getmonth() == SocialBee::currentdate.getmonth())
		{
			int year;
			year = SocialBee::currentdate.getyear() - timeline[i]->getyear();
			cout << "\u001b[32mOn this day" << endl << year << " years ago \u001b[0m" << endl;
			timeline[i]->print();
		}
	}
}
Date SocialBee::currentdate = 0;
void Memory::setvalues(Post* ptr, const char* text, Bees* user)
{
	this->setsharedby(user);
	this->text = new char[Helper::StringLength(text) + 1];
	int len = Helper::StringLength(text) + 1;
	strcpy_s(this->text, len, text);
	SharedDate = SocialBee::currentdate;
	originalpost = ptr;
	setyears(ptr);
}
void Memory::setyears(Post* ptr)
{
	years = SocialBee::currentdate.getyear() - ptr->returnptryear();
}

bool Post::comparedates()
{
	if (SocialBee::currentdate == this->SharedDate)
	{
		return 1;
	}
	else return 0;

}

int main()
{
	SocialBee bee;
	bee.load();
	bee.commands();
	system("pause");
}
