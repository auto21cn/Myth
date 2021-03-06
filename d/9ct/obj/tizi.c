// 木提子 by Calvin

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_give","这么珍贵的药，哪能随便给人？\n");
    set("no_put","木提子化成一滴清水,而后消失了。\n");
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}

void create()
{
  set_name(CYN "木提子" NOR , ({"mu tizi", "tizi","mutizi"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "颗");
    set("long", "这是楼兰天特有的珍稀药材。\n");
    set("value", 0);
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="mu tizi" && arg!="tizi")   return 0;
  
  me->add("max_force",(random(5)+9));
  message_vision(HIG "$N轻轻地将一颗木提子送入嘴中，一时间全身被一道蓝绿色光笼罩。\n" NOR, me);
  destruct(this_object());
  return 1;
}

