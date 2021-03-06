// suicide.c
// modify by mudring

#include <ansi.h>

inherit F_CLEAN_UP;

private int slow_suicide(object me);
private int halt_suicide(object me);

int main(object me, string arg)
{
    object *inv;
    int i;

    if (me->is_busy())
        return notify_fail("你上一个动作还没完成。\n");

    inv = deep_inventory(me);
    for (i = 0; i < sizeof(inv); i++)
    {
        if (!userp(inv[i]) && !playerp(inv[i])) continue;
            return notify_fail("你身上还有个大活人呢，想不开也别急呀？\n");
    }

    if (!arg) 
    {
        write("你重新投胎。\n");
        return 1;
    }

    if (arg != "-f") 
        return notify_fail("自杀有两种，您是要永远死掉(-f)还是重新投胎？\n");

    if (wizardp(me))
        return notify_fail("请不要自杀掉巫师帐号，谢谢！\n");
    if (me->query("club_master")) 
        return notify_fail("作为帮会领导人怎么可以轻言生死。？\n"); 

    write("您选择永远死掉的自杀方式，这个人物的资料将永远删除，请务必\n"
        "考虑清楚，确定的话请输入您的管理密码：");
    input_to("check_password", 1, me, 1);
    return 1;
}

private void check_password(string passwd, object me, int forever)
{
    object link_ob;
    string old_pass;

    link_ob = me->query_temp("link_ob");
    old_pass = link_ob->query("ad_password");
    if (!stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
    {
        write(HIR "密码错误！请注意，自杀必须输入管理密码。\n"NOR);
        return;
    }

    if (forever)
    {
        tell_object(me, HIR "\n你决定要自杀了，如果三十秒"
            "钟内不后悔，就真的永别了。\n\n" NOR);
        me->set_temp("suicide/time", time());
        me->set_temp("suicide/last", 0);
        me->set_temp("suicide/from", query_ip_number(me));
        me->start_busy((: slow_suicide, me :),
            (: halt_suicide, me :));
    }
}

private int slow_suicide(object me)
{
    object link_ob;
    int t, s_time;
    string myid, couple;

    if (!objectp(me))
        return 0;

    t = time() - me->query_temp("suicide/time");
    if (t < me->query_temp("suicide/last"))
    {
        me->delete_temp("suicide/");
        return 0;
    }

    if (t < 30)
    {
        if (t - me->query_temp("suicide/last") < 5)
            return 1;

        tell_object(me, HIR "\n你还有" + chinese_number(30 - t) +
            "秒钟仔细考虑(" HIC "halt停止" HIR ")。\n\n"HIG"        三界神话蛇口站全体人员奉劝你请不要轻言自杀!\n" NOR);
        me->set_temp("suicide/last", t / 5 * 5);
        return 1;
    }

    link_ob = me->query_temp("link_ob");
    if (!link_ob || !interactive(me)) return 0;

    log_file("static/suicide",
        sprintf("%s %s commits a suicide from %s\n",
            log_time(), log_id(me),
            me->query_temp("suicide/from")));

    seteuid(getuid());
    write("\n好吧，永别了:)。\n\n");
    write(HIG"无论如何,三界神话还是欢迎你再来!\n"
        HIB"牢记: 61.141.216.74 8383\n"HIM"好吧，永别了:( \n");
    CHANNEL_D->do_channel(this_object(), "rumor",
        sprintf("%s自杀了，以后你再也看不到这个人了。", me->name()));

    tell_room(environment(me), me->name() +
        "在你的面前化作轻烟，渐渐消失了...\n", ({me}));

    if (me->query("combat_exp") < 500000)
    {
// suicide not remove name,,, because can recovers...
        NAME_D->remove_name(me->query("name"), me->query("id"));
        rm( link_ob->query_save_file() + __SAVE_EXTENSION__ );
        rm( me->query_save_file() + __SAVE_EXTENSION__ );
    }
    else
    {
        link_ob->save();
        if (!environment(me)->query("no_save") && !me->is_ghost())
            me->set("startroom", base_name(environment(me)));
        if (me->query("club"))
            me->delete("club");

        if (s_time = me->query("suicide_time"))
            me->add("suicide_time", 1);
        else
            me->set("suicide_time", 1);
        if (s_time >= 10)
            s_time = 10;

        me->set("balance",0);
        me->add("potential", - me->query("potential"));
        me->set("daoxing", me->query("daoxing") / 10 * (10-s_time));
        me->set("combat_exp", me->query("combat_exp") / 10 * (10-s_time));
        me->save();

        rename( link_ob->query_save_file() + __SAVE_EXTENSION__, link_ob->query_save_file() + ".s.o" );
        rename( me->query_save_file() + __SAVE_EXTENSION__, me->query_save_file() + ".s.o" );
    }

    myid=me->query("id");

    // remove player home.
    rm( "/data/playerhomes/h_"+myid+ __SAVE_EXTENSION__ );

    // remove mailbox.
    rm( "/data/mail/"+myid[0..0]+"/"+myid+ __SAVE_EXTENSION__ );

    // remove couple's home as well. (the home is registered by the 
    // couple.)
    couple=me->query("coupld/id");
    if(couple)
        rm("/data/mail/"+couple[0..0]+"/"+couple+__SAVE_EXTENSION__);

    destruct(me);

    return 0;
}

private int halt_suicide(object me)
{
    tell_object(me, HIG "你打消了寻死的念头。\n" NOR);
    me->delete_temp("suicide");
    return 1;
}

int help (object me)
{
        write(@HELP
指令格式: suicide [-f]
 
如果因为某种原因你不想活了, 你可以选择自杀.
自杀分两种:
 
suicide    : 重新投胎
suicide -f : 永远的除去玩家资料, 系统会要求你
             输入密码以确认身份.
 
请慎重选择 :)
 
HELP );
        return 1;
}


