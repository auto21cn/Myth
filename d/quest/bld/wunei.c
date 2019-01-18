//room

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","屋内");
        set ("long", @LONG

这里是白须老者住的地方，房间布置的还不错，挺简朴的。靠近
西边放了一张床，南边开了窗，晴天坐在窗下，晒晒阳光还挺舒
服的。
LONG);

        set("exits", 
        ([ //sizeof() == 1
                "east" : __DIR__"wuwai",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));


        set("no_clean_up", 0);
        set("no_fight", 1);
        set("light_up", 1);
        set("no_magic", 1);
        set("sleep_room", 1);

        setup();
        replace_program(ROOM);
}

