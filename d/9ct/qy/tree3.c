// 九重天 普渡天 by Calvin

#include <ansi.h>
inherit "/d/9ct/qy/tree.c";

void falldown(object,object);
void create()
{
        set("short", YEL"三重·普渡天"NOR);
  set ("long", @LONG

          ※※※※※※※※※※※※※※※※※
          ※※※※※※※※※※※※※※※※※
          ※浊污染心清不在  普渡回头誓不迟※
          ※※※※※※※※※※※※※※※※※
          ※※※※※※※※※※※※※※※※※

LONG);

        set("exits", ([
  "down": __DIR__"san",
        ]));

        set("objects", ([
              "/d/9ct/obj/guo.c" : 1,
              ]));

        setup();
}
