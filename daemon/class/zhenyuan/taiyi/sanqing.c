//lestat 2001

#include <ansi.h>
inherit SSERVER;

int cast(object me, object target)
{
        int invocation_time;
        object soldier;

        if( !me->is_fighting() )
                return notify_fail("只有战斗中才能化三清。\n");
        
        if (!PFM_D->valid_family(me, "五庄观"))
                return notify_fail("一气化三清是五庄观绝技！\n");
        
        if(me->query_skill("taiyi", 1) < 220)
                return notify_fail("以你现在修为还不能化三清。\n");  
        
        invocation_time=30+(200-(int)me->query_skill("spells"));
        
        if(invocation_time<30) invocation_time=30;
        
        if((time()-me->query("last_invocation"))<invocation_time+30)
                return notify_fail("你刚化过三清，心力不足！\n");

        if( (int)me->query("mana") < 1000 )
                return notify_fail("你的法力不够了！\n");

        if( (int)me->query("sen") < 500 )
                return notify_fail("你的精神无法集中！\n");

        message_vision(HIG"$N跳出圈子来，把发冠一推，只见顶上三道气出，化为三清。\n"NOR, me);

        me->add("mana", -600);
        me->receive_damage("sen", 300);

        if( random(me->query("max_mana")) < 500 ) 
        {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }

        seteuid(getuid());
        soldier = new("/d/qujing/wuzhuang/npc/dao1");
        soldier->move(environment(me));
        soldier->invocation(me);
        soldier->set_temp("invoker",me);
        me->set("last_invocation",time());
        me->start_busy(1);
        if(me->query_skill("taiyi", 1) > 320)
                call_out("sanqing2", 1, me, target);   
        return 1;
}

int sanqing2(object me, object target)
{
        object soldier;
        seteuid(getuid());
        soldier = new("/d/qujing/wuzhuang/npc/dao2");
        soldier->move(environment(me));
        soldier->invocation(me);
        soldier->set_temp("invoker",me);
        if(me->query_skill("taiyi", 1) > 420)
                call_out("sanqing3", 1, me, target);   

        return 1;
}

int sanqing3(object me, object target)
{
        object soldier;
        seteuid(getuid());
        soldier = new("/d/qujing/wuzhuang/npc/dao3");
        soldier->move(environment(me));
        soldier->invocation(me);
        soldier->set_temp("invoker",me);
        return 1;
}

