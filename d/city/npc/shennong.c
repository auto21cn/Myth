//美容师,神农氏

#include <ansi.h>
inherit NPC;

int ask_ge();
int ask_la();
int ask_long();
int ask_sex();

void create()
{
        set_name(HIW"神农氏"NOR,({"shennong shi","meirong shi","shi"}));
        set("title",HIR"炎帝"NOR);
        set("nickname",HIC"尝百草，救众生"NOR);
        set("long",
                "\n这便是闻名天下的神农氏，只见他鹤发童颜，年纪虽大，但却健硕无比。\n"
                "他现在是三界神话的美容师,专门负责对容貌不佳的玩家进行美容服务。\n"
                "美容可是高消费哦,听说割双眼皮要1000gold，拉皮3000gold，隆胸5000gold，\n"
                "至于变性嘛,属于超前消费,一口价10000gold。\n");
        set("gender","男性");
        set("age",180);
        set("per",40);
        set("str",30);
        set("int",40);
        set("attitude", "friendly");    
        set("max_kee",50000);
        set("kee",50000);
        set("max_sen",50000);
        set("sen",50000);
        set("max_force",80000);
        set("force",80000);
        set("max_mana",80000);
        set("mana",80000);
        set("combat_exp",100000000);
        set("daoxing",100000000);
        set("force_factor", 500);
        set("mana_factor", 500);

        set_skill("blade",500);
        set_skill("dodge",500);
        set_skill("parry",500);
        set_skill("unarmed",500);
        set_skill("dragonfight",500);
        set_skill("kugu-blade",500);

        map_skill("dodge","kugu-blade");
        map_skill("parry","kugu-blade");
        map_skill("blade","kugu-blade");
        map_skill("unarmed","dragonfight");

        set("inquiry", ([
                "割双眼皮":(: ask_ge :),
                "隆胸":(: ask_long :),
                "拉皮":(: ask_la :),
                "变性":(: ask_sex :),
        ]) );

        set("chat_chance_combat", 80);

        set("chat_msg_combat", ({
                "\n神农氏摇头叹道：螳臂当车，不自量力。唉，你这又是何苦呢？\n",
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat 这位" + RANK_D->query_respect(this_player())+",你我无冤无仇，何必如此？\n") :),         
                (: perform_action, "blade", "diyu" :),
                (: exert_function, "recover" :),                          
        }) );
        setup();

        carry_object("/d/city/obj/dao")->wield();
        carry_object("/d/city/obj/dagua")->wear();
}

int ask_ge()
{
        object me = this_player();
         
        if (me->query("beauty_ge")=="done"){
//      command("hit"+ me->query("id"));
        tell_object(me,"你已经割过双眼皮了，还要割，难道你想割成三眼皮？ \n");
        return 1;
        }
        if (me->query("per")>=25){
        command("shake " + me->query("id"));
        tell_object(me,"你本来就是双眼皮，还割什么？ \n");
        return 1;
        }
        if (me->query("balance")<10000000){
//         command("slap " + me->query("id"));
         tell_object(me,"穷光蛋，饭都吃不饱，还来美容！ \n");
         return 1;
         }
        else {
                me->set("beauty_ge","done");
                me->add("per",1);
                me->save();
                me->add("balance",-10000000);
                command("ok " + me->query("id"));
                message("channel:chat",HIY+"【神农氏】：听说 "+me->query("name")+" 在神农草屋割了双眼皮！\n"+NOR,users());
                me->unconcious();
                
                return 1;
        }       
        return 1;
}

int ask_long()
{
        object me = this_player();
        
        if (me->query("gender")!="女性"){
//      command("slap " + me->query("id"));
        tell_object(me,"你变态呀，男的还来隆胸？？？？\n");
        message("channel:chat",HIY+"【神农氏】："+me->query("name")+" ！！你这个变态，男人居然跑到神农草屋来做隆胸！\n"+NOR,users());
        return 1;
        }        
        if (me->query("beauty_long")=="done"){
//      command("hammer " + me->query("id"));
        tell_object(me,"你的胸部都隆的和气球一样大了，还隆？ \n");
        return 1;
        }
        if (me->query("per")>=25){
        command("heihei " );
        tell_object(me,"你的胸部已经不小了！ \n");
        return 1;
        }
        if (me->query("balance")<50000000){
  //      command("slap " + me->query("id"));
        tell_object(me,"穷光蛋，饭都吃不饱，还来隆胸！ \n");
        return 1;
        }
        else {
                me->set("beauty_long","done");
                me->add("per",3);
                me->save();
                me->add("balance",-50000000);
                command("ok " + me->query("id"));
                message("channel:chat",HIY+"【神农氏】：听说 "+me->query("name")+" 在神农草屋做了一个隆胸手术，胸围增大了XX寸！\n"+NOR,users()); 
                me->unconcious();

                return 1;
        }       
         return 1;
}

int ask_la()
{
        object me = this_player();
         
        if (me->query("beauty_la")=="done"){
//      command("sigh " + me->query("id"));
        tell_object(me,"经常拉皮对身体不好！不要为了美容而伤了身体！ \n");
        return 1;
        }
        if (me->query("per")>=25){
//      command("pat " + me->query("id"));
        tell_object(me,"你的皮肤很好，不用拉了，再拉就拉成沙皮狗了！\n");
        return 1;
        }
        if (me->query("balance")<30000000){
  //       command("kick " + me->query("id"));
        tell_object(me,"穷光蛋，饭都吃不饱，还来美容！ \n");
        return 1;
         }
        else {
                me->set("beauty_la","done");
                me->add("per",2);
                me->save();
                me->add("balance",-30000000);
                command("nod " + me->query("id"));
                message("channel:chat",HIY+"【神农氏】：听说 "+me->query("name")+" 在神农草屋拉了个皮，变的年轻多了！\n"+NOR,users());
                me->unconcious();
                
                return 1;
        }       
        return 1;
}

int ask_sex()
{
        object me = this_player();

        tell_object(me,HIG"宇文无忧说我乱改男女性别，有违天道，已经让我从此禁止变性了！ \n");
        return 1;

        
        
}    


/*
int ask_sex()
{
        object me = this_player();

        if (me->query("beauty_sex")=="done"){
//      command("sigh " + me->query("id"));
        tell_object(me,"你这人是不是有毛病呀？当你的身体是泥巴捏的呀？随便乱搞！ \n");
        return 1;
        }

        if (me->query("balance")<100000000){
  //       command("kick " + me->query("id"));
        tell_object(me,"穷光蛋，饭都吃不饱，还来变性！ \n");
        return 1;
         }
        else {
                me->set("beauty_sex","done");
                
                if(me->query("gender")=="女性") 
                        me->set( "gender", "男性" );
                else me->set( "gender", "女性" );
                me->add("balance",-100000000);
//              me->add("per",-3);
                command("nod " + me->query("id"));
                message("channel:chat",HIY+"【神农氏】：听说 "+me->query("name")+" 在神农草屋做了个变性手术！\n"+NOR,users());
                me->unconcious();
                
                return 1;
        }       
        return 1;
}    
*/

   

