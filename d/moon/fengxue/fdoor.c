// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//fdoor.c

#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short", "枫雪宫大门");
  set ("long", @LONG

＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
     
   一切都是短暂得没有结束却又要开始。
   一切又都是漫长得没有停止却也不会完成。
   为了发现这个世界上永恒的也许只有失去，发现失去后也
   只能挥挥手说声再见却永无聚首的瞬间，你便经常惶惑着
   感到一种突如其来的悲哀。
   任何道路的选择都只能意味着选择其他道路的不再可能。
   你终将孤独。
   
＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
LONG);
 set("exits", ([ /* sizeof() == 2 */
 "south" : __DIR__"fxtd",
 "enter" : __DIR__"living",
]));
//        set("objects",([/* sizeof()==1*/
//       __DIR__"npc/tree":1,
// ]));
  setup();
}
void init()
{
this_player()->set("env/brief",0);
}

