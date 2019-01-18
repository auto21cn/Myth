//by dewbaby@sk_sjsh
//【怜月】

#include <ansi.h>
#include <combat.h>
inherit SSERVER;


int perform(object me, object target)
{
        object weapon,ob;
        string msg;
         int myexp,yourexp;
        int busy;    
        int hyjf;
        int damage;    
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展【怜月】？\n");
           if ((string)me->query("family/family_name")!="凌海神宫")
                return notify_fail("你不是凌海神宫中人，哪里偷学来的？\n"); 
         if( !me->is_fighting() )
                return notify_fail("【怜月】只能在战斗中使用。\n");

         if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("哪个师傅教你空手怜月的?\n");

         if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

         if( (int)me->query_skill("huanyue-jianfa", 1) < 120) 
                return notify_fail("你的【环月剑法】火侯不够，无法使用此招!\n");

         hyjf = (int)me->query_skill("huanyue-jianfa",1);

         if( (int)me->query_skill("sword",1) < hyjf)
                return notify_fail("你的基本剑术等级不够，无法使出【怜月】 。\n");

         if (me->query("force") < 300)
                return notify_fail("你内力不够，无法使用这一招。\n");

         me->clean_up_enemy();
         ob = me->select_opponent();
         myexp = (int) me->query("combat_exp");
         yourexp = (int) target->query("combat_exp");
         busy = (int)me->query_skill("parry",1)/54;
message_vision(HIY"\n$N腾空跃起，左手指尖向天，在空中画了个圆。右手剑气环绕，连绵不绝。正是"HIW"凌海神宫"HIY"千古绝技"BLINK""HIR"怜月\n"NOR,me,target);        
    
message_vision(HIR"\n\n            “月到伤心谁肯怜，每逢佳节更难圆。\n"NOR,me,target);
message_vision(HIR"\n\n            “暮云西聚竞相逐，碧水东流不复还。\n"NOR,me,target);
message_vision(HIR"\n\n            “桂叶含香几分泪，山风醒酒准无眠。\n"NOR,me,target);
message_vision(HIR"\n\n            “吴刚已倦应停斧，又恐衣单晓雨寒。\n"NOR,me,target);

         damage=(int)me->query_skill("parry")+random((int)me->query_skill("sword"));
         if(random(myexp)>yourexp/8)
         {
                
          msg = HIY "若问月下谁有心，千山明月可曾惜，雨夜寒烛裹单衣，梦中无梦忘今夕.....”\n" NOR;
          message_vision(msg, me, target);
          target->start_busy(3);
          target->receive_damage("kee",damage);
          target->receive_wound("kee",damage/3);
          target->receive_damage("sen",damage);
          target->receive_wound("sen",damage/2)+20;
          COMBAT_D->report_status(target);
      }
      else {
            message_vision(HIW"$n毫不动心，一声冷笑：“此情此景何需惜？自古至今月常新。”\n"NOR,me, target);
          me->start_busy(2);
          me->add("force", -100);
  

  }
          if( wizardp(me) && (string)me->query("env/combat")=="verbose" )    

          message_vision(msg, me, target); 
     return 1;  
}


