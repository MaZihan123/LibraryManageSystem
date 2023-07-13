#include "UserAll.h"//结构体群
#include<cstring>//使用strcmp
#include<iostream>
#include<fstream>//
#include<string>
#include <cstdio>
using namespace std;
void OutputFile(User user[], Books book[], Contents news[], int user_number, int book_number, int news_number);
void Interface()//开始界面
{
    cout << "**********************************" << endl;
    cout << "***欢迎来到马梓涵的图书管理系统***" << endl;
    cout << "**********************************" << endl;
}
bool login(User user[], int& n, int user_number)//登录界面
{
    int id;
    char Password[50];
    cout << "请输入您的ID号：";
    cin >> id;
    cout << "请输入您的密码： ";
    cin >> Password;
    //在用户数组中查找用户
    for (int i = 0; i <= user_number - 1; i++)
    {
        if (user[i].ID == id && !strcmp(user[i].password, Password))
        {
            cout << "密码正确!" << endl;
            n = i + 1;//i是数组下标，和rank差1
            return true;
        }
    }
    cout << "啊哦，密码输错了，请重新尝试" << endl;
    return false;

}
string CM = "普通";
string LM = "图管";
string SM = "超管";
string Yes = "正常";
string No = "异常";
void logined(User user[], int rank)//登录后显示界面
{


    
    if(strcmp(user[rank-1].type,"普通用户"))
    {
          cout << "Hi!"<<user[rank-1].type << user[rank - 1].name << "，今天宜多读书~" << endl;
    } 
    if(strcmp(user[rank-1].type,"图管"))
    {
        cout << "Hi!" << user[rank - 1].type<< user[rank - 1].name << "，服务大家，以你为荣" << endl;
    }
    if(strcmp(user[rank-1].type,"超管"))
    {
         cout << "Hi!" << user[rank - 1].type<< user[rank - 1].name << "，能力越大，责任越大" << endl;
        
    }

    /*
    switch (rank) {
    case 1:
        cout << "Hi!"<<user[rank-1].type << user[rank - 1].name << "，今天宜多读书~" << endl;
        break;
    case 2:
        cout << "Hi!" << user[rank - 1].type<< user[rank - 1].name << "，服务大家，以你为荣" << endl;
        break;
    case 3:
        cout << "Hi!" << user[rank - 1].type<< user[rank - 1].name << "，能力越大，责任越大" << endl;
        break;
    }*/
}
//普通用户实现功能函数1.预约
bool Reverse(Books book[], User user[], int& rank, int& book_number)//预约书函数
{
    while (1)
    {
        if (user[rank].person_state == No)
        {
            cout << "您的借阅状态异常，被图书管理员已标记，联系电话：17719577839" << endl;
            cout << "或选择微信转账50元，恢复借阅服务" << endl;
            break;
        }
        if (user[rank].number != 0)
        {
            cout << "您还有未还图书，请先进行还书操作后再进行借阅" << endl;
            break;
        }
        char book_name[100];
        cout << "请输入您预约借阅书籍的名称:" << endl;
        cin >> book_name;
        for (int i = 0; i < book_number; i++)
        {

            if (strcmp(book[i].name, book_name) == 0)
            {
                cout << "成功借阅" << book[i].name << ",不要忘记30天后需要还书哦~" << endl;
                strcpy_s(book[i].state, "已借阅");//将借阅状态改为已借阅
                user[rank].day = 30;//逾期还书的惩罚
                user[rank].number++;
                strcpy_s(user[rank].Lent_name, book_name);//登记所借书名
                return false;//返回false退出循环
            }
        }
        cout << "很抱歉，你输入的书名我们没有收录~(注意括号是中文输入法括号哦)" << endl;
        break;//返回
    }
}
//普通用户实现还书函数
void return_books(Books* book, User user[], int& rank, int& book_number)
{
    char a[50] = "确定";
    char b[50];
    if (user[rank].number > 0)
    {
        cout << "所借书籍:" << user[rank].Lent_name << endl;
        cout << "剩余时长:" << user[rank].day << endl;
        cout << "输入”确定“进行还书:";
        cin >> b;
        cout << b << endl;
        if (strcmp(a, b) == 0)//输入确定后，进行还书操作
        {

            if (user[rank].day > 0)//判断是否逾期还书
            {
                cout << "还书未逾期，欢迎下次借阅" << endl;
                
            }
            else
            {
                cout << "还书逾期，请注意按时还书" << endl;
                user[rank].bad_return_book++;//若逾期，则记录还书逾期次数
            }
            for (int i = 0; i < book_number; i++)//更新书本状态
            {
                if (strcmp(book[i].name, user[rank].Lent_name) == 0)
                {
                    memset(user[rank].Lent_name, 0, sizeof(user[rank].Lent_name));//user中借书清零
                    strcpy_s(book[i].state,"未借阅");
                }
            }
            strcpy_s(user[rank].Lent_name, "无");
            user[rank].number = 0;//借书的数目清零
        }
    }
    else
    {
        cout << "宝贝，你还没有借书呢，快去借阅一本吧~" << endl;
    }

}
void commonUser(Books book[], int rank, User user[], Contents news[], int& book_number, int news_number,int user_number)//普通用户实现功能函数
{
    cout << "======普通用户功能======" << endl;
    cout << "     1.预约借书      " << endl;
    cout << "     2.还书         " << endl;
    cout << "     3.查询个人信息   " << endl;
    cout << "     4.查询图书信息   " << endl;
    cout << "     5.查看公告      " << endl;
    cout << "   输入其他数字进入登出界面" << endl;
    cout << "=========================" << endl;
    while (1)
    {
        int n;
        cin >> n;
        if (n < 1 || n>5)
        {
            break;
        }
        switch (n) {
        case 0:
            break;
        case 1://借书
            
                Reverse(book, user, rank, book_number);
            
            break;
        case 2://还书
            return_books(book, user, rank, book_number);

            break;
        case 3://查询个人信息
            cout << "ID:" << user[rank].ID;
            cout << "号 姓名:" << user[rank].name << endl;
            cout << "用户借阅状态：";
            if (user[rank].person_state)
            {
                cout << "正常" << endl;
            }
            else {
                cout << "异常（有逾期未还记录）" << endl;
            }
            if (user[rank].number > 0)
            {
                cout << "所借书籍:" << user[rank].Lent_name << endl;
                cout << "剩余时长:" << user[rank].day << endl;
            }
            else
            {
                cout << "暂无借阅图书" << endl;
            }
            cout << "用户类型:普通用户" << endl;

            break;
        case 4://查询图书信息
            for (int i = 0; i < book_number; i++) {

                cout << "IBSN号:" << book[i].IBSN << endl;
                cout << "图书名称:" << book[i].name << endl;
                cout << "借阅状态:";
                if(strcmp(book[i].state,"未借阅")==0)
                {
                    cout << "未借阅" << endl;
                }
                else
                {
                    cout << "借阅中" << endl;
                }
                cout << endl;

            }
            break;
        case 5:
            for (int i = 0; i < news_number; i++)
            {
                cout << news[i].notice << endl;
            }

            break;
        }
        OutputFile(user, book, news, user_number, book_number, news_number);
        cout << endl;
        cout << "继续使用或输入其他数字退出登录" << endl;

    }
}
//图书管理员功能
//1.添加图书
void AddBook(int& book_number, Books book[])
{
    cout << "请输入新添加书本的书名：";
    cin >> book[book_number].name;
    cout << "请输入新添加书本的序列号：";
    cin >> book[book_number].IBSN;
    strcpy_s(book[book_number].state, "未借阅");
    book_number++;
}
void DeleteBook(int& book_number, Books book[])
{
    char a[50];
    cout << "请输入所需删除图书的名称：";
    cin >> a;
    int i = 0;
    for (; i < book_number; i++)
    {
        if (strcmp(a, book[i].name) == 0)
        {
            if (i == book_number - 1)
            {
                memset(book[i].name, 0, sizeof(book[i].name));
                memset(book[i].IBSN, 0, sizeof(book[i].IBSN));
            }
            else
            {
                Books temp;//删除图书短用strcpy，注销用户，用结构体存地址然后交换删最后一个
                strcpy_s(temp.state,book[i].state);
                strcpy_s(temp.name, book[i].name);
                strcpy_s(temp.IBSN, book[i].IBSN);
                strcpy_s(book[i].state,book[book_number].state);
                strcpy_s(book[i].name, book[book_number - 1].name);
                strcpy_s(book[i].IBSN, book[book_number - 1].IBSN);
                memset(book[book_number - 1].name, 0, sizeof(book[book_number - 1].name));
                memset(book[book_number - 1].IBSN, 0, sizeof(book[book_number - 1].IBSN));
            }
            book_number--;
            cout << "删除成功!" << endl;
        }
    }

}//异常处罚
void BadBeheavior(User user[], int& user_number)
{

    char a[5] = "是";
    char b[5];
    for (int i = 0; i < user_number; i++)
    {
        if (user[i].bad_return_book != 0)
        {
            cout << "发现异常还书用户:" << user[i].name << endl;
            cout << "是否对其进行处罚？（回复“是”或“否”）";
            cin >> b;
            if (strcmp(a, b) == 0)
            {
                cout << user[i].name << "因多次异常还书受到图书管理员处罚，暂停借阅服务，请联系图书管理员，联系电话：17719577839" << endl;
                cout << "或选择微信转账50元恢复借阅，微信号：ma23462471311" << endl;
            }
            strcpy_s(user[i].person_state, "异常");
        }
        else
        {
            cout << "用户" << user[i].name << "表现良好，不存在异常记录哦~" << endl;
        }
    }
}
void Announce(Contents news[], int& new_number)
{
    cout << "请发布新的公告:";
    cin >> news[new_number].notice;
    new_number++;
}
void LibraryManger(User user[], Books book[], Contents news[], int& book_number, int& news_number, int& user_number) {
    cout << "======图书管理员功能======" << endl;
    cout << "      1.添加图书      " << endl;
    cout << "      2.删除图书      " << endl;
    cout << "      3.异常还书处罚   " << endl;
    cout << "      4.发布公告      " << endl;
    cout << "     输入其他数字进入登出界面" << endl;
    cout << "=========================" << endl;
    while (1) {
        int n;
        cin >> n;
        if (n > 4 || n < 1)
        {
            break;
        }
        switch (n) {
        case 1:
            AddBook(book_number, book);//添加图书
            break;
        case 2:
            DeleteBook(book_number, book);//删除图书
            break;
        case 3:
            BadBeheavior(user, user_number);//异常行为处理
            break;
        case 4:
            Announce(news, news_number);//发布公告
            break;
        }
        OutputFile(user, book, news, user_number, book_number, news_number);
        cout << endl;
        cout << "继续使用或输入其他数字退出图管登录" << endl;
    }
}

