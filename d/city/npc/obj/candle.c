// by night
// fid 修改

inherit ITEM;
#include <ansi.h> 

void create()
{
        set_name("许愿蜡烛", ({"wish candle","candle"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "这是一支特制的蜡烛，据说吃蛋糕时点燃(fire)它可以实现一个愿望。\n");
                set("unit", "支");
                set("value", 5000);
        }
} 

void init()
{
    add_action("do_fire","fire");
}

int do_fire(string arg)
{    object me, ob;
    me=this_player();
    ob=this_object();

    if (arg=="wish candle"||arg=="candle") {
        if (!present("cake", me) ) 
                return notify_fail("你没有蛋糕，用许愿蜡烛有什么用？\n");
        message_vision(HIR"$N点燃蜡烛，轻轻地把蜡烛插在了蛋糕上。\n"NOR, me); 
     me->set("fired",1); 
     destruct(ob);     return 1;
     }    return notify_fail("你要点着什么？\n");
}

