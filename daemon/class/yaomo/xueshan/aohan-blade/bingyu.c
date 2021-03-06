//by koker@sjsh
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「冰风雪雨」？\n");
        
        if (!PFM_D->valid_family(me, "大雪山"))
                return notify_fail("你是哪儿偷学来的武功，也想用「冰风雪雨」?\n");

        if(!me->is_fighting())
                return notify_fail("「冰风雪雨」只能在战斗中使用！\n");

        weapon = me->query_temp("weapon");
        
        if( (string)weapon->query("skill_type") != "blade" )
                   return notify_fail("你手上无刀，不能使用六决刀法的冰风雪雨！\n");

        if((int)me->query("max_force") < 500)
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 300 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 300 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("aohan-liujue", 1) < 200)
                return notify_fail("你的六决刀法级别还不够，使用这一招会丧命的！\n");

        if (me->query_temp("ah_pfm_busy")) 
                return notify_fail("绝招用的太多太滥就不灵了。\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");

        message_vision(HIC"\n$N突然猛的盘旋起来，刹那间寒风刺骨，$n攻出了数招！\n"NOR,me,target);

        me->set_temp("AOHAN_perform", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("AOHAN_perform", 2);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

        me->set_temp("AOHAN_perform", 3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("AOHAN_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("AOHAN_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("AOHAN_perform", 4);
        target->start_busy(2);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->delete_temp("QJB_perform");

        me->receive_damage("sen", 200);
        me->add("force", -200);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else me->kill_ob(target);
                }
        }

        me->set_temp("ah_pfm_busy",1); 
        me->set_temp("no_move",1); 
        call_out("remove_effect",2+random(3),me); 
        call_out("remove_no_move",1,me); 
        return 1;
}

void remove_effect(object me) 
{ 
        if (me)  me->delete_temp("ah_pfm_busy"); 
} 
void remove_no_move(object me) 
{ 
        if (me) me->delete_temp("no_move"); 
} 

