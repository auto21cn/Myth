//room

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","屋外");
        set ("long", @LONG

这里是白须老者练功的地方。白须老者没事就喜欢踢踢腿，打打
拳，一般来说都是在这儿。
LONG);

        set("exits", 
        ([ //sizeof() == 2
            //    "north" : __DIR__"xuanya",
                "west" : __DIR__"wunei",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                "/d/quest/bld/npc/laozhe" : 1,
        ]));


        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

