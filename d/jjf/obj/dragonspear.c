//九转龙星枪 
//by junhyun@SK 

#include <weapon.h> 
//  inherit F_UNIQUE; 

inherit SPEAR; 
#include <ansi.h> 
void create() 
      { 
              set_name(HIC"九转龙星枪"NOR, ({"jiuzhuan dragonspear","spear","qiang"})); 
              set_weight(5000); 
      if( clonep() ) 
                      set_default_object(__FILE__); 
              else { 
      set("long","一杆长枪，枪尖如九转金龙盘绕，枪尖中嵌一颗闪亮的宝石\n"); 
                      set("unit", "柄"); 
                      set("value", 12000); 
                      set("wield_msg",HIC "$N手中闪出九道光环，随着天边龙吟，一杆明晃晃的长枪落入手中！\n"NOR); 
                      set("unwield_msg",HIC "$N手中的长枪化作一团雾气消失了。\n"); 
                      set("no_sell","你大脑有问题吧？这东西你都敢卖？\n");  
                      set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");  
       
                      set("weapon_prop/courage", 20); 
                      } 
              init_spear(120); 
              setup(); 
      } 
      mixed hit_ob(object me, object victim) 
      { 
          int damage_bonus = 0; 
           
          if( (string)me->query("family/family_name") == "将军府" 
                      && me->query_skill("bawang-qiang",1) > 1) 
          damage_bonus = me->query_skill("bawang-qiang",1); 
          damage_bonus = (damage_bonus+random(damage_bonus))/2; 
       
          victim->receive_wound("kee",damage_bonus); 
          return HIC"九转龙星枪上闪出一道霸气！\n" NOR; 
       
      }

