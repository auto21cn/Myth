// ling.c
// 令牌
// by mudring

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(HIG"令牌"NOR, ({ "tongchuan ling", "ling pai", "ling", }));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "个");
        set("long","这是朝廷用来传唤重要人物用的御赐金令。\n");
        set("value", 0);
        set("material", "gold");
        set("no_drop",1);
        set("no_put",1);
        set("no_give",1);
    }
}

void init()
{        
    add_action("do_send", "tongchuan");
    add_action("do_send", "chuanhuan");
    add_action("do_look", "kan");
    add_action("do_look", "chakan");
    call_out("dest", random(100)+600);
}

int do_look(string arg)
{
    object me = this_player();

    if (!arg) return 0;
    if ((arg=="ling pai" || arg=="ling" || arg=="tongchuan ling")
        && query("owner") == me
        && me->query_temp("tongchuan/get")
        && me->query_temp("tongchuan/name")
        && me->query_temp("tongchuan/id"))
    {
        tell_object(me, "你目前的任务是要去传唤" +
            me->query_temp("tongchuan/name") + "进殿！\n");
        return 1;
    }
    else return 0;
}

int do_send(string arg)
{
    int i, k;
    object me, target;
    string msg;

    me = this_player();
        
    if (!arg) return notify_fail("你要传唤谁？\n");
    if (!objectp(target = present(arg, environment(me)))) 
        return notify_fail("看清楚点，你要传唤的人不在这里！\n");
        
    if (userp(target)) 
        return notify_fail("嘿嘿，想作弊？那可要等没巫师的时候。。。\n");
        
    if (!living(target)) 
        return notify_fail("看清楚点，那人可以说话吗？\n");
                 
    message_vision("$N从怀中掏出一个御赐令牌。\n",me);
    message_vision(HIY"$N朝$n长声道：御旨到，将御赐金令呈在$n面前说道，"
        "太宗皇帝让"+RANK_D->query_self(me)+"转告您，请您速速进殿。\n"NOR, me, target);

    if (!me->query_temp("tongchuan/get"))
    {
        message_vision(CYN"$N道：你不是天朝传令使，怎么会有御赐金令？\n"NOR, target);
        return notify_fail("对方不理睬你的传唤。\n");
    }
    if (target->query("id") != me->query_temp("tongchuan/id")
        || target->query("name") != me->query_temp("tongchuan/name"))
    {
         message_vision(CYN"$N道：皇帝老儿与我素无来往，找我干什么？\n"NOR, target);
         return notify_fail("对方不理睬你的传唤。\n");
    }        
    if (query("owner") != me)
    {
         message_vision(CYN"$N道：这是大唐天朝的御赐金令，你是从哪儿抢来的？\n"NOR, target);
         this_object()->move(target);
         message_vision("$N将你手中的令牌没收了。\n", target);
         return 1;
    } else
    {
        message_vision(HIY "$N双手捧过金令说道：这位"+RANK_D->query_respect(me)
            +"您先行一步，我随后就到。\n"NOR, target, me);
/*
        target->command("job " + me->query("name") + 
            "奉御旨传唤" + target->query("name") + "进殿！");
*/
    }

    i = me->query("office_number");
    if (i < 800 )
    {
        i = 1000 + random(100) + i / 3;
    } else
    { 
        i = 1200 + random(200) + i / 5;
        if (i > 3000) i = 3000;
    }

    k = me->query_temp("tongchuan/kk");
    if (!k)
        i = i / 20;
    else
        i = i * k / 3;
    if (me->query("combat_exp") > 10000000)
        i = i / 3 * 5;
    me->add("combat_exp", i);
    me->add("daoxing", i);
    me->add("potential", i / 8);
    me->add("office_number", 1);
    me->add("weiwang", 1);
    tell_object(me, HIW"在此次行动中，你领悟到了"+chinese_number(i)+
        "点武学"+chinese_daoxing(i)+"道行以及"+chinese_number(i/8)+"点潜质。\n"NOR);
    tell_object(me, HIW"为朝廷出力，你的官职增加了。\n"NOR);

    msg = " do tongchuan got " + i + " exp " + i/8 +" pot ";
    MONITOR_D->report_debug_object_msg(me, msg);
    MONITOR_D->mudring_log("tcjob", me, msg);

    me->delete_temp("tongchuan");
    me->clear_condition("tongchuan_job");
    if (me->query("combat_exp") < 10000)
        me->apply_condition("job_busy", 5);
    else
        me->apply_condition("job_busy", 5 + random(5));

    this_object()->move(get_object("/obj/empty"));
    call_out("dest", 2);
    return 1;
}

void dest()
{
    object ob = this_object();

    if (ob)
    {
        message_vision("$N忽然掉落在路上不见了。\n", ob);  
        destruct(ob);
    }
}

