//兰陵

inherit ROOM;
void create ()
{
        set ("short", "藏武阁");
        set ("long", @LONG

两边的牌匾上密密麻麻的写满了从古至今的无数大英雄豪杰,
还有他们曾经留下的千古传奇般的神秘故事,再看正堂上方有一特
                     ※※※※※※※※※※※※※
大的牌匾,上面写着:   ※※  浩  然  正  气  ※※ 四个大字。
                     ※※※※※※※※※※※※※

LONG);

        set("exits", 
             ([ //sizeof() == 4
             "west" : "/d/calvin/lanling/jie5",   
          "east" : "/d/calvin/lanling/npcroom1",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
