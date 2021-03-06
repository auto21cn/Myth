//Creat by waiwai@2000/10/31

#include <ansi.h>
inherit NPC;
//inherit F_VENDOR;

string ask_me(); //定义ask_me
int do_gu(string arg); 
int do_dapi(string arg); 
int do_cuihuo(string arg); 
void reward(object me); 

void create()
{
set_name("周铁匠", ({ "zhou tiejiang", "zhou", "tiejiang", "smith"}) );
set("title", WHT"铁匠铺老板"NOR);
set("shen_type", 1);
set("gender", "男性" );
set("age", 33);
set("long", "周铁匠正用铁钳夹住一块红热的铁块放进炉中。\n");

        set("combat_exp", 10000);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("literate", 40);
        set("kee", 600);
        set("sen", 600);
        set("max_kee", 600);
        set("max_sen", 600);
        set("attitude", "friendly");
/*
        set("vendor_goods", ([
               "1": "/d/obj/weapon/dagger/dagger.c",
                "2": "/d/obj/weapon/axe/tiefu.c",
                "3": "/d/obj/weapon/hammer/hammer",
                "4": "/d/obj/weapon/fork/fork",
            	"5": "/d/obj/weapon/stick/bintiegun",
                "6":"/d/obj/weapon/whip/tielian",
                "7": "/d/obj/armor/niupi",
                "8": "/d/obj/weapon/sword/changjian",
                "9": "/d/obj/weapon/blade/blade",
                "10": "/d/obj/weapon/spear/tieqiang",
                "11": "/d/obj/weapon/staff/chanzhang",
                "12" : "/d/faith/obj/axe",
                "13" : "/d/faith/obj/pickaxe",
        ]) );

set("inquiry", ([ 
"工作" : (: ask_me :), 
"work" : (: ask_me :), 
]));
*/
setup();

        carry_object("/d/obj/cloth/linen")->wear();
        carry_object("/d/obj/weapon/hammer/hammer")->wield();
}

void init()//定义动作
{
//add_action("do_vendor_list", "list");
add_action("do_gu", "gu"); 
add_action("do_dapi", "dapi"); 
add_action("do_cuihuo", "cuihuo"); 
}

string ask_me() 
{ 
object me = this_player(); 

if (me->query("combat_exp") > 200000) //检查EXP是否大于200000
return "让您老干这个未免屈尊了吧？"; 

if(me->query("title") == "普通百姓")
    return "你是普通百姓不能做生意！"; 

if (me->query("PKS") > 1) //检查是否带着杀人记录
return "杀人凶手还要活干？没门！！！"; 

if (me->query("daoxing") < 100000) //检查DX是否小于100年
return "你的修行那么低能打出好铁来吗？"; 

if (me->query("kee") < 50) //检查气
return "你还是歇会儿吧！要是出了人命我可承担不起。"; 

if (me->query_temp("smith/gu")) //检查标记
return "让你鼓风箱，你怎么还磨蹭(gu)？"; 

if (me->query_temp("smith/dapi")) 
return "叫你打的坯你打了没有(dapi)？"; 

if (me->query_temp("smith/cuihuo")) 
return "叫你淬一下火(cuihuo)你瞎捣鼓什么？"; 

switch(random(3))//随机分配三个工作
{ 
case 0: 
me->set_temp("smith/gu", 1); 
return "好！"+me->name()+"你帮我鼓一会儿风箱(gu)"; 

case 1: 
me->set_temp("smith/dapi", 1); 
return "这样吧，你帮我打一下坯吧(dapi)！"; 

case 2:
me->set_temp("smith/cuihuo", 1); 
return "去帮我把这些刚出炉的淬一下火(cuihuo)。"; 

} 
} 

int do_gu(string arg) 
{ 
object me = this_player(); 

if (me->is_busy()) 
return notify_fail("你现在正忙。\n"); 

if (! me->query_temp("smith/gu")) 
{ 
message_vision(""+me->name()+"刚偷偷的拉起鼓风机，鼓了几阵风。" 
"就听见$N对"+me->name()+"大喝道：滚开，乱搞什么。\n", 
this_object(), me); 
return 1; 
} 

message_vision(""+me->name()+"拉起鼓风机拼命鼓了起来，$N看了点了点头。\n", 
this_object(), me); 
reward(me); 
return 1; 
} 

int do_dapi(string arg) 
{ 
object me = this_player(); 

if (me->is_busy()) 
return notify_fail("你现在正忙。\n"); 

if (! me->query_temp("smith/dapi")) 
{ 
message_vision(""+me->name()+"拿起几块生铁，在手里掂了掂。" 
"就听见$N对"+me->name()+"大喝道：放下，乱搞什么。\n", 
this_object(), me); 
return 1; 
} 

message_vision(""+me->name()+"拿着锤子对刚出炉的火热的生铁用力敲打着，" 
"$N“嗯”了一声，看上去有些满意。\n", 
this_object(), me); 
reward(me); 
return 1; 
} 

int do_cuihuo(string arg) 
{ 
object me = this_player(); 

if (me->is_busy()) 
return notify_fail("你现在正忙。\n"); 

if (! me->query_temp("smith/cuihuo")) 
{ 
message_vision(""+me->name()+"刚抄起一个打造好的坯子，" 
"就听见$N对"+me->name()+"大喝道：放下，别给我搞坏了。\n", 
this_object(),me);
return 1; 
} 

message_vision(""+me->name()+"用铁钳抄起一块火红的坯子，伸进了水" 
"池，“哧”的一声轻烟四冒。\n", 
me); 
reward(me); 
return 1; 
} 

void reward(object me) //工作结束，分配奖赏，移除标记
{ 
object money; 

me->delete_temp("smith/gu"); 
me->delete_temp("smith/dapi"); 
me->delete_temp("smith/cuihuo"); 

money = new("/obj/money/silver"); 
money->set_amount(20 + random(10)); 
money->move(this_player()); 
message_vision("$N对"+me->name()+"道：这是给你的工钱。\n", 
this_object(), me); 
//if (me->query("combat_exp") < 200000) 
//{
//me->add("potential", 5); 
//me->add("combat_exp", 50 + random(20)); 
//me->add("daoxing", 50 + random(20)); 
//} 
me->receive_damage("kee", 30); 
me->start_busy(8); 
} 

