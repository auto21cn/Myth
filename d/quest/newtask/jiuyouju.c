// Room: /d/quest/newtask/jiuyouju
//created by kuku@sjsh 2002/11

inherit ROOM;
#include <room.h>

void create ()
{
          set ("short", "九幽居");
          set ("long", @LONG

这里是九幽异人隐居的地方，房间虽小，
却是异常干净整洁。

LONG);

          set("objects", ([ /* sizeof() == 1 */
                  __DIR__"npc/jiuyou" : 1,
          ]));
          set("exits", ([ /* sizeof() == 2 */
                  "north" : "/d/changan/wside2",
          ]));

          create_door("north", "红木门", "south", DOOR_CLOSED);
          setup();
}
