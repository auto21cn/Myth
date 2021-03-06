//moonbox.c
#include <ansi.h>

inherit ITEM;

mapping moon_cake=([
	"五仁月饼":1,
	"豆沙月饼":2,
	"双黄月饼":4,
	"金腿月饼":8,
	"莲蓉月饼":16,
	"椰蓉月饼":32,
	"枣泥月饼":64,
	"七星伴月":128,
	]);
int mask=0;	
void give_reward(object me);
int put_cake(object);
int put_bs(object); 
void create()
{
	set_name(HIY"月饼盒子"NOR,({"moon box","box"}));
	set_weight(10000);
	if(clonep())
	{
		set_default_object(__FILE__);
	}
	else
	{
		set("unit", "个");
                set("long", @TEXT
一个圆不溜秋的月饼盒子，仔细看似乎有两层。每层有四个格子。
一些平时吃不完的月饼都可以放(fang)到格子里。
TEXT);
                set("no_sell",1);
          }
}


/*功能段*/
void self_dest()
{
	message_vision("盒子古怪地裂了开来，化作片片尘埃。\n",environment());
	destruct(this_object());
}

void init()
{
	add_action("put_item","fang");
	//add_action("get_item","get");
	if(present(query("id")+" 2",environment()))
		call_out("self_dest",1);
}

int put_item(string arg)
{
	object m;
	
	if(!arg){
		write("你要放什么进盒子？\n");
		return 0;
	}
	if(arg != "moon cake" && arg != "bao shi"){
		write("这样东西无法放进去。\n");
		return 0;
	}
	
	if(!(m=present(arg,this_player())))
	{
		write("好像你没有这个东西。\n");
		return 0;
	}
	if( arg == "moon cake" )
		return put_cake(m);
	return put_bs(m);
}	
int put_bs(object m)
{
	
	return 1;
}
		
int put_cake(object m)
{
	
	string text;
		
	if(!m->query("is_cake"))
		return 0;
	if(moon_cake[m->query("name")]&mask)
	{
		write("一种月饼只能放一个。\n");
		return 0;
	}
	
	message_vision("$N将$n小心地放进盒子里。\n",this_player(),m);
	text=query("long");
	if(!mask)
	text+="里面有：\n";
	text+=m->query("name")+"\n";
	set("long",text);
	mask+=moon_cake[m->query("name")];
	if(mask==255)
	{
		call_out("start_reward",2,this_player());
	}
	destruct(m);
	return 1;
}
/*奖励*/

void start_reward(object p)
{
	if(!p) return;
	p->set_temp("no_move",1);
	message_vision("所有的格子都被放满了……\n",p);
	call_out("start_reward1",2,p);	
}

void start_reward1(object p)
{
	if(!p) return;
	message_vision(HIY"盒子开始颤抖起来。\n"NOR,p);
	call_out("start_reward2",2,p);	
}

void start_reward2(object p)
{
	if(!p) return;
	message_vision(HIW"一道白光闪过，盒子不见了。\n"NOR,p);
	tell_room(environment(p),p->query("name")+"怔怔地站在那里，好像在出神。\n",p);
	tell_object(p,HIC"只见一位少女笑吟吟地看着你。\n"NOR);
	if(!p->query("obstacle/mooncake"))
		call_out("start_reward3",2,p);	
	else
		call_out("finish_reward",2,p);	
}

void start_reward3(object p)
{
	if(!p) return;
	tell_object(p,HIM"少女嘻嘻地笑了几声。\n"NOR);
	tell_object(p,HIM"少女说道：对不起啦。我爷爷他老人家最爱吃月饼，又喜欢捉弄人，你没被吓着吧。\n"NOR);
	call_out("start_reward4",2,p);	
}

void start_reward4(object p)
{
	if(!p) return;
	p->command("pa "+p->query("id"));
	tell_object(p,HIM"少女又笑了几声。\n"NOR);
	tell_object(p,HIM"少女想了想，又道：那，这样吧，我給你点补偿好咯。\n"NOR);
	call_out("finish_reward",2,p);
}

void finish_reward(object p)
{
	if(!p) return;
	tell_object(p,HIW"少女低头喃喃念了几句咒语，将手向你一指。\n"NOR);
	tell_room(environment(p),HIW"隐隐中传来吟诵之声。\n"NOR,p);
	tell_object(p,HIY"你只觉浑身气血翻腾，说不出的舒畅。\n"NOR);
	p->set("obstacle/mooncake","done");
	p->delete_temp("no_move");
	give_reward(p);
	destruct(this_object());
}

void give_reward(object me) 
{
	mapping skill=me->query_skills();
	string *skillnames;
	string selected,msg;
	int level, inc=1,pot;
	
	if (!skill) return;
	if(random(2))
	{
		selected=me->query_skill_mapped("force");
		level=skill[selected];
		if (level < 1) return;
  		me->set_skill(selected,level+1);
  		level=skill["force"];
		if (level < 1) return;
  		me->set_skill("force",level+1);
  		tell_object(me,HIC"你得到了一级"+ to_chinese(selected) + "和"+to_chinese("force")+"。\n"NOR);
  	}
	else
	{
		selected=me->query_skill_mapped("spells");
		level=skill[selected];
		if (level < 1) return;
  		me->set_skill(selected,level+1);
  		level=skill["spells"];
		if (level < 1) return;
  		me->set_skill("spells",level+1);
  		tell_object(me,HIC"你得到了一级"+ to_chinese(selected) + "和"+to_chinese("spells")+"。\n"NOR);
  	}
        
        return;
}
