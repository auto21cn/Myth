inherit BULLETIN_BOARD;
void create()
#include <ansi.h>
{
  set_name(HIR"杀手乐园留言板"NOR, ({ "board" }) );
  set("location", "/d/pkdao/pkdao.c");
  set("board_id", "pkboard");
  set("long", "杀手们对自己的杀戮生涯十分自豪，都喜欢留字做榜。\n" );
  setup();
  set("capacity", 80);
  replace_program(BULLETIN_BOARD);
}
