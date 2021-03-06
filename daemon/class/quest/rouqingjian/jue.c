//伤痛欲绝 jue.c
//by junhyun@SK

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        string msg;
        int success, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || target->is_corpse()
        || target==me)
                return notify_fail("你要对谁用伤痛欲绝？\n");

        if((int)me->query("force") < 4000 || (int)me->query("max_force") < 4000 )
                return notify_fail("你的内力不够，不能用伤痛欲绝！\n");

        if((int)me->query("force") < 1500 || (int)me->query("max_force") < 1500 )
                return notify_fail("你的内力不够，不能使用伤痛欲绝！\n");

        if((int)me->query_skill("rouqingjian", 1) < 400)
                return notify_fail("你的绕指柔情剑不够熟练，使用这一招会有困难！\n");

        if((int)me->query("sen") < 100 || (int)me->query("sen") < (int)me->query("max_sen")/2 )
                return notify_fail("你无法集中精力！\n");

        if( (int)me->query("combat_exp") < (int)target->query("combat_exp")/10  )
                return notify_fail("对方比你强太多了，还是别送死吧！\n");

        if( random(me->query("max_force")) < 2000 ) {
                write("你失败了！\n");
                return 1;
        }

        msg = HIW"$N剑势越来越慢，回想去和自己爱人的过去种种，不由觉得伤痛欲绝
"+HIM"“如果还有来生，你愿意和我在续前缘么？”
"+HIW"$N想起和爱人花前月下缠绵绯策时的话语，不由得痴了…………

"+HIR"$N又想到了至爱离你而去时依依不舍感情，无奈中含恨闭上双眼的情景……
"+HIR"突然间$N觉得全身的血液在沸腾……
"+HIW"$N喃喃自语道：“今生没有你，我活着还有什么意义？”
就在这个时候，$N仿佛看到至爱的人在对自己微笑……
"HIW"$N仰天长啸，身形陡转，背对$n飞了过来，手中长剑倒转“噗”的一声刺入自己的胸膛！\n" NOR;

        success = 1;
        ap = me->query_skill("rouqingjian");
        ap = ap * ap * ap /10 ;
        ap += (int)me->query("combat_exp");
        ap = 4*ap; //this is for 拼命 so easier.
        dp = target->query("combat_exp");
        if( random(ap + dp) < dp ) success = 0;

        ap = (int)me->query("max_force");
        dp = (int)target->query("max_force");
        if( ap < random(dp) ) success = 0;

        if(success == 1 ){//now both die.
                msg +=  HIR "$n被$N的举动吓呆了，一个没注意被$N透体而出的剑尖刺中胸口，顿时发出一声惨叫！\n而$N也身子一瘫，倒在地上。\n" NOR;
                message_vision(msg, me, target);

                target->kill_ob(me);
                me->kill_ob(target);
                //to produce killing messages.

                me->add_maximum_mana(-100);
                me->add_maximum_force(-50);
                me->save();
                //successed, attacker lost 100 max_fali and 50 max_neili.
                
     target->receive_damage("sen",target->query("max_sen")+1,me);
                target->receive_wound("sen", (int)target->query("max_sen")+1, me);
     target->receive_damage("kee",target->query("max_kee")+1,me);
                target->receive_wound("kee", (int)target->query("max_kee")+1, me);
                COMBAT_D->report_status(target);
  target->heart_beat();
                //target die here.

        me->receive_damage("sen", (int)me->query("max_sen")+1, target);
                me->receive_wound("sen", (int)me->query("max_sen")+1, target);
        me->receive_damage("kee", (int)me->query("max_kee")+1, target);
                me->receive_wound("kee", (int)me->query("max_kee")+1, target);
                COMBAT_D->report_status(me);
  me->heart_beat();
                //attacker die here.

        }
            
        else {
                msg +=  HIR "$n见次情景，顾不得什么别的了，就地一滚躲开了着致命的一击！\n$N长叹一声，身子一瘫，倒在地上。嘴角带着一丝微笑……\n" NOR;
                message_vision(msg, me, target);

                target->kill_ob(me);
                me->kill_ob(target);
                //to produce killing messages.

                me->add_maximum_mana(-50);
                me->add_maximum_force(-25);
                me->save();
                //failed, attacker lost 50 max_fali and 25 max_neili.
                
        me->receive_damage("sen", (int)me->query("max_sen")+1, target);
                me->receive_wound("sen", (int)me->query("max_sen")+1, target);
        me->receive_damage("kee", (int)me->query("max_kee")+1, target);
                me->receive_wound("kee", (int)me->query("max_kee")+1, target);
                COMBAT_D->report_status(me);
    me->heart_beat();
                //attacker die here.
        } 

        return 3+random(5);
}


