#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"四级通行证"NOR, ({ "passport IV","passport" }) ); 
        set_weight(100);
                set("unit", "张");
                set("material", "paper");
                set("pass_level",4);
                set("long", "这是一张进入魔幻世界探险的通行证。\n");
        setup();
}
