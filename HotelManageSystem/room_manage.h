#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H
#include<room.h>
#include<map>
#include<string>
class Room_Manager
{
public:
    Room_Manager();
    bool check_in(const string);
    void add_room(const Guest_Room room);
    bool remove_data (const string);
    void set_room_state (string number);

private:
    map<string, Guest_Room> m_room_list;
};

#endif // ROOM_MANAGER_H
