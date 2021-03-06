// wiuxuke.c 虬须客

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
       set_name(HIR"虬须客"NOR, ({"qiu xuke", "qiu"}));
       set("long", "自幼苦修道术学习，功力仅次于大师兄，但无故离开师门，音讯全无！\n");
       set("title", HIC"天一宫"NOR);
       set("per", 30);
       set("gender", "男性");
       set("age", 35);
       set("class", "sanjie");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "老道长");
       set("max_kee", 1000);
       set("max_gin", 100);
       set("max_sen", 1000);
       set("force", 1200);
       set("max_force", 1200);
       set("force_factor", 120);
       set("max_mana", 1200);
       set("mana", 1200);
       set("mana_factor", 120);
       set("combat_exp", 1400000);
       set("daoxing", 1500000);

        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("spells", 80);  
        set_skill("tianmogong", 80);
        set_skill("literate", 80);
        set_skill("sword", 120);  
        set_skill("huxiaojian", 120);
        set_skill("zhaoyangbu", 80);
        set_skill("force", 80);   
        set_skill("huntianforce", 80);
        set_skill("unarmed", 120); 
        set_skill("huxiaoquan", 120); 

        map_skill("spells", "tianmogong");
        map_skill("force", "huntianforce");
        map_skill("sword", "huxiaojian");
        map_skill("parry", "huxiaojian");
        map_skill("dodge", "zhaoyangbu");
        map_skill("unarmed", "huxiaoquan");

	create_family("三界山", 3, "蓝");
	
	set("inquiry", ([
	"name"     : "我叫虬须客，不过我的真名不是这个，你不问也罢。\n",
	"here"     : "这是后山禁地，没有批准不能进来。不过你既然以到，也是你的缘分。\n",
	"八卦"     : "后面的八卦图可以通向天一仙府，至于你有没有这个福分，就要随缘了。\n",
	]));
	
	setup();
	carry_object("/d/sanjie/obj/jinjia")->wear();
	carry_object("/d/sanjie/obj/qinghong")->wield();
}

void attempt_apprentice(object ob, object me)
{
        command("say 很好，" + RANK_D->query_respect(ob) +"多加努力，他日必定有成。\n");
        command("recruit " + ob->query("id") );
	return;
}	

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        ob->set("class", "sanjie");
}

�
