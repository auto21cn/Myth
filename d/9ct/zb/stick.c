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
              set("value", 8000); 
                set("material", "steel");
                set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");
        }
   init_stick(110);
        setup();
}

