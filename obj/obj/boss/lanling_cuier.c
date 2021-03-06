//inherit NPC;


inherit F_VENDOR_SALE;

void create()
{
        set_name("翠儿", ({"cui er"}));
        set("title", "兰陵小妹");
        set("gender", "女性");
        set("age", 22);
        set("long", "传说兰陵城外，有一位老人能找到任何神奇无比的东西，但是都托翠儿帮他卖掉。\n");

        set("combat_exp", 70000);
        set_skill("fonxansword", 30);
        set_skill("sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("moondance", 50);
        map_skill("dodge", "moondance");
        map_skill("sword", "fonxansword");
        map_skill("parry", "fonxansword");
        set("force", 200);
        set("max_force", 200);
        set("force_factor", 5);

        set("vendor_goods", ([
"mihou tao"                                          :"/d/obj/drug/mihoutao",
        ]) );

        setup();
        carry_object("/d/obj/cloth/pink_cloth")->wear();
        carry_object("/obj/loginload/shoes.c")->wear();

}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",1, ob);
        }
        add_action("do_vendor_list", "list");
        add_action("do_bid", "bid");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(3) ) {
                case 0:
                        say( name()+"：客官想买些什么？我这里都是天下少有的宝物。\n");
                        break;
        }
}
int accept_fight(object me)
{
        command("say 小女子我可不善于习武，兰陵城北有不少妖怪，你可以去试试！\n");
        return 1;
}
int do_bid(string arg)                                                       
{
        object who = this_player();                                           
        object me = this_object();                                            
        if(!arg || present(arg,environment(me))!=me) return 0;                
           command("joke "+who->query("id"));
                return 1;
}
