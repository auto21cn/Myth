#include <ansi.h>

inherit NPC;
int begin_chasing();
void create()
{
        set_name("二郎神", ({"erlang shen", "erlang", "shen"}));
        set("long",HIC "他是赤城昭惠英灵圣，显化无边号二郎。
力伏八怪声名远，义结梅山七圣行。\n"NOR);
        set("looking",HIM "仪容清俊貌堂堂，两耳垂肩目有光。"NOR);
        set("age", 28);
        set("attitude", "peaceful");

        set("gender", "男性");
        set("color", HIW);
        set("title", HIG"昭惠灵显王"NOR);
        set("str", 40);
        set("int", 40);
        set("per", 30);
        set("con", 30);
        set("max_kee",8000);
        set("max_sen", 8000);
        set("taskguai", 1);
        set("combat_exp", 20000000);
        set("daoxing", 20000000);

        set("force", 22000);
        set("max_force", 22000);
        set("mana", 22000);
        set("max_mana", 22000);
        set("force_factor", 500);
        set("mana_factor", 500);

 //       set("eff_dx", 800000);
        set("nkgain", 800);

        set_skill("unarmed", 280);
        set_skill("force", 280);
        set_skill("dodge", 280);
        set_skill("parry", 280);
        set_skill("spells", 280);
        set_skill("spear", 280);
        set_skill("bawang-qiang",280);
        set_skill("lengquan-force",280);
        set_skill("baguazhou",280);
        set_skill("yanxing-steps",280);
        set_skill("changquan",280);
        map_skill("dodge","yanxing-steps");
        map_skill("unarmed","changquan");
        map_skill("force","lengquan-force");
        map_skill("spells","baguazhou");
        map_skill("spear","bawang-qiang");
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
        (: exert_function, "powerup" :),
        (: perform_action,"spear", "bugong" :),
        (: perform_action,"spear", "meihua" :),
        (: perform_action,"unarmed", "zhiqi" :),         
        }) );



        create_family("将军府", 2, "蓝");

        set("inquiry", ([ /* sizeof() == 2 */
                "here" : "我在此看守我的妹妹 。",
                "name" : "我乃二郎神杨戬是也。",
        ]) );

        setup();
        carry_object("/d/meishan/npc/obj/spear")->wield();
        carry_object("/d/obj/armor/jinjia")->wear();
        carry_object("/d/obj/drug/jinchuang")->set_amount(random(10));
}

/*
void init()
{
    object me=this_object();
    object who=this_player();
           ::init();
   
   
}
int do_no(string arg)
{
        object who = this_player();
        object me = this_object();
        message_vision("$N鬼鬼遂遂不知想干什么，$n警惕的盯着$N。\n",who,me);
        return 1;
}
int do_qk(string arg)
{
    
        string cast_id,cast_name;
        object who = this_player();
        
    if (sscanf(arg, "%s on %s", cast_id,cast_name) == 2)
     
      if(cast_id=="qiankun" || arg=="qiankun")
     
       tell_object(who,"你隐隐的听到镇元大仙的声音：你这逆徒！"
                +"休要用我观中法术，以免牵带我全观弟子！\n");
      return 1;
 
   
}
*/
void kill_ob (object ob)
{
        set_temp("no_return",1);
        set_temp("my_killer",ob);
  call_out("check",1);
        ::kill_ob(ob);
}
                        
void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
    ob->clear_condition();
        if( ! me ) return ;
   if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                               

     switch(random(6))
     {        
        case 0:
        {
        message_vision(YEL"$N头上第三只眼睛闪出一道金光，金光向$n射来！\n",ob,me);


       if(random(3)==0)
                {
              message_vision(YEL"$N被金光笼罩全身,炙热难受！\n"NOR,me);
              me->receive_damage("kee",query("max_kee")/10);
              me->receive_wound("kee",query("max_sen")/10);
              me->receive_damage("sen",query("max_kee")/10);
              me->receive_wound("sen",query("max_sen")/10);
                }
        else
        message_vision(YEL"$N倒地一滚，狼狈的躲过这道金光！\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(YEL"$N念念有词，一只啸天犬向$n冲来！\n",ob,me);

                if(random(3)==0)

                {
              message_vision(YEL"$N被啸天犬的尖牙咬了个大窟窿！\n"NOR,me);
              me->receive_damage("kee",2*query("max_kee")/10);
              me->receive_wound("kee",2*query("max_sen")/10);
              me->receive_damage("sen",2*query("max_kee")/10);
              me->receive_wound("sen",2*query("max_sen")/10);
                }
        }
        break;

        case 2:
        {

        message_vision(HIR"$N化为金光向$n直冲过去。\n",ob,me);

                if(random(3)==0)

                {
              message_vision(HIR"$N不但不躲避，反而迎了上去！\n"NOR,me);
              me->receive_damage("kee",2*query("max_kee")/10);
              me->receive_wound("kee",2*query("max_sen")/10);
              me->receive_damage("sen",2*query("max_kee")/10);
              me->receive_wound("sen",2*query("max_sen")/10);
                }
        else
        message_vision(HIR"$N看准方向，躲开了$n的金光直射一招！\n"NOR,me,ob);
        }
        break;

  }
        if( random(8) == 5 )
        {  
           set("eff_kee", 8000);
           set("eff_gin", 8000);
           set("eff_sen", 8000);
           set("kee", 8000);
           set("gin", 8000);
           set("sen", 8000);
           set("force", 22000);
           set("mana", 22000);
        }

        remove_call_out("check");
        call_out("check",2+random(2));
}                     
void die()
{
  object ob = query_temp("my_killer");
  if (environment())
    message("sound", HIW"二郎神"NOR+"头上第三只眼睛闪了一闪又闭了起来。\n\n", environment());

  set("eff_kee", 8000);
  set("eff_gin", 8000);
  set("eff_sen", 8000);
  set("kee", 8000);
  set("gin", 8000);
  set("sen", 8000);
  set("force", 22000);
  set("mana", 22000);
  if (ob->query("bld/mother") == 1 &&  ob->query("bld/taxue") == 1 && ob->query("bld/laozhe") == 1 )
  {
if (random(50)> 25)
          { 
                if (environment())
          message("sound", HIW"二郎神"NOR+"躲在一旁不敢乱动了。\n\n", environment());
             this_player()->remove_all_killer();
             ob->remove_all_killer();
           ob->set("bld/erlang",1);  
             }
             else {  
                 if (environment())
    message("sound", HIW"二郎神"NOR+"头上第三只眼睛闪了一闪又闭了起来。\n\n", environment());
             }
        
      }
}

void unconcious()
{
  die ();  
}

