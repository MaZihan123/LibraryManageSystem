#pragma once
#include"Users.h"
#include"Book.h"
#include"Content.h"
#include<iostream>
#include"SuperManger.h"
#include<fstream>//读文件所需头文件
using namespace std;
#include<string>
//总界面
void Interface()//开始界面
{
    cout << "**********************************" << endl;
    cout << "***欢迎来到马梓涵的图书管理系统***" << endl;
    cout << "**********************************" << endl;
}
//写文件
void OutputFile(UserList userlist, BookList booklist, ContentList newlist, int user_number, int book_number, int news_number)
{
    //写文件操作：
    ofstream ofs;
    ofs.open("D:\\P2\\XXQLibrary\\BaseData\\User.txt", ios::trunc);
    UserNode* p = userlist.head;
    //写用户
     while(p)
    {
         ofs << p->user->ID << " " << p->user->Name << " " << p->user->Password << " " << p->user->Type << " " <<p->user->hua<<" " << p->user->person_state << " " << p->user->Identification << " " << p->user->bad_return_book << " " << p->user->BookNumber << " ";
         for (int i = 0;i< p->user->BookNumber; i++)
         {
             ofs << p->user->LentBook[i][0] << " " << p->user->LentBook[i][1] ;
             if (i != p->user->BookNumber-1)
             {
                 ofs<< " ";
             }
         }
         ofs<< endl;
         p = p->next;
    }
    ofs.close();
    //写书
    ofstream ofs1;
    ofs1.open("D:\\P2\\XXQLibrary\\BaseData\\Book.txt", ios::trunc);
    BookNode* p1 = booklist.head;
    while (p1)
    {
        ofs1 << p1->book->IBSN << " " << p1->book->name << " " << p1->book->state << " " << p1->book->number << " " << p1->book->hot << endl;

        p1 = p1->next;
    }
    ofs1.close();
    //文件写公告
    ofstream ofs2;
    ofs2.open("D:\\P2\\XXQLibrary\\BaseData\\Contents.txt", ios::trunc);
    ContentNode* p2 = newlist.head;
     while(p2)
    {
        ofs2 << p2->news->notice << endl;
        p2 = p2->next;
    }
    ofs2.close();
}

