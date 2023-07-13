#include "Content.h"
using namespace std;
string Contents::display()
{
    return notice;
}
//
void ContentList:: show()
{
    ContentNode* p = head;
    while (p != NULL)
    {
        cout << p->news->notice << " " << endl;
        p = p->next;
    }
}
void ContentList::AddNews(Contents* notice1)
{
    ContentNode* newNode = new ContentNode;
    newNode->news = notice1;
    newNode->next = NULL;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        ContentNode* p = head;
        while (p->next != NULL)//p的下一个不是空进入循环
        {
            p = p->next;
        }
        p->next = newNode;
    }
}
ContentList::ContentList()
{ 
    head = NULL; 
}
void Contents::set_news(string n) 
{
    notice = n; 
}

