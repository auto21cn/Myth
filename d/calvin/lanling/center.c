//shulin 兰陵

inherit ROOM;

void create ()
{
        set ("short", "兰陵城心");
        set ("long", @LONG

这里是兰陵城的市中心,这的交通发达,路上来往
游人特别的多.再往南去就是皇宫了,西边是石头
大街,据说走到头就是南海之滨了;东面是雨花石
路,这条路通往的地方很多 ... ...

LONG);

        set("exits", 
        ([ //sizeof() == 5
        "north" : __DIR__"jie8",
        "south" : __DIR__"kingdadao1",
        "west" : __DIR__"stone1",
        "east" : __DIR__"yuhua",
        "down" : "/d/calvin/lanling/x",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
