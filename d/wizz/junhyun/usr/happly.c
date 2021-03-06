// 玩家NPC
//by junhyun@SK

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("叶心"NOR, ({"happly's"}));
        set("title", HIW"寒月宫月影如水"NOR);
        set("nickname", HIM"惊虹舞姬"NOR);
        set("gender", "女性" );
      set("taskguai",1);
        set("age", 20);
        set("per", 40);
        set("str", 30);
        set("family/family_name", "月宫");
        set("class", "xian");
    set("long","
蛇口站资深玩家，高手排行榜前二十名内的佼佼者。
\n");

        set("attitude", "friendly");

  set("combat_exp", 68000000);
  set("daoxing", 60000000);

  set_skill("literate", 300);
  set_skill("unarmed", 300);
  set_skill("baihua-zhang", 300);
  set_skill("force", 300);
  set_skill("moonforce", 300);
  set_skill("sword", 300);
  set_skill("snowsword", 300);
  set_skill("blade", 300);
  set_skill("xuanhu-blade", 300);
  set_skill("parry", 300);
  set_skill("dodge", 300);
  set_skill("moondance", 300);
  set_skill("spells", 300);
  set_skill("moonshentong", 300);

  map_skill("force", "moonforce");
  map_skill("spells", "moonshentong");
  map_skill("sword", "snowsword");
  map_skill("parry", "snowsword");
  map_skill("dodge", "moondance");
  map_skill("blade", "xuanhu-blade");

  set("max_sen", 10000);
  set("max_kee", 10000);
  set("force", 16400); 
  set("max_force", 8200);
  set("force_factor", 500);
  set("max_mana", 6500);
  set("mana", 13000);
  set("mana_factor", 500);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
               (: perform_action, "sword", "tian" :), 
        }) );
  set_temp("apply/armor", 50);
  set_temp("apply/dodge", 50);

  setup();
  carry_object("/d/obj/weapon/sword/qingfeng.c")->wield();
}

