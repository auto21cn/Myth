//Created by kuku@sjsh 2003.2

inherit ROOM;

void create ()
{
        set ("short", "名剑无影");
        set ("long", @LONG

这里是天下著名兵器铸造师居住的地方，近年来江湖
恩怨不断，铸造师的生活也被纷至沓来请他铸造兵器
的人扰乱了。
LONG);

        set("exits", ([ /* sizeof() == 2 */             
                "north" : "/d/qujing/qinfa/jiedao5",
        ]));
        set("objects", ([  
                __DIR__"npc/zhuzaoshi" : 1,
        ])); 
        setup();
}
