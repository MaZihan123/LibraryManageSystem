#include"Book.h"
#include"Users.h"
#include"Content.h"
#include"UserFunctions.h"
#include<conio.h>
#include<iostream>
#include"LM.h"
#include"SuperManger.h"
//回显是星操作
string Unshow()
{
    char pass;
    string unshowpass;
    for (int i = 0; i < 6; i++)
    {
        pass = _getch();//输入不会显示在屏幕上
        if (pass >= 33 && pass <= 126)
        {
            if (i == 0) unshowpass = pass;
            else
                unshowpass = unshowpass + pass;
            cout << "*";// 回显星号
        }
        else
        {
            cout << "存在非法字符，请重新输入：" << endl;
            i = -1;
        }
    }
    cout << endl;
    return unshowpass;
}
string C;
string L;
string c,l;
int main()
{
    int user_number = 4; int book_number = 5; int news_number = 1;
    UserList userlist;      //用户链表
    BookList booklist;      //图书链表
    ContentList contentlist;   //公告链表
    int change = 0;//需要修改密码的人数
    //读入文件操作
    Read(user_number, userlist, book_number, booklist, news_number, contentlist);
    string NAME;
    //核心程序开始
    string id;
    while (1)
    {
        int lentnumber = 0;
        Interface();//总界面
        cout << "-----------------登录界面-----------------" << endl;
        cout << "1.登录" << endl;
        cout << "2.注册" << endl;
        cout << "3.忘记密码" << endl;
        cout << "输入其他数字退出程序" << endl;
        //  userlist.show();//测试用户输出
        //  booklist.show();//测试书本输出
        //  contentlist.show();//测试公告输出
        int n; cin >> n;
        //登录界面
        if (n == 1)
        {
            cout << "请输入您的ID:" << endl; cin >> id;//ID识别
            cout << "请选择密码输入模式:" << endl;
            cout << "  1.显示密码  ||  2.隐藏密码" << endl;
            cout << "请输入选项:";
            int mod; cin >> mod;
            cout << "请输入您的密码（六位密码）:";
            //密码回显为* 、判断密码是否正确
            if (mod == 2)//回显是星号
            {
                string pass1;
                cout << "密码(六位密码)：";
                pass1 = Unshow();
                cout << endl;
                while (  true)
                {
                    if (Correct(userlist, pass1,id))
                    {
                        cout << "您的密码输入有误，请重新输入:";
                        cout << "密码(六位密码)：";
                        pass1 = Unshow();
                        cout << endl;
                    }
                    else
                    {
                        break;
                    }

                }
                cout << "密码正确！" << endl;
            }
            else
            {
                string pass1;
                cin >> pass1;
                while (true)
                {
                    if(Correct(userlist, pass1,id))
                    {
                        
                        cout << "您的密码输入有误，请重新输入:";
                        cin >> pass1;
                    }
                    else
                    {
                        break;
                    }
                }
                cout << "成功登录！" << endl;
            }
            UserList new_userlist = FaceUser(userlist, id);//找到ID所对应的用户记作  new_userlist、
            //普通用户
            if (new_userlist.head->user->Type == "普通用户")
            {
                while (1)
                {
                    if (new_userlist.head->user->hua !="")
                    {
                        cout << "有超级管理员通知：" << L;
                    }
                    cout << "Hi!普通用户" << new_userlist.head->user->Name << "，今天宜多读书~" << endl;
                    //普通用户功能和推送界面↓
                    CommonUserLogin(booklist);
                    if (new_userlist.head->user->ID == c)
                    {
                        cout << "有超级管理员通知：" << C;
                    }
                    int n;
                    cin >> n;
                    if (n < 1 || n>6)
                    {
                        break;
                    }
                    switch (n)
                    {
                    case 1://预约借书功能
                        Lent(new_userlist, booklist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        break;
                    case 2://还书功能
                        Give(new_userlist, booklist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        break;
                    case 3://查看个人信息功能
                        FindMessage(new_userlist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        break;
                    case 4://查询图书信息
                        FindBook(booklist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        break;
                    case 5://查询公告
                        FindContent(contentlist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        break;
                    case 6://修改密码
                        ChangeMiMa(new_userlist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        break;
                    }
                    if (n == 6)
                    {
                        break;
                    }

                }
            }
            //图书管理员
            else if (new_userlist.head->user->Type == "图书管理员")
            {
                while (1)
                {
                    cout << "Hi!管理员" << new_userlist.head->user->Name << "，服务大家，以你为荣" << endl;
                    LibraryMangerLogin();//登录后展示的界面
                    int num; cin >> num;
                    if (num > 5 || num < 1)
                    {
                        break;
                    }
                    if (new_userlist.head->user->hua =="无")
                    {
                        
                    }
                    else
                    {
                        cout << "有超级管理员通知：" << L;
                    }
                    switch (num)
                    {
                    case 1://添加图书功能
                    {
                        while (1)
                        {
                            string bookname; int addnumber, bookibsn;
                            cout << "您要补充现有图书库存，还是添加新图书？" << endl << "1.补充现有图书 || 2.添加新图书 || 输入其他数字退出程序" << endl;
                            int n; cin >> n;
                            if (n == 1)
                            {
                                cout << "请输入您想要补充图书的名称：";
                                cin >> bookname;
                                cout << "请输入您想要补充图书的本数：";
                                cin >> addnumber;
                                if (AddNowBook(booklist, addnumber, bookname))
                                {
                                    cout << "补充书本成功！" << endl;
                                }
                                else
                                {
                                    cout << "补充书本有误，请稍后再试" << endl;
                                    break;
                                }


                            }
                            else if (n == 2)
                            {

                                cout << "请输入您要添加图书的名称：";
                                cin >> bookname;
                                while (1)
                                {
                                    int panduan = 0;
                                    cout << "请输入您要添加图书的IBSN号：";/////////////////这步函数是看IBSN号重复否
                                    cin >> bookibsn;
                                    BookNode* p = booklist.head;
                                    while (p)
                                    {
                                        if (p->book->IBSN == bookibsn)
                                        {
                                            cout << "您输入的IBSN号重复，请重新输入" << endl;
                                            panduan = 1;
                                        }
                                        p = p->next;
                                    }
                                    if (panduan)
                                    {
                                        continue;
                                    }
                                    break;

                                }

                                cout << "请输入您想要补充图书的本数：";
                                cin >> addnumber;
                                Book* a = new Book;
                                a->set_bookname(bookname); a->set_number(addnumber); a->set_IBSN(bookibsn);
                                booklist.AddBook(a);
                            }
                            else
                            {
                                break;
                            }
                        }
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    }
                    break;
                    case 2: //删除图书功能
                        //  while (1)
                        //  {
                            //  string n1;
                             // cout << "输入确定，继续删除操作，输入其他则退出程序。";cout << endl;
                             // cin >> n1;
                             // if (n1 == "确定")
                            //  {
                    {string bookname1;
                    cout << "请输入所需删除图书的名称：";
                    cin >> bookname1;
                    DeleteBook(booklist, bookname1, book_number);
                    cout << "已按要求删除图书" << endl;
                    OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number); 
                    }
                    //  }
                     // else
                    //  {
                   //       break;
                     // }
                //  }
                    break;
                    case 3://异常处罚
                    {
                        Punish(userlist);
                        cout << "*异常查询结束*" << endl; 
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    }
                    break;
                    case 4://发布公告
                    {  
                        string bookname;
                        PostContent(contentlist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    }
                    break;
                    case 5://修改密码
                    {
                        ChangeMiMa(new_userlist);
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    }
                    break;
                    if (n == 5)
                    {
                        break;
                    }
                    }
                }
            }
            //超级管理员
            else
            {
                cout << "Hi!超管" << new_userlist.head->user->Name << "，能力越大，责任越大" << endl;

                while (1)
                {
                    SuperMangerLogin();
                    int n;
                    cin >> n;
                    if (n < 1 || n>5)
                    {
                        break;
                    }
                    switch (n)
                    {
                        //修改密码
                    case 1:
                    {
                        string id;
                        cout << "您想修改ID为多少的用户密码？";
                        cin >> id;
                        while (1)//判断id是否合法
                        {
                            if (IDCorrect(userlist, id))
                            {
                                break;
                            }
                            cout << "ID输入不合法，请重新输入：";
                        }
                        string new_pass1;
                        UserNode* p = userlist.head;
                        while (p)
                        {
                            if (p->user->ID == id)
                            {
                                cout << "您想将其密码修改为多少？(六位密码)" << endl;
                                cin >> new_pass1;
                                //判断长度
                                while (1)
                                {
                                    if (new_pass1.length() == 6)
                                    {
                                        break;
                                    }
                                    cout << "长度有误，请重新输入" << endl;
                                    cin >> new_pass1;
                                }
                                p->user->Password = new_pass1;
                                cout << "修改成功！" << endl;
                                break;
                            }
                            p = p->next;
                        }
                        OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    }
                    break;
                    //管理用户
                    case 2:
                    {
                        cout << "====管理用户====" << endl;
                        cout << "1.显示用户信息" << endl;
                        cout << "2.注销用户" << endl;
                        cout << "输入其他数字退出管理用户" << endl;
                        cout << "===================" << endl;
                        int n;
                        cin >> n;
                        switch (n)
                        {
                        case 1:
                        {
                            cout << "请输入你想查看的用户ID：";
                            string id;
                            cin >> id;
                            FindUser(userlist,id);
                            OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        }
                        break;
                        case 2:
                        {
                            DeleteLoop(userlist,user_number);
                            cout << "已注销" << endl;
                            OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                        }
                        }
                    }
                    break;;
                    case  3:
                    {
                         SortByHot(booklist);
                         OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    }
                    break;
                    case 4:
                    {
                        cout << "请输入您想通知的用户ID：";
                        cin >> l;
                        cout << "请输入您想要传达的信息：";
                            cin >> L;
                            UserNode* p = userlist.head;
                            while (p)
                            {
                                if (p->user->ID == l)
                                {
                                    p->user->hua = L;
                                    break;
                                }
                                p = p->next;
                            }
                            
                    }
                    OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
                    break;
                    }
                   
                }
            }
        }

        //注册界面
        else if (n == 2)/////////////////////// 注 册 界 面 ////
        {
            cout << "=====欢迎来到注册界面====" << endl;
            string aID;
            cout << "请输入您的姓名：";
            cin >> NAME;
            cout << "输入ID：";
            cin >> aID;
            while (IDCorrect(userlist, aID))
            {
                cout << "您所输入的ID已经有用户使用了，请输入一个新的ID：";
                cin >> aID;
            }

            string pass1, pass2;
            cout << "请选择密码输入模式:" << endl;
            cout << "  1.显示密码  ||  2.隐藏密码" << endl;

            int n; cin >> n;
            //判断输入的选项模块是否合法
            while (1)
            {
                if (n == 1 || n == 2)
                {
                    break;
                }
                else
                {
                    cout << "无效数字，请重新输入：";
                    cin >> n;
                }
            }
            cout << "请输入您的密码(六位密码）：";
            if (n == 1)
            {
                cin >> pass1;
                cout << endl << "请再次输入";
                cin >> pass2;
                while (1)
                {
                    if (pass1 == pass2 && size(pass1) == 6)
                    {
                        break;
                    }
                    else
                    {
                        cout << "抱歉，您的密码输入两次不同或长度有误，请重新输入" << endl;
                        cout << "请输入您的密码(六位密码）：";
                        cin >> pass1;
                        cout << endl << "请再次输入";
                        cin >> pass2;
                    }
                }
            }
            else
            {
                pass1 = Unshow();
                cout << endl << "请再次输入:";
                pass2 = Unshow();
                //核对密码
                while (pass1 != pass2)
                {
                    cout << "两次所输入的密码不同，请再次尝试。" << endl;
                    cout << "请输入您的密码（六位密码）:";
                    pass1 = Unshow();
                    cout << "请再确认一次密码：";
                    pass2 = Unshow();
                    cout << endl;

                }
            }
            string Idten1, Idten2;//核对身份证
            while (1)
            {
                cout << "请输入您的身份证号(务必检查）："; cin >> Idten1;
                cout << "请再次输入一次："; cin >> Idten2;
                if (Idten1 != Idten2)
                {
                    cout << "两次输入的身份证信息不统一，请再次尝试：" << endl;
                    continue;
                }
                else
                {
                    break;
                }
            }
            User* a = new User;
            string putong = "普通用户";
            a->set_ID(aID); a->set_name(NAME); a->set_Password(pass1); a->set_Ident(Idten1); a->set_Type(putong), a->set_BookNumber(0);
            userlist.AddUser(a);
            cout << "成功注册！"; cout << endl;

            OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);
        }
        //忘记密码操作
        else if (n == 3)
        {
            string aID, NAME; string shenfenzhenghao;
            cout << "请输入您的ID："; cin >> aID;
            cout << endl << "请输入您的姓名："; cin >> NAME;
            cout << endl << "请输入您的身份证号："; cin >> shenfenzhenghao;
            if (ChangeCorrect(userlist, aID, NAME, shenfenzhenghao))
            {
                ChangePassword(userlist, aID);
                cout << "已将您的密码修改为666666（6个6)" << endl;

            }
            else
            {
                cout << "输入有误，请稍后尝试" << endl;

            }
            OutputFile(userlist, booklist, contentlist, user_number, book_number, news_number);

        }
        //退出程序
        else
        {
            break;
        }
    }
}