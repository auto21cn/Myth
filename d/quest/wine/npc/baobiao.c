// baobiao.c  
// created by kuku@sjsh 2002/12

#include <ansi.h>
inherit NPC;

string* dart_area=({"/d/city/dangpu","/d/dntg/hgs/pownshop","/d/city/bank",
"/d/kaifeng/dangpu"});
string* dart_short=({"董记当铺","吴家当铺","相记钱庄","当铺"});
string* dart_id=({"dong pusheng","wu benqian","tie suanpan","xu laoban"});
string* dart_name=({"董朴升","吴本钱","铁算盘","徐老板"});

string do_job();
int do_give();
int ask_cancel();

void create()
{
        set_name("李超凡", ({ "li chaofan", "li"}));
        set("gender", "男性");
        set("age", 45);
        set("title", "威远镖局总镖头");
        set("long", "他就是「威远镖局」的总镖头－－李超凡。\n");
        set("combat_exp", 30000);
        set("max_force", 500);
        set("force", 500);
        set("force_factor", 50);
        set_skill("force", 40);
        set("per",19);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set("inquiry", ([ 
                "运镖" : (: do_job :),
                "镖"   : (: do_job :),
                "工作" : (: do_job :),
                "job"  : (: do_job :),
                "米酒" : (: do_give :),
            "放弃" : (: ask_cancel :),
                 ]) );
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);
        setup();
        carry_object("/d/obj/weapon/sword/changjian")->wield();
        carry_object("/d/obj/cloth/linen")->wear();
}

string chinese_time(int t)
{
        int d, h, m, s;
        string time;
        s = t % 60;     t /= 60;
        m = t % 60;     t /= 60;
        h = t % 24;     t /= 24;
        d = t;
        if(d) time = chinese_number(d) + "天";
        else time = "";
        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
        return time;
}

string do_job()
{   
    int n;
    object ob,cart;
    ob=this_player(); 
    n=random(sizeof(dart_area));   

    if ( ob->query_temp("in_dart"))
       return "你不是才要了任务吗？\n";

    if ( !ob->query("wine/start") || !present("jiu pai",ob)) 
       return "我这里没有任务给你。\n";

    if ( (int)ob->query_condition("dart_limit" ) > 0 )
       return "你好象没完成任务吧。\n";

    if ( ob->is_busy() || ob->query_temp("pending/exercising"))
                return "你现在正忙着呢。\n";

    if ( (int)ob->query("combat_exp") < 200000 )
       return "护镖是件危险工作，我看"+RANK_D->query_respect(ob)+"似乎没有这能力！\n";

    if ( (int)ob->query_skill("force") < 60 )
       return "护镖是件危险工作，我看"+RANK_D->query_respect(ob)+"的基本内力不足！\n";
    if ( (int)ob->query("level")< 30)
       return "这位"+RANK_D->query_respect(ob)+"，你的等级太低，不够要这项任务。\n";

    ob->set_temp("in_dart",1);
    ob->set_temp("dart_area",dart_area[n]);
    ob->set_temp("dart_id",dart_id[n]);
    ob->set_temp("dart_name",dart_name[n]);
    ob->apply_condition("dart_limit", 60);

    cart=new(__DIR__"cart");
    cart->set("master",ob->query("name"));
    cart->set("masterid",ob->query("id"));
    cart->move("/d/quest/wine/biaoju");
    command("nod");
    message_vision(CYN "几个伙计将镖推了出来。\n" NOR,ob); 
CHANNEL_D->do_channel(this_object(),"rumor",ob->name()+"的镖车从震远镖局出发了,大伙并肩子上啊!");
    return ob->name(1)+"你把这批红货送到"+dart_short[n]+"的"+dart_name[n]+"手中。\n";
}

int do_give()
{
        int tt;
        object ob,jiu;
        ob=this_player();
        tt=ob->query("wine/mijiu");
        if ( !ob->query("wine/start") || !present("jiu pai",ob)) 
            {command("say 我这没有这种酒。\n");
              return 1;}
        if ( !ob->query_temp("in_dart"))
            {command("say 想要酒需要先帮我做些工作。\n");
             return 1;}
        if ( !ob->query_temp("over_dart") )
            {command("say 想要酒要先完成我给你的任务！\n");
            return 1;}
        if( tt) 
         { if(tt<=time() && time()<tt+2400) 
        { message_vision("\n"+this_object()->query("name")+"说道：你刚要过酒，等等再来吧。\n",ob); 
            return 1; } 
        }
        ob->delete_temp("in_dart");
        ob->delete_temp("over_dart");
        ob->delete_temp("dart_name");
        ob->delete_temp("dart_id");
        ob->delete_temp("dart_area");
        jiu=new("/d/quest/wine/obj/mijiu");
        jiu->move(ob);
        ob->set("wine/mijiu",time());
        command("pat "+ob->query("id"));
        command("say 不错不错，给你一杯酒寥表敬意吧。 \n"); 
        message_vision("$N给了$n一杯"+jiu->query("name")+"。\n", this_object(),ob);
        return 1;
}

int ask_cancel()
{
         object ob=this_player();
         if ( !ob->query_temp("in_dart"))
           return notify_fail("你有任务吗？\n");
         ob->delete_temp("in_dart");
         ob->delete_temp("dart_name");
         ob->delete_temp("dart_id");
         ob->delete_temp("dart_area");
         ob->apply_condition("dart_limit", 0);
         command("say 下次可不能这样啦。\n");
         return 1;
}
