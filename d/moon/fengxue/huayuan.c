//edit by xuanzi
inherit ROOM;
#include <ansi.h>

void create()
{
  set("short",HIG"花园"NOR);
  set("long",@LONG

这里是一个美丽的花园，里面有许多许多很漂亮的花，争奇斗艳，花色
独特，似乎不是凡间所有。

LONG);

 set("outdoors",__DIR__);
 set("exits",([
   "south":__DIR__"wytdamen",
   ]));

  setup();
}
void init()
{
  add_action("do_fl","zhong");
}

int do_fl(string arg)
{
  object me = this_player();
if (!arg||(string)arg!="flower") return notify_fail("什么？\n");
if ((int)me->query("kee")<100)
return notify_fail("你太累了，还是先休息一下吧！\n");
if (me->is_busy())
return notify_fail("你正忙着呢！\n");
  
  message_vision("$N拿起一把小锄头，仔细地挖一个坑，放一粒花籽进去！\n",me);
me->add("kee",-50);
me->start_busy(8);
  remove_call_out("finish");
  call_out("finish",5,me);
  return 1;
}

void finish(object me)
{
  object flower;
if (random(2)) message_vision("\n你浇水不及，结果花没有开。\n",me);
else {
flower = new("/d/obj/flower/rose999");
 message_vision("\n一阵风吹来，花开了，"+flower->name()+"在风中摇曳，好漂亮啊。\n",me);
  flower->move(me);
}
}

