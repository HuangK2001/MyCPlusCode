#ifndef GUEST_ROOM_H
#define GUEST_ROOM_H
#pragma once
#include <string>
#include <map>
using namespace std;
enum ROOM_STATE { FREE=0, CHECK_IN };

class Guest_Room
{
public:
    Guest_Room() =default;
    Guest_Room(string, int, int, int, ROOM_STATE) ;
    string generate_number() ;
    string show_state();
    bool save_data (map<string, Guest_Room>&) ;
    map<string, Guest_Room> read_data();
public:
    string get_num() ;
    string get_name() ;
    int get_price() ;
    int get_area();
    int get_bed_num() ;
    void set_state();
    private:
    string m_number;
    int m_price;
    int m_area;
    int m_bed_number;
    string m_name;
    enum ROOM_STATE m_state;

};
#endif // GUEST_ROOM_H
