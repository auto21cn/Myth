//by dewbaby

//minghu4   
#include <ansi.h> 
inherit ROOM; 
        
void create () 
       { 
         set ("short", HIC"大明湖畔"NOR); 
         set ("long", @LONG 
        
这里是大明湖畔，岸上翠柳垂荫，婀娜多姿。湖中碧
波泛荡，荷花似锦；水面小舟争渡，画舫徐行。更有那
楼台亭树，隐现其间。简直美不胜收。这时，你听到西
面传来阵阵喧哗声，似乎是个小店铺。
LONG); 
       
        set("outdoors", 2); 
        set("exits", ([ /* sizeof() == 2 */ 
        "north" : __DIR__"minghu5", 
         "south" : __DIR__"minghu3",
         "west"  : __DIR__"xdian",      
        ])); 
       
        setup(); 
      }


      void init() 
      { 
          add_action("do_dive", "dive"); 
      } 
      int do_dive() 
      {   object me,ridee; 
          me=this_player(); 
          ridee=me->ride(); 
                   if( (!present("bishui zhou", me))&& 
                   (!((string)me->query("family/family_name")=="东海龙宫")) ) 
                   return 
      notify_fail(HIY"你一个猛子扎到水里......\n\n"HIW"但没过多久就被憋得半死，只得赶紧爬上岸来。\n"NOR); 
       
                 if (ridee && ridee->query("under_water")) {  
                   message_vision("$N一拍$n的头，连人带马跃入水中。\n",me,ridee);  
                   ridee->move(__DIR__"hudi2");  
      } 
       else 
           message_vision("$N神情欢快，一个猛子扎到水中，然后不见了。\n", me); 
            me->move(__DIR__"hudi1"); 
           message_vision("$N游了过来。 \n", me); 
           return 1; 
      } 
 



 

