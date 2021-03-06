// Crack By stey

inherit NPC;

#include <ansi.h>
#include "pfm.h"
string ask_xiaoxi();
string ask_shimen();
void _leave();
void leave();
void copy_status(object me, int level);
void set_skills(int max_value, int level);
void set_hp_status(object me, int level);
void to_escape();


object owner() {return query("owner");}


string *dirs1 = ({
  "/d/qujing/baotou", 
  "/d/qujing/baoxiang", 
  "/d/qujing/biqiu",
  "/d/qujing/chechi",
  "/d/qujing/dudi",
  "/d/qujing/fengxian",
  "/d/qujing/firemount",
  "/d/qujing/jilei",
  "/d/qujing/jindou",
  "/d/qujing/jinping",
  "/d/qujing/jisaiguo",
  "/d/qujing/maoying",
  "/d/qujing/nuerguo",
  "/d/qujing/pingding",
  "/d/qujing/pansi",
  "/d/qujing/tongtian",
  "/d/qujing/qilin",
  "/d/qujing/qinfa",
  "/d/qujing/qinglong",
  "/d/qujing/tianzhu",
  "/d/qujing/wudidong",
  "/d/qujing/wuji",
  "/d/qujing/xiaoxitian",
  "/d/qujing/yinwu",
  "/d/qujing/yuhua",
  "/d/qujing/zhujie",
  "/d/qujing/zhuzi",

});

string *names = ({
  "狐狸",
  "黑熊",
  "狗熊",
  "白熊",
  "蝎子",
  "蜈蚣",
  "花豹",
  "斑马",
  "黑狮",
  "黄狮",
  "豺狼",
  "老虎",
  "狮子",
  "黄狮",
  "白狮",
  "花豹",
  "山豹",
  "草豹",
  "大雕",
  "马猴",
  "猕猴",
  "猿猴",
  "灰狼",
  "野猪",
  "马鹿",
  "白鹿",
  "灰鹿",
  "黑鹿",
  "花狐狸",
  "白狐狸",
  "灰狐狸",
  "猩猩",
  "狒狒",
  "水牛",
  "牦牛",
  "野牛",
  "白鼠",
  "灰鼠",
  "黑蚂蚁",
  "蚂蚁",
  "白蚁",
});

int random_place(object me, string* dirs);

void setname()
{
object ob = this_player(); 
//object me = this_object(); 
    int i;
    string name;
    i=random(sizeof(names));
    name=names[i]+(random(2)?"精":"怪");

set_name(name, ({ob->query("id") + " yao guai"}));

}

void create()
{        
    setname();
    set("age", 100+random(80));
    set("gender", random(2)?"男性":"女性");
    set("attitude", "heroism");
    set("per", 40);
    set("str", 100);
    set("cor", 40);
    set("con", 40);
    set("int", 40);
    set("spi", 40);
    set("cps", 40);
    set("kar", 40);
    set("max_gin", 1000);
    set("food", 10000);
    set("water", 10000);
    set_weight(30000);
    set("no_steal",1);
    set("taskguai",1);
    set("questguai",1);
    set("chat_chance", 5);
    set("chat_msg", ({
	(: random_move :)
      }) );
    set("inquiry", ([
	"消息": (: ask_xiaoxi :),
	"师门": (: ask_shimen :),
      ]) );

    setup();
}

int random_place(object me, string* dirs)
{
    int  i, j, k;
    object  newob;
    mixed*  file, exit;

    if( !sizeof(dirs) )  return 0;

    i = random(sizeof(dirs));    // pick up one directory

    file = get_dir( dirs[i]+"/*.c", -1 );
    if( !sizeof(file) )             return 0;

    for(k=0;k<30;k++) { // try 30 times
	j = random(sizeof(file));
	if( file[j][1] > 0 ) {
	    newob=load_object(dirs[i]+"/"+file[j][0]);
	    if (newob) {  
		if(newob->query("no_fight") ||
		  newob->query("no_magic") ||
		  newob->query("no_mieyao") ||
		  !(exit=newob->query("exits")) ||
		  sizeof(exit)<1 ||
		  !newob->query("outdoors") )
		    continue;

		if(me->move(newob)) {
		    message_vision("$N走了过来。\n",me);
		    return 1;
		}
	    }
	}
    }

    return 0;
}



