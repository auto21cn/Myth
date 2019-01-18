
inherit ROOM;

void create()
{
	set("short", "林间小道");
	set("long", @LONG
这是一条从四通八达的林间小道，沿途风景极之清幽，参天古树，拔地而
起，两旁百花争艳。令人留连忘返。北面是个道场，写着〖神谷道场〗。
LONG );
	set("exits", ([
		"south" : __DIR__"qingcaop",
		"north" : __DIR__"gate",
                "west" : __DIR__"xiaodao2",
	]));
	set("no_clean_up", 0);
	set("outdoors", 1);
	setup();
	replace_program(ROOM);
}
