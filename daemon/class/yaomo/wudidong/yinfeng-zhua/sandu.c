// sandu.c 阴风爪散毒 edited by stey

#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
        string msg;

        if( !target ) target = offensive_target(me);
        if( !target 
        ||      !target->is_character() 
        ||      !me->is_fighting(target) ) 
                return notify_fail("「散毒」只能对战斗中的对手使用。\n"); 

        if( environment(me)->query("no_fight") )
                return notify_fail("这里不能攻击别人! \n");

        if( (int)target->query("combat_exp") < (int)me->query("combat_exp")/2 )
                return notify_fail("对这人散毒是没用的。\n");

        if (!PFM_D->valid_family(me, "陷空山无底洞"))
                return notify_fail("只有无底洞门人才可以用！\n");
                
        if( (int)me->query_skill("huntian-qigong", 1) < 180 )
                return notify_fail("你的混天气功大法不够娴熟，不能散毒。\n");

        if( (int)me->query_skill("yinfeng-zhua", 1) < 180 )
                return notify_fail("你的阴风爪不够娴熟，不能散毒。\n");

        msg = GRN "只听得$N的骨节格格作响，$N的手猛地长了半尺，居然一把抓住$n手
腕，将毒质运于手心，源源不断传入$n体内。\n";

        me->start_busy(1);
        if( random( (int)me->query_skill("yinfeng-zhua",1)) > random(target->query_skill("dodge") /2 ) ) 
        {
                msg += CYN " 结果$p无力挣扎，$P的本身阴毒不断散入$n体内！\n" NOR;
                target->receive_damage("kee", 200, me, "pfm");
                target->receive_wound("kee", 100 + random(80), me, "pfm");
                target->apply_condition("poison_sandu", 1000);
                me->clear_condition();
                target->start_busy(random(2));
        } 
        else 
        {
                msg += YEL"可是$p急提内力奋力一震，将$N的手震了开去。\n" NOR;
                me->start_busy(3);
        }
        message_vision(msg, me, target);
        if( !target->is_killing(me) ) target->kill_ob(me);
        return 1;
}

