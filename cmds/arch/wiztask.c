// wiztask.c
// by mudring
// Modified by Longer@SJSH

#include <ansi.h>
#include <mudlib.h>
inherit F_CLEAN_UP;
string query_time(int time);

string *mission;
int level(mixed, mixed);
string get_mission( string );
void create() { seteuid( getuid() ); }

int main(object me, string arg)
{
        string *list, hood = "", str, msg, scr, jobmsg, att,time_msg;
        int adm_n, arc_n, wiz_n, apr_n, imm_n, j, k,inv=0;
        object ob,body;
        int freeze_time;        

        list = sort_array(SECURITY_D->query_wizlist(1), (: level :));
        list = filter_array(list, "filter_adm");
        str = HIR"★ "HIC+MUD_NAME+HIC+"巫师组成员： \n"NOR;
        str +=HIY"≡≡"HIW"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"HIY"≡≡\n"NOR;
        str +=WHT"   系统级别             ID        名  字        状       态\n"NOR;
        str +=HIY"≡≡"HIW"───────────────────────────────────"HIY"≡≡\n"NOR;
        for(int i=0; i<sizeof(list); i++) {
                        switch (wizhood(list[i])) { 
                                case "(admin)": adm_n++;break;
                                case "(arch)":  arc_n++;break;
                                case "(wizard)":        wiz_n++ ;break;
                                case "(apprentice)":    apr_n++;break;
                                case "(immortal)":      imm_n++;break;
                        }
        }
        for(int i=0; i<sizeof(list); i++) {
                if (hood != wizhood(list[i])) {
                        hood = wizhood(list[i]);
                        switch (hood) { 
                                case "(admin)":
                                  msg =HIW"〖 总管巫师 〗"NOR;k=adm_n;break;
                                case "(arch)":
                                  msg =HIC"〖 开发巫师 〗"NOR;k=arc_n;break;
                                case "(wizard)":
                                  msg =HIG"〖 维护巫师 〗"NOR;k=wiz_n ;break;
                                case "(apprentice)":
                                  msg =HIM"〖 管理巫师 〗"NOR;k=apr_n;break;
                                case "(immortal)":
                                 msg =HIY"〖 客座巫师 〗"NOR;k=imm_n;break;
                                }
                        j=1;
                } else {
                        msg="";
                        j++;
                }
                if ( k == 1) scr=WHT"━━━━"NOR;
                else scr=WHT"━━┳━"NOR;
                if ( k!=j && k!=1 && j!=1 ) scr=WHT"  ┣━"NOR;
                if ( k==j && k!=1 && j!=1 )     scr=WHT"  ┗━"NOR;

                inv=0;
                ob=new(LOGIN_OB);
                ob->set("id", list[i]);
                ob->restore();

                if(objectp(body=find_player(list[i])) && !body->query("env/invisibility")) {
                     //By waiwai@2001/07/06
                     if(interactive(body) && (query_idle(body)) > 300 )
                     att=sprintf(HIM"在线：已发呆%5d 秒钟"NOR,query_idle(body))+"";
                                     else
                        if (!interactive(body)) att=HIR"在线：断线中．．．    "NOR;
                     else
                        if (this_player()->visible(body)) 
                        att=HIG"在线："+query_time(body->query_temp("logon_time"))+"";
                str += sprintf("%-16s%s "YEL"%-11s%-14s"NOR"%-29s\n",msg, scr, list[i],body->name(1),att);
                     inv=1;
                } else {att="离线："+query_time(ob->query("last_on"))+"";
                str += sprintf("%-16s%s "YEL"%-11s%-14s"NOR"%-22s\n",msg, scr, list[i],ob->query("name"),att);

                destruct(ob);
                inv=0;}
        }
        str +=HIY"≡≡"HIW"───────────────────────────────────"HIY"≡≡\n"NOR;
        str += HIR"★ "HIC+MUD_NAME+HIG" 目前共有 " + sizeof(list) + " 位维护管理巫师。\n"NOR;
        
        me->start_more(str);
        return 1;
}

int level(mixed ob1, mixed ob2)
{
        if (wiz_level(ob1) != wiz_level(ob2))
                return wiz_level(ob2) - wiz_level(ob1);
        return ob1 < ob2?-1:1;
}

string query_time(int time)
{
        string msg;
        int day, hour, min;
        
        time=time()-time;
        
        msg="";
        day=time/86400;
        hour=time%86400/3600;
        min=time/60%60;

        if(min<1)
                min=1;
        if(day)
                msg+=sprintf("%s天", chinese_number(day));
        if(day<10 && hour)
                msg+=sprintf("%s小时", chinese_number(hour));
        if(!day && hour<20 && min )
                msg+=sprintf("%s分", chinese_number(min));

        return msg;
}

int filter_adm(string arg)
{
return 1;
}

int help(object me)
{
write(@HELP

指令格式 : wiztask

用途 : 列出目前三界神话巫师组成员系统级别以及当前状态。

HELP
     );
     return 1;
}

