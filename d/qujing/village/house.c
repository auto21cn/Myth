//Cracked by Roath
//  妖神之争 １。０
//  by happ@YSZZ 2000.4.7
//  /d/qujing/village/road1.c

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "客厅");
  set ("long", @LONG

帘栊高控，屏门上，挂一轴寿山福海的横批画，正中间放着一个
古铜兽炉。两边金漆柱上，贴着一副大红纸的春联，上书：
[32m
        丝飘弱柳平桥晚，雪点香梅小院春。

[m
LONG);
  set("exits", ([
        "west"  : __DIR__"kitchen",
         "east" : __DIR__"born",
         "south": __DIR__"inroom",
         "out": __DIR__"road4",
          ]));
  set("objects", ([
        __DIR__"npc/oldwoman":1,
        ]));
/*
// 这个地方先设置成no_fight
// 如果谁要改回去，请先在wiz_room post
// 我也不知道改成no_fight有没有影响　
// 但如果不改，可以用来躲pk
// 暂时我没搞清楚这儿是做什么用的
// 所以先这样　:)
// mudring Dec/08/2002
set("no_fight",1);
*/
// 终于有好办法处理了.
// mudring Dec/10/2002
set("no_pk",1);
  setup();
}

void init()
{
        add_action("do_none","perform");
        add_action("do_none","cast");
        add_action("do_none","kill");
        add_action("do_none","steal");
        add_action("do_none","ji");
}

int do_none()
{
        object ob = this_object();

        tell_object(ob,HIC"老妈妈慈祥的看着你。\n"NOR);
        return 1;
}
