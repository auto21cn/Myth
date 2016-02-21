// kanjian.c
//lizuole 99.12.13

#include <armor.h>
#include <ansi.h>

inherit WAIST;

void create()
{
	set_name(HIM "坎肩" NOR, ({ "coat","kanjian" }) );
	set_weight(1500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "\n这是雪儿的胸甲。粉红色的小坎肩上绣着几只鸳鸯，闻起来还有一股淡香。\n");
		set("unit", "件");
		set("value", 5000);
		set("material", "丝");
		set("armor_prop/armor", 3);
		set("armor_prop/personality", 3);
		set("female_only", 1);
		set("no_sell", "这个东西不能卖。\n");
	}
	setup();
}

