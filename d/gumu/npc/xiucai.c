//轩辕古墓三代师傅
inherit NPC;
inherit F_SAVE;  
#include <ansi.h>
inherit F_MASTER;
int rank_me();
#include <ansi.h>

void create()
{
       set_name("林秀才", ({"lin xiucai", "lin", "xiucai","master"}));
       set("long",
"一只修炼百年成精的小狐仙，变成人后醉心功名利禄，
可惜屡考不中，只弄个秀才的头名。\n");
       set("title", "小狐仙");
       set("gender", "男性");
       set("age", 28);
       set("class", "yaomo");
       set("attitude", "friendly");
       set("rank_info/respect", "先生");
       set("per", 40);
        set("int", 30);
       set("max_kee", 500);
       set("max_gin", 500);
       set("force", 500);
       set("max_force", 500); 
       set("force_factor", 20);
       set("max_mana", 300);
       set("mana", 300);
       set("mana_factor", 20);
       set("combat_exp", 200000);
  set("daoxing", 100000);


        set("eff_dx", 70000);
        set("nkgain", 260);

       set_skill("literate", 20);
       set_skill("unarmed", 50);
       set_skill("dodge", 80);
       set_skill("force", 50);
       set_skill("parry", 50);
       set_skill("sword", 50);
       set_skill("spells", 50);
        set_skill("youming-spells", 60);
        set_skill("jiuyin-zhua", 60);
        set_skill("qinghu-jian", 60);
        set_skill("jiuyin-force", 60);
        set_skill("kongming-steps", 60);
        map_skill("spells", "youming-spells");
        map_skill("unarmed", "jiuyin-zhua");
        map_skill("force", "jiuyin-force");
        map_skill("sword", "qinghu-jian");
        map_skill("parry", "snowsword");
        map_skill("dodge", "kongming-steps");
        set("inquiry", ([

         "职位": (: rank_me :),
                ]) );
create_family("轩辕古墓", 3, "弟子");
setup();

        carry_object("/d/obj/cloth/baipao")->wear();
      //  carry_object("/d/moon/obj/guihuajian")->wield();
}

int rank_me()
{
        object me=this_player();
        int exp;
        exp=(int)me->query("combat_exp");
        if( me->query("title") == "古墓主人")
                return notify_fail("你已经是掌门人了，还来要什么职位．\n");
        if( me->query("gender") == "女性")
                return notify_fail("你想变性啊？\n");
        if( (string)me->query("family/family_name") == "轩辕古墓"){
                if( exp <= 100000 ){
                        me->set("title", HIW"轩辕古墓"HIG"小狐仙"NOR);
                  } else if(exp <= 3000000 ){
                        me->set("title", HIW"轩辕古墓"HIM"百变狐妖"NOR);
                  } else if(exp <= 5000000 ){
                        me->set("title", HIW"轩辕古墓"HIM"长生狐仙"NOR);
                  } else if(exp <= 15000000 ){
                        me->set("title", HIW"轩辕古墓"HIR"乱世妖仙"NOR);
                } else {
                        me->set("title", HIW"女娲坐下"HIB"九天神将"NOR);
                }

                tell_object(me, "林秀才对你说：你可以做"+me->query("title")+"。\n"
);
                tell_room(environment(me),
"林秀才对"+me->query("name")+"说：你可以做"+me->query("title")+"。\n", ({me, me}));
     me->save();  
        }
return 1;  
}
void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="男性")){
           command("shake");
           command("say 我只收男徒，这位" +
RANK_D->query_respect(ob) + "还是去媚娘那里试试吧。\n");
           return;
        }

        command("nod "+ob->query("id"));
        command("pat "+ob->query("id"));
        command("say 不错，" + RANK_D->query_respect(ob) +
"以后有前途啊！要多加努力！\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "yaomo");

}


