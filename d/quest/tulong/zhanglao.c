inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "长老室");
        set("long",HIG @LONG 
这是精灵长老所在的房间，一个白胡子的精灵族老人正坐在窗
前沉思着什么。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
        "west" : "/d/quest/tulong/village",     "southeast" : "/d/quest/tulong/xiuxishi",     ]));

        setup();
        replace_program(ROOM);

}


