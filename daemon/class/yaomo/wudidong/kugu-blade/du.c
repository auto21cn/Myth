// by iceland 
// changed by emnil     2/7/2000 
// changed by wuyou@sk_sjsh  Feb/25/2003 
// 书剑里的pfm修改过来的 

#include <ansi.h> 
#include <combat.h> 
inherit F_SSERVER; 
 
#include <combat_msg.h> 
#include "du.h"; 

int perform(object me, object target) 
{ 
        string msg; 
        int times,p,damage,x,h,t,lx,i; 
        object weapon; 

        weapon = me->query_temp("weapon"); 
        x = me->query_skill("kugu-blade", 1)/4; 
        h = me->query_skill("blade", 1)/4; 

        if( !target ) target = offensive_target(me); 

        if( !target 
        ||!target->is_character() 
        ||target->is_corpse() 
        ||target==me) 
                return notify_fail("「人莫予毒」只能对战斗中的对手使用。\n"); 

        if (!weapon)  return notify_fail("你必须在使用枯骨刀法时才能施展「人莫予毒」！\n"); 

        t = weapon->query_amount(); 

        if (!PFM_D->valid_family(me, "陷空山无底洞"))
                return notify_fail("只有无底洞门人才可以用！\n");
                
        if (me->query_skill_mapped("blade") != "kugu-blade") 
                return notify_fail("你必须激发枯骨刀法才能施展「人莫予毒」！\n"); 

        if(me->query_skill("kugu-blade", 1) < 410 ) 
                return notify_fail("你的枯骨刀法还不够娴熟，使不出「人莫予毒」绝技。\n"); 

        if(me->query_skill("huntian-qigong", 1) < 400 ) 
                return notify_fail("你的混天气功尚未达到境界，无法使出「人莫予毒」绝技。\n"); 

        if((int)me->query_skill("force") < 400 ) 
                return notify_fail("你的内功等级不够，使不出「人莫予毒」绝技。\n"); 

        if((int)me->query_str() < 40) 
                return notify_fail("你的膂力还不够强劲，使不出「人莫予毒」绝技。\n");                      
                
        if((int)me->query("max_force") < 3000 ) 
                return notify_fail("你内力修为尚浅，使不出「人莫予毒」。\n");       
        
        if( (int)me->query("force") < 500 ) 
                return notify_fail("你现在真气太弱，使不出「人莫予毒」。\n"); 
        
        msg = HIY"\n$N突然仰天长嚎，声声入耳，犹如天雷劈顶，$n头痛脑胀，心中烦躁不已。$N双目精光咋现，稍微“嘿嘿”一笑，将手中"+weapon->query("name")+HIY"旋转掷出，使出「"+MAG"人莫予毒"+HIY"」绝技！\n"NOR; 
    

        t=5; 

        msg+= HIR"只见"+weapon->query("name")+HIR"发出丝丝妖气和阵阵腥臭，化为一团五彩斑斓的毒雾，携带着漫天黄沙，排山倒海般攻向$n！\n\n"NOR; 

        lx = me->query_skill("huntian-qigong",1)/5; 
        if(lx>50) lx = 50; 
        if(me->query_temp("apply/damage") >= 500 ) lx = lx/2; 

        msg += "\n"; 
        message_vision(msg, me, target); 

        me->add_temp("apply/strength", x); 
        me->add_temp("apply/blade", h);  
        me->add_temp("apply/attack",x*5 ); 
        me->add_temp("apply/damage", x*5);  

        if(wizardp(me) && me->query("env/test"))  
                tell_object(me,sprintf("lx:%d , str:%d , att:%d , damage:%d\n",lx,x,h,me->query_temp("apply/damage"))); 
        i = 0; 
        for (times=0;times<t;times++) 
        { 
                switch(times) 
                { 
                        case 0: 
                                msg=msga[random(sizeof(msga))]; 
                                if (random(me->query_skill("blade")) > target->query_skill("parry") /2 ) 
                                { 
                                        damage = (int)me->query_skill("kugu-blade",1) + (int)me->query_skill("huntian-qigong",1);  
                                        damage = damage + random(damage)*(100+lx)/100; 
                                        target->receive_damage("kee", damage, me, "pfm"); 
                                        target->receive_wound("kee", damage/2, me, "pfm"); 
                                        me->add("force", -80); 
                                        p = (int)target->query("kee")*100/(int)target->query("max_kee"); 
                                        msg += damage_msg(damage, "瘀伤"); 
                                        msg += "( $n"+eff_status_msg(p)+" )\n"; 
                                        if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("damage:%d   ",damage)); 
                                        i++; 
                                } 
                                else 
                                { 
                                        me->add("force", -30); 
                                        msg += msgd[random(sizeof(msgd))]; 
                                } 

                                message_vision(msg, me, target); 
                                break; 
                        case 1: 
                                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
                                message_vision("\n",me); 
                                break; 
                        case 2: 
                                msg=msga[random(sizeof(msga))]; 
                                if (random(me->query("combat_exp")) > target->query("combat_exp") /2 ) { 
                                        damage = (int)me->query_skill("kugu-blade",1) + (int)me->query_skill("huntian-qigong",1); 
                                        damage = damage + random(damage)*(100+lx)/100; 
                                        target->receive_damage("kee", damage, me, "pfm"); 
                                        target->receive_wound("kee", damage/2, me, "pfm"); 
                                        me->add("force", -80); 
                                        p = (int)target->query("kee")*100/(int)target->query("max_kee"); 
                                        msg += damage_msg(damage, "瘀伤"); 
                                        msg += "( $n"+eff_status_msg(p)+" )\n"; 
                                        if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("damage:%d   ",damage)); 
                                        i++; 
                                } 
                                else 
                                { 
                                        me->add("force", -30); 
                                        msg += msgd[random(sizeof(msgd))]; 
                                } 

                                message_vision(msg, me, target); 
                                break; 
                        case 3: 
                                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
                                message_vision("\n",me); 
                                me->add("force", -50); 
                                break; 
                        case 4: 
                                msg=msga[random(sizeof(msga))]; 
                                if ( random(me->query_con()+me->query_str())*2 > target->query_dex() ) { 
                                        if(!target->is_busy()) target->start_busy(2); 
                                        damage = (int)me->query_skill("kugu-blade",1) + (int)me->query_skill("huntian-qigong",1); 
                                        damage = damage/2 + random(damage)*(150+lx)/150; 
                                        target->receive_damage("kee", damage, me, "pfm"); 
                                        target->receive_wound("kee", damage/3, me, "pfm"); 
                                        me->add("force", -100); 
                                        p = (int)target->query("kee")*100/(int)target->query("max_kee"); 
                                        msg += damage_msg(damage, "瘀伤"); 
                                        msg += "( $n"+eff_status_msg(p)+" )\n"; 
                                        if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("damage:%d   ",damage)); 
                                } 
                                else 
                                { 
                                        me->add("force", -50); 
                                        msg += msgd[random(sizeof(msgd))]; 
                                } 
                                message_vision(msg, me, target); 
                                break; 
                } 
        } 

        if(me->query("force")<0) me->set("force",0); 

        msg=HIY"\n$N精力已尽，不得不收刀后退，气喘吁吁，犹如脱力一般，行动迟滞了许多。\n"NOR; 
        message_vision(msg, me, target);        
        
        me->add_temp("apply/strength", -x); 
        me->add_temp("apply/blade", -h);
        me->add_temp("apply/attack", -x*5 );
        me->add_temp("apply/damage", -x*5);
        me->start_busy(random(3)+1);
        return 1;  
}

