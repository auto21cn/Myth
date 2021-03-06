// top.c

#include <ansi.h>

inherit F_CLEAN_UP;


// 逆序排列(从高到低)
int sort_party(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

int main(object me, string arg)
{
        mapping last, fame;
        string *fam;
        string msg;
        int delta;
        int i;

        if (! arg || arg == "party")
        {
                fame = PARTY_D->query_party_fame();
                last = PARTY_D->query_all_last_party_fame();
        
                fam = keys(fame) - ({ 0 });
                if (sizeof(fam) < 1)
                        return notify_fail("目前江湖上没有什么"
                                           "有名的帮会。\n");

                fam = sort_array(fam, (: sort_party :), fame);
        
                msg = WHT "目前江湖上著名帮会的声望状况\n" NOR
                      HIY "────────────────\n" NOR;
                for (i = 0; i < sizeof(fam) && i < 30; i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }
        
                msg += HIY "────────────────\n" NOR
                       WHT "列出了" + chinese_number(i) + "个帮会。\n" NOR;
        } else
                return notify_fail("你要看什么排行榜？\n");

        write(msg);
        return 1;
}

int help(object me)
{
   	write(@HELP
指令格式: top

查看目前江湖上著名帮派的排名状况和相比去年变化
的程度。
HELP );
   	return 1;
}
