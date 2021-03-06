//
//npc--chenxiang

inherit NPC;
#include <ansi.h>

int ask_mother ();

void create()
{
  set_name( HIW "沉香" NOR, ({"chen xiang","chen", "xiang"}));
  set("title",HIC+"神之子"+NOR);

  set("long", HIY"三圣母私下天庭和凡人所生之子。据说此子天资聪慧，力大无穷，专门帮助弱小者，
认识他的人都喜欢他！\n"NOR);

  set("gender", "男性");
  set("attitude", "peaceful");
  set("class", "xian");
  set("age", 16);
  set("str", 40+random(10));
  set("int", 30);
  set("per", 26+random(4));
  set("con", 20);
  set("max_kee", 6000);
  set("max_sen", 6000);
  set("max_force", 20000);
  set("force", 20000);
  set("force_factor", 500);
  set("max_mana", 20000);
  set("mana", 20000);
  set("mana_factor", 500);
  set("combat_exp", 12000000);
  set("daoxing", 12000000);

  set("chat_chance_combat", 70);
  set("chat_msg_combat", ({
                (: cast_spell, "bighammer" :),
        }) );

  create_family("南海普陀山", 2, "弟子");


  set("inquiry", ([
    "三圣母" : (: ask_mother :),
    "sanshengmu" : (: ask_mother :),
    "gshengmu" : (: ask_mother :),
    "母亲" : (: ask_mother :),
    "妈妈" : (: ask_mother :),
   "mother" : (: ask_mother :),


  ]) );

  set_skill("force", 250);
  set_skill("unarmed", 250);
  set_skill("dodge", 250);
  set_skill("parry", 250);
  set_skill("staff", 250);
  set_skill("lotusforce", 250);
  set_skill("lunhui-zhang", 250);
  set_skill("jienan-zhi", 250);
  set_skill("lotusmove", 250);
  set_skill("spells",250);
  set_skill("buddhism",250);
  map_skill("spells","buddhism");
  map_skill("dodge", "lotusmove");
  map_skill("unarmed", "jienan-zhi");
  map_skill("staff", "lunhui-zhang");
  map_skill("parry", "lunhui-zhang");
  map_skill("force", "lotusforce");

  setup();
  
  add_money("gold", 2);

  carry_object("/d/obj/armor/jinjia")->wear();
  carry_object("/d/nanhai/obj/budd_staff")->wield();

}


void relay_emote(object ob, string verb)
{
        if( ob->query("id") == "shao") return;
        command("slap "+ob->query("id"));
}


int ask_mother ()
{

  if ( this_player()->query("bld/monkey") != 1) {
       command("heng");
       command("say 不要瞎问！ \n");
       command("hammer "+this_player()->query("id") );
       return 1;}

  if ( this_player()->query("bld/mother")  == 1) {
       command("say 你怎么这么烦？不是告诉你了吗？ \n");
       command("say 不要来捣乱！ \n");
       return 1;}
  
  command("say 我妈妈被二郎神抓走了，我要去救她。 \n");
  command("say 要救他必须找到神斧和宝莲灯，可我怎么都找不到。 \n");
  command("sigh");
  command("say 神斧在华山一位老头那儿，宝莲灯在月宫。 \n");
  command("say 如果你帮我救出妈妈，我一定谢你！ \n");
  command("say 不说了，我要去找那两样宝贝了，走了。 \n");
  message_vision("$N化做一只大鸟飞上天去。\n", this_object());

  this_player()->set("bld/mother",1);
  destruct(this_object());
        
       return 1;
}

void die()
{
  if (environment())
    message("sound", HIW "沉香" NOR+"轻轻一笑,根本不把你放在眼里。\n\n", environment());

  set("eff_kee", 6000);
  set("eff_gin", 6000);
  set("eff_sen", 6000);
  set("kee", 6000);
  set("gin", 6000);
  set("sen", 6000);
  set("force", 20000);
  set("mana", 20000);
}

void unconcious()
{
  die ();
}

