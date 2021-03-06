//元始天尊
//任务NPC

inherit NPC;
#include <ansi.h>
#include "teamjob.c"

string ask_newjob();
string ask_newover();
void create()
{
       set_name(HIY"元始天尊"NOR, ({"yuanshi tianzun","tianzun", "master"}));
       set("long", "他是阐教教主，洪均老祖亲传的三大弟子之一,其法力无边，在三界之中有着举足轻重的地位。\n");
       set("title", HIW"三清之首"NOR);
       set("gender", "男性");
       set("age", 100);
       set("class", "xian");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("family/family_name", "五庄观");
       set("per", 40);
       set("int", 60);
       set("max_kee", 10000);
       set("max_gin", 10000);
       set("max_sen", 10000);
       set("force", 60000);
       set("max_force", 60000);
       set("force_factor", 750);
       set("max_mana", 10000);
       set("mana", 10000);
       set("mana_factor", 750);
       set("combat_exp", 30000000);
       set("daoxing", 200000000);

        set_skill("spells",1000);
        set_skill("force", 1000);
        set_skill("dodge", 1000);
        set_skill("parry", 1000);
        set_skill("sword", 1000);
        set_skill("wuxiangforce", 1000);
        set_skill("jindouyun", 1000);
        set_skill("wuxing-quan", 1000);
        set_skill("sanqing-jian", 1000);
        set_skill("literate", 1000);
        set_skill("unarmed", 1000);
        set_skill("dao", 300);
        map_skill("spells", "dao");
        map_skill("dodge", "jindouyun");
        map_skill("force", "wuxiangforce");
        map_skill("parry", "sanqing-jian");
        map_skill("sword", "sanqing-jian");
        map_skill("unarmed", "wuxing-quan");

        set("chat_chance_combat", 30);  
        set("chat_msg_combat", ({ 
           (: cast_spell, "light" :), 
           (: cast_spell, "thunder" :), 
           (: cast_spell, "dingshen" :) 
           })); 
        
        set("chat_chance", 1);
        set("chat_msg", ({
                "元始天尊叹了口气道：“最近妖魔为患，群魔伺机而动，有哪位神尊愿意挺身而出，铲除妖孽呢？\n",
        
        }));
        set("inquiry", ([
                "无忧无虑" : "无忧无虑乃众神之首，我甘愿俯首称臣。\n",
                "洪均老祖" : "你见到我师尊了吗？他现在可好？\n",
                "太上老君" : "我师哥潜心修道，功德无量啊！\n",
                "通天教主" : "唉，我这个师弟，又不知道最近在酝酿什么阴谋诡计。\n",
//                "功德"  : (: ask_gongde :),
                "魔界窃贼"  : (: ask_jianxi :),
                "thief" : (: ask_jianxi :),
                "守护天宫" : (: ask_newjob :),
                "job"  : (: ask_newjob :),
                "撤退"  : (: ask_newover :),

                ]));


        setup();

        carry_object("/d/lingtai/obj/shoe")->wear();
        carry_object("/d/zhuxian/obj/wuchen")->wield();
}


void init()
{
        add_action("job_over","task");
}

