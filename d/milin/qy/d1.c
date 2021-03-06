// 密林宝库 by Calvin
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密林墓碑");
        set ("long", @LONG
墓碑后多有尖石玲珑，耸拔瘦削。远观如有山云突涌，夹杂草木嫩
绿满山。墓碑下却有一铜石，中有小孔(hole)。间闻墓旁阴笑阵阵，
极是恐怖。
LONG);
  set("item_desc", ([ /* sizeof() == 1 */
  "hole" : "洞中似乎是个机关，能放(insert)下什么东西。\n",
]));

        set("exits", 
        ([ //sizeof() == 4
           "up" :__DIR__"7",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("no_clean_up", 0);
        set("water", 1);
        setup();
//      replace_program(ROOM);
}

void init()
{
        add_action("do_insert", "insert");
}
int do_insert(string arg)
{
        object mishi, ob, me;
        me=this_player();
        if( !arg )
                return notify_fail("你要放什么东西？\n");

        if( !arg || arg!="yao shi" )
                return notify_fail("似乎孔中放不下这个东西。\n");

        if( !(mishi = find_object(__DIR__"mishi2")) )
                mishi = load_object(__DIR__"mishi2");

        if( mishi = find_object(__DIR__"mishi2") ) 
        {
                set("exits/enter", __DIR__"mishi2");

                message_vision("$N将白银钥匙塞入小孔，只听喀喀几声，一座大石移开，露出一个通口。\n", me, ob);
                message("vision", "大石被人从外推开了。。\n", mishi );
                mishi->set("exits/out", __DIR__"d1");
                destruct(ob);
        call_out("close_down", 5);
        }
        return 1;
}

void close_down()
{
        object mishi;

        message("vision", "大石轰地又回到原位。\n", this_object() );
        if( mishi= find_object(__DIR__"mishi1")) {
        message("vision", "大石轰地又回到原位。\n", mishi);
        mishi->delete("exits/out");
        }

        delete("exits/enter");

}
