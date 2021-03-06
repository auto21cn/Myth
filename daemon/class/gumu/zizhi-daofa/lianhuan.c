//lianhuan.c
//by junhyun@SK
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void lh_ok(object);

int perform(object me, object target)
{
        int damage,damagea;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「玲珑连环」？\n");
                if(me->query("family/family_name") != "轩辕古墓")
                return notify_fail("[玲珑连环]是月宫不传之密！\n");
                if(!me->is_fighting())
                return notify_fail("「玲珑连环」只能在战斗中使用！\n");
                if((int)me->query("max_force") < 300 )
                return notify_fail("你的内力不够！\n");
                if((int)me->query("force") < 300 )
                return notify_fail("你的内力不足！\n");

                if((int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
                if((int)me->query_skill("kongming-steps", 1) < 120)
                return notify_fail("你的空冥步法不够娴熟，使用这一招会有困难！\n");                
                if((int)me->query_skill("zizhi-blade", 1) < 120)
                return notify_fail("你的紫雉刀法不够熟练，使用这一招会有困难！\n");
                if (me->query_skill_mapped("force")!="jiuyin-force")
                return notify_fail("「玲珑连环」必须配合九阴真经才能使用。\n");

                if(me->query_temp("no_lh"))
                return notify_fail("你不怕闪了腰？！\n");
                me->delete("env/brief_message");
                target->delete("env/brief_message");

            damagea=random((int)me->query_skill("dodge"));
if(random((int)target->query("combat_exp")) < (int)me->query("combat_exp"))
{
              message_vision(HIG"\n$N刀势突转使出玄天紫雉刀的绝学--玲珑连环！！\n"NOR,me,target); 

              message_vision(HIG"\n第一招----风玲珑，$N手中的利刃如一阵疾风般攻向$n！\n"NOR,me,target);
              target->receive_damage("kee",damagea,me);
              target->receive_wound("kee",damagea/2,me);
              target->receive_damage("sen",damagea/3,me);
              target->start_busy(2);
              COMBAT_D->report_status(target);
}
else {
              message_vision(HIG""NOR,me,target);
             }
                message_vision(HIG"\n第二招——花玲珑，$N手中的利刃连刺五刀如一朵盛放的梅花！\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

                message_vision(HIG"\n第三招——雪玲珑！$N手中的利刃突闪一道寒光，如片片雪花！。\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

                message_vision(HIG"\n第四招——月玲珑！$N手中的利刃从上至下，之劈下来，犹如一轮弯月！”\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
               damage=(int)me->query_skill("sword")+random((int)me->query_skill("parry"));
if(random((int)target->query("combat_exp"))<(int)me->query("combat_exp"))
{
              message_vision(HIC"\n风花雪月·玲珑连环，$n早就被着良辰美景搞得飘飘然了，哪里还记得自己在战斗....\n"NOR,me,target);
              target->receive_damage("kee",damage/2,me,"cast");
              target->receive_wound("kee",damage/2,me,"cast");
              COMBAT_D->report_status(target);
}
else {
              message_vision(HIR"\n$n拍了拍头道：“什么鬼玩艺，消遣我？看打！”\n"NOR,me,target);
             }
              me->receive_damage("sen", 30);
              me->add("force", -100);
              me->set_temp("no_lh",1);
              call_out("lh_ok",2+random(2),me);
              if( !target->is_fighting(me) ) {
              if( living(target) ) {
              if( userp(target) ) target->fight_ob(me);
              else target->kill_ob(me);
}
}
return 1;
}

void lh_ok(object me)
{
if (!me) return;
      me->delete_temp("no_lh");
}


