//zhaoyaojian.c
#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
    set_name( HIW "还阳丹" NOR, ({ "wawasword", "jian"}) );
    set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100000);
                set("material", "iron");
                set("long", "一粒还阳丹，据说有起死回生之效。\n");
                set("wield_msg","随着一声清啸，还阳丹已跃入$N的手中。\n");
                set("unwield_msg", "隐隐寒光渐渐散去，还阳丹轻灵的跃回剑鞘。\n");
                                set("no_sell","你真厉害，敢买娃娃的宝剑？嘿嘿……你完蛋了。\n");
                                set("no_drop","你要是把娃娃的宝剑扔了，你的小命也就没了。\n");
                                set("no_give","不是吧？着你也敢送人？你真是不要命了。\n");
                }
        init_sword(120);
        setup();
}

