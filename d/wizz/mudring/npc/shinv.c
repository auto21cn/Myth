 // d/wizz/mudring/npc/shinv.c 使女

inherit NPC;

void create()
{
        set_name("老板", ({"shi nv"}) );
        set("nickname", "酒吧老板");
        set("gender", "女性" );
        set("age", 12+random(6));
        set("long",
          "这是个情蔻初开的小姑娘，一举一动都透出青春的气息。\n"
          "手脚勤快，讨人喜爱。见有人稍微示意，便过去调酒送吃的。\n");
        set("attitude", "friendly");
    set("shen_type", 1);

        set("str", 20);
        set("int", 28);
        set("con", 24);
        set("dex", 20);

        set("max_qi", 150);
        set("max_jing", 100);
        set("neili", 150);
        set("max_neili", 150);

        set("combat_exp", 1000+random(800));
        set("score", 1000);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("unarmed", 15+random(10));
        set_skill("parry", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 3);

        setup();
                carry_object("/obj/cloth")->wear();
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
        if( !ob || environment(ob) != environment() ) return;

        say("使女笑吟吟地说道：这位" + RANK_D->query_respect(ob)
             + "请先入座，" + "我这就给您调酒。\n");
}


void serve_tea(object who)
{
        object obt, obc, obn;
        object room;

        if( !who || environment(who) != environment() ) return;

        if( !who->query_temp("marks/sit") ) return;
        
        if( !objectp(room = environment()) ) return;

        if ( (int)who->query_temp("tea_cup") <= 0 )
        {
                obn = new("/d/wizz/mudring/obj/wine");
                obn->move(who);
                message_vision("使女拿出各种调酒器皿，开始摆弄起来。\n",
                        who);
        } else 
        {
                who->add_temp("tea_cup", -1);
                obn = new("/d/wizz/mudring/obj/wine");
                obn->move(who);
                message_vision("使女那出精致的绍兴小酒杯，沏了杯好酒，放在桌上．\n",
                        who);
        }

        obn = new("/d/wizz/mudring/obj/wine");
        obn->move(who);
        message_vision("使女拿出一块大雪糕，放在桌上．\n", who);
        
        return;
}

