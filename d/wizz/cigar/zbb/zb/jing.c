// 护心镜 by Calvin

#include <ansi.h>
#include <armor.h>

inherit WAIST;

string *names = ({
  HIW"护心镜"NOR,
  HIW"护心镜"NOR,
});

string *ids = ({
  "huxin jing",
  "huxin jing",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i], "huxin jing", "jing", "huxin"}));
  set_weight(5000);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "件");
             set("value", 0);
   set("material", "metal");
//   set("armor_prop/armor", 14);
   set("armor_prop/armor", 20);
   set("armor_prop/dodge", -5);
  }
  setup();
}
