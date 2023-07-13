#pragma once
#include<string>
#include<iostream>
using namespace std;
/// //////////////////////////////////////////////// 图 书 类 链 表 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 图书类
class Book
{
public:
    int IBSN;
    string name;
    string state = "可借阅";
    int number;//图书数量
    int hot = 0;//图书借阅的火爆程度，用被借阅几次来表示
    void display();
    void set_bookname(string n) { name = n; }
    void set_number(int n) { number = n; }
    void set_IBSN(int i) { IBSN = i; }
};
//
struct BookNode
{
    Book* book;
    BookNode* next;
};
///
class BookList
{
public:
    BookNode* head;
    BookList()
    {
        head = NULL;
    }
    //添加书本操作
    void AddBook(Book* book1);
    //展示书本：
    void show();
    
};



