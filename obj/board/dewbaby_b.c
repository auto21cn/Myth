    //无梦无幻
    //无梦个人留言板

inherit BULLETIN_BOARD;
#include <ansi.h>
void create()
{
  set_name(HIY"无"HIC"梦"HIG"无"HIW"幻"NOR,({"board"}));
      set("location","/u/dewbaby/workroom");
      set("board_id","dewbaby_b");
      set("long",
         HIW"无梦的私人留言板，有什么事情可留言。\n"NOR);
    setup();
    set("capacity",100);
    replace_program(BULLETIN_BOARD);
}
