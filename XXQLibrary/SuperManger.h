#pragma once
#include<iostream>
#include<string>
#include"Book.h"
#include"Content.h"
#include"Users.h"
#include"Book.h"
#include"Content.h"
#include"Users.h"
//////////////////////////////////////////////////////////////////////////////////// 超 级 管 理 员 //////////////////////////////
//登录
void SuperMangerLogin()
{
    cout << "======超级管理员功能======" << endl;
    cout << "      1.修改密码      " << endl;
    cout << "      2.管理用户      " << endl;
    cout << "      3.图书排行   " << endl;
    cout << "      4.传信给用户   " << endl;
    cout << "     输入其他数字进入登出界面" << endl;
    cout << "============================" << endl;
}
//
void DeleteUser(UserList& userlist, string name1, int& number1)
{
    UserNode* p = userlist.head;
    UserNode* temp = NULL;
    while (p != NULL)
    {
        if (p->user->Name == name1)
        {
            if (p == userlist.head)
            {
                userlist.head = p->next;
                delete p->user;
                delete p;
                number1--;
                p = userlist.head;//更新p为头
            }
            else if (p->next == NULL)//书在末尾时
            {
                temp->next = NULL;
                delete p->user;
                delete p;
                number1--;
                p = NULL;

            }
            else
            {
                temp->next = p->next;
                delete p->user;
                delete p;
                number1--;
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
