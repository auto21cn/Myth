// Created by waiwai@2001/03/23
// 落叶(Fallen leaves)
// [1;31m此文件禁止更改和移动[0m

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL "落叶" NOR, ({ "fallen leaves", "leaves", "fallen" }) );
	set_weight( 100 );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("long", "这是一片被风吹落的落叶，透着黯然的忧伤。\n");
		set("value", 100);
		set("des", 1);
		set("can_auction", 1);
    };
	set_temp("drop_msg", "飘落不见了！\n");//drop时的输出信息

	setup();
}

void init() 
{	
	if( this_player()==environment() )
	add_action("do_combine","combine"); 
}

int do_combine()
{
	object me, a, b, c, item;

	me=this_player();
	a=this_object();

	if( !wizardp(me) && userp(me) ) {
       if(!environment(me)->query("cold"))
             return notify_fail("此地灵气不够，无法合并物品。\n");

	if( (int)me->query("force") < (int)me->query("max_force") )
		return notify_fail("你的内力不足，很难将物品合并。\n");

	if( (int)me->query("mana") < (int)me->query("max_mana") )
		return notify_fail("你的法力不足以支持合并物品。\n");
       }

       if ( !(b=present("magic jade",me)))
                return notify_fail(CYN"你尚缺 "HIG"神之翡翠 "NOR CYN"无法合成火灵珠。\n"NOR);

       if ( !(c=present("lan crystal",me)))
                return notify_fail(CYN"你尚缺 "HIM"蓝晶 "NOR CYN"无法合成火灵珠。\n"NOR);

	if( item=new("/obj/self/item/huozhu")){
		if( me->query_encumbrance() + item->query_weight()
			> me->query_max_encumbrance())
		return notify_fail("你的负重过高不能合并物品。\n");
		destruct(b);
		destruct(c);

	item->move(me);
	me->start_busy(3);
	message_vision(WHT"$N将手中的 "HIG"神之翡翠 "HIM"蓝晶"NOR WHT
	"与"NOR YEL"落叶"NOR WHT"摆在一起，只见几道耀眼霞光掠过,竟然合并出一颗火灵珠。\n"NOR,me);
        message("channel:rumor",
	WHT"┋"HIR"小道消息"NOR WHT"┋听说："+log_id(me)+"合成了"HIR"火灵珠"NOR WHT"了！\n"NOR,users() );

	destruct(a);
	}
	return 1;
}

