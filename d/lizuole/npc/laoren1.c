
/* <SecCrypt CPL V3R05> */
 
// laoren.c
//ssdd...10/23/99.
//lizuole 99.11.12
#include <ansi.h>
#include <login.h>
inherit NPC;

void create()
{
        set_name(HIR"福利老人"NOR, ({"lao ren","laoren","ren"}));
        set("title",HIC"神的使者"NOR);
        set("gender", "男性" );
        set("age", 168);
        set("class","taoist");
        set("long", "这位老人看上去一百多岁，又长又白的发须直落到地，慈祥的目光中带着亲切。\n");
        set("combat_exp", 8000);
        set("attitude", "peaceful");
        set_skill("unarmed", 1000);
        set_skill("dodge", 2000);
        set_skill("parry", 2000);
        set_skill("literate", 500);
        set_skill("spells", 5000);
        set("per", 150);
        set("max_kee", 3500);
        set("max_gin", 3000);
        set("max_sen", 3000);
        set("max_mana", 2000);
        set("mana", 2000);
        set("mana_factor", 500);
        setup();
      //  carry_object("/d/obj/cloth/choupao")->wear();
        carry_object("/d/obj/cloth/linen")->wear();
       // carry_object("/d/obj/book/chunyang")->tear();
}

void init()
{
        object ob;

        ::init();
        set("chat_chance", 3);
        set("inquiry", ([
                "name" : "老夫是天神派来的使者．．．嘿嘿。\n",
                "here" : "你没来过长安？这地方可是天下第一繁华所在。\n", 
   ]) );

        set("chat_msg", ({
                "福利老人高声说：新来的玩家可以到我这里来领福利。\n",   
                //"福利老人上上下下打量了你几眼。\n",
                "福利老人高声说：新玩家快来领福利呀！\n",
                "福利老人晃了晃酒瓶，笑道：我这人没别的毛病，就是好点这个。\n",

       }) );
}

/*int accept_object(object me, object ob)
{
   object xiannidan;

     if ((string)ob->query("name")!="桂花酒袋") {
            command("say 你太客气了，不过吗。。。。。");
     command("give " + ob->query("id") + "to " + me->query("id"));
            return 1;
        }
        else {
     command("u&me " + me->query("id"));
            command("say 这位" + RANK_D->query_respect(me) + "你向天神奉献出了诚意。\n你的诚意感动了天神，他决定给你一颗陷泥丹。\n");
           carry_object("/d/obj/book/chunyang");
           command("give book to " + me->query("id"));
            return 1;
        }
}  */
/*int accept_object(object me, object ob)
{
   object nowords;
   if ( me->query("xnd") == "吃过了" ){
  	  command("kick " + me->query("id"));
          command("say 我都给过你了，还想上我这来骗？");
          //command("give " + ob->query("id") + "to " + me->query("id"));
          return 1;}
    else{        
     if ((string)ob->query("name")!="桂花酒袋") {
            command("say 不敢当不敢当．．．您太客气了。");
            command("give " + ob->query("id") + "to " + me->query("id"));
            return 1;
        }
        else {
            command("u&me " + me->query("id"));
            command("say 这位" + RANK_D->query_respect(me) + "你向天神奉献出了诚意。\n你的诚意感动了天神，他决定给你一颗陷泥丹。\n");
           carry_object("/d/obj/book/nowords");
           command("give nowords to " + me->query("id"));
           me->set("xnd", "吃过了");
            return 1;
        }
       } 
}*/

int accept_object(object me, object ob)
{
   object xnd;
 
     if ((string)ob->query("name")!="桂花酒袋") {
            command("say 呵呵，你到是挺会拍马屁呦。");
            //command("give " + ob->query("id") + "to " + me->query("id"));
            return 1;
        }
        else {
           if ( me->query("xndf") == "发过了" ){
  	       command("kick " + me->query("id"));
               command("say 我都给过你了，还想上我这来骗？\n你要是再来骗我，我可要不客气了!");
               command("say 不过看在你会拍我老人家的马屁份上就饶你这一回,下不为例呀!");
               return 1;}
	     else{
               command("u&me " + me->query("id"));
               command("say 这位" + RANK_D->query_respect(me) + "你向天神奉献出了诚意。\n" + me->query("name") + "的诚意感动了天神，他决定给" + me->query("name") + "一颗陷泥丹。\n");
               carry_object("/obj/xnd");
               command("give xnd to " + me->query("id"));
               me->set("xndf", "发过了");
               return 1;
                 }
             } 
}

