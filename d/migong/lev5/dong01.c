
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", BLU"ɽ��"NOR);
        set("long", BLU @LONG
 ��Խ��Խ���Χ��ǽ���ƺ���Щ�����ˡ� 
LONG NOR);
        set("exits", ([
                "east" : __DIR__"dong"+(random(20)+1),
                "south" : __DIR__"dong"+(random(15)+1),
                "west" : __DIR__"dong"+(random(10)+1),
                "north" : __DIR__"dong"+(random(5)+1),
        ]));
        set("objects", ([
              "/d/migong/box/gbox" : random(2),
         ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
