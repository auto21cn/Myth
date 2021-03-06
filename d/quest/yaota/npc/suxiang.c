//  /d/quest/yaota/npc/suxiang.c
// created by kuku@sjsh  2002.12.8
      
inherit NPC; 
#include <ansi.h> 
int ask_xiangyao();

void create() 
{ 
         set_name( HIW"小仙女"HIY"金身"NOR, ({"xiannv suxiang","suxiang"})); 
        set("title",HIR+"授命除妖"+NOR);  
        set("long", "这就是授命降临人间寻找降妖除魔的侠义之士的小仙女的塑像，她看上去雍容华贵，气度非凡。\n");  
        set("gender", "女性");  
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
    
        set_skill("unarmed", 600);  
        set_skill("force", 600);  
        set_skill("dodge", 600);  
        set_skill("parry", 600);  
        set_skill("spells", 600);  
        set_skill("sword", 600);  
        set_skill("snowsword",600);  
        set_skill("moonforce",600);  
        set_skill("moonshentong",600);  
        set_skill("moondance",600);  
        set_skill("baihua-zhang",600); 
        map_skill("dodge","moondance");  
        map_skill("unarmed","baihua-zhang");  
        map_skill("force","moonforce");  
        map_skill("spells","moonshentong");  
        map_skill("sword","snowsword");  
        map_skill("parry","snowsword");   
        set("chat_chance_combat", 80);  
        set("chat_msg_combat", ({ 
                (: exert_function, "recover" :),  
                (: perform_action, "sword", "hanyue" :),  
                (: perform_action, "sword", "tian" :),  
        }) );  
        set("inquiry", ([ 
                "降妖" : (: ask_xiangyao :),
        ]) );
         
        setup(); 
         
        carry_object("/d/obj/cloth/nichang")->wear();   
        carry_object("/d/obj/cloth/huazheboots")->wear();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();   
}

void init()
{
        add_action("do_kneel", "kneel");
}

int ask_xiangyao()
{
        object me;
        me = this_player();
        if (!userp(me)){ 
                command("tender"); 
                return 1;
        }
        if( me->query_temp("yaota_passnum") != 8 || me->query("yaotapass")>=3 || !pointerp(me->query_team()) ) {
                command("tender");
        }
        else{
                message_vision("少顷，$N仿佛看见神像露出满意的笑容，哇~~，圣像显灵了！\n\n",me);
                command("smile");        
                tell_object(me, "这位" + RANK_D->query_respect(me) + "在圣像面前要恭敬些，站着说话不太好吧，如果你有诚心，请给圣像磕头(kneel)。\n");
        }
        return 1;
}

int do_kneel()
{
        object me=this_player();
        if( me->query_temp("yaota_passnum") != 8 || me->query("yaotapass")>=3 || !pointerp(me->query_team()) ) 
                return notify_fail("这里不是寺庙！\n");
        message_vision(HIC "$N双手合十，恭恭敬敬地跪了下来。\n\n"NOR,this_player() );
        if(userp(me)){
        if (me->is_team_leader()){
                me->delete_temp("yaota_passnum");
                me->add("combat_exp",800000); 
                me->add("daoxing",800000); 
                me->add("potential",400000); 
                message_vision("$N听到$n轻轻的说：谢谢你帮我降妖除魔，你的武学经验、道行和潜能都增加了，这是给你的奖励，继续努力啊！\n\n",this_player(),this_object() );
                log_file("yaota","["+ctime(time())+"] "+sprintf("%s(%s)闯过妖塔，得到了80万武学、800年道行和40万潜能。\n", me->query("name"),me->query("id")));
        }
        else{
                me->delete_temp("yaota_passnum");
                me->add("combat_exp",600000);
                me->add("daoxing",600000);
                me->add("potential",300000);
                message_vision("$N听到$n轻轻的说：谢谢你帮我降妖除魔，你的武学经验、道行和潜能都增加了，这是给你的奖励，继续努力啊！\n\n",this_player(),this_object() );
                log_file("yaota","["+ctime(time())+"] "+sprintf("%s(%s)闯过妖塔，得到了60万武学、600年道行和30万潜能。\n", me->query("name"),me->query("id")));
        }
        }
        if(me->query("yaotapass")<3) 
                me->add("yaotapass", 1);
                me->set("yaota/done","done");
                me->dismiss_team();  
                me->save();
                return 1;
}
