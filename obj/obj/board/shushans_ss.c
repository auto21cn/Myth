inherit BULLETIN_BOARD;
#include <ansi.h>

void create()
{
            set_name(HIW"经阁密语"NOR, ({ "board" }) );
           set("location", "/d/shushan/jinglou");
             set("board_id", "shushans_ss");
          set("long",     "这个留言板是剑客们共同开心留言的地方，放开你的胸怀，说上几句吧。\n" );
        setup();
          set("capacity", 300);
        replace_program(BULLETIN_BOARD);
}
