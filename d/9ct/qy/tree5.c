// 九重天 千紫天 by Calvin

#include <ansi.h>
inherit "/d/9ct/qy/tree.c";

void falldown(object,object);
void create()
{
        set("short", MAG"五重·千紫天"NOR);
  set ("long", @LONG

          ※※※※※※※※※※※※※※※※※
          ※※※※※※※※※※※※※※※※※
          ※千紫攀云云极处  心依随风风清扬※
          ※※※※※※※※※※※※※※※※※
          ※※※※※※※※※※※※※※※※※

LONG);

        set("exits", ([
  "down": "/d/9ct/qy/wu.c",
        ]));

        set("objects", ([
            "/d/9ct/obj/doujia.c" : 1,
              ]));

        setup();
}
