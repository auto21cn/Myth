// 九重天神 "格月瓢彩 红霞" by Calvin

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
       set_name(HIR"红霞"NOR, ({"hong xia", "xia", "hongxia","master","hong","tianshen"}));
       set("long", "相传红霞本是盘丝洞祖师紫青双霞的师傅
但因为其两位徒弟一直的斗呕赌气, 结果
扰乱了天界安宁, 后来其两位弟子被罚做
佛祖灯心,而红霞也被罚守卫九重天。

\n");
       set("title", HIR"格月瓢彩"NOR);
       set("gender", "女性");
       set("age", 20);
       set("class","xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙子");
       set("cor", 30);
       set("per", 40);
       set("max_kee", 6000);
       set("max_gin", 800);
       set("max_sen", 6000);
       set("force", 5000);
       set("max_force", 3000);
       set("force_factor", 125);
       set("max_mana", 2500);
       set("mana", 5000);
       set("mana_factor", 250);
       set("combat_exp", 5000000);
           set("daoxing", 5000000);

       set_skill("literate", 350);
       set_skill("unarmed", 350);
       set_skill("dodge", 350);
       set_skill("force", 350);
       set_skill("parry", 350);
       set_skill("sword", 350);
       set_skill("spells", 350);
       set_skill("whip", 350);
   set_skill("pansi-dafa", 350);
   set_skill("lanhua-shou", 350);
   set_skill("jiuyin-xinjing", 350);
   set_skill("chixin-jian", 350);
   set_skill("qin", 350);
   set_skill("yueying-wubu", 350);
   set_skill("yinsuo-jinling", 350);
   map_skill("spells", "pansi-dafa");
   map_skill("unarmed", "lanhua-shou");
   map_skill("force", "jiuyin-xinjing");
   map_skill("sword", "chixin-jian");
   map_skill("parry", "yinsuo-jinling");
   map_skill("dodge", "yueying-wubu");
   map_skill("whip", "yinsuo-jinling");
        set("chat_msg_combat", ({
                (: cast_spell, "wuzhishan" :),
                (: cast_spell, "ziqi" :)
        }) );
create_family("盘丝洞", 1, "红");
setup();

        carry_object("/d/9ct/zb/xue")->wear();
        carry_object("/d/9ct/zb/zhaoxia")->wield();
}

void attempt_apprentice(object ob)
{
  if ( (string)ob->query("family/family_name")=="盘丝洞") {
   if (((int)ob->query("combat_exp") < 2000000 )) {
   command("say " + RANK_D->query_respect(ob) +
"的修行不够彻底，继续学习可能有所困难。\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，并珍惜这一切,莫再有紫青双霞这样勾心斗角。\n");
       command("recruit " + ob->query("id") );
           ob->set("title", HIM"花果山盘丝小仙"NOR);
           ob->set("class", "xian");
   return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"还是先去学些基础功夫吧。\n");
        return;
}

