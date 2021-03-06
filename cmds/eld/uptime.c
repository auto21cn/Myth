//CMDS USR uptime.c
//Created by waiwai@2000/11/13

#include <localtime.h>
#include <mudlib.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int main(int i)
{
        int t, y, mo, d, h, m, s;
        mixed *ltime;
        string time;

        ltime = localtime(time());
        s = ltime[LT_SEC];
        m = ltime[LT_MIN];
        h = ltime[LT_HOUR];
        d = ltime[LT_MDAY];
        mo = ltime[LT_MON]+1;
        y = ltime[LT_YEAR];
//      time = "二零零零年";
        
/*
        if (!intp(i)){
                write(CHINESE_MUD_NAME+"上次当机原因："+read_file("/log/static/LASTCRASH") );

        }
*/
        
        while (y) {
                time = chinese_number(y%10) + time;
                y /= 10;
        }
        time += chinese_number(mo) + "月";
        time += chinese_number(d) + "日";
        time += chinese_number(h) + "时";
        time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        t = uptime();
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        write(CHINESE_MUD_NAME+"已经连续运行了" + time + "\n");
        
        return 1;
}

int help(object me)
{
        write(
"\n指令格式 : uptime\n\n"
"这个指令告诉您「" CHINESE_MUD_NAME "」泥巴游戏已经连续执行了多久。\n"
    );
    return 1;
}


