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
	set("short", "小径");
        set("long",@LONG

尚书府的小径走到这似乎到了尽头。小径的东边是一间小屋，平
时房门总是关的，每天按时由一名又聋又哑的仆役送饭进去，其
他人一概不让入内。南边不远处就是尚书府庭院了。
LONG
        );

        set("exits", ([
                "east" :        __DIR__"xiaowu",
		"south":	__DIR__"road2",
                ]));

	set("objects", ([
		__DIR__"npc/huyuan":	1,
		]) );

	set("outdoors", "city");
	
	create_door ("east", "小木门", "west", DOOR_CLOSED);

        setup();
        replace_program(ROOM);
}

