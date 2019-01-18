#include <room.h>
inherit HOCKSHOP;

void create()
{
        set("short", "当铺");
        set("long", @LONG
这是洛阳城里最大的一家当铺了，素来以买卖公平着称。门帘上绣了
个大大的“當“字，使人一目了然。当铺门口横摆着一个五尺来高的柜台，
将当铺内的一切当了个严严实实，上面摆着一个牌子 (paizi)。这里成了
那些手头不宽裕的人常来的地方。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "down" : __DIR__"cunchu",
                "east" : __DIR__"sroad1",
        ]));
        
  set("item_desc", ([ /* sizeof() == 1 */
  "paizi" : "
本当铺财力雄厚，童叟无欺，欢迎惠顾，绝对保密。
客官可以在这里：
    ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
    ＊  典当(pawn)              ＊
    ＊  卖断(sell)              ＊
    ＊  估价(value)             ＊
    ＊  赎回(retrieve stamp)    ＊
    ＊  购买(buy) 用list查看。  ＊
    ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
各种货物，铜钱、银两、黄金、银票一概通用。

"]));

        set("objects", ([
                __DIR__"npc/qi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
int clean_up()
{
      return 0;
}

