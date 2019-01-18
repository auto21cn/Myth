#include <ansi.h>
inherit ROOM;
void home( object ob ) ;
void create()
{
    set("short", "海港");
    set("long", @LONG
这里就是东瀛岛了。西边是一望无际的大海；往北则是通向城市的道路。
岛上的空气似乎又热又闷,咸湿的海风中带着一股腥臭,又夹杂了一缕奇
特的花香,闻起来十分怪异.海边泊着一艘大船(chuan)。
LONG
    );
    set("item_desc", ([
        "chuan" : "这是东瀛岛对外联系的大船。来往的人只要\n"
                  "上船(enter)就可以回中原。\n",
    ]));
    set("exits",([
     "north" :__DIR__"shulin1",
]));
    set("outdoors", 1);
    setup();
}
void init()
{
    add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
    object ob ;
    if( !arg || arg !="chuan" ) 
       {
         tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
         return 1 ;
       }
    ob = this_player () ;
    message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
    message_vision("船夫升起帆，船就向西方航行。\n", ob);
    ob ->move("/d/dongying/dahai") ;
    tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
    call_out("home", 20 , ob );
    return 1 ;
}
void home( object ob )
{
     if (!ob) return;
  tell_object(ob , "大船终于抵达了西游世界的一个港口。你走下船来。\n" ) ;
  ob->move ("/d/dongying/haigang") ;
}
