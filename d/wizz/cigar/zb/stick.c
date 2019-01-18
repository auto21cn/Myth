// 灵佛棒 by Calvin

#include <weapon.h>
#include <ansi.h>

inherit STICK;

void create()
{
        set_name(HIY"灵佛棒"NOR, ({"lingfo stick", "bang","stick"}));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
		set("no_sell", 1);
                set("long", "世间凡尘造就的灵佛棒,金黄色的体肤闪闪发光。\n");
                set("value", 200000);
                set("no_sell", "这种罕见的神兵可不是随便可以买卖的!\n");
                set("material", "steel");
                set("no_give", 1);
                set("no_get", 1);
                set("no_give", 1);
                set("no_put", 1);
                set("no_drop", 1);
                set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");
        }
  init_stick(200);
        setup();
}

