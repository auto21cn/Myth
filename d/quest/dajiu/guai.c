// guai.c
// modify by mudring

#include <ansi.h>

inherit JOBNPC;

object owner() {return query("owner");}
void leave();
#include "guai.h"

string *names = ({
  "黑衣", "红衣", "白衣", "紫衣",
  "闪电", "雷霆", "追风", "采云",
});

void setname()
{
    int i;
    string name;
    i = random(sizeof(names));
    name = names[i] + (random(2)?"杀手":"刺客");
    set_name(name, ({"attacker"}));
}

void create()
{        
    setname();
    set("age", 100+random(80));
    set("gender", random(2)?"男性":"女性");
    set("attitude", "heroism");
    set("food", 10000);
    set("water", 10000);
    set_weight(30000);
    set("no_steal",1);
    set("taskguai",1);
    set("chat_chance", 5);
    setup();
}

void kill_owner(object ob)
{
    command("say 想跑？没那么容易！");
    kill_ob(ob);
}

void init()
{
    if (this_player() == owner())
        call_out("kill_owner", 0, owner());
    add_action("do_no", "fight");
    add_action("do_no", "kill");
    add_action("do_no", "steal");
//    add_action("do_no", "cast");
    add_action("do_no","ji");
    add_action("do_no","throw");
}

int do_no(string arg)
{
    object who = this_player();
    object me = this_object();

    if (arg != "attacker") return 1;
    if (!userp(who)) return 1;
    if (who != owner())
    {
        message_vision(CYN"$N说道：你不怕死就滚！。\n"NOR,me);
        return 1;
    } 

    me->kill_ob(who);
    return 0;
}

void heart_beat()
{
    object guai = this_object();
    object who = owner();
  
    ::heart_beat();  

    if (living(who) && is_fighting(who))
    {
        if (who->query("env/invisibility"))
        {
            who->delete_temp("yinshentime");
            who->set("env/invisibility",0);
            message_vision(HIW"\n$N吹了口气,$n又现出了身形。\n"NOR, guai,who); 
        }
    }
}       

void unconcious()
{
    die();
}

void leave()
{
    object guai = this_object();

    if (objectp(guai))
    {
        if (environment()) 
        { 
            message("vision",HIB + name() + 
                    "身子一晃，变成一股青烟散去了。\n" NOR, environment());
        }
        guai->move(get_object("/obj/empty"));
        destruct (guai);
    }
    return;
}

