// /d/quest/newdomain/npc/npc3.c
// Created by kuku 2003.5.10 
      
inherit NPC; 
#include <ansi.h> 
int ask_zhou();

void create() 
{ 
        set_name( HIB "地狱使者" NOR, ({"hell envoy","envoy"})); 
        set("title",HIR+"奇幻世界探密报名处"+NOR);  
        set("long", "他看上去一脸严肃的样子。\n");  
        set("gender", "男性");  
        set("attitude", "peaceful"); 
        set("class", "xian"); 
        set("age", 16); 
        set("str", 40+random(10)); 
        set("int", 30); 
        set("per", 30+random(4)); 
        set("con", 20); 
        set("max_kee", 50000);    
        set("max_sen", 50000);     
        set("kee", 50000);   
        set("sen", 50000);    
        set("max_force", 30000);   
        set("force", 30000);  
        set("force_factor", 450);  
        set("max_mana", 30000);   
        set("mana", 30000);   
        set("mana_factor", 450);  
        set("combat_exp", 15000000);   
        set("daoxing", 15000000);  

        set("inquiry", ([   
                "奇幻探密": "你真的想去探险吗？你要知道你将去的地方是很危险的，\n"+
                "不过如果你有胆量前去一试，全身而退后还是会得到很丰厚的奖励的。\n"+
                "如果你已经决定了，请使用baoming先报名，不要走开，五分钟后我自\n"+
                "会送你进入那个神秘而充满挑战的世界。\n",
                "卷轴" : (: ask_zhou :),
        ]));
         
        setup(); 
         
        carry_object("/d/obj/cloth/linen")->wear();   
        carry_object("/d/obj/weapon/sword/qinghong")->wield();   
} 

void init ()
{
        add_action ("do_baoming","baoming");
}
             
int do_baoming (string arg)
{ 
        int tt,j,k; 
        object *ilist;    
        object me = this_object();
        object who = this_player();
        
        if(who->query("daoxing")<8000000 || who->query("level") < 80){  
                command("say 以你现在的修为去探险太危险了，还是好好练练再来吧。\n");  
                command("pat " +who->query("id"));  
                return 1;
        }       
        
        ilist = all_inventory(who);
        k=0; 
        for(j=0; j<sizeof(ilist); j++) {
                if( ilist[j]->query("pass_level")<3 ) { 
                        continue; 
                }              
                k++; 
        } 
        if(k < 1 || !present("passport III",who) ) 
                return notify_fail("你还没拿到去探险所需的通行证。\n");  
                         
        if( tt=(int)who->query("dyzz/enter") ) { 
                if(tt<=time() && time()<tt+3600) { 
                        message_vision("\n"+me->query("name")+"说道:你刚去过，先休息休息，等一个小时后再来吧。\n",who); 
                        return 1; 
                } 
        } 
        
        if(me->query("dyzz/baoming") < 5){
                message("chat",YEL"【"+HIB"地狱使者"+YEL"】："HIR"奇幻世界探密"HIW"报名工作已经开始，欢迎勇士们前往魔幻世界！\n"NOR,users());                       
                me->add("dyzz/baoming",1);   
                if(!who->query_temp("dyzz/baoming"))
                        who->set_temp("dyzz/baoming",1);                                
                command("say 五分钟后送你过去，别走开喔。\n");                  
                call_out("dyzz_enter",300,me);                  
        }
        
        if(me->query("dyzz/baoming")==5){
                command("say 人数已经够了，等一个小时后再来吧。\n");
                message("chat",YEL"【"+HIB"地狱使者"+YEL"】："HIR"奇幻世界探密"HIW"报名工作已经结束，一个小时后可以继续报名！\n"NOR,users());           
                call_out("clear",3600,me);
        }                       
        return 1;
}

int dyzz_enter(object me)
{
        object passport;
        object who = this_player();
        
        passport = present("passport III",who);
        
        if (who->query_temp("dyzz/baoming") && passport && present(who, environment(me)) ){
                message_vision("$N将通行证交给$n。\n", who,me);  
                destruct(passport);
                tell_object(who,HIR"去那里凶多吉少啊，你要好自为之，我这就送你到那充满魅力的奇幻世界，祝你好运！\n"NOR);    
                tell_room(environment(who),HIB"\n突然一股阴风平地而起，把"+who->query("name")+"刮得无影无踪。\n"NOR);
                who->set_temp("teamqy","dyzz");
                who->move("/d/quest/dyzz/saiwai");                
                who->delete("dyzz/enter"); 
                who->delete_temp("dyzz/baoming");
                who->set("dyzz/enter",time());                 
        }        
        return 1; 
} 

int clear(object me)
{
        object who = this_player();
        
        me->delete("dyzz/baoming");
        message("chat",YEL"【"+HIB"地狱使者"+YEL"】："HIR"奇幻世界探密"HIW"新一轮报名工作开始！\n"NOR,users());  
        return 1;
}         

int ask_zhou()
{
        object ob;
        object me = this_object();
        object who = this_player();
        ob = new("/d/quest/newdomain/obj/juanzhou3");
        
        if(who->query("daoxing")<8000000 || who->query("level") < 80){  
                command("say 以你现在的修为去探险太危险了，还是好好练练再来吧。\n");  
                command("pat " +who->query("id"));  
                return 1;
        }       
        
        if(!who->query_temp("task/done"))
                command("say 要想得到探险卷轴，必须先帮九幽异人完成一个任务。\n");
        else {
                command("say 干的不错，既然你这么想去探险，那我就助你一臂之力吧。\n"); 
                ob->move(who);
                message_vision("$N给了$n一个"+ob->query("name")+"。\n", me,who);
                who->delete_temp("task/done");
        }
        return 1;
}  


void die()
{
        if (environment())
        message("sound", "地狱使者「唉」的一声叹了口气！\n", environment());

        set("eff_kee", 10000);
        set("eff_gin", 10000);
        set("eff_sen", 10000);
        set("kee", 10000);
        set("gin", 10000);
        set("sen", 10000);
        set("force", 10000);
        set("mana", 10000);
}

void unconcious()
{
        die ();
}
