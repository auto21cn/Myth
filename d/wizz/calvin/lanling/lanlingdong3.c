//shulin ����

inherit ROOM;

void create ()
{
        set ("short", "���궫��");
        set ("long", @LONG

����������ǵĶ���,��������·������ľ����,����ʤ��.

LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "west" : "/d/calvin/lanling/lanlingdong2",
                "east" : "/d/calvin/lanling/xiaolu1",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}