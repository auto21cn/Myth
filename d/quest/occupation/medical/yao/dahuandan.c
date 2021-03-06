// dahuandan.c 大还丹

#include <ansi.h>
inherit ITEM;

void init()
{                                      
        add_action("do_eat", "eat");
        add_action("do_drop","drop");
}

void create()
{
        set_name(HIR "大还丹" NOR, ({"dahuan dan", "dan"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "一粒大还丹，据说有起死回生之效。\n");
                set("value", 2000);
                set("no_sell",1);
                set("drug_type", "补品");
        }
        set("is_monitored", 1);
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if (!id(arg))
                return notify_fail("你要吃什么？\n");

        me->add("combat_exp", (int)me->query("combat_exp") / 40);
        if( (int)me->query("potential") > (int)me->query("learned_points"))
                me->add("potential",(int)me->query("potential") - (int)me->query("learned_points") );
        me->skill_death_recover();
        me->add("daoxing",me->query("death/dx_loss"));
        me->save();

        if( userp(me) ) log_file("RECOVER", sprintf("%s(%s) Got recovered on %s.\n", me->name(1), geteuid(me), ctime(time()) ) );

        message_vision(HIR "\n$N吃下一粒大还丹，硬是从白无常那里逃脱，捡回了一条小命。\n\n" NOR, me);
        destruct(this_object());
        return 1;
}

int do_drop(string arg)
{
        object ob = this_object();
        object me = this_player();
        
        if(arg == "dahuan dan" || arg == "dan"){
                message_vision("好可惜呀，这么珍贵的药就这样被"+me->query("name")+"随手扔掉了，"+ob->query("name")+"转眼间就消失的无影无踪。\n",me,ob); 
                destruct(ob);
        }
        return 1;
}
