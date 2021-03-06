#include <ansi.h>
#include <combat.h>

inherit SSERVER;

string get_name(string str)
{
        str="冰雪纷飞";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｂｘｆｆ\n"
        +"条件：百鸟剑法160级，内力1000"
        +"寒冬之夜，冰雪漫天，萋萋惨惨";
        return str;
}


int perform(object me, object target)
{
        object weapon, ob;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这招「冰雪纷飞」?\n");


        if( !me->is_fighting() )
            return notify_fail("「冰雪纷飞」只能在战斗中使用。\n");

        if (!PFM_D->valid_family(me, "大雪山"))
                return notify_fail("你不是大雪山弟子，怎么能使用大雪山绝技？\n");
                
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        if( (int)me->query_skill("bainiao-jian",1) < 50 )
                return notify_fail("你的百鸟剑等级不够，你怎么能使出「冰雪纷飞」。\n");

        if( time()-(int)me->query_temp("bxffs_end") < 3 )    
                return notify_fail(CYN"你哪有这么多的真气牵动「冰雪纷飞」？\n"NOR);    
                
        if (me->query("force") < 1000)
                return notify_fail("你内力不继，难以使出「冰雪纷飞」。\n");

//        if( target->is_busy() )
//                return notify_fail(target->name() + "目前正手忙脚乱，赶快进攻吧！\n");
        

        msg = HIW "$N使出「冰雪纷飞」，似漫无边际的雪花一般向无数方向发出攻击！\n\n" NOR;
        message_vision(msg, me);

        me->clean_up_enemy();
        ob = me->select_opponent();

        target->start_busy(1);
        message_vision(HIW"只见一片雪花飘飘然飞向$n。"NOR, me, ob);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

        message_vision(HIC"只见一块冰晶闪电般的冲向$n。"NOR, me, ob);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

        message_vision(HIB"冬季刮骨的寒风似小刀一般刮向$n。"NOR, me, ob);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

        if( (int)me->query_skill("bainiao-jian",1) > 99 )
        {
                message_vision(HIM"寒夜的雷电肆无忌惮的射向$n。"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

                message_vision(HIY"冬夜的寒霜围绕着$n。"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

                message_vision(HIG"寒冬迷失方向幽灵让人不寒而栗哭嚎着。"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        }
        
        if( (int)me->query_skill("bainiao-jian",1) > 149 )
        {
                message_vision(HIR"寒冬之夜觅食的野兽围绕着$n周围。"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), TYPE_SUPER);

                message_vision(YEL"飘雪的天空$n不时的听见枯鸦的哀鸣。"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), TYPE_SUPER);
        }

        if ((int)me->query_skill("bainiao-jian",1) > 179 )
        {
            me->add("force", -200);
            me->add_temp("apply/attack", get_level(me->query("combat_exp")));
            me->add_temp("apply/damage", get_level(me->query("combat_exp")));
            message_vision(MAG"迷路的$n早已心神混乱，$N乘机全力挥出致命一击。"NOR, me, ob);

            COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), TYPE_SUPER);

            me->add_temp("apply/damage", -get_level(me->query("combat_exp")));
            me->add_temp("apply/attack", -get_level(me->query("combat_exp")));
        }            
        me->add("force", -100);
        me->set_temp("bxffs_end",time());    



        return 1;  

}

