//tan1.c

inherit ROOM;

void create()
{
        set("short", "开封西湖 ");
        set("long",
             "这里是开封西湖水下 ，四周倒还比较明亮，几道天光从头顶的潭水中投射下来，\n"
             "显得十分美丽。脚下漆黑一片也不知有些什么。你不由对自己说......\n"

        );
        set("exits", ([
                "up" : "/d/kaifeng/xihu1",
                "down" : __DIR__"tan2",
        ]));
        setup();
        replace_program(ROOM);
}

