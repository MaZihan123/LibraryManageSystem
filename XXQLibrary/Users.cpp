#include "Users.h"
/// /////////// 赋 值 //////////////////////////////////////////////////
void User::set_name(string n)
{ Name = n; }
void User::set_Password(string P) 
{ Password = P; }
void User::set_ID(string id) 
{ ID = id; }
void User::set_Ident(string i) 
{ Identification = i; }
void User::set_Type(string T) 
{ Type = T; }
void User::set_BookNumber(int n) 
{ BookNumber = n; }
///////////////////////////////////////// 展 示 用 户 信 息 //////////////////////////
void UserList::show()
{
    UserNode* p = head;
    while (p != NULL)
    {
        cout << p->user->ID << " " << p->user->Name << " " << p->user->Password << " " << p->user->Type << " " << p->user->person_state << " " << p->user->Identification << " " << p->user->bad_return_book << " " << p->user->BookNumber;
        for (int i = 0; i < p->user->BookNumber; i++)
        {
            if (p->user->BookNumber == 0)
            {
                break;
            }
            cout << " 借阅的书本：" << p->user->LentBook[i][0] << "," << "剩余时长：" << p->user->LentBook[i][1];
        }
        cout << endl;
        p = p->next;
    }
}
/////////////////////////////////////// 登 录 /////////////////////
int UserList::login(const string Id, const string password)
{
    UserNode* temp = this->head;
    while (temp)
    {
        if (temp->user->ID == Id && temp->user->Password == password)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;

}
/////////////////////////////// 拓 展 链 表 ， 加 用 户 ///////////////////////
void UserList::AddUser(User* user1)
{
    UserNode* newNode = new UserNode();
    newNode->user = user1;
    newNode->next = NULL;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        UserNode* p = head;
        while (p->next != NULL)//p的下一个不是空进入循环
        {
            p = p->next;
        }
        p->next = newNode;
    }
}