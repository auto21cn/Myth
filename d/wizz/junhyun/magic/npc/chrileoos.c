//魔导圣战NPC - 三界破坏神虚空之依丽娜(未完成)
//by junhyun@SK
#include <ansi.h>
inherit NPC;
int give_gift();

void create()
{
        set_name(HIW"克里欧斯"NOR, ({"chriloos"}));
        set("title", HIC"精灵王"NOR );
//        set("nickname", HIW""NOR );
        set("gender", "男性" );
        set("age", 5000);
        set("per", 40);
        set("str", 30);
            set ("long", @LONG
精灵族永恒的领袖

LONG);

        set("combat_exp", 290000);
        set("daoxing", 40000000000);
        set_skill("unarmed", 370);
        set_skill("dodge", 340);
        set("max_kee", 10000);
        set("max_sen", 10000);
        set("force", 6000);
        set("max_force", 3000);
        set("mana", 6000);
        set("max_mana", 3000);  
        set("force_factor", 1000);
        set("mana_factor", 1000);
        set("inquiry", ([
           "name" : "哼，想知道我的名字，就要用你的血来祭奠！\n",
     "here" : "这里是黑暗的边缘！\n",
         ]) );


            setup();
}


