#include <armor.h>

inherit SURCOAT;
#include <ansi.h>
void create()
{
  set_name(HIC"天地无极"NOR, ({"zhitao"}));
  set_weight(4500);
  if( clonep() )
    set_default_object(__FILE__);
  else
  {
    set("long", "一件披风。\n");
    set("material", "leather");
    set("unit", "件");
    set("value", 700);
    set("armor_prop/armor", 60);
  }
  setup();
}
