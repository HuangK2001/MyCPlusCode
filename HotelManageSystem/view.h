#ifndef ROMM_VIEW_H
#define ROMM_VIEW_H
#include<room_manage.h>

class Romm_view
{
public:
    void show_menu();
    void Add_Room();
    void remove_data();
    void set_room();
    void show_all();
    void run();
private:
    Room_Manager m_grm;


};

#endif // ROMM_VIEW_H