string ask_newjob()
{
        object *ene;
        object me = this_player();

        if(is_fighting()) 
        {
                ene=query_enemy();
                
                if(sizeof(ene)>1) 
                        return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和这"+sizeof(ene)+"位神仙切磋几下！”\n";

                if(sizeof(ene)==1) 
                        return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和"+ene[0]->name()+"切磋几下！”\n";
        }

        if(me->query_temp("mark/job_shadi")>0 ) 
                return "“"+RANK_D->query_respect(me)+"不是已有任务了吗！”\n";

        if ((int)me->query("combat_exp")<2000000) 
                return "“"+RANK_D->query_respect(me)+"修行尚浅，还是别领任务的为好！”\n";

        if ( (int)me->query_skill("force",1) < 200 )
                return "守护天宫是件危险工作，我看"+RANK_D->query_respect(me)+"的功夫不足兮！\n";

        if ((int)me->query_condition("jobshadi_failed"))
        {
                message_vision("$N对着$n摇了摇头说：逃跑失败了还来见我？\n", this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你还是别领任务的为好！”\n";
        }

        if ((int)me->query_condition("jobshadi_limit")>1)
        {
                message_vision("$N对着$n摇了摇头说：你不是正做着吗？\n", this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你快点回去铲除妖孽！”\n";
        }
     
        if ((int)me->query_condition("guojob2_busy"))
        {
                message_vision("$N对着$n摇了摇头说：现在群魔正在攻打天宫！！\n", this_object(), me);
                return "“"+RANK_D->query_respect(me)+"你等会再来！”\n"; 
        }

        message("channel:chat", HIW"【天宫急报】"HIR + "各路群魔马上要进攻天宫了！！！\n"NOR,users() );
        
        switch( random(4) ) {
                case 0:
                        me->set_temp("mark/job_shadi",1);
                        me->set_temp("carry_location","eastgate");            
                      me->apply_condition("guojob2_busy",5);
                      me->start_busy(5+random(3));
                        return "“现在群魔侵犯天宫，这位"+RANK_D->query_respect(me)+"速去东天门帮助天兵天将守护天宫吧。";

                       break;
                case 1:
                        me->set_temp("mark/job_shadi",2);
                        me->set_temp("carry_location","southgate");            
                      me->apply_condition("guojob2_busy",5);
                      me->start_busy(5+random(3));
                        return "“现在群魔侵犯天宫，这位"+RANK_D->query_respect(me)+"速去南天门帮助天兵天将守护天宫吧。";

                       break;
                        
                case 2:
                        me->set_temp("mark/job_shadi",3);
                        me->set_temp("carry_location","westgate");
                      me->apply_condition("guojob2_busy",5);
                      me->start_busy(5+random(3));
                        return "“现在群魔侵犯天宫，这位"+RANK_D->query_respect(me)+"速去西天门帮助天兵天将守护天宫吧。";

                       break;
                case 3:
                        me->set_temp("mark/job_shadi",4);
                        me->set_temp("carry_location","northgate");
                      me->apply_condition("guojob2_busy",5);
                      me->start_busy(5+random(3));
                        return "“现在群魔侵犯天宫，这位"+RANK_D->query_respect(me)+"速去北天门帮助天兵天将守护天宫吧。";

                       break;
                
        }
}


int job_over(string arg)
{
        int job_pot,job_exp,job_dx;
        object me = this_player();
        object badguy;
        object room;

        if(!arg) return 1;

        if(arg!="over") return 1;
        if(me->query_temp("help_killed")>0)
        {
                message_vision(CYN "$N冲着$n笑道：“"+RANK_D->query_respect(me)+"，为天庭效力，前途无量啊！”\n" NOR, this_object(), me);
                job_exp=((int)me->query_temp("killed_mgb"))*80;
                job_pot=job_exp/3;
                job_dx=job_exp + random(1000) - random(1000);
                job_exp=job_exp;
                me->add("combat_exp", job_exp);
                me->add("potential",job_pot);
                me->add("daoxing",job_dx);
                tell_object(me, "你被奖励了"+chinese_number(job_exp)+"点武学！"+chinese_daoxing(job_dx)+"的道行！"+chinese_number(job_pot)+"点潜能！\n");
                me->delete_temp("killed_mgb");        
                me->delete_temp("job_over");
                me->delete_temp("mark/job_shadi");
                me->delete_temp("help_killed");
                me->start_busy(2);
                me->apply_condition("guojob2_busy",6);
                return 1;
        }
                
        if(me->query_temp("mark/job_shadi")==0)
        {
                message_vision(CYN"$N瞧了$n一眼:“你没有去灭妖何来奖励？”\n",this_object(),me);
                return 1;
        }
        
        if(me->query_temp("job_over")==0)
        {
                message_vision(CYN"$N瞧了$n一眼:“妖孽未除尽兮。”\n"NOR,this_object(),me);
                return 1;
        }

        if(me->query_temp("killed_mgb")<2)
        {
                message_vision(CYN"$N瞧了$n一眼:“唉，你刚刚杀了几个妖魔？这么点作为何来领赏？。”\n"NOR,this_object(),me);
                me->delete_temp("job_over");
                me->delete_temp("mark/job_shadi");
                return 1;
          }

        message_vision(CYN "$N对$n说道：“"+RANK_D->query_respect(me)+"辛苦了，去休息一下吧！”\n" NOR, this_object(), me);
        me->delete_temp("job_over");
        me->delete_temp("mark/job_shadi");
        job_exp=((int)me->query_temp("killed_mgb"))*80;
        job_pot=job_exp/3;
        job_dx=job_exp + random(1000) - random(1000);
        job_exp=job_exp;
        if (job_exp >3000) job_exp=3000;
        if (job_pot >500) job_pot=500;
        tell_object(me, "你被奖励了"+chinese_number(job_exp)+"点经验值！"+chinese_daoxing(job_dx)+"的道行！"+chinese_number(job_pot)+"点潜能！\n");
        me->apply_condition("guojob2_busy",6);
        me->add("combat_exp", job_exp);
        me->add("potential",job_pot);
        me->add("daoxing",job_dx);
        me->delete_temp("killed_mgb");        
        me->start_busy(2);
        if (random(4) == 0)
        {
                message("channel:chat", HIW"【天庭战报】"HIR + "数位天兵天将身受重伤，已经退到了天河附近！\n"NOR,users() );
                if(objectp(room=load_object("/d/dntg/sky/dadao1")) && 
                objectp(badguy = new("/d/quest/teamjob/npc/tianbing")))
                badguy->move(room);
                room=load_object("/d/dntg/sky/dadao2");
                badguy = new("/d/quest/teamjob/npc/tianbing");
                badguy->move(room);
                room=load_object("/d/dntg/sky/dadao3");
                badguy = new("/d/quest/teamjob/npc/tianbing");
                badguy->move(room);
        }
        if (random(4) == 1)
        {
                message("channel:chat", HIW"【天庭战报】"HIR + "几个妖魔冲进了北天门，速速前来支援！\n"NOR,users() );
                if(objectp(room=load_object("/d/dntg/sky/jiashan")) && 
                objectp(badguy = new("/d/quest/teamjob/npc/yaomo2")))
                room=load_object("/d/dntg/sky/jiashan");
                badguy = new("/d/quest/teamjob/npc/yaomo3");
                badguy->move(room);
                room=load_object("/d/dntg/sky/yunlun1");
                badguy = new("/d/quest/teamjob/npc/yaomo3");
                badguy->move(room);
                room=load_object("/d/dntg/sky/yunlun2");
                badguy = new("/d/quest/teamjob/npc/yaomo2");
                badguy->move(room);
                room=load_object("/d/dntg/sky/yunlun3");
                badguy = new("/d/quest/teamjob/npc/yaomo2");
                badguy->move(room);
        }
        if (random(4) == 2)
        {
                message("channel:chat", HIW"【天庭战报】"HIR + "一大队妖孽冲进了西天门，请速来支援！\n"NOR,users() );
                if(objectp(room=load_object("/d/dntg/sky/yunluw4")) && 
                objectp(badguy = new("/d/quest/teamjob/npc/yaomo1")))
                badguy->move(room);
                room=load_object("/d/dntg/sky/yunluw3");
                badguy = new("/d/quest/teamjob/npc/yaomo1");
                badguy->move(room);
                room=load_object("/d/dntg/sky/yunluw2");
                badguy = new("/d/quest/teamjob/npc/yaomo1");
                badguy->move(room);
                room=load_object("/d/dntg/bmw/hgj4");
                badguy = new("/d/quest/teamjob/npc/yaomo1");
                badguy->move(room);
                room=load_object("/d/dntg/bmw/hgj3");
                badguy = new("/d/quest/teamjob/npc/yaomo1");
                badguy->move(room);
                
        }
        if (random(4) == 3)
        {
                message("channel:chat", HIR"【天庭战报】"HIR + "有几名法力高强的魔怪变化身形，混进了南天门，攻到了彩虹桥！\n"NOR,users() );
                if(objectp(room=load_object("/d/dntg/sky/caihongqiao")) && 
                objectp(badguy = new("/d/quest/teamjob/npc/yaomo4")))
                badguy->move(room);
                room=load_object("/d/dntg/sky/caihongqiao");
                badguy = new("/d/quest/teamjob/npc/yaomo4");
                badguy->move(room);
        }

        return 1;

}

string ask_newover()
{
         object me;
         me = this_player();
         if(me->query_condition("jobshadi_limit")<=1)
                 return "你没有消灭妖孽，不要来滥竽充数！";
         me->clear_condition("jobshadi_limit");
         me->add("combat_exp",-300+random(50));
         me->apply_condition("jobshadi_failed",10);
         me->delete_temp("mark/job_shadi");
         me->delete_temp("carry_location");
         me->delete_temp("job_over");
         me->delete_temp("start_job");
         return "坚持不懈，永不放弃。希望你下次继续努力 。";
}

int accept_fight(object me, object ob)
{       ob=this_player();
        command("say " + RANK_D->query_rude(ob) + "杀心太重，恐祸不久已！\n");
        return 0;
}
void die()
{

        if( environment() ) {
        message("sound", "\n\n元始天尊微皱眉头，道：这家伙这么厉害，也罢！！！\n\n", environment());
        command("sigh");
        message("sound", "\n元始天尊身形一转，架起一朵莲花飞上天空。。。\n\n", environment());
        }

        destruct(this_object());
}

