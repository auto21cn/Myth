//npc--dog

#include <ansi.h>

inherit NPC;
int begin_chasing();
void create()
{
        set_name("啸天犬", ({"xiaotian quan", "xiaotian", "quan","dog"}));
        set("long",HIC "他是二郎神神犬，本领非凡。\n"NOR);
        set("age", 40);
        set("attitude", "peaceful");

        set("color", HIW);
        set("gender", "男性");
        set("title", HIG"犬王"NOR);
        set("str", 40);
        set("int", 40);
        set("per", 10+random(5));
        set("con", 30);
        set("max_kee",5000);
        set("max_sen", 5000);
        set("combat_exp", 15000000);
        set("daoxing", 15000000);

        set("force", 12000);
        set("max_force", 12000);
        set("mana", 12000);
        set("max_mana", 12000);
        set("force_factor", 300);
        set("mana_factor", 1200);

        set("eff_dx", 800000);
        set("nkgain", 800);

        set_skill("unarmed", 200);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set_skill("spells", 200);
        set_skill("spear", 200);
        set_skill("bawang-qiang",200);
        set_skill("lengquan-force",200);
        set_skill("baguazhou",200);
        set_skill("yanxing-steps",200);
        set_skill("changquan",200);
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


        create_family("将军府", 3, "蓝");

        set("inquiry", ([ /* sizeof() == 2 */
                "name" : "我乃犬王啸天犬是也。",
        ]) );

        setup();
        carry_object("/d/obj/armor/jinjia")->wear();
}

        void kill_ob (object ob)
{
        set_temp("no_return",1);
        set_temp("my_killer",ob);
        ::kill_ob(ob);
}
                        
                     
void die()
{
  object ob = query_temp("my_killer");
//
    this_object()->clear_condition();
  

  set("eff_kee", 5000);
  set("eff_gin", 5000);
  set("eff_sen", 5000);
  set("kee", 5000);
  set("gin", 5000);
  set("sen", 5000);
  set("force", 12000);
  set("mana", 12000);
  if (ob->query("bld/mother") == 1 &&  ob->query("bld/taxue") == 1 && ob->query("bld/laozhe") == 1 )
   {
        if (random(50)>20)
          { 
                if (environment())
          message("sound", HIW"啸天犬"NOR+"就地一滚不敢乱动了。\n\n", environment());
             this_player()->remove_all_killer();
             ob->remove_all_killer();
             ob->set("bld/dog",1);
             }
             else {  
                 if (environment())
              message("sound", HIW"啸天犬"NOR+"就地一滚就爬了起来。\n\n", environment());}
             }
  }

void unconcious()
{
  die ();  
}
