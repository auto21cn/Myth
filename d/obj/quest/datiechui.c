//By waiwai@mszj 2000/12/02


inherit ITEM;
#include <task.h>
#include <ansi.h> 

void create()
{
        set_name(YEL "大号铁锤" NOR, ({"datie chui"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把打铁用的锤子。\n");
                set("unit", "碗");
            set("owner_name","张铁臂"); 
            set("owner_id","blacksmith"); 
        }
}


