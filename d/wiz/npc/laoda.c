//cigar 轮回转世NPC 
 
#include <ansi.h> 
inherit NPC; 
string ask_for_leave(); 
 
void create() 
{ 
        set_name(HIW"转世轮回菩萨"NOR, ({"lunhui pusa","pusa"})); 
        set("gender", "女性" ); 
        set("age", 25); 
        set("title",HIY"眼望世间虚缈，空、无、灭"NOR); 
        set("long", HIG"\n\n佛祖如来身边掌管转世轮回的大智、无我菩萨\n\n"NOR); 
        set("combat_exp", 1000000000); 
          set("daoxing", 5000); 
 
        set("attitude", "peaceful"); 
        set("per", 40); 
        set("max_kee", 20000); 
        set("max_gin", 20000); 
        set("max_sen", 20000); 
        set("inquiry", ([ 
                "轮回转世" : (: ask_for_leave :), 
                "投胎" : (: ask_for_leave :), 
                ]) ); 
        setup(); 
        carry_object("/d/ourhome/obj/pink_cloth")->wear(); 
        carry_object("/d/ourhome/obj/shoes")->wear(); 
} 
 
void init() 
{ 
        add_action("do_agree", "agree"); 
} 
 
string ask_for_leave() 
{ 
        object me=this_player(); 
 
      if ((int)me->query("combat_exp") > 900000000 ) 
{ 
                command("say 你可思虑过？轮回转世不可儿戏，你苦练已久的武功和情感方面都要放弃。"); 
                me->set_temp("c_lunhui", 2); 
                return ("沧海桑田，无望无我，你可愿意抛弃你的一切的一切，破红尘，忘自我，离师判门，你愿意否(agree)？"); 
        } 
 
        return ("你现在转世轮回有如沧海小舟，无济于事。\n"); 
} 
 
int do_agree(string arg) 
{ 
        int i,j,level;
        mapping skill_status;
        object ob;
        string skill,obj;
        string *skills;
        
        ob=this_player();
        if(!ob->query_temp("c_lunhui")) { 
                 command("say 你从哪里来？。");
                 return 1;
                 }
        if(ob->query_temp("c_lunhui") > 1 ) { 
                message_vision("$N说道：“红尘淡淡，我欲轮回转世，超度一生的罪孽”。\n\n", ob); 
                command("say 既然如此，我现在就上奏佛祖如来，破你红尘之身，圆你超度之意！"); 
                ob->delete("betray");      //删除判师纪录 
                  ob->set("combat_exp",400000); 
         ob->set("daoxing",400000); 
         ob->set("maximum_mana",1500); 
         ob->set("maximum_force",1500); 
         ob->set("mud_age",0); 
         ob->set("class","lunhui");   
         ob->set("lunhui/lunhui",1);   
         
         if( (int)ob->query("potential") > (int)ob->query("learned_points")) 
                ob->add("potential", ((int)ob->query("learned_points") - (int)ob->query("potential")+20000)); 
             //删除此玩家所有的原始数据 
 
         ob->set("office_number",0); 
         ob->delete("qingren"); 
         ob->delete("obstacle"); 
         ob->delete("nyj"); 
         ob->delete("mieyao"); 
         ob->delete("members_level"); 
         ob->delete("lucky"); 
         ob->delete("lll"); 
         ob->delete("liyiru"); 
         ob->delete("liwuu"); 
         ob->delete("level"); 
         ob->delete("killme_number"); 
         ob->delete("kusong"); 
         ob->delete("kill"); 
         ob->delete("jjj"); 
         ob->delete("jjjj"); 
         ob->delete("gift_adjust"); 
         ob->delete("gift"); 
         ob->delete("fabao"); 
         ob->delete("faith"); 
         ob->delete("donation"); 
         ob->delete("eat_biou"); 
         ob->delete("eat_huozao"); 
         ob->delete("eat_jiaoli"); 
         ob->delete("eat_neidan"); 
         ob->delete("dntg"); 
         ob->delete("degree"); 
         ob->delete("death"); 
         ob->delete("baohuhuaxian"); 
         ob->delete("baohu"); 
         ob->delete("bld"); 
         ob->delete("added_title"); 
         ob->delete("PKS"); 
         ob->delete("PKD"); 
         ob->delete("MKS"); 
         ob->delete("HellZhenPass"); 
         ob->delete("DIE"); 
         ob->delete("pfmjinlei"); 
         ob->delete("rebirth"); 
         ob->delete("rsg_eaten"); 
         ob->delete("rulaitask_log"); 
         ob->delete("rulaitaskjob"); 
         ob->delete("secmieyao_killedtime"); 
         ob->delete("shengao"); 
         ob->delete("shengri"); 
         ob->delete("shushan"); 
         ob->delete("soilder"); 
         ob->delete("soilder_pay"); 
         ob->delete("task_job"); 
         ob->delete("xndc"); 
         ob->delete("xndcc"); 
         ob->delete("xndf"); 
         ob->delete("xujl"); 
         ob->delete("zhailiwu_time"); 
         ob->delete("ziyougift"); 
         ob->delete("wuji_bonus"); 
 
              //给此玩家设定转世之后的属性 
 
         ob->set("str",40); 
         ob->set("cor",40); 
         ob->set("int",30); 
         ob->set("spi",40); 
         ob->set("cps",40); 
         ob->set("per",30); 
         ob->set("con",40); 
         ob->set("kar",30); 
 
 
    // 删除此玩家所有的基本skill，别的skill留给player没法子自己要放弃，除非脑子怀掉了！ 
               if ( (skill_status = ob->query_skills()) || sizeof(skill_status) )
                   {
                skills  = keys(skill_status);
                j = sizeof(skill_status);  
                for(i=0; i<j; i++) {
                               ob->delete_skill(skills[i]);
                                write("deleting->" + to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")\n"); 
                                   }
                     }     
                                     
                   
 
                 
                ob->delete("family"); 
                ob->set("title", HIW"转世轮回"+ HIY"空有一切似云烟"NOR); 
                ob->add("lunhui_zhuanshi", 1); 
                ob->delete_temp("betray"); 
                ob->save(); 
                command("say 你现在极限无量！\n"); 
                command("chat 所有一切众生类摄。若卵生若胎生若湿生若化生。若有色若无色。若有想若无想。若非有想若非无想。乃至众生界及假名说。\n"); 
                command("chat 不应生住法心。不应生住非法心。不应生有所住心。何以故。若心有住则为非住故。\n"); 
                command("chat 轮回转世空空荡去，世间万物终有一度，"+ob->query("name")+"破红尘之身，化世俗凡念，心归我佛，轮回转世了。\n"); 
                return 1; 
        } 
} 
 

