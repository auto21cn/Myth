//By waiwai@mszj 2000/12/02

inherit ITEM;

#include <ansi.h>
#include <task.h>

void create()
{
        set_name(HIW"佛宝舍利子"NOR, ({"tooth"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一颗淡黄色的珠子，象有种神奇的力量孕育其中。\n");
                set("unit", "颗");
               set("owner_name","祭赛国国王");
               set("owner_id","jisai guowang");
        }
}
