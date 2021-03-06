
#include <ansi.h>
#include <weapon.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, attp, defp;
        object weapon;

        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「玉石俱焚」？\n");
                
        if (!PFM_D->valid_family(me, "大雪山"))
                return notify_fail("你的冰魄寒刀是从哪里偷学来的？\n");
                
        if(!me->is_fighting())
                return notify_fail("「玉石俱焚」只能在战斗中使用！\n");

        if ((int)me->query_skill("bingpo-blade", 1) < 150)
                return notify_fail("你的冰魄寒刀级别还不够，使用这一招会有困难！\n");

        if ((int)me->query_skill("ningxie-force", 1) < 150)
                return notify_fail("你的冰谷凝血功火侯太浅，无法震断手中兵器。\n");

        if ((int)me->query("force",1) < 160)
                return notify_fail("你的内力不够，无法震断手中兵器。\n");

        message_combatd( HIR "$N聚气于刀，默运内力，只听“铮”的一声，忽然间银光闪耀，$N手中"+ weapon->name() + HIR"竟断为无数\n"
         + "截，如漫天红云般向$n激射而出！\n"NOR, me, target, "");

        attp = me->query_skill("ningxie-force",1) + me->query_skill("bingpo-blade",1);
        defp = target->query_skill("dodge");

//      if( random( attp ) > random( defp ) )
        if(  attp  > random( defp ) )
        {
                damage = me->query_skill("bingpo-blade",1) + me->query_skill("blade",1)+ (int)me->query_skill("ningxie-force", 1)*2;
                damage = damage - random( target->query_skill("dodge")/3 );

                target->receive_wound("sen", random( damage ), me, "pfm");
                target->receive_damage("kee", 20 + random(damage)+damage, me, "pfm");
                target->receive_wound("kee", 20 + damage, me, "pfm");
                me->start_busy(3);
                target->start_busy(3 + random(4));
        }
        else 
        {
                message_combatd( HIY "可是$p晃动身形，迅速的闪过了无数刀屑。\n" NOR, me, target, "" );
                me->start_busy(2);
        }

        if( !target->is_killing(me) ) me->kill_ob(target);

        me->add("force", -150);
        destruct( weapon );

        return 1;

}