//超级管理员功能
void ChangePassword(User user[], int& user_number)
{
    int id1;
    cout << "您想修改ID为多少的用户密码？";
    cin >> id1;
    char new_password[50];
    for (int i = 0; i < user_number; i++)
    {
        if (id1 == user[i].ID)
        {
            cout << "请输入更改后的新密码:";
            cin >> new_password;
            strcpy_s(user[i].password, new_password);
            break;
        }
    }

    cout << "以按您要求重新为用户跟新密码!" << endl;
}
void DeleteLast(User user[], int i)
{
    user[i].ID = NULL;
    memset(user[i].name, 0, sizeof(user[i].name));
    memset(user[i].password, 0, sizeof(user[i].password));
    memset(user[i].Lent_name, 0, sizeof(user[i]).Lent_name);
    memset(user[i].type, 0, sizeof(user[i].type));//注销清空
    user[i].number = 0;//所借书数目
    user[i].day = NULL;
    user[i].bad_return_book = NULL;
    memset(user[i].person_state, 0, sizeof(user[i].person_state));
}
void DeleteUser(User user[], int& user_number, int i)
{
    strcpy_s(user[i].name, user[user_number - 1].name);
    strcpy_s(user[i].password, user[user_number - 1].password);
    strcpy_s(user[i].Lent_name, user[user_number - 1].Lent_name);
    strcpy_s(user[i].person_state, user[user_number - 1].person_state);
    user[i].ID = user[user_number - 1].ID;
    strcpy_s(user[i].type, user[user_number - 1].type);
    user[i].day = user[user_number - 1].day;
    user[i].number = user[user_number - 1].number;
    user[i].bad_return_book = user[user_number - 1].bad_return_book;
    //清除
    user[user_number - 1].ID = NULL;
    memset(user[user_number - 1].name, 0, sizeof(user[user_number - 1].name));
    memset(user[user_number - 1].password, 0, sizeof(user[user_number - 1].password));
    memset(user[user_number - 1].Lent_name, 0, sizeof(user[user_number - 1]).Lent_name);
    memset(user[user_number - 1].type, 0, sizeof(user[user_number - 1]).type);
    user[user_number - 1].number = NULL;
    user[user_number - 1].bad_return_book = NULL;
    memset(user[user_number - 1].person_state, 0, sizeof(user[user_number - 1]).person_state);
    user[user_number - 1].number = NULL;//所借书数目
}
void MangeCommonUser(User user[], int& user_number)
{
    int id1;
    cout << "您想管理ID为多少的普通用户？" << endl;
    cin >> id1;
    for (int i = 0; i < user_number; i++)
    {
        if (id1 == user[i].ID)
        {
            if (strcmp(user[i].type,"普通")!=0)
            {
                cout << "抱歉，该ID的用户不是普通用户";
            }
            else
            {
                while (1)
                {
                    cout << "====管理普通用户====" << endl;
                    cout << "1.查看用户借阅状态" << endl;
                    cout << "2.查看用户所借图书" << endl;
                    cout << "3.查看用户异常还书次数" << endl;
                    cout << "4.查看用户借阅剩余时长" << endl;
                    cout << "5.显示用户信息" << endl;
                    cout << "6.注销用户" << endl;
                    cout << "输入其他数字退出管理普通用户" << endl;
                    cout << "===================" << endl;

                    int n;
                    cin >> n;
                    if (n > 6 || n < 1)
                    {
                        break;
                    }
                    switch (n) {
                    case 1:
                        cout << user[i].name << "的借阅状态：";
                        if (user[i].person_state) {
                            cout << "正常借阅" << endl;
                        }
                        else {
                            cout << "暂停借阅服务" << endl;
                        }
                        break;
                    case 2:
                        if (user[i].number) { cout << user[i].name << "的所借图书：" << user[i].Lent_name << endl; }
                        else {
                            cout << user[i].name << "尚未借阅图书" << endl;
                        }
                        break;
                    case 3:
                        cout << user[i].name << "的异常还书次数:" << user[i].bad_return_book << endl;
                        break;
                    case 4:
                        cout << user[i].name << "的剩余还书时长:" << user[i].day << endl;
                        break;
                    case 5:
                        cout << user[i].name << "的用户基本信息：" << endl;
                        cout << "姓名:" << user[i].name << endl << "ID:" << user[i].ID << endl << "密码:"
                            << user[i].password << endl;
                        break;
                    case 6:
                        if (i == user_number - 1) {
                            DeleteLast(user, i);
                        }
                        else {//换位
                            
                            DeleteUser(user, user_number, i);
                        }
                        cout << "已注销" << endl;
                        user_number--;
                        break;
                    }
                }
                
            }
        }
    }

}
void MangerLibrary(User user[], int &user_number,int & book_number,int& news_number,Books book[],Contents news[])
{
    int id1;
    cout << "您想管理ID为多少的图书管理员？";
    cin >> id1;
    for (int i = 0; i < user_number; i++)
    {
        if (id1 == i + 1)
        {
            if (strcmp(user[i].type,"图管")!=0)
            {
                cout << "抱歉，该ID的用户不是图书管理员";
            }
            else
            {
                while (1)
                {
                    cout << "====管理图书管理员====" << endl;
                    cout << "1.查看用户借阅状态" << endl;
                    cout << "2.查看用户所借图书" << endl;
                    cout << "3.查看用户异常还书次数" << endl;
                    cout << "4.查看用户借阅剩余时长" << endl;
                    cout << "5.显示用户信息" << endl;
                    cout << "6.注销用户" << endl;
                    cout << "输入其他数字退出管理图书管理员" << endl;
                    cout << "===================" << endl;
                    int n;
                    cin >> n;
                    if (n > 7 || n < 1)
                    {
                        break;
                    }
                    switch (n) {
                    case 1:
                        cout << user[i].name << "的借阅状态：";
                        if (user[i].person_state) {
                            cout << "正常借阅" << endl << endl;
                        }
                        else {
                            cout << "暂停借阅服务" << endl;
                        }
                        break;
                    case 2:
                        if (user[i].number) { cout << user[i].name << "的所借图书：" << user[i].Lent_name << endl; }
                        else {
                            cout << user[i].name << "尚未借阅图书" << endl;
                        }
                        break;
                    case 3:
                        cout << user[i].name << "的异常还书次数:" << user[i].bad_return_book << endl;
                        break;
                    case 4:
                        cout << user[i].name << "的剩余还书时长:" << user[i].day << endl;
                        break;
                    case 5:
                        cout << user[i].name << "的用户基本信息：" << endl;
                        cout << "姓名:" << user[i].name << endl << "ID:" << user[i].ID << endl << "密码:"
                            << user[i].password << endl;
                        break;
                    case 6:
                        if (i == user_number - 1) {
                            DeleteLast(user, i);
                        }
                        else {
                            DeleteUser(user, user_number, i);
                        }
                        cout << "已注销" << endl;
                        user_number--;
                        break;
                    }
                }
                OutputFile(user, book, news, user_number,book_number,news_number);
            }
        }
    }

}

