

#include <ansi.h>
inherit ROOM;
inherit "/d/9ct/qy/climbtree.c";

void create ()
{
  set ("short", HIW"天外神天"NOR);
  set ("long", @LONG

这里就是天外神天了，你身处一片云海之中，隐约中你看到了
一座华丽的宫殿，你定睛一看，原来是兰青阁，这是一处修身
养性的仙境，宫殿四周盛开着鲜花，小溪缓缓流过，令人着迷
这里住着三界中最令人羡慕的一对爱侣


LONG);

  set("exits", ([
//           "up" : __DIR__"tree1",
      ]));

  set("objects", ([
           "/d/wizz/junhyun/usr/lange.c" : 1,
           "/d/wizz/junhyun/usr/caiqing.c" : 1,
      ]));

  setup();
}

int do_climb(string arg)
{
        object tianshen; 
  object me=this_player();

  if( (!arg) || !((arg == "sky") || (arg == "天外天")))
    return notify_fail("登什么？\n");
  if (me->is_busy()) return notify_fail("你现在正忙着呢。");
  if( me->query("kee") < (int)(me->query("max_kee")/3)){
    me->receive_damage("kee",(int)me->query("max_kee")*20/100);
    return notify_fail("你身子发虚，一头栽了下来，哎呀！\n");
}
  else
    {
      if ((int)me->query_skill("dodge", 1)<60 && (int)me->query_skill("moondance", 1) < 200)
        {
          message_vision("$N小心翼翼的往上攀登了一点，觉得头晕眼花，就赶紧爬了下来．\n", me);
          me->improve_skill("dodge", 60-me->query("str"));
          tell_object(me, "你领悟出一些基本轻功方面的窍门。\n");
        }
      else
        {
          message_vision("$N轻轻地一跃好似踩着无形的阶梯,一会便消失在云海之中。。\n", me);
                   me->move(__DIR__"tian1.c");
        }
    }
  me->receive_damage("kee", (int)me->query("max_kee")*10/100);
  return 1;
}

int valid_leave(object me, string dir)
{
        object a;
   if (dir == "up" ) {
                if(objectp(a=present("tianshen", environment(me))) &&
living(a) )
        return notify_fail("天神拦住你说道:天外神天的一些禁地请不要前去。\n");
        }   
        return ::valid_leave(me, dir);
}