//读取文档操作↓
void Read(int user_number, UserList& userlist, int book_number, BookList& booklist, int new_number, ContentList& contentlist)
{
    //读用户文件并创建用户类链表
    string filename = "D:\\P2\\XXQLibrary\\BaseData\\User.txt";
    ifstream fin(filename, ios::in);//读入文件
    for (int i = 0; i < user_number; i++)
    {
        User* user = new User;
        fin >> user->ID >> user->Name >> user->Password >> user->Type >>user->hua>> user->person_state >> user->Identification >> user->bad_return_book >> user->BookNumber;
        //导入借书数据
        for (int i = 0; i < user->BookNumber; i++)
        {

            fin >> user->LentBook[i][0] >> user->LentBook[i][1];
        }

        userlist.AddUser(user);
    }
   // userlist.show();
     //cout << endl;
      //读图书文件并创建图书类链表
    string filename1 = "D:\\P2\\XXQLibrary\\BaseData\\Book.txt";
    ifstream fin1(filename1, ios::in);//读入文件
    for (int i = 0; i < book_number; i++)
    {
        Book* book = new Book;
        fin1 >> book->IBSN >> book->name >> book->state >> book->number >> book->hot;
        booklist.AddBook(book);
    }
    // booklist.show();
     //读入公告
    string filename2 = "D:\\P2\\XXQLibrary\\BaseData\\Contents.txt";
    ifstream fin2(filename2, ios::in);//读入文件
    for (int i = 0; i < new_number; i++)
    {
        Contents* news = new Contents;
        fin2 >> news->notice;
        contentlist.AddNews(news);
    }
    //  contentlist.show();
}
//登录操作
bool login(string id, string password, UserList user)//引用user链
{
    if (user.login(id, password))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/////////////////////////////////////////////判断密码输的对不对操作
bool Correct(UserList userlist, string password,string id)
{
    UserNode *p = userlist.head;
    while (p)
    {
        if (p->user->Password == password&&p->user->ID==id)
        {
            return false;//输对了就返回false，结束虚幻
        }
        p = p->next;
    }
    return true;
}
/////////////////////////////////////////////判断用户ID是否合法
bool IDCorrect(UserList userlist, string Id)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->ID == Id)
        {
            return true;
        }
        p.head = p.head->next;
    }
    return false;//返回T再循环
}
//用于修改密码的整体确认值是否正确
bool ChangeCorrect(UserList userlist, string Id, string name, string shenfen)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->ID == Id)
        {
            if (p.head->user->Name == name && p.head->user->Identification == shenfen)
            {
                return true;
            }
        }
        p.head = p.head->next;
    }
    return false;//返回T再循环
}
//判断用户姓名是否正确
bool NameCorrect(UserList userlist, string n)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->Name == n)
        {
            return true;
        }
        p.head = p.head->next;
    }
    return false;
}
//判断身份证号是否正确的代码
bool ShenFenZhengCorrect(UserList userlist, string shengfenzhenghao)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->Identification == shengfenzhenghao)
        {
            return true;
        }
        p.head = p.head->next;
    }
    return false;
}
//切换用户↓
UserList FaceUser(UserList userlist, string aId)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->ID == aId)
        {
            return p;
        }
        p.head = p.head->next;
    }
}
//寻找指定用户类型////////////////////////////////////////////////////////////////////////////////////////////// 普 通 用 户 实 现 代 码 ///////////////
int FindType(UserList userlist, string aID)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->ID == aID)
        {
            if (p.head->user->Type == "图书管理员")
            {
                return 2;
            }
            else if (p.head->user->Type == "普通用户")
            {
                return 1;
            }
            else
            {
                return 3;
            }
        }
        p.head = p.head->next;
    }
    return 0;
}
//普通用户登陆后显示的界面↓
void CommonUserLogin(BookList booklist)
{
    BookNode* temp = booklist.head;
    string book1 = temp->book->name;
    int n = temp->book->hot;
    cout << "========推送功能========" << endl;
    while (temp)
    {
        if (temp->book->hot > n)
        {
            n = temp->book->hot;
            book1 = temp->book->name;
        }
        temp = temp->next;
    }
    cout << "目前火爆图书：" << book1 << endl;
    cout << "========================" << endl<<endl;
    cout << "======普通用户功能======" << endl;
    cout << "     1.预约借书      " << endl;
    cout << "     2.还书         " << endl;
    cout << "     3.查询个人信息   " << endl;
    cout << "     4.查询图书信息   " << endl;
    cout << "     5.查看公告      " << endl;
    cout << "     6.修改密码      " << endl;
    cout << "   输入其他数字进入登出界面" << endl;
    cout << "=========================" << endl;
}
//普通用户查询个人信息功能函数
void FindMessage(UserList new_userlist)
{
    cout << "姓名：" << new_userlist.head->user->Name << endl;
    cout << "ID：" << new_userlist.head->user->ID << endl;
    cout << "用户类型：" << new_userlist.head->user->Type << endl;
    cout << "借阅状态：" << new_userlist.head->user->person_state << endl;
    if (new_userlist.head->user->BookNumber != 0)
    {
        for (int i = 0; i < new_userlist.head->user->BookNumber; i++)
        {
            cout << "正在借阅：" << new_userlist.head->user->LentBook[i][0];
            cout << ",剩余时长：" << new_userlist.head->user->LentBook[i][1] << "天" << endl;
        }
    }
    else
    {
        cout << "用户未借阅图书";
    }
    cout << endl;
}
//超管补充
void FindUser(UserList userlist, string id)
{
    UserNode* p = userlist.head;
    while (p)
    {
        if (p->user->ID == id)
        {
            cout << "姓名：" << p->user->Name<<endl;

            cout << "用户类型：" << p->user->Type << endl;
            cout << "借阅状态：" << p->user->person_state << endl;
            if (p->user->BookNumber != 0)
            {
                for (int i = 0; i < p->user->BookNumber; i++)
                {
                    cout << "正在借阅：" << p->user->LentBook[i][0];
                    cout << ",剩余时长：" << p->user->LentBook[i][1] << "天" << endl;
                }
            }
            else
            {
                cout << "用户未借阅图书";
            }
            cout << endl;
            break;
        }
        p = p->next;
    }
}

