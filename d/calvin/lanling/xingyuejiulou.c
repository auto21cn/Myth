#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "星月酒楼");
  set ("long", @LONG

这是兰陵出了名的老酒楼了,这里的酒香飘百里
店里的生意好的实在是没得说了.店中共有桌椅
五百一十九坐,伙计3名...酒楼里的酒据说是从
老远的比丘国运来的 ... ...
LONG);

  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
    "east" : "/d/calvin/lanling/jie8",
]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

  setup();
}
