
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;

        if (!target ) target = offensive_target(me);

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "stick")
                return notify_fail(WHT"没有棍子怎么用释厄棍法？\n"NOR);

        if (!target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「修身心，悟禅道」只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("buddha-stick", 1) < 90 )
                return notify_fail(WHT"你释厄棍法不够娴熟，使不出「修身心，悟禅道」。\n"NOR);
 
        if ((int)me->query_skill("lotusforce", 1) < 90 )
                return notify_fail(WHT"你莲台心法火候不够，使不出「修身心，悟禅道」。\n"NOR);

        if (!PFM_D->valid_family(me, "南海普陀山")) 
                return notify_fail("只有佛门中人才可以用「修身心，悟禅道」！\n");

        if ((int)me->query("max_force") < 600)
                return notify_fail(WHT"你内力修为不足。\n"NOR);

        if ((int)me->query("force") < 600)
                return notify_fail(WHT"你现在内力不够，不能使出「修身心，悟禅道」！\n"NOR);

        if ((int)me->query_skill("buddhism",1) < 90)  
                return notify_fail("佛门以佛法为上乘法术，你修行太差。\n");  
 
        me->delete("env/brief_message"); 
     
        message_vision(HIW"\n$N盘膝而座，口中有词曰：“不应生住法心。不应生住非法心。不应生有所住心。\n"NOR, me, target); 
        message_vision(HIW"\n所有一切众生类摄。若卵生若胎生若湿生若化生。何以故。若心有住则为非住故。\n"NOR, me, target); 
        message_vision(HIW"\n若有色若无色。若有想若无想。若非有想若非无想。乃至众生界及假名说。善哉．．善哉．．．”\n\n"NOR, me, target);
        

        if( ((random(me->query("combat_exp")) + (me->query("combat_exp")/2) > (int)target->query("combat_exp")/2 ))) 
        {
                message_vision(HIY"$n被$N的佛理所感动，听得痴迷如醉，不知所措。\n"NOR,me,target);
                damage = me->query_skill("buddha-stick",1) + random(me->query_skill("buddha-stick",1));
                me->add("force", -200);
                me->recevive_damage("kee", 200);
                me->start_busy(1);
                target->start_busy(2+random(2));
                target->receive_damage("kee", damage/2,me,"pfm");
                target->receive_wound("kee", damage/2,me,"pfm");
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
         }
        else
        {
                me->start_busy(2);
                me->add("kee", -100);
                message_vision(HIC"$n喝道：“我又不是佛门中人，何必和我婆婆妈妈？”\n"NOR,me,target);
                me->add("force", -120);
         }
   
   
         return 1;
}
