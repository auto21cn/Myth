
#include <ansi.h>

inherit SSERVER;

string get_name(string str)
{
        str="掌心雷";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｚｈａｎｇｘｉｎｌｅｉ\n"
        +"威力惊人！";
        return str;
}

int perform(object me, object target)
{
        object weapon;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招掌心雷？\n");

        if(!me->is_fighting())
                return notify_fail("掌心雷只能在战斗中使用！\n");
        
        if (!PFM_D->valid_family(me, "火云洞"))
                return notify_fail("“掌心雷”只有火云洞门人才可以用！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("kee") < 300 )
                return notify_fail("你的气血不足，没法子施用外功！\n");

        if((int)me->query_skill("moyun-shou", 1) < 50)
                return notify_fail("你的摩云手级别还不够，使用这一招会有困难！\n");

        me->delete("env/brief_message");

        message_vision("\n$N大喝一声“掌心雷”！\n", me);

        target->start_busy(random(2));

        me->set_temp("moyunshou_per", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->delete_temp("moyunshou_per");

        me->receive_damage("kee", 50);
        me->add("force", -100);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(1+random(2));
        return 1;
}

