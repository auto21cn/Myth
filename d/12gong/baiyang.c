// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "第一宫：亥宫");
        set ("long", @LONG
肖猪星戍非常重眠，只要一天睡眠充足便精力充沛，反之，睡眠不足则百病丛生，
故肖猪星戍健康最佳保健方法即是要有充足的睡眠。肖猪星戍因无体筋所以睡一边不必翻身，
因此有人骂肖猪星戍，睡得条猪一样不会翻身。肖猪星戍的个性坦白、直率不善隐瞒，
心里有话喜欢直接讲出来。


LONG);


        set("exits", ([
        "northup"    :       __DIR__"by2jn1",
            "eastdown"  :       __DIR__"toby2",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/baiyang" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}
int valid_leave(object me, string dir)
{
        if ( present("xiaoshu jun") && dir == "northup" )
        return notify_fail("肖猪星戍冷笑一声：先过我这关再说！\n");
        return ::valid_leave(me, dir);
}

void init()
{
    add_action("block_cmd", "", 1);
}
int block_cmd(string args)
{
string verb;
verb = query_verb();
    if (verb == "recall") return 1;
    return 0;
}
