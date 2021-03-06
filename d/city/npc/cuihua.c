/******************************************/
/* MUDLIB：Biographies         〓悟空传〓  */
/* Created Admin By Waiwai@2001/02/18     */
/* Admin Email：wkzstory@21cn.com         */
/******************************************/
// Update by waiwai@2001/04/17
// Last modified by waiwai@2002/12/05

#include <ansi.h>

inherit F_VENDOR_SALE;

void create()
{
	reload("city_cui_hua");
	set_name("翠花", ({"cui hua", "cui", "hua"}));
	set("shop_id", ({"cuihua"}));
	set("shop_title", "长安人氏");
	set("changed", "长安");
	set("gender", "女性");
	set("age", 26);
	set("per", 20);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 100);

	set("vendor_goods", ([
	    "1": "/d/city/obj/suancai",
	    "2": "/d/city/obj/zhurou",
	    "3": "/d/city/obj/mixian",
	    "4": "/d/city/obj/juhua",
	    "5": "/d/city/obj/sherou",
	]) );

	setup();
	carry_object("/d/obj/cloth/skirt")->wear();
}

void init()
{
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
	if( !ob || !visible(ob) || environment(ob) != environment() ) return;
       if( ob->query("env/invisibility") ) return;

	switch( random(3) ) {  // 1/3 chance to greet.
	    case 0:
      say ("翠花笑咪咪地说道：这位" + RANK_D->query_respect(ob)
           + "，进来喝口热酒吧\n");
	break;
	}
}

