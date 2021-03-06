inherit NPC;
int give_magic();
void create()
{

        set_name("魔法师", ({ "magic wizard" }) );
        set("race", "人类");
        set("age", 3000);
        set("long", "拥有无上魔法点的魔法师。\n");
        set("str", 20);
        set("cor", 30);
        set("max_force", 3000);
        set("mana", 5000);
        set("force", 5000);
        set("max_mana", 3000);
        set("force_factor", 100);
        set("mana_factor", 150);
        set("max_kee", 2000);
        set("max_sen", 2000);
        set("verbs", ({ "bite", "claw"}) );
            set_temp("position/xx",18+random(5));
            set_temp("position/yy",18+random(5));
            set_temp("position/zz",0);

        set("combat_exp", 1000000+random(1000000));
        set("daoxing", 5000000);

       set_skill("dodge", 160);
       set_skill("unarmed", 100);
       set_skill("parry", 160);
       set_skill("moshenbu", 160);
       set_skill("force", 160);
       set_skill("wuxiangforce", 160);
       set_skill("sword", 200);
       set_skill("sanqing-jian", 200);
       set_skill("dao", 200);
       set_skill("spells", 200);
       map_skill("force", "wuxiangforce");
       map_skill("parry", "sanqing-jian");
       map_skill("sword", "sanqing-jian");
       map_skill("dodge", "moshenbu");
       map_skill("spells", "dao");
         set("hell_skill/dodge", 160);
         set("hell_skill/unarmed", 100);
         set("hell_skill/sword", 100);
         set("chat_chance_combat", 30);
         set("chat_msg_combat", ({
        (: cast_spell, "light" :),
        (: cast_spell, "thunder" :),
        (: cast_spell, "dingshen" :)
       }));
        set_temp("apply/armor", 80);
        set_temp("apply/damage",80);
        set_temp("apply/armor_vs_force",300);
        set_weight(1000000);
        set("hell_type","魔法师");

            set("inquiry", ([
            "name"    : "我是地狱火的魔法师！拥有无上的魔法点",
            "magic"    :(:give_magic:),
            "魔法点"    :(:give_magic:),
               ]));
        setup();
        carry_object("/d/obj/weapon/sword/changjian")->wield();

        carry_object("/d/obj/armor/tongjia")->wear();
}


void init()
{

        add_action("do_cast", "cast");
        add_action("do_perform", "perform");
        add_action("do_ji", "ji");

}

int give_magic()
{
        object me,who;
        me =this_object();
        who=this_player();
      if(who->query_temp("position/xx") != me->query_temp("position/xx") 
        || who->query_temp("position/yy") != me->query_temp("position/yy")) 
       {tell_object(who,"你不在"+me->name()+"方位，怎么问呀？\n");return 1;}

        if(me->is_fighting())
               { command("say 慢慢来，不要急。\n");return 1;}
        if(who->query("balance")<1000000)
                {tell_object(who,"你的黄金存量不够!\n");return 1;}
         tell_object(who,me->name()+"说一百两购买一次，可给你增加魔法点2000点！你如果确实要买请输入yes,否则输入no。\n");
         input_to("get_com",who);
         return 1;
}


void die()
{
   return;
}
int get_com(string msg,object who)
{
        if(msg=="yes")
        {
                who->add("balance",-1000000);
                who->add("magic_pointed",2000);
                write("魔法师说：很高兴和你交易，随时为你效劳。\n");
                return 1;
        }
        else if(msg=="no")
               {
                write("魔法师说：哎，下次再为你效劳。\n");
                return 1;
        }
        write("魔法师说一百两购买一次，可给你增加魔法点2000点！你如果确实要买请输入yes,否则输入no。\n");
       input_to("get_com",who);
        return 1;
}

int do_cast(string arg)
{
        object who = this_player();
        object me = this_object();
        message_vision("$N张开嘴，结结吧吧地念了几声咒语。\n", who);
        message_vision ("$N对$n摇了摇头。\n", me, who);
        return 1;
}



int do_perform(string arg)
{
        object who = this_player();
        object me = this_object();
        message_vision("$N脸色不大对，好象动了杀机！\n", who);
        message_vision ("$N对$n摇了摇头。\n", me, who);
        return 1;
}

int do_ji(string arg)
{
        object who = this_player();
        object me = this_object();
        message_vision("$N偷偷把手伸进怀里，想用什么法宝！\n", who);
        message_vision ("$N对$n摇了摇头。\n", me, who);
        return 1;
}

