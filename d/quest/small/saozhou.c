// saozhou
// by mudring Dec/22/2002

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("大扫帚", ({"sao zhou", "saozhou"}));
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "把");
        set("no_drop","自己是扫大街的都乱扔东西？\n");
        set("no_sell","这么脏的东西谁要？\n");
        set("no_put",1);
        set("long", "这是一把大扫帚，你可以用它来扫(sao)大街。\n");
        set("value", 100);
    }
    setup();
}

void init()
{
    add_action("do_saojie", "sao");
    add_action("do_saojie", "saojie");
}

int do_saojie(string arg)
{
    int t;
    object me = this_player();
    object env = environment(me);

    if (!arg || arg != "here")
        return notify_fail("你想干什么？\n");  

    if (!env->query("outdoors"))
        return notify_fail("你是扫大街还是帮人家做钟点工呀？\n");

/*
    if (env->query("outdoors") != "changan")
        return notify_fail("你的任务是清扫长安街道吧！？\n");
*/

    if (time() - env->query_temp("last_sao") < 30)
        return notify_fail("现在这儿很干净呢！\n");

    if (me->is_busy())
        return notify_fail("你现在正忙着呢！\n");

    if (me->is_fighting())
        return notify_fail("边打架边扫大街？你超人啊！\n");

    if (me->query("sen") < 100 || me->query("kee") < 100)
        return notify_fail("你太累了，还是先休息一会吧！\n");

    tell_object (me,"你看了看四周，然后开始扫大街！\n"NOR);

    if (me->query("daoxing") > 20000 || me->query("combat_exp") > 20000)
    {
        tell_object (me,"常做义务工，你真伟大，不过好象有一些丢人！！\n"NOR);
        me->add("potential", 5 + random(6));
        if (me->query("weiwang") > 5) me->add("weiwang", -5);
    } else
    {
        tell_object (me,"看了看很脏的地面，想想还要糊口，你极不情愿的开始打扫！！\n"NOR);
        me->add("daoxing", 10 + random(15));
        me->add("combat_exp", 10 + random(15));
        me->add("potential", 5 + random(10));
    }

    message_vision(HIC"$N拿起大扫帚开始在大街上卖力的扫了起来！\n"NOR,me);

    if (!random(3))
    {
        MONEY_D->pay_player(me, 70 + random(30));
        tell_object (me,HIY"突然发现地上有一些铜板，你赶紧检了起来纳入怀中！\n"NOR);
    }
    env->set_temp("last_sao",  time());
    me->start_busy(5);
    t++;

    if (t > (20 + random(10)))
    {
        message_vision("扫帚已经磨损的不行了，看来得去要个新的了。\n",me); 
        message_vision("你将破烂的扫帚扔在地上，扫帚消失了。\n",me); 
        call_out("dest", 2);
    }
    return 1;
}

void dest()
{   
    if (this_object())
        destruct(this_object());
}

