//kickout.c
//Ronger 10/98
#include <command.h>
#include <ansi.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        int i;
        object ob, *all, link_ob;
        all = users();

        seteuid(ROOT_UID);
        if(!arg || arg =="")
        return notify_fail("你要把谁踢出去？\n");

        if( LOGIN_D->get_madlock()) 
                return notify_fail("时空已经封闭，没有人能够退出这个时空了。\n");

        for(i=0; i<sizeof(all); i++)
        {
                if( arg == all[i]->query("id"))
                        ob = all[i];
        }

        if (!ob)
        return notify_fail("没有这个玩家。\n");

        if (ob == me)
        return notify_fail("自己把自己踢出去？有病？\n");

        if ( wiz_level(me) < wiz_level(ob) ) return notify_fail("你一脚狠狠地踢在铁板上，爽呀！\n");
        if (wiz_level(ob) && !is_root(me))
                return notify_fail("Xu...Yi...Ye...\n");

        link_ob = ob->query_temp("link_ob");

        if( link_ob ) {
                link_ob->set("last_on", time());
                link_ob->set("kickout_time",time());
                link_ob->set("last_from", query_ip_number(ob));
                link_ob->save();
                ob->save();
                if( environment(ob)->query("valid_startroom") )
                {
                        ob->set("startroom", base_name(environment(ob)));
                        tell_object(ob,"你被系统踢出了三界神话，但我们欢迎您再来，只是要注意自己的言行。\n");
                        tell_object(ob,"退出中...\n");
                }

                destruct(link_ob);
        }

        tell_object(ob,"欢迎下次再来！\n");
        message("system", ob->name() + "离开游戏。\n", environment(ob), ob);

        CHANNEL_D->do_channel(me, "sys",
                HIR""+ob->name() + "(" + ob->query("id") + ")被系统踢出了三界神话。"NOR);

        ob->save();
        destruct(ob);
        seteuid(getuid());

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : kickout <id>

你想把人踢出三界神话时，可利用此一指令。
HELP
    );
    return 1;
}

