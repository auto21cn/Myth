// by snowcat
inherit NPC;

void create()
{
       set_name("兽官", ({"shou guan","guan"}));
       set("gender", "男性");
        set("combat_exp", 3000);
       set("age", 28);
       set("per", 40);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 70);
       set_skill("dodge", 70);
       set_skill("parry", 70);

       setup();
       carry_object("/d/obj/cloth/linen")->wear();
       add_money("gold", 2);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(3) ) {  // 1/3 chance to greet.
                case 0:
                        say( "兽官一鞠躬说道：这位" + RANK_D->query_respect(ob)
                                + "请进！\n");
                        break;
        }
}
