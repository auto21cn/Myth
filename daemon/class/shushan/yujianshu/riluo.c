#include <ansi.h>

inherit SSERVER;


int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int myexp,yourexp,busy;    
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展“ 日落 ”?\n");
         
        if (!PFM_D->valid_family(me, "蜀山剑派"))
                return notify_fail("你不是蜀山之人,不可乱用!\n"); 
        if( !me->is_fighting() )
                return notify_fail("“ 日落 ”只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("手中无利器怎能画出朝霞落日？\n");

        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        if( (int)me->query_skill("yujianshu", 1) < 120)
                return notify_fail("你的御剑术等级不够，你怎么能使出“ 日落 ”。\n");

        if (me->query("force") < 300)
                return notify_fail("你内力不继，难以使出“ 日落 ”。\n");

        me->clean_up_enemy();
        ob = me->select_opponent();
        myexp = (int) me->query("combat_exp");
        yourexp = (int) target->query("combat_exp");
        busy = (int)me->query_skill("parry",1)/60;
        message_vision(HIY"\n$N信步于朝霞黄昏之中，眺望雾中西山，脚步轻盈，灵由神生，使出"+HIR"「日落」"+HIY"一技。\n"NOR,me,target);        
        msg = HIC"\n日，朦胧降于小雾西山，犹有风吹，只为洒脱，衬佳人漫步。\n" NOR;
        if(random(myexp)>yourexp/8)
        {
                message_vision(msg + "\n", me, target);
                
                msg = HIC "“亭下花草，万千，袅袅婷婷，雨露知多少，含香含态醉人，暮香深惹情深......”\n" NOR;
                message_vision(msg, me, target);
                target->start_busy(random(busy));
                message_vision(HIG"$n觉，影动雾稀，日落西山，驻足，叹：“惜哉，惜哉...”"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

                message_vision(HIG"$n眺，叶落花残，侔憔悴，意：“怜哉，怜哉...”"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

                message_vision(HIW"$n忆当年，最爱弄玉团酥，幽卧，孤赏霞中日落，悯：“风亭梦魂，幽意何去，唉...”"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

        }
        else 
        {
                message_vision(msg +"\n", me, target);
                msg = HIM "落日朝霞化于无形之中，$n庆幸自己于朝霞之中拓步而归。\n" NOR;
                message_vision(msg, me, target);
                me->start_busy(2); 
        }        
        me->add("force", -150);

        me->start_busy(1+random(2));
        return 1;  

}

