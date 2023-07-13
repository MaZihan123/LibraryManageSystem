#include "Book.h"
using namespace std;
//展示书本：
void BookList::show()
{
    BookNode* p = head;
    while (p != NULL)
    {
        cout << p->book->IBSN << " " << p->book->name << " " << p->book->state << " " << p->book->number << endl;
        p = p->next;
    }
}
//书类中添加书本操作
void BookList::AddBook(Book* book1)//传入的新成员
{
    BookNode* newNode = new BookNode;
    newNode->book = book1;
    newNode->next = NULL;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        BookNode* p = head;
        while (p->next != NULL)//p的下一个不是空进入循环
        {
            p = p->next;
        }
        p->next = newNode;
    }
}

/* ~BookList()
    {
        BookNode* temp = NULL;
        BookNode* p = head;
        while (p != NULL)
        {
            temp = p;
            p = p->next;
            delete temp->book;
            delete temp;
        }
    }*/