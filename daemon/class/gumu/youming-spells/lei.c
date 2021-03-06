//轩辕古墓 幽明神通 幽明玄雷
#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        int success_adj, damage_adj;

success_adj = 130;
damage_adj = 130;

        if( me->query("gender") =="女性" )
                return notify_fail("女孩子可召唤不了雷神哦。\n");

        if( !target ) target = offensive_target(me);

        if( random(me->query("max_mana")) < 850 ) {
                write("你的没有那么多法力来召唤暗黑雷神\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要用雷劈谁？\n");

        if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") )
                return notify_fail("你的法力不够！\n");

        if((int)me->query("sen") < 50 )
                return notify_fail("你无法集中精力瞄准！\n");

        me->add("mana", -25-2*(int)me->query("mana_factor"));
                me->receive_damage("sen", 10);

                return 1;
        }

        SPELL_D->attacking_cast(
                me, 
                        //attacker 
                target, 
                        //target
                success_adj,    
                        //success adjustment
                damage_adj,     
                        //damage adjustment
                "both",                 
                        //damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
                HIW "
$N大喝一声：“雷神助我”，天空中顿时乌云密布，雷声滚滚\n
突然一个接一个黑色的闪电夹杂在滚滚的雷声中蒙的劈向$n\n" NOR,
                        //initial message
                WHT "结果一道闪电从$n身上透体而过，$n顿时被劈的焦黑！\n" NOR, 
                        //success message
                HIC "只见$n施展轻功连连跳跃，每一道闪电都从身边擦过！\n" NOR, 
                        //fail message
        HIC "之见$n双眼放光，大喝一声“回去”闪电竟然折向$N！\n" NOR,
                        //backfire initial message
                HIC "结果一道闪电从$n身上透体而过，$n顿时被劈的焦黑\n" NOR
                        //backfire hit message. note here $N and $n!!!
        );

        me->start_busy(1+random(2));
        return 3+random(5);
}


