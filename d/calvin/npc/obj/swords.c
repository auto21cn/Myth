#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
    set_name( HIW "回眸一笑" NOR, ({ "sword" }) );
    set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100000);
//              set("no_drop", "1");
                set("material", "iron");
                set("long", "这把神剑是懿馨的法宝，她用此剑斩杀了无数妖魔。\n");
                set("wield_msg","$N微微一笑，$n已在$N手中，周围之人都羡慕不已。\n");
                set("unwield_msg", "$N将$n插回腰间，温柔的笑声依然不减。\n");
                                set("no_sell",1);
                                set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");
                }
        init_sword(150);
        setup();
}
