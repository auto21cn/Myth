// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit F_AUTOLOAD; 
inherit ITEM;

void create()
{
  set_name(HIG "碧玉萧" NOR, ({ "biyu xiao","xiao"}));
  set_weight(100);
  set("long",HIG"这是小蔓用碧玉雕出的长萧，萧的一头还垂着一对白玉的蝴蝶。\n" NOR );
  set("unit", "根");
  setup();
}

init ()
{
  add_action ("do_play", "chui");
}

int do_play (string arg)
{
  object me = this_player();
  object qin = this_object();
  string *msgs = ({
    HIY"$N把萧在唇边轻轻吹了一声，立刻清亮的萧声穿云而去，远远似乎有人在和道：
        待月西厢下，迎风户半开。
        隔墙花影动，疑是玉人来……

\n" NOR ,
    HIR"$N低低地吹了几曲，突然异峰突起，却是一曲《凤求凰》：

    凤兮凤兮归故乡，游遨四海求其皇，有一艳女在此堂，室迩人遐毒我肠，何由交接为鸳鸯
    凤兮凤兮从皇栖，得讬子尾永为妃。交情通体必和谐，中夜相从别有谁。

\n" NOR ,
    HIM"$N纤长的手指象跳舞一样地在箫上点着，一颗泪珠从脸颊上滑落，这正是：
        
        美人掷珠帘，深坐颦娥眉。
        但见泪痕湿，不知心恨谁……

\n" NOR ,
    HIG"$N微微皱了皱眉，幽怨地望着远方，却是吹了一曲又一曲：

        可怜青铜镜，挂在白玉堂。
        玉堂有美女，娇弄明月光。
        罗袖拂金鹊，彩屏点红妆。
        妆罢含情坐，春风桃李香……

\n" NOR ,
    HIW"$N道了声“春”，微微一笑，箫声欢快而清亮：

        一对紫燕儿雕梁上肩相并， 一对粉蝶儿花丛上偏相趁，
        一对鸳鸯儿水面上相交颈， 一对虎猫儿绣凳上相偎定。
        觑了动人情， 不由人心儿硬， 冷清清偏俺合孤零……

\n" NOR ,
  });

  if (arg != "xiao")
  {
    tell_object (me,"吹什么好呢呢？\n");
    return 1;
  }

  message_vision (msgs[random(sizeof(msgs))],me);
  return 1;
}

int query_autoload() { return 1; }
