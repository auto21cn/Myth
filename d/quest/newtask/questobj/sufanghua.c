#include <ansi.h>
inherit ITEM;
void create()
{
    set_name("苏坊花", ({ "sufang hua" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "只");
            set("long", "一只苏坊花\n");
          }

    setup();
}
