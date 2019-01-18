// 巧克力 by Cigar

#include <ansi.h>

inherit ITEM;

void create()
{
  set_name(HIW"德芙巧克力"+HIG"太妃糖"NOR , ({"qiaoke li", "taifei tang","tang"}));
  set_weight(120);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "块");
    set("long", HIB"浓浓的巧克力味道，甜甜的香草味道，你再看，我就吃掉你。\n"NOR);
    set("value", 0);
    set("no_sell", 1);
    set("drug_type", "补品");
  }
  setup();
  call_out ("becoming_old",1800);
}
void becoming_old ()
{
  object me = this_object();
  object where = environment (me);
  object dan = new (__DIR__"dou");

  dan->move(where);
  destruct (me);
}

void init()
{
  add_action("do_eat", "eat");
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="qiaoke li" && arg!="tang") 
    return 0;
  
  me->set("food", (int)me->max_food_capacity()*20+random(100));
  me->set("water", (int)me->max_water_capacity()*20+random(100));
   message_vision(HIM "$N美美的吃下一块"+HIW"德芙巧克力"+HIG"太妃糖"+HIM"好香甜啊，这种滋味  好像初恋的感觉，甜甜的、浓浓的，也不知何时，天长地久似乎已变的苍白无力，海枯石烂美丽却是虚无，爱之深，情之切，曾经海誓山盟，曾经天荒地老，我的心只为你而跳跃...\n" NOR, me);
  tell_object(me, HIY"但我仍然向往着那童话般的结局… …爱你到天荒地老。\n");
  destruct(this_object());
  return 1;
}
