#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob, where;
        int i, skill, damage, force;

        where=environment(me);
        if( where->query("no_fight") )
                return notify_fail("打架时你在吹吧\n");
       if (!present("yu xiao", me))
                return notify_fail("想吹奏「碧海潮生」没有玉箫怎么行？\n");
        if( !me->is_fighting() )
                return notify_fail("没人打你呀，吹什么呀？\n");
        if (!PFM_D->valid_family(me, "轩辕古墓"))
                return notify_fail("这『碧海潮生曲』是轩辕古墓的绝密，你如何得知的！？\n");
        if( (int)me->query("force") < 200 )
                return notify_fail("你的内力不够。\n");
        if( (int)me->query("kee") < 100)
                return notify_fail("你的力气不够了。\n");
        if (me->query_skill("xiao",1)<100)
                return notify_fail("你会吹箫么？瞎捣乱\n");
        if (me->query_skill("jiuyin-force",1)<200)
                return notify_fail("没那么强的内功，小心走火入魔！\n");
        skill = me->query_skill("force");
        force = me->query("max_force");
        me->add("force", -150);
        me->receive_damage("kee", 50);

        me->start_busy(5);
        message_vision(HIG "$N左手一探,手中多出一只玉箫,只见$N脚踏九宫八卦的方位悠扬的吹起箫曲。\n\n"NOR,me); 
        message_vision(HIC "需知这曲中暗含上乘内力，若听者定力稍差，则会心魔攻体，随曲狂舞至死！\n"NOR,me);
        message_vision(HIW "               此曲就是以九阴真经为根基的古墓绝学\n\n"NOR,me); 
        message_vision(HIW+BLINK"                        《碧海潮生曲》\n\n"NOR,me);
 ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ) continue;
                if(!me->visible(ob[i])) continue;
                if( skill/2 + random(skill/2) < (int)ob[i]->query("cps") * 2 ) continue;

                damage = skill + force/5 - ((int)ob[i]->query("max_force") / 5);
                if( damage > 0 ) {
                        ob[i]->receive_damage("sen", damage,me,"pfm");
                        if( (int)ob[i]->query("force") < skill * 2 )
                                ob[i]->receive_wound("sen", damage/2,me,"pfm");
  message_vision(HIR "$n听到此曲，不由心神一荡,只觉的内心一阵悸动,身体不由自主的随曲而舞！\n\n"NOR,me,ob[i]); 
                        tell_object(ob[i], "你觉得眼前一阵金星乱冒，脑袋痛得像是要裂开一样！\n");
                }
                COMBAT_D->report_sen_status(ob[i]);             
                if( userp(ob[i]) ) ob[i]->fight_ob(me);
                else if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);

        }

        return 1;
}

