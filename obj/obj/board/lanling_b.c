inherit BULLETIN_BOARD;
#include <ansi.h>

void create()
{
        set_name(HIR"兰陵告示榜"NOR, ({ "board" }) );
        set("location", "/d/lanling/兰陵城心");
       set("board_id", "lanling1_b");
        set("long",
                "这是一个公告版,是专门为那些喜欢到处留点墨笔的人提供的.你可以(post)。\n" );
        setup();
        set("capacity", 200);
        replace_program(BULLETIN_BOARD);
}