//普通用户查询图书的功能函数
void FindBook(BookList& booklist)
{
    BookNode* p = booklist.head;
    while (p)
    {
        cout << "ID号：" << p->book->IBSN << "，图书名称：" << p->book->name << "，图书库存：" << p->book->number << "，图书火热程度：";
        int index = 1;
        if (p->book->hot >= 0&& p->book->hot <= 5)
        {
            index = 1;
        }
        else if (p->book->hot > 5 && p->book->hot <= 10)
        {
            index = 2;
        }
        else if ((int)p->book->hot > 10 && (int)p->book->hot <= 15)
        {
            index = 3;
        }
        else if ((int)p->book->hot > 15 && (int)p->book->hot <= 20)
        {
            index = 4;
        }
        else
        {
            index = 5;
        }
        for (int i = 0; i < index; i++)
        {
            cout << "*";
        }
        cout << endl;
        p = p->next;
    }
}
//修改密码
void ChangePassword(UserList userlist, string aID)
{
    UserList p = userlist;
    while (p.head != NULL)
    {
        if (p.head->user->ID == aID)
        {
            p.head->user->Password = "666666";
            break;
        }
        p.head = p.head->next;
    }
}
//普通用户查看公告函数
void FindContent(ContentList contentlist)
{
    ContentNode* p = contentlist.head;
    while (p)
    {
        cout << "公告：" << p->news->notice << endl;
        p = p->next;
    }
}
//普通用户预约借书功能
bool Lent(UserList userlist, BookList booklist)
{
    while (1)
    {
        if (userlist.head->user->person_state == "异常")
        {
            cout << "您的借阅状态异常，被图书管理员已标记，联系电话：17719577839" << endl;
            cout << "或选择微信转账50元，恢复借阅功能，微信号：ma2362471311" << endl;
            break;
        }
        string ibsn, NAME;
        cout << "当前可借阅图书：" << endl; BookNode* p = booklist.head;//显示当前可借阅图书
        while (p)
        {
            if (p->book->number > 0)
            {
                cout << "IBSN号：" << p->book->IBSN << "，书名：" << p->book->name << endl;
            }
            p = p->next;
        }   cout << "请输入您要借阅图书的名称：" << endl; cin >> NAME;
        p = booklist.head;
        while (p)
        {
            if (p->book->name == NAME)
            {
                if (p->book->number == 0)
                {
                    cout << "抱歉库存不足,请稍后换一本图书进行借阅" << endl;
                    return false;
                }
                p->book->number--;
                cout << "成功借阅!不要忘记三十天后还书哦" << endl;
                

                if (p->book->number == 0)
                {
                    p->book->state = "不可借阅";
                }
                userlist.head->user->LentBook[userlist.head->user->BookNumber][0] = NAME;
                userlist.head->user->LentBook[userlist.head->user->BookNumber++][1] = "30";
                booklist.head->book->hot++;
                return true;
            }
            p = p->next;
        }
        cout << "很抱歉，您输入的书名，我们没有收录" << endl;
        return false;
    }
    return true;
}
//普通用户还书实现核心程序
void FunctionGive(UserList userlist, int n)
{
    if (n == userlist.head->user->BookNumber - 1)
    {
        userlist.head->user->LentBook[n][0] = "";
        userlist.head->user->LentBook[n][1] = "";
    }
    else
    {
        userlist.head->user->LentBook[n][0] = userlist.head->user->LentBook[userlist.head->user->BookNumber - 1][0];
        userlist.head->user->LentBook[n][1] = userlist.head->user->LentBook[userlist.head->user->BookNumber - 1][1];
        userlist.head->user->LentBook[userlist.head->user->BookNumber - 1][0] = "";
        userlist.head->user->LentBook[userlist.head->user->BookNumber - 1][1] = "";
    }
}
//普通用户实现还书功能
bool Give(UserList& userlist, BookList& booklist)
{
    string book1;//归还的图书名
    while (true)
    {
        cout << "借书数：" << userlist.head->user->BookNumber << endl;
        if (userlist.head->user->BookNumber > 0)
        {
            cout << "请输入您想归还的图书：" << endl;
            cin >> book1;
            int i;
            for (i = 0; i < userlist.head->user->BookNumber; i++)
            {
                if (userlist.head->user->LentBook[i][0] == book1)//找还书的书名
                {
                    if (userlist.head->user->LentBook[i][1] > "0")//找还书的编号
                    {

                        cout << "还书未逾期，欢迎下次借阅~" << endl;
                    }
                    else
                    {
                        cout << "还书逾期，请注意按时还书！！！" << endl;
                        userlist.head->user->bad_return_book++;

                    }
                    FunctionGive(userlist, i);//还
                    BookNode* p = booklist.head;
                    while (p)//藏书库中加一
                    {
                        if (p->book->name == book1)
                        {
                            p->book->number++;
                            break;
                        }
                        p = p->next;
                    }
                    userlist.head->user->BookNumber--;
                    break;
                }
                if (i == userlist.head->user->BookNumber)
                {
                    cout << "还书失败，我们未收录该书" << endl;
                }
            }
        }
        else
        {
            cout << "您没有在借图书，无需还书" << endl;
            break;
        }
        cout << "===选择是否继续还书===" << endl << "1.是  ||  2.否" << endl;
        int num; cin >> num;
        if (num == 2)
        {
            break;
        }
    }
    return true;
}
void SortByHot(BookList booklist)
{
    BookNode* first = booklist.head->next;
    BookNode* p, * q, * tail;
    tail = NULL; // tail表示已经排好序的结点
    while (booklist.head->next != tail)
    { // 外层循环
        p = booklist.head; // p指头
        q = booklist.head->next; // q指第一个
        while (q->next != tail) { // 比较
            if (q->book->hot < q->next->book->hot) {
                p->next = q->next; // p的next指向q的下一个结点
                q->next = q->next->next; // q的next指向q的下下一个结点
                p->next->next = q; // p的下一个结点的next指向q
                q = p->next; // q指向p的下一个结点，即交换后的位置
            }
            p = p->next; // p和q都后移
            q = q->next;
        }
        tail = q; // tail指向最后一个已经排好序的结点
    }
    BookNode* r = booklist.head->next;
    while (r)
    {
        cout << "图书名称：" << r->book->name << "，图书火热程度：";
        int index = 1;
        if (r->book->hot >= 0 && r->book->hot <= 5)
        {
            index = 1;
        }
        else if (r->book->hot > 5 && r->book->hot <= 10)
        {
            index = 2;
        }
        else if ((int)r->book->hot > 10 && (int)r->book->hot <= 15)
        {
            index = 3;
        }
        else if ((int)r->book->hot > 15 && (int)r->book->hot <= 20)
        {
            index = 4;
        }
        else
        {
            index = 5;
        }
        for (int i = 0; i < index; i++)
        {
            cout << "*";
        }
        cout << endl << flush;
        r = r->next;
    }

}

