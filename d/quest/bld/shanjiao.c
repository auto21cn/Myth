//room

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","山脚");
        set ("long", @LONG

华山果然不是一般，站在山脚就能感觉到他的险要。向上看，山
石嶙峋，树木深深，比其五岳其他各山自有一番不同。
LONG);

        set("exits", 
        ([ //sizeof() == 2
                "west" : __DIR__"shanbian1",
             "southdown" : "/d/westway/jiayu",
                "east" : __DIR__"shanbian2",
                "north": __DIR__"shanlu1",
        ]));

        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

