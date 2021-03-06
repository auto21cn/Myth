inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "浴缸");
  set ("long", HIR@LONG

    一股热气腾腾的白雾将你团团围住，你几乎在浴缸里睡着了。鲜花漂浮
在葡萄酒色的浴液中，几股强劲的水流按摩着你白皙的皮肤。
    你简直陶醉的不愿意出来了。
    窗外是星空闪烁的美景。
LONG NOR);

  set("exits", ([
        "up"     : __DIR__"woshi",
      ]));
  set("objects", ([ /* sizeof() == 1 */
     //  __DIR__"npc/girl" : 2,
      ]));
  set("resource", ([ /* sizeof() == 1 */
    "spring" : 1,
      ]));

  set("outdoors", __DIR__);

  setup();
}

int init ()
{
  add_action ("do_bath","bath");
  add_action ("do_cure","cure");
  return 1;
}

int do_bath (string arg)
{
  string *msgs = ({
    "$N在浴水中洗了起来。\n",
    "$N用浴水洗了洗自己。\n",
    "$N在浴水中热气腾腾地洗了起来。\n",
    "$N用热热的浴水洗了洗自己。\n",
  });
  string *actions = ({
    "你感觉到浴水有一种说不出来的的神力。\n",
    "你仿佛觉得浴水有一种神秘的法力慢慢渗进你的体内。\n",
    "你似乎感觉到有一种神力渗进体内。\n",
    "你恍惚觉得有一种神秘的法力将你笼罩。\n",
    "似乎有一种神秘的法力渗进你的体内。\n",
  });
  object me = this_player();

  if (me->query("kee")<10 ||
      me->query("sen")<10)
  {
    tell_object (me,"你太虚弱了，洗热水浴有危险！\n");
    me->unconcious();
    return 1;
  }
  if (me->is_busy())
    return notify_fail ("你正在浴缸中忙着呢！\n");
  message_vision (msgs[random(sizeof(msgs))],me);
  me->add("kee",-10);
  me->add("sen",-10);
  me->improve_skill("spells",1+random(3),1);
  tell_object (me,actions[random(sizeof(actions))]);
  me->start_busy(1,1);
  return 1;
}

int do_cure (string arg)
{
  string *msgs = ({
    "$N捧起浴水往身上慢慢地浇下来。\n",
    "$N用浴巾使劲地往自己身上搓着。\n",
    "$N舀起热热的浴水，往身上浇下来。\n",
    "$N躺在庞大的浴缸中，泡着自己的身体。\n",
    "$N坐进热气腾腾的浴缸。\n",
    "$N泡在浴缸中，慢慢地坐浴。\n",
  });
  object me = this_player();

  if (me->is_busy())
    return notify_fail ("你正在浴缸中忙着呢！\n");
  message_vision (msgs[random(sizeof(msgs))],me);
  me->start_busy(1,1);
  if ((me->query("kar")+me->query_temp("spring/cure_times")) > 60)
  {
    if (! me->update_condition())
      return 1;
    message_vision ("$N红光满面地站了起来，坐在了浴缸沿上。\n",me);
    me->clear_condition();
    me->unconcious();
  }
  me->add_temp("spring/cure_times",1);
  return 1;
}

int valid_leave(object me, string dir)
{
  me->delete_temp("spring/cure_times",1);
  return ::valid_leave(me, dir);
}

