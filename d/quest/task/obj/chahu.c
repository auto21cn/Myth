//By waiwai@mszj 2000/12/02

#include <ansi.h>
inherit ITEM;
#include <task.h>
void create()
{
        set_name(HIB"茶壶", ({"cha hu"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把专门沏茶用的茶壶。\n");
                set("unit", "把");
                 set("owner_name","黄汤");
                set("owner_id","huang tang");
        }
}

