//兰陵 kz_up

inherit ROOM;

void create ()
{
        set ("short", "三楼雅座");
        set ("long", @LONG

这里是兰陵客栈的三楼雅座,这里风景优美,兰陵的景色尽受眼底。

这里也是无数富家子弟常到之处,他们都喜欢在这里卖弄文才。

LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "down": "/d/calvin/kezhan2",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

//      set("outdoors", "changan");
        set("no_clean_up", 0);
  set("no_time",1);
  set("no_fight", 1);
  set("no_kill", 1);
  set("no_magic", 1);
  set("freeze",1);
        setup();
        replace_program(ROOM);
}
