inherit "/std/room/shengdian.c";

void create ()
{
reload("΄σ΄ΘΉβ·πΜΓ");
set ("short", "΄σ΄ΘΉβ·πΜΓ");
set ("long", @LONG

‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨¨¨¨‘‘‘‘¨‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨‘‘‘‘¨‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨‘‘‘‘¨‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨¨¨¨¨¨¨‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨‘‘‘‘¨‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨‘‘‘‘¨‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
‘‘‘‘‘‘‘‘‘‘‘‘‘‘¨‘‘‘‘¨¨¨¨
LONG);

  set("exits", ([
 // "down" : __DIR__"jiuguan1",
 // "up" : "/d/quest/club/clubbar",
]));
  set("no_clean_up", 1);
    set("where_name","΄σ΄ΘΉβ·π");
  set("outdoor", 1);
   get_fo_npc();
  setup();
}

int clean_up()
{
      return 0;
}

