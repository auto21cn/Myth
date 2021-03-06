
#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int perform(object me, object target)
{
       object weapon;
       string msg;
       int p,skill,damage;
       int d;
       
       if( !target ) target = offensive_target(me);

       if(!objectp(weapon = me->query_temp("weapon"))
        ||(string)weapon->query("skill_type") != "sword")
            return notify_fail("你使用的武器不对。\n");

       if( !target 
        || !me->is_fighting(target) )
            return notify_fail("「圣灵媚舞」只能在战斗中对对手使用。\n");

        if ( me->query("gender") =="男性" ) 
                return notify_fail("大男人用这招好象不太合适吧..?\n");

       if((int)me->query_skill("shengling-sword", 1) < 220 )
            return notify_fail("你的圣灵剑法等级不够!\n");       

//       if (me->query_skill_mapped("force") != "jiuyin-force")
//            return notify_fail("你所使用的内功不对。\n");

       if ((int)me->query_skill("jiuyin-force", 1) < 200 )
            return notify_fail("你的玄天九阴心经等级不够!\n");    
      
       d = (int)me->query_skill("shengling-sword",1);

       if ((int)me->query_skill("sword", 1) < 200 )
            return notify_fail("你的基本剑法不够娴熟!\n");    

       if ((int)me->query("sen") < 1000)
            return notify_fail("你的精神不太好,似乎无法用这一招!\n");

       if ((int)me->query("force") < 800 )
            return notify_fail("你现在的真气太弱!\n");

       if ((int)me->query("max_force") < 2000 )
            return notify_fail("你现在内力太弱!\n");

        if( time()-(int)me->query_temp("posui_end") < 4 ) 
                return notify_fail("你现在真气不纯。\n");

           skill = me->query_skill("shengling-sword",1)/2;
           damage = skill*3 + random(skill);
           damage = damage*2 + random(damage);
       message_vision(MAG"$N迎风而立，洁白如莲的衣裳上沾着细碎的桃花瓣，\n
"MAG"妖娆娇媚不可名状。风中只见她轻扬手中"+weapon->name()+"\n
"MAG"双眸幽若秋水，低声吟道：\n"NOR, me, target);
     message_vision(WHT"          “寒心未尽怨春迟，谁记清溪叶落叶。\n"NOR,me,target);
     message_vision(WHT"            羞与碧霜描旧景，怕同飞雪论新诗。”\n"NOR,me,target); 
     COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
       if (random(me->query_skill("force")) > target->query_skill("force")/3){
          target->receive_damage("kee", damage);
          target->receive_wound("kee", damage/2);
          target->start_busy(3);
          message_vision(HIR"$n"HIR"被$N惹人心动的幽怨眼神惑住，一不留神左臂被砍得鲜血淋淋!\n"NOR, me, target); 
       }
       else{
  message_vision(HIW"$n嘿嘿一笑，对$N的美貌毫不动心,手上的劲力更加大了!\n"NOR,me,target);
       }          
       message_vision(MAG"\n$N“哼”地冷笑一声，风中只见她面无血色，却更显娇媚。\n
"MAG"刀光剑影中，她袅娜娉婷的身影随风飘荡，手中"+weapon->name()+""MAG"直挥向$n!\n"NOR, me, target);
       message_vision(WHT"         “红颜带露愁何限，玉蕊凝香意更痴。\n"NOR,me,target);
       message_vision(WHT"           不见倔根连秃干，孤芳岑戚倚空枝。”\n"NOR,me,target);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
//       me->start_busy(1);
        me->add("force", -200);
        me->receive_damage("sen", 150);
        me->set_temp("posui_end", time());
       return 1;
}

