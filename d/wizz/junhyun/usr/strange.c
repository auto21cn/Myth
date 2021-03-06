// 玩家NPC
//by junhyun@SK

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("懿馨"NOR, ({"strange's"}));
        set("title", HIW"三界山"HIY"轮回圣女"NOR);
        set("nickname", MAG"幽冥星尊"NOR);
        set("gender", "女性" );
      set("taskguai",1);
        set("age", 20);
        set("per", 40);
        set("str", 30);
        set("family/family_name", "三界山");
        set("class", "yaomo");
    set("long","
蛇口站资深玩家，高手排行榜前二十名内的佼佼者。\n");

        set("attitude", "friendly");

  set("combat_exp", 100000000);
  set("daoxing", 100000000);

  set_skill("literate", 300);
  set_skill("unarmed", 300);
  set_skill("huxiaoquan", 300);
  set_skill("force", 300);
  set_skill("huntianforce", 300);
  set_skill("sword", 300);
  set_skill("huxiaojian", 300);
  set_skill("blade", 300);
  set_skill("zileidao", 300);
  set_skill("parry", 300);
  set_skill("dodge", 300);
  set_skill("zhaoyangbu", 300);
  set_skill("spells", 300);
  set_skill("tianmogong", 300);

  map_skill("force", "huntianforce");
  map_skill("spells", "tianmogong");
  map_skill("sword", "huxiaojian");
  map_skill("parry", "huxiaojian");
  map_skill("dodge", "zhaoyangbu");
  map_skill("blade", "zileidao");

  set("max_sen", 7000);
  set("max_kee", 7000);
  set("force", 16000); 
  set("max_force", 8000);
  set("force_factor", 100);
  set("max_mana", 8000);
  set("mana", 16000);
  set("mana_factor", 100);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
               (: perform_action, "sword", "dunnotruth" :), 
        }) );
  set_temp("apply/armor", 50);
  set_temp("apply/dodge", 50);

  setup();
  carry_object("/d/obj/weapon/sword/qingfeng.c")->wield();
}

