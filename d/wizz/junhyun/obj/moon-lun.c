#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit F_UNIQUE;
inherit NECK;

int do_wear(string arg);
int do_remove(string arg);
object offensive_target(object me);

void create()
{
        set_name(HIW"月轮之翼"NOR, ({"moon-plumage","neck"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "对");
                set("material", "crystal");
                set("value",10000);
set("no_steal",1);
                set("no_drop", "如此宝贵的宝物再世难求啊。\n");
//                set("no_get", "送人？亏你想的出来！\n");
        set("no_give", "这种稀世之宝怎么能轻易送人呢?\n");
        set("no_steal", "这种稀世之宝怎么能轻易被偷呢?\n");
                set("no_sell", "卖?这种稀世之宝谁买得起啊!\n");
                set("long","天神的翅膀。\n");
                set("replace_file", "/d/obj/flower/rose");
                set("armor_prop/armor", 1);
                set("spells/fire", 1);
                set("spells/thunder",1);
                set("spells/water",1);
                set("spells/wind",1);
                set("spells/earth",1);
        }
        setup();
}

int init()
{
        object who = this_player();
        {
        if ( interactive(environment()) && 
        environment()->query("combat_exp") < 800000 )
        this_object()->move("/obj/empty"); 
         }
        add_action("do_wear","wear");
        add_action("do_remove", "remove");

}

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
        int sz;
        object *enemy;

        enemy = me->query_enemy();
        if( !enemy || !arrayp(enemy) ) return 0;

        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;

        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}

int do_wear (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if(arg!="all"&&arg != "sheng lingzhu" )
    return notify_fail("你要佩带什么？\n");
  msg = "$N心诀移动，背后慢慢生出一对"+name+"。\n"; 
  zhu->set("wear_msg",msg);
remove_call_out("shengzhuconditions");
call_out("shengzhuconditions",1,me,zhu);
  return 0;
}

int do_remove (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if ( arg!= "all" && arg != "sheng lingzhu")
    return notify_fail("你要摘掉什么？\n");

  msg = "$N收回心诀"+name+"慢慢的收拢……\n"; 
  zhu->set("unequip_msg",msg);
remove_call_out("shengzhuconditions");
  return 0;
}

void shengzhuconditions(object who,object ob)
{
     object target;
     int ap,dp,damage;
     string msg;
          
string type;
type = ob->query("armor_type");
if( who->query_temp("armor/" + type) && ob->query("equipped")!="worn")
return;
  if( who->is_fighting())
     {
        target = offensive_target(who);
  if( ! target ) return ;      
 if( ! present( target,environment(who)) ) return ;    
        msg = HIW"月轮之翼突然毫光猛然四射，刹时雪白的羽毛夹杂着风雨雷电而至！\n"NOR;
//divid by 10;

                ap = 5000000;
                dp = target->query("combat_exp");
                        
                        
                if( random(ap + dp) > dp )
                 {
                        damage = 500+random(300);
                        damage -= (int)target->query("max_mana") / 10 + random((int)target->query("eff_sen") / 5);
                        damage -= random((int)target->query("mana_factor"));

                        if( damage > 0 ) 
                        {
                                msg += HIW "
结果$n躲避不及，被羽毛当胸穿过，雪白的羽毛变染成了红色！\n" NOR;

                                target->receive_damage("sen", damage*8/5);
                                target->receive_wound("sen", damage*2/3);
                                target->receive_damage("kee", damage*8/5);
                                target->receive_wound("kee", damage/2);
                                target->start_busy(5);
                        } 
            else
//here, cast failed and the target's mana_factor will be added to the previous
//damage to hurt yourself:(...note damage<0.
                msg += HIC "\n谁知$n就地一滚，闪开了。\n" NOR;   
                }
                else
                        msg += "但是被$n躲开了。\n";
                        msg += "但是被$n躲开了。\n";

                message_vision(msg, who, target); 
        }
call_out("shengzhuconditions",7,who,ob);
}

