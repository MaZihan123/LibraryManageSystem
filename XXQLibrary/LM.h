#pragma once
#include<iostream>
#include<string>
#include"Book.h"
#include"Content.h"
#include"Users.h"
////////////////////////////////////////////////////////////////////////////// 图 书 管 理 员 功 能 函 数 //////////
//登录后的展示界面
void LibraryMangerLogin()
{
    cout << "======图书管理员功能======" << endl;
    cout << "      1.添加图书      " << endl;
    cout << "      2.删除图书      " << endl;
    cout << "      3.异常还书处罚   " << endl;
    cout << "      4.发布公告      " << endl;
    cout << "      5.修改密码      " << endl;
    cout << "     输入其他数字进入登出界面" << endl;
    cout << "=========================" << endl;
}
//补充现有图书函数
bool AddNowBook(BookList& booklist, int booknumber, string bookname)
{
    BookNode* p = booklist.head;
    while (p)
    {
        if (p->book->name == bookname)
        {
            p->book->number += booknumber;
            return true;
        }
        p = p->next;
    }
    return false;
}
//删除图书函数
void DeleteBook(BookList& booklist, string bookname, int& book_number)
{
    BookNode* p = booklist.head;
    BookNode* temp = NULL;
    while (p != NULL)
    {
        if (p->book->name == bookname)
        {
            if (p == booklist.head)
            {
                booklist.head = p->next;
                delete p->book;
                delete p;
                book_number--;
                p = booklist.head;//更新p为头
            }
            else if (p->next == NULL)//书在末尾时
            {
                temp->next = NULL;
                delete p->book;
                delete p;
                book_number--;
                p = NULL;

            }
            else
            {
                temp->next = p->next;
                delete p->book;
                delete p;
                book_number--;
                p = temp->next;//更新p
            }
        }
        else
        {
            temp = p;
            p = p->next;
        }

    }
}
//异常处罚函数
void Punish(UserList& userlist)
{
    string No = "异常";
    UserNode* p = userlist.head;
    while (p)
    {
        if (p->user->bad_return_book > 0)
        {
            cout << p->user->Type << p->user->Name << "有异常还书记录，是否对其进行标记？" << endl;
            cout << "1.标记 || 2.放过 " << endl;
            int n;
            cin >> n;
            if (n == 1)
            {
                p->user->person_state = No;
                cout << "已将其借阅状态改为“异常”。" << endl;
            }
            else if (n == 2)
            {
                cout << "那就放ta一马" << endl;
            }
            else
            {
                cout << "输入有误，请稍后再试。" << endl;
            }

        }
        else
        {
            cout << p->user->Type << p->user->Name << "无异常记录" << endl;
        }
        p = p->next;
    }
}
//发布公告
void PostContent(ContentList& contentlist)
{
    cout << "请输入您要添加的新公告：";
    string news1;
    cin >> news1;
    Contents* a = new Contents;
    a->set_news(news1);
    contentlist.AddNews(a);
}
