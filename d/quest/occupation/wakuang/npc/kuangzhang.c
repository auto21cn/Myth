// Created by kuku@sjsh  2003.1
// 选择职业的npc

inherit NPC;
string apply_occupation(object me);
int ask_leave();

void create()
{
        set_name("老矿长", ({"lao kuangzhang", "kuangzhang","lao"}));
        set("age", 52);
        set("gender", "男性");
        set("int", 35);
        set("long","他是矿工职业工会负责申请职业的老矿长，要想进入矿工工会找他没错。\n");
        set("attitude", "friendly");
        set("combat_exp", 40000);
        set("daoxing", 100000);
        set("max_force", 400);
        set("force", 400);
        set("force_factor", 5);
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("literate", 150);
        set("inquiry", ([   
                "职业" : (: apply_occupation :),
                "leave": (: ask_leave :),
        ]) );
        setup();
        carry_object("/d/obj/cloth/linen")->wear();
}

void init()
{
        add_action("do_yes","yes");
        call_out("greeting", 1, this_player());
        ::init();
}

void greeting(object who) 
{
        if( !who || environment(who) != environment() ) return;
        if( !who->query("occupation") ) {
                tell_object(who,"老矿长悄悄告诉你：来我们矿工协会(ask kuangzhang about 职业)吧，有很多好处喔。\n");  
        }
}

string apply_occupation(object me)
{
        me=this_player();
        if( me->query("occupation")!= 0 && me->query("occupation") != "矿工"){
                return "你不是已经有职业了吗？\n";
        } 
        if( me->is_busy() || me->is_fighting() )
                return "你先忙完再说吧。\n";
                 
        if( this_object()->is_busy() || this_object()->is_fighting())
                return "我正忙着呢，等等。\n";
                 
        if (me->query("balance") < 1000000)
                return "你的存款不够付会费。\n";
                
        if(me->query("occupation") == "矿工"){
                write("你想换职业？要换职业请先离开(ask kuangzhang about leave)矿工协会。\n");
                return "三思而后行啊，换职业可是要付出很大代价的喔。\n";
        }
        me->set_temp("need_zhiye", 1);
        write("我这里只能申请【矿工】这个职业，你确定(yes)要这个职业吗？\n");
        return "欢迎各界人士光临矿工协会！\n";
}

int do_yes()
{
        object me = this_player();
        object ob = this_object();
        
        if (me->query("occupation") != 0)
                return notify_fail("你不是已经有职业了吗？\n");
                
        if (me->query("balance") < 1000000){
                command("say 进入职业工会要交纳一定数量的会费，你目前还没那么多钱入会吧。\n");
                return 1;
        }       
        if(me->query_temp("need_zhiye")) {              
                command("say 进入职业工会要交纳一定数量的会费，离开工会预交款不予退回。\n");
                tell_object(me,"你的存款被扣除一百两黄金。\n"); 
                me->add("balance",-1000000);
                me->set("occupation","矿工");
                tell_object(me,"你选择了"+me->query("occupation")+"作为你今生的职业。\n");  
                write("好好奋斗吧，他日一定有所作为！\n");
                me->delete_temp("need_zhiye");
                me->save();
                return 1;
        }
        return 0;
}

int ask_leave()
{
        object me = this_player();
        object ob = this_object();
        
        if (!me->query("occupation") || me->query("occupation") != "矿工"){
                write("找错地方了吧？\n");
                return 1;
        }
        if ( me->query("occupation") == "矿工" && me->query("work/wakuang") < 50 ){
                write("才做这么点工作就想离开，早了点吧？\n");
                return 1;
        }
        
        if (me->query("balance") < 1000000){
                write("你的存款不够付手续费。\n");
                return 1;
        }
        
        command("sigh " +me->query("id"));  
        command("say 人各有志，既然你去意已绝，也只好由你去了。\n");  
        command("say 离开工会要交一定数量的手续费，想开点吧。\n");
        tell_object(me,"你给了老矿长一百两黄金。\n"); 
        me->add("balance",-1000000);
        me->delete("work/wukuang");
        me->delete("occupation");
        return 1;
}
