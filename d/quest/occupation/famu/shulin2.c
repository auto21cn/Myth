
inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
一片杂树林,地上铺了厚厚一层落叶.有一条小径隐约穿过树林,前 
方似乎还升起一缕青烟. 
LONG
        );

        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/chen" : 1,
        ]));
        set("exits", ([ /* sizeof() == 4 */
                "west" : __DIR__"fmxh",
                "northeast" : __DIR__"shulin1",
        ]));
        set("outdoors", 1);

        setup();
}
