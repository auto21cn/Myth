inherit "/std/room/shengdian.c";

void create ()
{
reload("才光明佛");
set ("short", "才光明佛");
set ("long", @LONG

　　　　　　　████　　█　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　　　　█　　█　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　　　　█　　█　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　███████　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　█　　█　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　█　　█　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　█　　████
LONG);

  set("exits", ([
   "west" : __DIR__"dian3",
]));
  set("no_clean_up", 1);
    set("where_name","才光明佛");
  set("outdoor", 1);
   get_fo_npc();
  setup();
}

int clean_up()
{
      return 0;
}

