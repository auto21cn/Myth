inherit ROOM; 
#include <ansi.h> 
void create () 
{
set ("short","山口"); 
set ("long", @LONG 

　　天流山的山脚，站在这好象可以听到山上传来的阵阵丝竹之声，引人入神，心情好
象也变得舒畅多了。
　　路旁插了个红色的牌子，牌子上用很大很大的字写着“天流仙境，凡人莫入”。据
说这是那些在尘世间已经修炼成佛的人居住的地方。从山上随便下来一个人都是神仙一
的人物。不过凡人是没法进去的！
LONG); 
set("outdoors", "tianliu"); 
set("exits", ([ /* sizeof() == 2 */ 
"up" : __DIR__"shanpo", 
])); 
set("objects", ([ /* sizeof() == 1 */ 
])); 
setup(); 
}
