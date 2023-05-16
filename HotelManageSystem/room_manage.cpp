#include "room_manage.h"
#include <room.h>
#include<iostream>
using namespace std;

Room_Manager::Room_Manager ()
{
    Guest_Room().read_data();
}

bool Room_Manager::check_in(const string number)
{
     Guest_Room grm;
    m_room_list = grm.read_data();
    if (m_room_list.find(number) == m_room_list.end())
    {
        return false;
        return true;
    }
}
void Room_Manager::add_room( Guest_Room room)
{
    if (check_in (room.get_num()))
    {
        cout << "房间已存在"<<endl;
    return;
    }

m_room_list.insert(make_pair(room.get_num(), room));
Guest_Room().save_data(m_room_list);
}
bool Room_Manager::remove_data(const string number)
{
    if (!check_in(number))
    {
        cout << "房间不存在"<< endl;
        return  false;
    }

    m_room_list = Guest_Room().read_data() ;
    m_room_list.erase(number) ;
    Guest_Room().save_data(m_room_list) ;
    return true;
    Guest_Room().save_data(m_room_list);
    return true;
}

void Room_Manager::set_room_state(string number)
{
    if (!check_in (number))
    {
        cout << "房间不存在" << endl;
        return;
    }
    else
    {
        m_room_list = Guest_Room().read_data() ;
        m_room_list[number].set_state() ;
        Guest_Room().save_data(m_room_list);
    }
}
