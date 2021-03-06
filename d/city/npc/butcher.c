//NPC /d/city/npc/butcher.c
//Created by waiwai@2001/05/03

#include <allobj.h>
inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("郑屠夫", ({ "butcher", "zheng" }) );
        set("title", "镇南肉铺");
        set("gender", "男性" );
        set("age", 35);
        set("long", "你看到一个剽悍的大块头, 正在用钢刀剔牛骨。\n");
        set("str", 29);
        set("int", 14);
        set("per", 18);
        set("combat_exp", 90000);
        set("attitude", "heroism");
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("dagger", 200);

        set("vendor_goods", ([
	         "1": CITY_NPC"meat/b_beef",
	         "2": CITY_NPC"meat/hind",
	         "3": CITY_NPC"meat/tail",
	         "4": CITY_NPC"meat/zasui",
	         "5": CITY_NPC"meat/dog_m",
        ]) );

       set("changed", "长安");
	set("area_name","长安城");

        setup();
        carry_object("/obj/cloth")->wear();
        carry_object(CITY_NPC"obj/knife")->wield();
        carry_object(CITY_NPC"obj/skin_belt")->wear();
}

void init()
{
        object area,ob;
        area=new("/obj/area");
        area->create(query("area_name"));
        set("banghui",(string)area->query("banghui"));
        destruct(area);

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
       if( !ob || environment(ob) != environment() ) return;
       if( ob->query("env/invisibility") ) return;

        switch( random(4) ) {
                case 0:
                        say( "屠夫边剔骨头边嘟囔着：真是好刀，剔得好舒服! \n");
                        break;
                case 1:
                        say( "屠夫摇摇头, 叹了口气说：唉, 不知那碧玉刀究竟"
                                +"比我这刀厉害几倍...\n");
                        break;
                case 2:
                        say( "屠夫咧开大嘴, 笑着道：这位"  
                                + RANK_D->query_respect(ob)
                                + "，要买肉是吗? \n");
                        break;
                case 3:
                        say( "屠夫忙着给人取肉, 似乎没注意到你进来。\n");
                        break;
        }
}

 
