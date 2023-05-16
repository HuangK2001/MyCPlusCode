#include "view.h"
#include<iostream>
#include<room.h>
using namespace std;
 void Romm_view::show_menu()
 {
     cout<<"1、显示客房信息 "<<endl;
     cout<<"2、设置客房状态 "<<endl;
     cout<<"3、删除客房信息 "<<endl;
     cout<<"4、添加客房信息 "<<endl;
     cout<<"0、退出客房信息 "<<endl;
 }

 void Romm_view:: Add_Room()
 {
     string name;
     int price;
     int bed_num;
     int area;
     cout << "请输入客房名称:"; cin >> name;
     cout << "请输入客房价格:"; cin >> price;
     cout << "请输入客房床数量:"; cin >> bed_num;
     cout << "请输入客房面积:"; cin >> area;
     Guest_Room room(name, price, bed_num,area,FREE);
     //调用客房管理模块的add_ room() 函数添加客房
     m_grm.add_room(room);
 }
void Romm_view::remove_data ()
{
 cout << "请输入您要删除的客房编号:";
 string room_number;
 cin >>room_number;
 //调用客房管理模块的remove_ data ()函数
 m_grm.remove_data(room_number) ;
}

void Romm_view::set_room()
{
    string number;
    cout << "请输入要设置的客房编号:";
    cin>>number;
    m_grm.set_room_state (number) ;
}

void Romm_view::show_all()
{
    cout<< "--------------------------------------------"<<endl;
    cout << "编号" << "\t  "<< "名称" << "\t\t" << "面积"<< "\t"
         << "价格"<< "\t" << "床位数量" << "\t" << "状态"<<endl;
    cout<<"------------------------------------------" << endl;
    Guest_Room grm;
    map<string, Guest_Room> rooms ;
    rooms=grm.read_data() ;
    if (rooms.empty())
    {
        cout<<"请添加客房信息后再进行操作! "<<endl;
    }
    for (auto& room:rooms)
    {
        cout<< room.second.get_num() << "\t"
            << room. second.get_name() << "\t"<< room. second.get_area ()
             << "平方\t" << room. second.get_price()<< "元\t "
             << room. second.get_bed_num() << "个\t\t"
             << room. second.show_state() << endl;
    }
    cout<<"-----------------------------------------------------"<<endl;
}

void Romm_view::run()
{
    bool state = true;
    while (state)
    {
        show_menu();
        int flag=-1;
        cout<<"请输入您的操作:";
        cin>>flag;
        system("cls");
        switch (flag)
        {
        case 1:
            show_all();
            break;
        case 2:
            set_room();
            break;
        case 3:
            remove_data();
            break;
        case 4:
            Add_Room();
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
}
