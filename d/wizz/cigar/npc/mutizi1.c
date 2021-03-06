// 九重天神 "四重天神 木提子" by Calvin

#define DEBUG 0
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string expell_me(object me);

void create()
{
   set_name(CYN"木提子"NOR, ({"mu tizi", "mu", "tizi","mutizi","tianshen","si"}));
   set("title", CYN"雅木查"NOR);
   set("gender", "男性" );
   set("age", 100);
   set("per", 24);
   set("str", 30);
   set("long", "此乃镇元大仙的结拜义兄,前生是先天界的一棵青木。\n");
   set("class", "xian");
   set("combat_exp", 5600000);
   set("attitude", "peaceful");
   create_family("五庄观", 1, "祖师");
   set("rank_info/respect", "木尊");

   set_skill("unarmed", 350);
   set_skill("wuxing-quan", 350);
   set_skill("dodge", 350);
   set_skill("baguazhen", 350);
   set_skill("parry", 350);
   set_skill("sword", 350);
   set_skill("sanqing-jian", 350);
   set_skill("staff", 350);
   set_skill("fumo-zhang", 350);
   set_skill("hammer", 350);
   set_skill("xiaofeng-sword", 350);
   set_skill("kaishan-chui", 350);
   set_skill("blade", 350);
   set_skill("yange-blade", 350);
   set_skill("force", 350);   
   set_skill("zhenyuan-force", 350);
   set_skill("literate", 350);
   set_skill("spells", 350);
   set_skill("taiyi", 350);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "sanqing-jian");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");

   set("max_kee", 6000);
   set("max_sen", 6000);
   set("force", 5000);
   set("max_force", 2500);
   set("mana", 7000);
   set("max_mana", 3500);   
   set("force_factor", 200);
   set("mana_factor", 200);

   set("spell_qiankun_on", 1);
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
     (: cast_spell, "zhenhuo" :),
     (: cast_spell, "qiankun" :),
   }) );
  setup();
      carry_object("/d/9ct/zb/tianjia")->wear();
//   carry_object("/d/9ct/zb/")->wield();
}

void attempt_apprentice(object ob)
{
   if( (string)ob->query("class")=="dao" )
     command("say 好，好！道仙本一家。\n");

   if( (string)ob->query("family/family_name")=="五庄观" )
   {
     if( (int)ob->query("family/generation") > 3   )
     {
        command("say 五庄观门下正在招纳贤才,你还是去那看看吧。\n");
     }
     else 
     {
        if( (int)ob->query("combat_exp") >= 300000 && (int)ob->query_skill("taiyi", 1) >= 120 )
        {
          command("nod ");
          command("say 好，" + RANK_D->query_respect(ob) + "不愧是本门的人才！\n");
          command("recruit " + ob->query("id") );
ob->set("title",HIR"五庄观乘云阁主"NOR);
        }
        else
        {
          command("say 你的修为是很不错,但是不断的加油才会更好。\n");
        }
     }
   }

   else
   {
     command("nod");
     command("say 这位" + RANK_D->query_respect(ob) + "，你还是先去五庄观看看,学扎实点基础功吧。\n");
   }

   return;
}