void SuperManger(User user[], Books book[], Contents news[], int& book_number, int& news_number, int& user_number) {
    cout << "======超级管理员功能======" << endl;
    cout << "      1.修改密码      " << endl;
    cout << "      2.管理普通用户      " << endl;
    cout << "      3.管理图书管理员   " << endl;
    cout << "     输入其他数字进入登出界面" << endl;
    cout << "============================" << endl;
    while (1) {
        int n;
        cin >> n;
        if (n > 3 || n < 1)
        {
            break;
        }
        switch (n) {
        case 1:
            ChangePassword(user, user_number);
            break;
        case 2:
            MangeCommonUser(user, user_number);
            break;
        case 3:
            //User user[], int user_number,int & book_number,int& news_number,Book book[],Contents news[]
            MangerLibrary(user, user_number,book_number,news_number,book,news);
            break;
        }
        cout << endl;
        OutputFile(user, book, news, user_number, book_number, news_number);
        cout << "继续使用或输入其他数字退出超管登录" << endl;
    }
}
void OutputFile(User user[], Books book[], Contents news[], int user_number, int book_number, int news_number)
{
    //写文件操作：
    ofstream ofs;
    ofs.open("User.txt", ios::trunc);
    //写用户
    for (int i = 0; i < user_number; i++)
    {//            1                  王富贵                 1                          普通                  0                      正常                             无                               0                         0
        ofs << user[i].ID << " " << user[i].name << " " << user[i].password << " " << user[i].type << " " << user[i].day << " "<< user[i].person_state << " " << user[i].Lent_name << " " << user[i].bad_return_book<<" "<<user[i].number << endl;
        
    }
    ofs.close();
    //写公告
    ofstream ofs1;
    ofs1.open("news.txt", ios::trunc);
    for (int i = 0; i < news_number;i++)
    {
        ofs1 << news[i].notice << endl;
    }
    ofs1.close();
    //文件写书
    ofstream ofs2;
    ofs2.open("Book.txt", ios::trunc);
    for (int i = 0; i < book_number; i++)
    {
        ofs2 << book[i].name << " " << book[i].IBSN <<" "<<book[i].state << endl;
    }
    ofs2.close();
}