void DeleteLoop(UserList &userlist, int& user_number)
{
    cout << "输出你想注销用户ID：";
    string id;
    cin >> id;
    UserNode* s = userlist.head;
    UserNode* temp = NULL;
    while (s)
    {
        if (s->user->ID == id)
        {
            if (s == userlist.head)
            {
                userlist.head = s->next;
                if (s->user != NULL) //判断s->user是否为空
                {
                    delete s->user; //如果不为空，就删除它
                }
                if (s != NULL) //判断s是否为空
                {
                    delete s; //如果不为空，就删除它
                }
                user_number--;
                s = userlist.head;//更新s为头
            }
            else if (s->next == NULL)//在末尾时
            {
                temp->next = NULL;
                delete s->user;
                delete s;
                user_number--;
                s = NULL;

            }
            else
            {
                temp->next = s->next;
                delete s->user;
                delete s;
                user_number--;
                s = temp->next;//更新s
            }
            break;
        }
        temp = s; //记录前驱结点
        s = s->next;
    }
}
//适用于普通用户和图管的修改密码函数
void ChangeMiMa(UserList new_userlist)
{
    
        cout << "请输入你想更改的密码：";
        string n;
        cin >> n;
        new_userlist.head->user->Password = n;
        cout << "您的密码已修改！请重新登录" << endl;
    
}