#include <ansi.h>
inherit ITEM;
void create()
{
    set_name("护花铃", ({ "huhua" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "个");
            set("material", "steel");
            set("long", "一个小铃铛\n");
          }

    setup();
}
