//sea.c player装备
//by junhyun@SK

#include <armor.h>
#include <ansi.h>

inherit SHIELD;


void create()
{
        set_name(HIW"天之光"NOR, ({ "godarmor", "armor" }) );
        set("long", "散发着天之光辉的盾牌。\n");
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("material", "cloth");
                set("armor_prop/armor", 20);
                set("armor_prop/spells", 50);
                set("armor_prop/dodge", 20);
                set("value", 50000);
        }
        setup();
}

