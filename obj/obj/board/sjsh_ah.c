
inherit BULLETIN_BOARD;
#include <ansi.h>

void create()
{
            set_name("三界神话发展讨论板", ({ "board" }) );
           set("location", "/d/wiz/entrance");
             set("board_id", "sjsh_ah");
          set("long",     "这是供巫师和玩家互相交流，共同促进三界神话发展的讨论板。\n" );
	setup();
          set("capacity", 300);
	replace_program(BULLETIN_BOARD);
}