string invocation(object me, int level)
{
    object guai,env;        
    string *dirs, where;

    dirs=dirs1;
    guai=this_object();
    copy_status(me, level);

    set("owner", me);
    set("kind",me->query("rulaitask/kind"));
    set("level",level);

    if(!random_place(guai, dirs))  return "没妖怪。";

    env=environment(guai);
    where=guai->query("name");

    if(env)
	where += "在"+MISC_D->find_place(env);
    return where;


}

void copy_status(object me, int level)
{
    mapping me_skill;
    int *skill_value, max_value, i;

    me_skill = me->query_skills();
    i=sizeof(me_skill);
    if(i>0) {
	skill_value=values(me_skill);
	max_value=skill_value[0];
	while(i--) { // 找出玩家skill最大值
	    if(skill_value[i]>max_value)
		max_value=skill_value[i];
	}
    } else max_value=1;
    set("stay_time",time()+600+random(60));              
    set_skills(max_value, level);

    set_hp_status(me,level);

}         

void set_skills(int max_value, int level)
{
//  object guai=this_object();       
    int guai_value;

    if (level==1) guai_value = max_value+max_value/5;
    else if (level==2) guai_value = max_value+max_value/4;
    else guai_value = max_value+max_value/3;

    set_skill("unarmed", guai_value+random(16));
    set_skill("dodge", guai_value+random(16));
    set_skill("parry", guai_value+random(16));
    set_skill("force", guai_value+random(16));
    set_skill("spells", guai_value+20+random(16));
}       


void set_hp_status(object me, int level)
{       int max_kee,max_sen,skill_force,maximum_mana,exp,daoxing;
    max_kee = me->query("max_kee");
    max_sen = me->query("max_sen");
    skill_force = query_skill("force");
    maximum_mana = me->query("maximum_mana");
    exp = me->query("combat_exp");
    daoxing = me->query("daoxing");

    set("max_force", skill_force*10);
    set("force", skill_force*20);
    set("force_factor", skill_force/2);
    set("mana_factor", query_skill("spells",1)/3);

    if (level==1)
    {
	set("max_kee", max_kee*2);
	set("eff_kee", max_kee*3);
	set("max_sen", max_sen*3/2);
	set("eff_sen", max_sen*3/2);
	set("kee", max_kee*3/2);
	set("sen", max_sen*3/2);
	set("max_mana", maximum_mana*9/10);
	set("mana",maximum_mana*10/11);
	set("combat_exp", exp+exp*1/10+random(exp));
	set("daoxing", daoxing+daoxing*1/8+random(daoxing*1/16));
        set_temp("apply/armor", 1000);
        set_temp("apply/damage", 380);
    }

    else if (level==2)
    {
	set("max_kee", max_kee*7/3);
        set("eff_kee", max_kee*8/3);
	set("max_sen", max_sen*2);
	set("eff_sen", max_sen*2);
	set("kee", max_kee*5/3);
	set("sen", max_sen*5/3);
	set("max_mana", maximum_mana*8/9);
	set("mana",maximum_mana*9/10);
	set("combat_exp", exp+exp*1/18+random(exp*1/12));
	set("daoxing", daoxing+daoxing*1/20+random(daoxing*1/12));
        set_temp("apply/armor",1250);
        set_temp("apply/damage", 430);
    }   

    else
    {
	set("max_kee", max_kee*3);
	set("eff_kee", max_kee*3);
	set("eff_kee", max_kee*2);
	set("max_sen", max_sen*2);
        set("eff_sen", max_sen*2);
	set("kee", max_kee*2);
	set("sen", max_sen*2);
	set("max_mana", maximum_mana*8/9);
	set("mana",maximum_mana*10/11);
	set("combat_exp", exp+exp*1/10+random(exp*1/6));
	set("daoxing", daoxing+daoxing*1/10+random(daoxing*1/10));
        set_temp("apply/armor", 1500);
        set_temp("apply/damage", 580);
    }   
    if ( exp > 50000000)
    {
	add("combat_exp", exp*1/8+random(exp*1/10));
	add("daoxing", daoxing*1/8+random(daoxing*1/10));
	add_temp("apply/armor", exp/120000);

	add_temp("armor_prop/armor_vs_force", exp/50000);
	add_temp("armor_prop/dodge",exp/50000);

	//                set("force", skill_force*20);
	add("max_kee", max_kee*2);
	add("eff_kee", max_kee*2);
	add("kee", max_kee*3/2);
	add("eff_sen", max_kee*2);
	add("max_sen", max_kee*2);
	add("sen", max_kee*2);
    }
}

