//By waiwai@mszj 2000/12/02

inherit ITEM;

#include <ansi.h>
#include <task.h>

void create()
{
        set_name("铁扇", ({"tie shan"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把大铁扇，法力无穷。\n");
                set("unit", "把");
              set("owner_name","铁扇公主");
               set("owner_id","tieshan gongzhu");
        }
}

