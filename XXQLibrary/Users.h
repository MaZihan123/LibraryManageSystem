#pragma once
#include<string>
#include<iostream>
#include<string>
using namespace std;
/// ///////////////////////////////////////// 用 户 类 链 表 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//用户类
class User//用户类
{
public:
    string ID;//编号
    string Name;//表示用户姓名
    string Password;//密码
    string Type;//表示用户的类型
    string person_state;//成员的借阅状态
    string Identification;//身份证号
    int bad_return_book;//异常还书次数
    int BookNumber;
    string LentBook[10][2];
    string hua;
    User() {
        Type = "普通用户";
        person_state = "正常";
        bad_return_book = 0;//异常还书次数
    }
    void set_name(string n);
    void set_Password(string P);
    void set_ID(string id);
    void set_Ident(string i);
    void set_Type(string T);
    void set_BookNumber(int n);
    
};
//节点类，存user↓
struct UserNode
{
    User* user;
    UserNode* next;
};
//存头和功能函数↓,头是struct类型的节点类
class UserList
{

public:
    UserNode* head;
    UserList() { head = NULL; }
    //添加用户
    void AddUser(User* user1);
    //登录操作
    int login(const string Id, const string password);
    //显示用户
    void show();
};


///

