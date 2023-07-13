#pragma once
#ifndef _LIBRARY_H
#define _LIBRARY_H
//所需结构体群
#include<iostream>
#include<cstring>
using namespace std;

//书的结构体
struct Books
{
    char name[100];//书名
    char IBSN[100];//IBSN号
    char state[20]= "未借阅";//书本状态:未借阅\已借阅
    
};

struct User
{
    int ID;//ID                                                  
    char name[50];//姓名                                        
    char password[100];//密码                                   
    char type[100];//成员类型                                  
    int day = 0;//借阅剩余时长                                 
    int number=0;//所借书数目                                  
    char person_state[10] = "正常";//是否可以借阅的状态        
    char Lent_name[100];//所借书名1                            
    int bad_return_book = 0;//异常还书次数                     

};
//公告的结构体
struct Contents
{
    char notice[500];
};



#endif //_LIBRARY_H