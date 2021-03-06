/***************************************
MUDLIB：Biographies         〓悟空传〓  
Created Admin By Waiwai@2001/02/18
Admin Email：wkzstory@21cn.com         
****************************************/
//Created by waiwai@2001/05/12

#include <room.h>

inherit ROOM;

void create()
{
    	  set("short", "尚书府大门");
        set("long",@LONG

你来到尚书府大门。门上悬挂着一块很大的黑色牌匾，上面用隶
书写着三个金字「尚书府」。牌匾上的一行小字表明这是当今皇
上所题，可以看出其官势显赫。
LONG
        );

        set("exits", ([
             "north" :        "/d/city/zhuque-e2",
             "east" :        __DIR__"yuan",
        ]));

        set("objects", ([
             __DIR__"npc/guard":     1,
        ]));

	set("area","长安城");
       set("outdoors", "长安城");
	set("no_clean_up", 0);
       create_door ("east", "大铁门", "west", DOOR_CLOSED);

        setup();
}

int valid_leave(object me,string dir)
{
	object ob;
	string banghui;
	object lp;
	mapping data;

       if( wizardp(me)) return 1;

	if( !userp(me)) return ::valid_leave(me,dir);

	if(! (ob=present("guard",environment(me))) && ! living(ob))
		return ::valid_leave(me,dir);

	banghui=(string) me->query("banghui");
	lp=new("/obj/lingpai");
	lp->create(banghui);
	data=lp->query("area");
	destruct(lp);
	if(! mapp(data))	data=([]);
	if( data[query("area")])	{
		return ::valid_leave(me,dir);
	}

	if(!me->query_temp("oldsix/can_leave") && dir=="east")	{
	message_vision("$N伸手拦住了去路，挡在$n面前道：先交了买路钱再说，不多"+
MONEY_D->money_str(ob->query("money_need"))+"。\n",
		ob,me);
		return notify_fail("\n");
	} else

	if(me->query_temp("oldsix/can_leave") && dir=="east")	{
		me->delete_temp("oldsix/can_leave");
		return ::valid_leave(me,dir);
	} 
	return ::valid_leave(me,dir);
}
