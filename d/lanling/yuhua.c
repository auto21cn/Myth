//shulin 兰陵

inherit ROOM;

void create ()
{
        set ("short", "雨花石路");
        set ("long", @LONG

这里是兰陵的第三大街,这里地理环境较好,并且有着
较高的商业活动,这里的人流量常常大的惊人,并且时
而有交通堵塞的情况出现,这个问题也是当地官府最
为头痛的事

LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                 "west" : "/d/lanling/center",
                "east" : __DIR__"yuhua2",
                 "north" : "/d/calvin/lanling/tan1",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
