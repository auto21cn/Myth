#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,j,damage;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要攻击谁？\n");

        if(!me->is_fighting())
                return notify_fail("你们没有在打架！\n");

        if (!PFM_D->valid_family(me, "南海普陀山"))
                      return notify_fail("非神非佛怎么能用佛门不传之密！\n"); 

        if((int)me->query("max_force") < 800 )
                return notify_fail("你的内功太差。\n");

        if((int)me->query("force") < 200 )
                return notify_fail("你的内力不足！\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        i=(int)me->query_skill("lunhui-zhang",1)+me->query_skill("staff",1)/2;
        j=(int)me->query_skill("lunhui-zhang",1);

        if(i<60 || j<10)        
                return notify_fail("你的轮回杖级别还不够，使用这一招会有困难！\n");
        
        me->delete("env/brief_message");
        target->delete("env/brief_message");

        message_vision(HIY"\n$N口诵佛号，将千年修为注入手中"+weapon->name()+NOR+HIY"顿时间霞光四射，照得$n睁不开眼！\n"NOR,me,target);
        message_vision(HIW"\n                    〓〓我入地狱〓〓 \n"NOR,me,target);
        message_vision(HIC"\n我不入地狱，谁入地狱，不惟入地狱，且常住地狱，
不惟常住地狱，而且庄严地狱。弘发‘五愿’，地狱未空，誓不成佛，众
生度尽，方证菩提。\n"NOR,me,target);
        
        damage=me->query_skill("buddhism") + me->query_skill("staff") +                me->query_skill("lunhui-zhang") + me->query("max_force");

        if(random((int)target->query("combat_exp")) < (int)me->query("combat_exp")) 
        {
                target->receive_damage("kee",damage/3,me,"cast");
                me->receive_damage("sen", 100+random(50),me,"cast");
                me->receive_damage("kee", 100+random(50),me,"cast");
                COMBAT_D->report_status(target);
                COMBAT_D->report_status(me);            
                
        }

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(2);
        return 1;
}

