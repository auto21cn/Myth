// 三重天神 "天道明灯 木惠" by Calvin

inherit NPC;
#include <ansi.h>
inherit F_MASTER;

int do_drop(object, object);

void create()
{
           set_name(YEL"木惠"NOR, ({ "mu hui", "tianshen", "muhui","hui","mu" }));
        set("title", YEL"天道明灯"NOR);
        set("long", @LONG
他本是天界一盏神灯,后来因为一点点的过失被罚为下界
在下界的他刻苦修炼,潜心钻道,最终诚得了上天的认可成
为了守护九重天的其中之一天神。
LONG);
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("rank_info/self", "小神");
        set("rank_info/respect", "天祖");
        set("class", "bonze");
                set("str",24);
                set("per",100);
        set("max_kee", 5000);
        set("max_gin", 5000);
        set("max_sen", 5000);
        set("force", 4000);
        set("max_force", 2500);
        set("force_factor", 145);
        set("max_mana", 3000);
        set("mana", 6000);
        set("mana_factor", 150);
        set("combat_exp", 5000000);
        set("daoxing", 5000000);

        set_skill("literate", 350);
        set_skill("spells", 350);
        set_skill("buddhism", 350);
        set_skill("unarmed", 350);
        set_skill("jienan-zhi", 350);
        set_skill("dodge", 350);
        set_skill("lotusmove", 350);
        set_skill("parry", 350);
//        set_skill("huoyun-qiang", 350);
        set_skill("force", 350);
        set_skill("lotusforce", 350);
        set_skill("staff", 350);
        set_skill("lunhui-zhang", 350);
//        set_skill("spear", 350);
//        set_skill("stick", 350);
//        set_skill("buddha-stick", 350);
        map_skill("spells", "buddhism");
        map_skill("unarmed", "jienan-zhi");
        map_skill("dodge", "lotusmove");
        map_skill("force", "lotusforce");
        map_skill("parry", "lunhui-zhang");
        map_skill("staff", "lunhui-zhang");
        map_skill("stick", "buddha-stick");
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: cast_spell, "bighammer" :),
        }) );

        create_family("南海普陀山", 1, "菩萨");

        setup();
        carry_object("/d/9ct/zb/pao")->wear();
        carry_object("/d/9ct/zb/pudu")->wield();
}

void attempt_apprentice(object ob)
{
        if (!((string)ob->query("bonze/class") =="bonze" )) {
                command("say 未入佛门，" + RANK_D->query_respect(ob) + "不可一试啊。\n");
                write("看样子木惠并不喜欢和凡人过多接触。\n");
                return;
        }       
//        if (((int)ob->query_skill("buddhism", 1) < 250 )) {
        if (((int)ob->query_skill("buddhism", 1) < 220 )) {
                command("say " + RANK_D->query_respect(ob) + "不在佛法上苦修，恐怕难成正果。\n");
                return;
        }
        command("pat " + ob->query("id") );
        command("say 好！这才是我佛门的好弟子。只要多加努力，定可早成正果。\n");

        command("recruit " + ob->query("id") );
        ob->set("title",HIW"普陀山天之骄子"NOR);
        return; 
}
void die()
{
        int i;
        string file;
        object *inv;
      if( environment() ) {
        message("sound", "\n\n木惠摇头叹道：刚离迷障，又入魔障，世间疾苦，何人度之！\n\n", environment());
        command("sigh");
        message("sound", "\n木惠叹了声气。\n\n", environment());
        inv = all_inventory(this_object());
        for(i=0; i<sizeof(inv); i++) {
                if (inv[i]->query("no_drop")) continue;
                do_drop(this_object(), inv[i]);
        }
        }

        destruct(this_object());
}

int do_drop(object me, object obj) {
  if (obj->move(environment(me))) {
      if((obj->query_temp("d_mana"))>0) {
            if( obj->query_temp("is_living")==1 )
                 message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
            else {
                 message_vision( sprintf("$N丢下一%s$n。\n",
                 undefinedp(obj->query_temp("unit"))?
                         "个":obj->query_temp("unit")
                        ), me, obj );
           }
      } else {
           if( obj->is_character() )
                  message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
           else {
             message_vision( sprintf("$N丢下一%s$n。\n", obj->query("unit")),
                     me, obj );
             if( !obj->query("value") && !obj->value() ) {
                tell_object(me,"因为这样东西并不值钱，所以人们并不会注意到它的存在
                   。\n");
                destruct(obj);
             }
           }
      }
      return 1;
  }
  return 0;
}


void unconcious()
{
     die();
}

