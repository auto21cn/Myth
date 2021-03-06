// Created by aeddy@2003/05/05

#include <armor.h>

inherit FLOWER;

void create ()
{
	set_name(HIW "雨花" NOR, ({ "rain flower", "rain", "flower" }));
	set_weight(100);
	set("long",WHT"一朵雨落在地上开的花，晶莹剔透，像一滴眼泪，留在心里。。。\n"NOR);
	set("unit", "朵");
	set("value", 1);
	set("female_only", 1);
	set("no_break", 1);
	set("armor_type", "flower");
	set("material", "flower");
	set("Fmaterial", "wood");
	set("no_sell", "这么美丽的雨花你也要换钱吗？\n");
	set("no_drop", "仍掉了雨花，就象仍掉了一个梦想，还是好好珍惜它吧。\n");
	set("no_give", "送掉了雨花就是忘记了那曾经绽放在心里的雨朵之花。\n");
	set("no_get", "大自然是雨花的摇篮，不要私藏使它枯竭。\n");
	set("no_put", "雨花需要绽放在你的眼里，不要私藏使它枯竭。\n");
	set("armor_prop/armor", 10);
	set("armor_prop/personality", 10);
	set("unequip_msg","$N将晶莹的"+query("name")+"轻轻地放在手心……。\n");
	set("wear_msg", "$N将一朵晶莹的"+query("name")+"戴在胸前，晶莹剔透中映出了$P那美丽的身影。\n" );
	setup();
}
