// zhui.c 天魔锥

#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	int success_adj, damage_adj;

	success_adj = 100;
	damage_adj = 100;

	if( !target ) target = offensive_target(me);

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("你要对谁施展「天魔锥」？\n");

	if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("sen") < 50 )
		return notify_fail("你无法集中精力瞄准！\n");

	me->add("mana", -25-2*(int)me->query("mana_factor"));
		me->receive_damage("sen", 10);

	if( random(me->query("max_mana")) < 50 ) {
		write("你真气一窒，发不出这招！\n");
		return 1;
	}

	SPELL_D->attacking_cast(
		me, 
		target, 
		success_adj, 	
		damage_adj, 	
		"both", 		
		HIC "$N"NOR+HIC"口中念了几句咒文，以双手做武器，全身高速旋转，向着$n"NOR+HIC"飞钻过去。\n" NOR,
		HIC "结果$N"NOR+HIC"从$n"NOR+HIC"身上透体而过，顿时血花飞溅！\n" NOR, 
		HIC "只见$n"NOR+HIC"轻轻一跳，$N"NOR+HIC"正好插在$n"NOR+HIC"脚边，四周飞砂走石！\n" NOR, 
        	HIC "但是$n"NOR+HIC"以法力一拨，$N"NOR+HIC"身形一窒！\n" NOR,
		HIC "结果$n"NOR+HIC"内力逆转，血气倒流，张口吐出一大口鲜血！\n" NOR
	);

	me->start_busy(1+random(2));
	return 3+random(5);
}