int main()
{
    //初始化部分
    User user[50];
    string a;
    int user_number = 3;
    string filename = "E:\\图书VS\\LibraryManger\\Project1\\User.txt";
    ifstream fin(filename,ios::in);//读入操作

    int i = 0,index=3;
    while(fin >> user[i].ID >> user[i].name >> user[i].password >> user[i].type >> user[i].day >>user[i].person_state >> user[i].Lent_name >> user[i].bad_return_book>>user[i].number)
    {
        
         
         i++;
    }
    fin.close();//关 
    Contents news[100];
    int news_number = 1;
    string filename1 = "E:\\图书VS\\LibraryManger\\Project1\\news.txt";
    ifstream fin1(filename1, ios::in); i = 0;
    while(fin1 >> news[i].notice)
    {
        i++;
    }
    fin1.close();
    Books book[50];
    string filename3 = "E:\\图书VS\\LibraryManger\\Project1\\Book.txt";
    int book_number = 3;
    ifstream fin3(filename3, ios::in); i = 0;
    while (fin3 >> book[i].name >> book[i].IBSN >> book[i].state)
    {
        i++;
    }
    //核心程序开始！
    while (1)
    {
        int rank = 0;//成员类型，1是普通，2是图管，3是超管
        Interface();//创建界面
        cout << "             登录界面" << endl;
        while (1)
        {
            if (login(user, rank, user_number))//唤醒输密码界面，输正确进行下一步
            {
                break;
            }
        }
        logined(user, rank);//登陆后告知信息
        switch (rank)//分步实现每一用户地功能
        {
        case 1://实现普通用户的各种功能
            //Books book[], int rank, User user[], Contents news[], int& book_number, int news_number,int user_number
            commonUser(book, rank - 1, user, news, book_number, news_number,user_number);//rank输入减一因为是数组0开
            break;
        case 2:
            LibraryManger(user, book, news, book_number, news_number, user_number);
            break;
        case 3:
            SuperManger(user, book, news, book_number, news_number, user_number);
            break;
        }
        cout << "*退出程序请输入”0“*" << endl;
        cout << "如果想继续浏览图书管理系统则输入任意非零数字即可" << endl;
        int num;
        cin >> num;
        if (num)
        {
            continue;
        }
        else
        {
            break;
        }
    }

}
