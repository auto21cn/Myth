#include <ansi.h>
inherit F_CLEAN_UP;

int main()
{
        string day,season,time;
       mapping date;      
       int hour;
          
       date=XYJTIME_D->check_time(time());
       season=XYJTIME_D->check_season();
       day=date["YEAR"]+date["MONTH"]+date["DAY"]+date["HOUR"]+date["QUARTER"];
       time="三界纪年时辰："+day+" "+season+" \n"NOR;
       write( time );

       return 1;
}

int help()
{
        write("

指令格式：xyjtime 

此命令用来查看现在西游记所处创世纪年中的日期!

相关信息：time，uptime
");
        return 1;
}

