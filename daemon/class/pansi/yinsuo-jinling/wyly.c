//modified by longer

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,j;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「五韵连音」？\n");

        if(!me->is_fighting())
                return notify_fail("「五韵连音」只能在战斗中使用！\n");

        if((int)me->query("force") < 100 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("kee") < 100 )
                return notify_fail("你的气血不足，没法子施用外功！\n");

        if((int)me->query_skill("yinsuo-jinling", 1) < 150)
                return notify_fail("你的银索金铃级别还不够，无法领会五韵精髓！\n");

               weapon=me->query_temp("weapon");

        if( me->query("env/brief_message") ){
                i=1;
        } else {
                i=0;
        }
        if( target->query("env/brief_message") ){
                j=1;
        } else {
                j=0;
        }

        me->delete("env/brief_message");
        target->delete("env/brief_message");

        message_vision(HIY"$N双手急速挥舞银索金铃，竟发出隐藏着宇宙最神奇力量的五韵之声,
☆宫☆\n"NOR, me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        message_vision(HIW"☆商☆\n"NOR, me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        message_vision(HIR"☆角☆\n"NOR, me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        message_vision(HIB"☆徵☆\n"NOR, me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        
        message_vision(HIM"☆羽☆ \n"NOR, me);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

                if( i ) me->set("env/brief_message", 1);
        if( j ) target->set("env/brief_message", 1);

        me->receive_damage("kee", 50);
        me->add("force", -30);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(1);
        return 1;
}

