inherit "/std/room/shengdian.c";

void create ()
{
reload("金华光佛");
set ("short", "金华光佛");
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
   "east" : __DIR__"dian4",
]));
  set("no_clean_up", 1);
    set("where_name","金华光佛");
  set("outdoor", 1);
   get_fo_npc();
  setup();
}

int clean_up()
{
      return 0;
}

