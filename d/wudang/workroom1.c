#include <ansi.h>

inherit ROOM;

void create ()
{
  set ("short", "淡淡的云的工作室");
  set("long", "好地方。\n");

  set("exits", ([ 
  "kz" : "/d/city/kezhan",
  "wizroom" : "/adm/npc/wizroom",
]));
  set("valid_startroom", 1);
  set("no_upgrade_age",1);
   set("freeze",1);
   set("no_time",1);
  set("outdoors", "/u/afei");

  setup();
}
void init()
{
        mixed *local;
        int  t;
        local = localtime(time()*60);
        t = local[2] * 60 + local[1]; 
        add_action("do_look", "look");
}

int do_look()
{
        mixed *local;
        int  t;
        local = localtime(time()*60);
        t = local[2] * 60 + local[1];

        if( t > 30 && t < 260)
        {
                set("long", BLU"那繁星流转，日月迁移，黎明前最后的一丝黑暗。天明就要到来！
淡淡的云沉睡于自已的床上，在美好的梦中找寻自己心中的天女。\n"NOR);
        }
        if( t > 260 && t < 510)
        {
                set("long", HIC"天光微明！花草带露！万物凄美！淡淡的云的工作室里一片美好！
那清晨里清亮的鸟鸣送给淡淡的云无限的希望。\n"NOR);
        }
        if( t > 510 && t < 630)
        {
               set("long", HIY"亮丽的上半天是一天中每好的开始， 勤劳的淡淡的云早早的起来了，
因为他为了养活自己,马上要去上班了。上班去喽!!\n"NOR);
        }
        if( t < 810 && t > 630)
        {
                set("long", HIW"中午的到来让淡淡的云不得不停下了手上的程序,肚子里咕咕乱叫,
实在是顶不住了,走!吃饭去,吃完饭后淡淡的云便和几个朋友打起了乒乓球。\n"NOR);
        }
        if( t < 990 && t > 810)
        {
               set("long", HIG"转眼就到了要吃晚饭的时候，一天累劳的工作终于结束了,终于回
到家的淡淡的云和家人围坐在一起边看动画片边吃晚饭,生活真是无限好。\n"NOR);
        }
        if( t < 1170 && t > 990)
        {
                set("long", HIR"由于淡淡的云的文凭是在单位中最差的,所以淡淡的云不得不坐一个
多小时的汽车,去市区读书,可是,成果却.......现在的大连真像一个大的拳击台,不
是你击倒我就是我击到你。唉!\n"NOR);
        }
        if( t < 1360 && t > 1170)
        {
                set("long", RED"天色已经很暗了，到这个时候，淡淡的云终于到了东北财经大学,和
朋友们坐在了一起,谈天说地.无说不为.看来这次英语和高数又要玩完了。\n"NOR);
        }
        if( t < 30 || t > 1360)
        {
                set("long", BLU"夜深人静了，淡淡的云拖着快要倒下的身子回到了杏花小区家,
到了家已经不行了,往床上一躺,在睡觉前躺在床上看武侠小说是淡淡的云最好的休息。\n"NOR);
        }
}
