#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        if( target != me )
                return notify_fail("你只能用镇元神功来提升自己的战斗力。\n");
        if( (int)me->query("force") < 250  )
                return notify_fail("你的内力不够。\n");
        if( (int)me->query_temp("powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        me->add("force", -200);
        message_vision(HIY "$N微一凝神，运起镇元神功，就见$N道冠冲天，全身真气冲关欲出。\n" NOR,me);
        me->add_temp("apply/attack", skill/4);
        me->add_temp("apply/dodge", skill/4);
        me->add_temp("apply/armor", skill/4);
        me->add_temp("apply/defense", skill/4);
        me->add_temp("apply/damage", skill/4);
        me->set_temp("powerup", 1);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill/4:), skill);
        if( me->is_fighting() ) me->start_busy(2);
        return 1;
}

void remove_effect(object me, int amount)
{
        me->add_temp("apply/attack", - amount);
        me->add_temp("apply/dodge", - amount);
        me->add_temp("apply/armor", - amount);
        me->add_temp("apply/defense", - amount);
        me->add_temp("apply/damage", - amount);
        me->delete_temp("powerup");
        tell_object(me, "你的镇元神功运行完毕，将内力收回丹田。\n");
}

