//轩辕古墓 幽明神通 幽明·媚
//By ivy 2002.4.5
#include <ansi.h>

inherit SSERVER;

void free(object target);

int cast(object me, object target)
{
        string msg;
        int success, ap, dp, ap2, ap3, ap4, dp2, dp3, dp4,howlong;

        if( me->query("gender") =="男性" )
                return notify_fail("你想变成女人么？变态哦\n");

        if( !target ) target = offensive_target(me);

        if((int)me->query_skill("spells") < 100 || (int)me->query_skill("youming-spells",1) < 60)
                return notify_fail("你还是小孩子 没本钱迷惑男人\n");


        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("跳舞给自己看？\n");  

        if(target->query_temp("no_move"))
        return notify_fail(target->query("name")+"已经不行了么，别跳了？\n");  

        if((int)me->query("mana") < 200 )
                return notify_fail("你的法力不够！\n");

        if((int)me->query("sen") < 10 )
                return notify_fail("你无法集中精力！\n");

        me->add("mana", -200);
        me->receive_damage("sen", 10);

        msg = HIW
"$N剑走轻盈，脚踩舞步，对$n莞尔一笑....\n
"HIM" 渐渐的$n觉得$N越来越美，当真是姣花照水，貌如西子胜三分，\n
"HIW"$N越舞越快，$n觉得头昏眼花，只看到一个人影在不停的舞动，一股香气渐渐侵入丹田
\n" 
NOR;

        success = 1;
        ap = me->query_skill("spells");
        ap = ap * ap * ap /12 ;
        ap += (int)me->query("daoxing");
        dp = target->query("daoxing");
//      if( random(ap + dp) < dp ) success = 0;
//here we compared exp and spells level. 
//note: has nothing to do with target's spells level.

        ap2 = (int)me->query_per();
        dp2 = (int)target->query_per();
//      if( random(4*ap) < ((int)target->query_cps()+dp)) success = 0;
//here we compare per and guy's ding li.


        ap3 = (int)me->query("mana");
        dp3 = (int)target->query("mana");
        if( random(ap + dp + 2500*(ap2+dp2)+200*(ap3+dp3)) < (dp+2500*dp2+200*dp3) ) success = 0;

//here we compare current mana. this is important. you need recover to try again.

        if(success == 1 ){
                msg +=  HIR "$n不知被$N的媚魂香气所迷惑，只觉得全身无力无法移动！\n" NOR;
                target->set_temp("no_move", 1);
        
                howlong = random((me->query_skill("spells") -100))+1;
                if(howlong>60) howlong=60;
                call_out("free", howlong, target);
        }           
        else {
                msg +=  HIR "$n鄙夷地看了$N一眼道:“我岂能被你这荡妇所迷惑？！”\n" NOR;   
                me->start_busy(1+random(2));        
                if( living(target) ) target->kill_ob(me);
        } 

        message_vision(msg, me, target);

        return 1;
}

void free(object target)
{
        if (target)
        target->delete_temp("no_move");      
        return;
}

