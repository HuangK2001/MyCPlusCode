#include "view.h"
#include<iostream>
#include<room.h>
using namespace std;
 void Romm_view::show_menu()
 {
     cout<<"1����ʾ�ͷ���Ϣ "<<endl;
     cout<<"2�����ÿͷ�״̬ "<<endl;
     cout<<"3��ɾ���ͷ���Ϣ "<<endl;
     cout<<"4����ӿͷ���Ϣ "<<endl;
     cout<<"0���˳��ͷ���Ϣ "<<endl;
 }

 void Romm_view:: Add_Room()
 {
     string name;
     int price;
     int bed_num;
     int area;
     cout << "������ͷ�����:"; cin >> name;
     cout << "������ͷ��۸�:"; cin >> price;
     cout << "������ͷ�������:"; cin >> bed_num;
     cout << "������ͷ����:"; cin >> area;
     Guest_Room room(name, price, bed_num,area,FREE);
     //���ÿͷ�����ģ���add_ room() ������ӿͷ�
     m_grm.add_room(room);
 }
void Romm_view::remove_data ()
{
 cout << "��������Ҫɾ���Ŀͷ����:";
 string room_number;
 cin >>room_number;
 //���ÿͷ�����ģ���remove_ data ()����
 m_grm.remove_data(room_number) ;
}

void Romm_view::set_room()
{
    string number;
    cout << "������Ҫ���õĿͷ����:";
    cin>>number;
    m_grm.set_room_state (number) ;
}

void Romm_view::show_all()
{
    cout<< "--------------------------------------------"<<endl;
    cout << "���" << "\t  "<< "����" << "\t\t" << "���"<< "\t"
         << "�۸�"<< "\t" << "��λ����" << "\t" << "״̬"<<endl;
    cout<<"------------------------------------------" << endl;
    Guest_Room grm;
    map<string, Guest_Room> rooms ;
    rooms=grm.read_data() ;
    if (rooms.empty())
    {
        cout<<"����ӿͷ���Ϣ���ٽ��в���! "<<endl;
    }
    for (auto& room:rooms)
    {
        cout<< room.second.get_num() << "\t"
            << room. second.get_name() << "\t"<< room. second.get_area ()
             << "ƽ��\t" << room. second.get_price()<< "Ԫ\t "
             << room. second.get_bed_num() << "��\t\t"
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
        cout<<"���������Ĳ���:";
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
