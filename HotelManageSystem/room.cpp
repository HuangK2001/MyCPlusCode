#include "room.h"
#define _CRTT SECURE NO WARNINGS
#include<time.h>
#include<iostream>
#include<fstream>
const char* const room_data_file = "room.dat";
Guest_Room::Guest_Room(string name, int price,int bed_num,int area,ROOM_STATE state=FREE)
{
        this->m_name = name ;
        this->m_price = price;
        this->m_bed_number = bed_num;
        this->m_area = area;
        this->m_number = generate_number () ;
        this->m_state = state;
}

string Guest_Room::generate_number ()
{
    time_t my_time = time (NULL) ;
    struct tm*my_tm = localtime (&my_time) ;
    char tim_buffer[128]={0};
    sprintf(tim_buffer, "%d%d", my_tm->tm_yday, my_tm->tm_sec);
    int rand_num = rand()%50;
    char buf[128] = { 0 } ;
    sprintf (buf, "%d",rand_num) ;
    return string(tim_buffer) + string (buf);
}

string Guest_Room::show_state ()
{
    if (m_state == FREE)
        return "¿ÕÏÐ";
    if (m_state == CHECK_IN)
        return "Èë×¡";
}

bool Guest_Room::save_data (map<string, Guest_Room>& room_list)
{
    ofstream ofs (room_data_file, ios::out);
    if(!ofs)
    {
        return false;
    }

    for (auto& room : room_list)
    {
        size_t name_len = room.second.m_name.size();
        ofs.write(reinterpret_cast<const char*>(&name_len),sizeof (size_t));
        ofs.write(room.second.m_name.c_str(),name_len);
        ofs.write (reinterpret_cast<const char*> (&room.second.m_price),sizeof (int)) ;
        ofs.write (reinterpret_cast<const char*> (&room.second.m_area),sizeof (int));
        ofs.write (reinterpret_cast<const char*>(&room. second.m_bed_number),sizeof (int));
        ofs.write (reinterpret_cast<const char*> (&room.second.m_state) ,sizeof(enum ROOM_STATE));
        size_t number_len = room. second.m_number.size();
        ofs.write (reinterpret_cast<const char*> (&number_len), sizeof(size_t));
        ofs.write(room.second.m_number.c_str(),number_len);
    }
    ofs.close();
    return true;
}

map<string,Guest_Room> Guest_Room::read_data()
{
    map<string,Guest_Room> room_list;
    ifstream ifs(room_data_file, ios::in);
    if(!ifs)
    {
        return room_list;
    }
    while (ifs.peek() != EOF)
    {
        Guest_Room room;
        size_t name_1en = 0;
        ifs.read(reinterpret_cast<char*>(&name_1en),sizeof(size_t));
        char name_buffer[128] = { 0 };
        ifs.read(name_buffer,name_1en) ;
        room.m_name = name_buffer;
        ifs.read(reinterpret_cast<char*> (&room.m_price) ,sizeof(int)) ;
        ifs.read(reinterpret_cast<char*> (&room.m_area) ,sizeof(int)) ;
        ifs.read(reinterpret_cast<char*> (&room.m_area) ,sizeof (int));
        ifs. read (reinterpret_cast<char*> (&room.m_bed_number) ,
                   sizeof (int));
        ifs. read (reinterpret_cast<char*> (&room.m_state) ,
                   sizeof(enum ROOM_STATE)) ;
        size_t number_len = 0;
        ifs.read (reinterpret_cast<char*> (&number_len) ,sizeof(size_t));
        char number_buffer[128] = { 0 };
        ifs. read (number_buffer, number_len) ;
        room.m_number = number_buffer;
        room_list. insert (make_pair (room.m_number,room));
    }
    ifs.close();
    return room_list;
}

string Guest_Room::get_num()
{
    return m_number;
}

 void Guest_Room::set_state()
{
    m_state=CHECK_IN;
}

string Guest_Room::get_name()
{
    return m_name;
}

int Guest_Room::get_price()
{
    return m_price;
}

int Guest_Room::get_area()
{
    return m_area;
}

int Guest_Room::get_bed_num()
{
    return m_bed_number;
}
