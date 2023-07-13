#pragma once
#include<string>
#include<iostream>
using namespace std;
// ////////////////////////////////////////////// 公 告 类 链 表 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 公告类
class Contents
{
public:
    string notice;
    string display();//返回公告
    void set_news(string n);

};

struct ContentNode {
    Contents* news;
    ContentNode* next;

};

class ContentList
{
public:
    ContentNode* head;
    ContentList();
    void AddNews(Contents* notice1);
    void show();
    
};