int accept_fight(object ob)
{       
    object me=this_object();
    if (ob != owner())
    {message_vision(CYN"$N说道：快走开，要不我吃了你。\n"NOR,me);
	return 0;
    }

    else {if ( query("kind")!="降" )
	{
	    command("say 我不找你，你倒送上门来了，我就成全了你。");
	    me->kill_ob(ob);
	    return 1;
	}
	else {  
	    if ( query("eff_kee") < query("max_kee") 
	      || query("eff_sen") < query("max_sen") )
	    {message_vision(CYN"$N说道：我受伤了，这样打不公平吧。\n"NOR,me);
		return 0;
	    }
	    command("say 废话少说，尽管放马过来，看谁怕谁。");
	    remove_call_out("check_result");
	    call_out("check_result", 1, me, ob);
	    return 1;
	}
    }                  
}                 

void init ()
{   
//  object me=this_object();
    object who=this_player();
//  int type;
    int t=query("stay_time");
    ::init();
    add_action("do_persuade", "persuade");

    if(t && time()>(t+300)) {
	remove_call_out("leave");
	call_out("leave",1);
	return;
    }

    if(t && time()>t) {
	remove_call_out("_leave");
	call_out("_leave",300);
    }
    if(!living(this_object())) return;
    if(!living(who)) return;
    remove_call_out("check_room");
    call_out("check_room",2);
}

string ask_xiaoxi()
{
    object obj;
    if(objectp(obj = query("owner")))
	return ("听说一个叫"+obj->query("name")+"("+obj->query("id")+")要来找我的麻烦,就是你么?\n");
    return ("我不知道") ;
}

string ask_shimen()
{
    return ("我可是出自名门："+query("family/family_name")+"\n");
}

void heart_beat()
{  object guai = this_object();
    ::heart_beat();

    if ( !is_fighting()
      && query("eff_kee") >= query("max_kee") / 2 
      && !query_skill("tonsillit",1)
      && !query_skill("shushan-force",1)
      && query("kind") != "降" 
      && query("eff_kee") <  query("max_kee") )
    {
	//    command("exert heal");
	set("eff_kee",query("max_kee"));
	set("eff_sen",query("max_sen"));
	//           if (random(3) =1) call_out("check2",0);
    }
    if (query("kee") < query("eff_kee")-10 && query("kind") != "降")
    {
	if(query("force")<100)        add("kee",20);
	command("exert recover");
	//          if (random(4) >3) call_out("check2",0);
    }
    if (query("sen") < query("eff_sen")-10) 
	command("exert refresh");
    if( is_busy() && random(3)>1)
	start_busy(1);
    if (query("force") < query("max_force"))
	command("cast transfer");
    if (!owner() || owner()->query("rulaitask/fail") )    
	destruct(guai);

    if (is_fighting() )
    {
        if ( random(7)==1 ) call_out("check2",0);
    }
}       


int check_result(object me, object ob)
{
    int guai_max_kee, ob_max_kee;

    guai_max_kee  = me->query("max_kee");
    ob_max_kee = ob->query("max_kee");

    if (me->is_fighting())
    {
	call_out("check_result",1, me, ob);
	return 1;
    }

    if ( !living(me) 
      || (int)me->query("kee") < 1 
      || (int)me->query("sen") < 1 ) return 1;

    if (((int)me->query("kee")*100/guai_max_kee) <= 20 )
    {
	if ( !living(me) 
	  || (int)me->query("kee") < 1 
	  || (int)me->query("sen") < 1 ) return 1;

	if (random(6) < 1)  command ("say 我还没准备好，你就开打了，不算数。");
	else { if (ob->query_temp("rulaitask/fight_time"))
	    { command ("say 我现在方知天外有天，人外有人，我还要回山多多修炼，告辞了。");
		ob->set("rulaitask/accomplish",1);
		ob->set("rulaitask/end_time",time());
		ob->delete_temp("rulaitask/fight_time");
		ob->delete("rulaitask/get");
		ob->set("rulaitask/done",1);
		destruct(me);
		return 1;
	    }

	    else { command ("say 我一时大意，也没尽全力，我不服，再比一次。");
		ob->set_temp("rulaitask/fight_time",1);
		return 1;
	    }
	}
    }

    else  {
	command("say 哈哈，你输了，我天下无敌。");
	return 1;
    }
}

