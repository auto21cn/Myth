inherit F_CLEAN_UP;
// pkl

#include <ansi.h>
#include <obstacle.h>

int telling (object me, object who);

string name;

int main(object me, string arg)
{
    object ob;

    if( !arg ) {
	ob = me;
	name = "你";
    } else if (wizardp (me)) {
	ob = find_player(arg);
	if(!ob) ob = find_living(arg);

	if(!ob) ob = LOGIN_D->find_body(arg);

	if(!ob || !me->visible(ob)) return notify_fail("没有这个人。\n");

	name = ob->query("name");
    } else
	return 0;

    telling(me, ob);

    return 1;
}

int help()
{
    write(@TEXT
指令格式：quests <某人>

显示某人解谜的资料。 

TEXT
    );
    return 1;
}

int telling (object me, object who)
{
    mapping mapp;

    write ("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    write (HIY+name+"的灭妖任务：（最近一次灭妖）\n"NOR);
    write ("    开始时间："+ctime(who->query("mieyao/time_start"))+"\n");
    if (!who->query("mieyao/done")) write ("    完成时间：尚未完成\n"NOR);
    else write ("    完成时间："+ctime(who->query("mieyao/time_finish"))+"\n"NOR);
    write ("    妖怪名称："+who->query("mieyao/name")+"("+who->query("mieyao/id")+")\n");
    write ("    妖怪初始地点："+who->query("mieyao/where")+"\n");
    write ("    目前困难等级："+chinese_number(who->query_temp("mieyao/level"))+"级怪\n\n");
    write (HIR+name+"的灭妖奖励是如下：\n"NOR);
    write ("   总共的得到了"+to_chinese(who->query("mieyao/number"))+"次杀妖任务。\n");
    write ("   总共完成了"+to_chinese(who->query("mieyao/number_fns"))+"次杀妖任务。\n");
    write ("    共获得：\n"NOR);
    write ("    潜能："NOR+to_chinese(who->query("mieyao/reward/pot"))+"点。\n");
    write ("    武学："NOR+to_chinese(who->query("mieyao/reward/exp"))+"武学。\n");
    write ("    技能："NOR+to_chinese(who->query("mieyao/reward/skills"))+"次skills奖励。\n");
/*
    mapp = who->query("mieyao/reward/skills");
    if (mapp)
    {
	string *my_keys = keys (mapp);
	int i = sizeof (my_keys);

	while (i--)
	{
	    write ("        "+to_chinese(my_keys[i])+to_chinese(mapp[my_keys[i]])
	      +"级\n");
	}
    }
*/
    write ("\n");
  write ("\n");
  write (HIY+name+"的门派灭妖任务：（最近一次灭妖）\n"NOR);
  write ("    妖怪名称："+who->query("secmieyao/name")+"("+who->query("secmieyao/id")+")\n");
  write ("    妖怪初始地点："+who->query("secmieyao/place")+"\n");
    write ("   总共完成了"+to_chinese(who->query("mieyao/menpai_num"))+"次门派杀妖任务。\n");
  write (HIR+name+"的门派灭妖奖励是如下：\n"NOR);
  write ("    潜能："NOR+to_chinese(who->query("mieyao/menpai_reward/pot"))+"点。\n");
  write ("    道行："NOR+to_chinese(who->query("mieyao/menpai_reward/dh"))+"点。\n");
  write ("\n");
    write ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

