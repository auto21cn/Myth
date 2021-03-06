//edited by dewbaby@sjsh

#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int kee_wound, damagea;
	        
	if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「万铃魔音」？\n");

        if(!me->is_fighting())
                return notify_fail("「万铃魔音」只能在战斗中使用！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");
        if (!PFM_D->valid_family(me, "盘丝洞"))
                return notify_fail("“万铃魔音”只有盘丝洞门人才可以用！\n");
        if((int)me->query("kee") < 300 )
                return notify_fail("你的气血不足，没法子施用外功！\n");

        if((int)me->query_skill("yinsuo-jinling", 1) < 450)
                return notify_fail("你的银索金铃级别还不够，使用这一招会有困难！\n");
        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("你现在无法使用「万铃魔音」来攻击。\n");
	if(random((int)me->qurey("PKS")) >5 )
                 return notify_fail("你充满邪恶之气，驱动不了至灵的银索。\n");
/*
         if(random(100) > (int)me->query("kar"))
                 return notify_fail("你银索金铃不听你的使唤了。\n");     
*/
	me->delete("env/brief_message");

        message_vision(HIC"\n$N运足精神，内力行走了大小周天，幽然媚笑一声“"HIR"万铃魔音"NOR+HIC"”！顿时间天昏地暗，电闪雷鸣，地动天摇！\n"NOR, me);

        target->start_busy(2);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        
        kee_wound = me->query("eff_kee")/(4+random(5));
	me->receive_damage("kee", 50);
	target->add("kee", -kee_wound);	
	target->add("eff_kee", -(kee_wound));
        damagea=((int)me->query_skill("yinsuo-jinling")); 
        if(random((int)target->query("combat_exp")) < (int)me->query("combat_exp")) 
        {
        
                target->receive_damage("kee",damagea,me,"pfm");
                target->receive_wound("kee",damagea/2,me,"pfm");
                target->receive_damage("sen",damagea,me,"pfm");
                target->receive_wound("sen",damagea/2,me,"pfm"); 
                target->start_busy(3);
        }
	me->add("force", -100);
	message_vision(HIW"$n被万铃齐鸣的魔音搅心神不定，七窍五俯震坏了，翻倒在地。\n"NOR,me, target);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(1+random(1));
	return 1;
}
