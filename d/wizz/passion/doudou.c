inherit NPC;

int give_dan();

#define UPPLAYER   "/cmds/wiz/update"

#include <ansi.h>

void create()

{

  set_name("大唐欢迎大使", ({ "doudou" }) );

        set("gender", "女性" );

      set("color", HIR); 

         set("age", 9);

        set("age", 20);

           set("title", HIY "痴"+ HIR "情" + HIM "大" + HIC"唐" NOR);

        set("long",

                HIM "MUD为不辞劳苦,希望大家完的高兴\n" NOR);

        set("combat_exp", 5000000);

        set("attitude", "friendly");

        set("per",50);

        set_skill("unarmed",200);

            set_skill("dodge",200);

        set("inquiry", ([

                "大唐" : (: give_dan :),

            ]));

        setup();

}

int give_dan()

{

object dan;

object who;

who = this_player();

if (!userp(who))

{

command("heng");

command("say 什么小猫小狗也来要礼物啊？！");

command("qi");

return 1;

}

         if ((string)this_player()->query("passionset")=="1")

{

          message_vision("$N对着$n哼了一声。\n",this_object(),this_player());

       command("say 你是谁呀，好象登记过了呀！");

  return 1;

}

if ( who->query("mudage") < 6100 ) 
{
who->set("title","大唐");
message_vision(HIY"$N浑身散发耀眼的金光!\n$N手一指，金光笼罩在$n身上。\n"NOR,this_object(),this_player());
message_vision(HIW"欢迎$n来到三界蛇口站,祝$n在本站完的高兴。\n"NOR,this_object(),this_player());
who->set("passionset","1");
UPPLAYER->update_player(who);
 return 0;
}




/*
message_vision(HIY"$N浑身散发耀眼的金光!\n$N手一指，金光笼罩在$n身上。\n"NOR,this_object(),this_player());

message_vision(HIW"欢迎$n来到三界蛇口站,祝$n在本站完的高兴。\n"NOR,this_object(),this_player());

who->set("passionset","1");

UPPLAYER->update_player(who);

*/
message_vision(HIW"你不是新人了，继续努力吧。\n"NOR,this_object(),this_player());
 return 1;

}




