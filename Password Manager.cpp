#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>

using namespace std;

string encrypt(string text)
{
    for(int i =0;i<text.length();i++)
    {
        text[i] = text[i] + 1;
    }
    return text;
}

string decrypt(string cypher)
{
    for(int i =0;i<cypher.length();i++)
    {
        cypher[i] = cypher[i] - 1;
    }
    return cypher;
}   


void saveCredentials(string account, string password)
{
    ofstream outFile;
    outFile.open("credentials.txt",ios::app);
    if(outFile.is_open())
    {
        outFile << account << " " << encrypt(password) << endl;
        outFile.close();
    }
    else
    {
        cout << "无法打开文件保存凭据！"<<endl;
    }
}

void viewCredentials()
{
    ifstream inFile;
    inFile.open("credentials.txt");
    if(inFile.is_open())
    {
        string account,password;
        while(inFile >> account >> password)
        {
            cout << account << " " << decrypt(password) << endl;
        }
        inFile.close();
    }
    else{
        cout << "无法打开文件查看凭据！"<<endl;
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    string masterPassword;
    ifstream checkMaster("master.txt");
    if(!checkMaster.is_open())
    {
        cout << "欢迎使用！检测到您是首次运行，请设置您的大师密码（主密码）: ";
        cin >>masterPassword;
        cout << "主密码设置成功！已自动解锁。" << endl;
        ofstream outMaster("master.txt");
        if(outMaster.is_open())
        {
            outMaster << masterPassword;
            outMaster.close();
        }
    }
    else
    {
        checkMaster >> masterPassword;
        checkMaster.close();
        string inputPassword;
        cout << "请输入主密码解锁: ";
        while(true)
        {
            cin >> inputPassword;
            if(inputPassword == masterPassword)
            {
                cout << "解锁成功" << endl;
                break;
            }
            else
            {
                cout << "解锁失败，请重新输入主密码。" << endl;
            }
        }
    }



    while(true)
    {
        cout << "\n=== 命令行密码管理器 ===" << endl;
        cout << "1. 添加新凭据" << endl;
        cout << "2. 查看所有凭据" << endl;
        cout << "3. 退出程序" << endl;
        cout << "请选择操作 (1-3): ";
        char choice;

        cin >> choice;
        switch(choice)
        {
            case '1':
            {
                string account,password;
                cout << "请输入账户名称: ";
                cin >> account;
                cout << "请输入密码: ";
                cin >> password;
                saveCredentials(account,password);
                cout << "密码已保存！" << endl;
                break;
            }
            case '2':
            {
                viewCredentials();
                break;
            }
            case '3':
            {
                cout << "感谢使用，再见！" << endl;
                return 0;
            }
            default:
            {
                cout << "选择无效，请重新输入" << endl;
            }
        }
    }
    return 0;
}
