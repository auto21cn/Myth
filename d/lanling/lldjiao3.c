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
                "west" : "/u/calvin/����/����/���궫��2",
                "east" : "/u/calvin/����/����/С·1",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}