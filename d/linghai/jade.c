//by dewbaby
//jade2 
  
#include <ansi.h> 
inherit ROOM; 
        
void create () 
       { 
         set ("short", HIC"书房"NOR); 
         set ("long", @LONG 
        
这是凝玉轩下面的一个书房。你细细闻去，空气
中有淡淡的油墨香，似乎这些书已存放在此很多
年了。
LONG); 
        
         
        set("exits", ([ /* sizeof==1 */

        "up":__DIR__"jade2",        
        ])); 

        setup(); 
       }