int do_persuade(string arg)
{
    object me =this_player();
    object ob;
    int guai_max_kee,guai_eff_kee;

    if(!arg) return 0;
    ob = present(arg, environment(me));
    if (!ob)   return notify_fail("你要劝谁？\n");
    if (me->query("rulaitask/kind") != "劝"  || ob->query("kind") != "劝") return 0;

    if (me->is_busy())
	return notify_fail("你正忙着呢。\n");

    me->command("say 放下屠刀，立地成佛。");

    if ( !living(ob) )   return notify_fail("很显然，"+ob->name()+"听不见你说的话。\n");

    if ( me != ob->query("owner") || !ob->is_fighting(me) )
    { message_vision(CYN"$N说道：你罗嗦些什么，快滚开。\n"NOR,ob);
	return 1;
    }

    guai_max_kee = ob->query("max_kee");
    guai_eff_kee = ob->query("eff_kee");

    if ( guai_eff_kee*100/guai_max_kee < 8 )
    {
	command("say 你说的有道理，我这就回山去。");
	me->set("rulaitask/accomplish",1);
	me->set("rulaitask/end_time",time());
	me->delete("rulaitask/get");
	me->set("rulaitask/done",1);
	destruct(ob);
	return 1;
    }

    else if ( guai_eff_kee*100/guai_max_kee < 20 )
    {
	command("say 你看我现在，不比做佛快乐吗。");
	me->start_busy(1+random(3));
	return 1;
    }

    else {
	me->start_busy(3);
	return notify_fail(ob->name()+"正专心致志战斗，懒得理你。\n");
    }
}


void die()
{       object me = owner();
    if (me->query("rulaitask/kind") == "杀"  && query("kind") == "杀")
         {
        if (random(3)!=0)
       {
//
      this_object()->set("kee",this_object()->query("max_kee"));
      this_object()->set("eff_kee",this_object()->query("max_kee"));
      this_object()->set("eff_sen",this_object()->query("max_sen"));
      this_object()->set("sen",this_object()->query("max_sen"));
      call_out("to_escape",0);
          } else
	{me->set("rulaitask/accomplish",1);
	    me->set("rulaitask/end_time",time());
	    me->delete("rulaitask/get");
	    me->set("rulaitask/done",1);
    ::die();
       }
	}       
	else { me->delete("rulaitask/get");
	    me->set("rulaitask/fail",1);
    ::die();
	} 
}


int accept_object (object who, object ob)
{
    object guai;
    guai = this_object();

    if ( ob->name() != "金创药" || ob->query("id") != "jinchuang yao" )
    { message_vision(CYN"$N说道：这是什么玩意儿，想毒死我啊。\n"NOR,guai);
	return 0;
    }
    else { guai->receive_curing("kee", 100);
	guai->receive_curing("sen", 100);
	command("exert recover");
	call_out ("destruct_ob",1,ob);
	if ( query("eff_kee") == query("max_kee") )
	    message_vision(CYN"$N说道：我好了，来来来，咱们再大战三百回合。\n"NOR,guai);
	return 1;
    }
}

void destruct_ob (object ob)
{
    destruct (ob);
}

void kill_ob (object ob)
{
    object me = this_object();  
    if (me->query("level")>1)
	me->set_leader(ob);
    ::kill_ob(ob);
}

void check_room()
{
    object me=this_object();
    object env=environment(me);
    if(!living(me)) return;
    if(env && (env->query("no_fight") ||
	env->query("no_magic"))) {
	random_move();
    }
}

void to_escape()
{
    // 随机逃跑

    object guai,env;        
    string *dirs, where;
    dirs=dirs1;
    guai=this_object();

    message("vision",CYN + name() + 
                  "起个云头，将身一纵跳在半空，一拱手道：你家大爷我受伤了，没空陪你玩了，跑也！ 
。\n" NOR,environment());       
         tell_object(owner(),"你的怪逃跑了，快去追！\n");

        remove_call_out("to_escape");
        if(!random_place(guai, dirs)) return ;
        env=environment(guai);
        where=guai->query("name");
        if(env)
        where += "在"+MISC_D->find_place(env);
        owner()->set("rulaitask/where",where);
        
        return ;
}

void _leave()
{
        object me=this_object();
        if(me->is_fighting() || me->is_busy())
        return;
        leave();
}

void leave()
{
      if(this_object()) {
        if(environment())
{
          message("vision",HIB + name() + 
                  "身子一晃，变成一股青烟散去了。\n" NOR,environment());
}
        destruct(this_object());
      }
      return;
}