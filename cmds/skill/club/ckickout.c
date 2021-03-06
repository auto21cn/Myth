//ckickout.c
//Edited by wuyou@sk_sjsj 2003-4-8

#include <ansi.h>

inherit F_CLEAN_UP;

int main(string arg)
{
    string club_name;
    object ob ,me;
    me=this_player();

    if (!me->query("club_master") && !wizardp(me))
        return notify_fail("只有帮会领导人才可以将帮众踢出帮派。\n");

    if (!arg)
        return notify_fail("你要将谁踢出帮派？\n");

    if (sscanf(arg, "%s", arg) == 1)
        ob = present(arg, environment(me));
    else 
        return notify_fail("指令格式：ckickout <某人> \n");

    if (!ob)
        return notify_fail("这里没有这个人。\n");

    if (ob == me && !wizardp(me))
        return notify_fail("如果你自己想离开帮派，请用leaveclub命令。\n");

    if (!userp(ob) && !wizardp(me))
        return notify_fail("这里有这个人吗？\n");

    if (ob->query("club") != me->query("club") && !wizardp(me))
        return notify_fail("你只对本帮会的玩家使用这条命令！\n");

    if (me->is_busy() || me->is_fighting())
        return notify_fail("你正忙着呢！\n");

    if (ob->is_busy() || ob->is_fighting())
        return notify_fail("对方正忙着呢！\n");
    
    club_name=me->query("club");

    ob->delete("club_level");
    ob->delete("club");
    if (ob->query("new_title")) 
        ob->delete("new_title"); 

    message_vision("$N强制$n退出了"+club_name+"。\n",me,ob);
    ob->save();

    return 1;
}


int help(object me)
{
write(@HELP
指令格式 : ckickout <某人> 

将帮派中的某人开除。
HELP
    );
    return 1;
}

