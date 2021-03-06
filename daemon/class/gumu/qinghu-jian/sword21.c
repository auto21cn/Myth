// shengling-sword 剑二十一式

#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra,lvl;
        int i;
        object weapon,ob;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("剑二十一式威力太大，轻易不要乱用。\n");
        weapon = me->query_temp("weapon");
        if (!weapon) return notify_fail("虽然剑二十一式是剑气伤人，你也不能真不拿剑呀！\n");
        if(me->query("family/family_name")!="轩辕古墓")
return notify_fail("“剑二十一式”只有圣灵剑传人才可以用！\n");
        if( (string)weapon->query("skill_type") != "sword" )
        return notify_fail("剑二十一式”是剑法绝学！\n");
              if( (int)me->query_skill("qinghu-jian", 1) < 250) 
              return notify_fail("你的青狐剑等级太低，无法使出剑二十一式。\n"); 
        if ( (string) me->query_skill_mapped("sword") != "qinghu-jian")
        return notify_fail("你的青狐剑不熟练，无法使用剑二十一式\n");
        if (me->query_skill_mapped("force")!="jiuyin-force")
                return notify_fail("只有九阴真经才能有如此浑厚的内力。\n");
        if((int)me->query("force") < 800 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("kee") < 400 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if((int)me->query("sen") < 400 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        extra = me->query_skill("qinghu-jian",1) / 15;
        extra += me->query_skill("kongming-steps",1) / 15;
        me->add_temp("apply/attack", extra*3);    
        me->add_temp("apply/damage", extra*3);
        me->receive_damage("kee", 100);
        msg = HIW  "$N一甩手，将手中宝剑掷上天空，凝神敛气，以气御剑，剑气不绝！
        \n"HIY"
只见$N拔地而起，随着"+ weapon->name() +HIY"，化作一股无边剑气狂风般卷向$n！\n\n" NOR;
        message_vision(msg, me, target);
           target->start_busy(1);
        msg =  HIW"圣灵剑绝学剑二十一式\n\n" NOR;
        message_vision(msg, me, target);
        me->clean_up_enemy();
        ob = me->select_opponent();
                lvl=extra;
    if(lvl>3) lvl =21;
        for(i=0;i<lvl;i++)
        {
        msg = HIW "$N以气御剑，身随剑走，飘然一剑袭来！\n" NOR;
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 2);
        }
        me->add_temp("apply/attack", -extra*3);
        me->add_temp("apply/damage", -extra*3);
        me->start_busy(random(extra/4));
        me->receive_damage("sen", 200);
        me->add("force", -400);
        me->receive_damage("kee", 200);
        return 1;
}

