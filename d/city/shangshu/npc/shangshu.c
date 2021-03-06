//Creat by waiwai@2001/05/19

inherit NPC;
#include <ansi.h>
int promote_me(object ob);

void create()
{
        set_name(HIR"庾子建"NOR, ({ "shangshu","yu" }));
	set("title", HIY "朝廷一品官 吏部尚书" NOR );
        set("gender", "男性");
        set("age", 54);
        set("long",
        "他是当今皇上身边的红人，与宫中的关系也很熟络，手中掌管着\n"
		"升降官员大权,不过能爬上这个位置，绝不是仅仅因为溜须拍马的缘\n"
		"故，当年战功赫赫，才有今天的地位。\n"
		);

        set("vendetta_mark", "authority");
        set("attitude", "peaceful");
        set("str", 27);
        set("int", 25);

  set_skill("literate", 800);
  set_skill("spear", 800);
  set_skill("force", 800);
  set_skill("dodge", 800);
  set_skill("parry", 800);
  set_skill("mace", 800);
  set_skill("archery", 800);
  set_skill("wusi-mace", 800);
  set_skill("yanxing-steps", 800);
  set_skill("bawang-qiang", 800);
  set_skill("lengquan-force", 800);
  set_skill("unarmed", 800);
  set_skill("changquan", 800);
  set_skill("spells", 800);
  set_skill("baguazhou", 800);
  map_skill("spells", "baguazhou");

  map_skill("mace", "wusi-mace");
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  set("max_sen", 6000);
  set("max_kee", 6000);
  set("force", 6000);
  set("max_force", 6000);
  set("force_factor", 300);
  set("mana", 6000);
  set("max_mana", 6000);
  set("mana_factor", 300);
        set("rank",1);
	 create_family("朝廷", 5, "尚书");
        set("class", "officer");

        set("office_number", 6000);

	set("inquiry", ([
            "加官进爵" :  (: promote_me :),
             "升官" : (: promote_me :),]) );

        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
            (: command ("alert") :),
            (: command ("alert") :),
            (: command ("alert") :),
	(: perform_action, "mace", "jianshen" :),
                        }) );

        setup();

  carry_object("/d/obj/armor/tiejia")->wear();
  carry_object("/d/obj/weapon/mace/copperjian")->wield();
}

int promote_me(object ob)
{
	int exp,mpzc;
       ob=this_player();

if(ob->query("family/family_name") == "大唐将军府")
		{
		exp=ob->query("combat_exp");
		mpzc=ob->query("mpzc");	
		if(exp<250000)
			{
			command("say 就凭你？这点小功劳就想升官？？？甭想！！！");				
			return 1;
		    }
		if(ob->query_temp("ASK_TO_RISE")<1)
			{
			ob->set_temp("ASK_TO_RISE",1);
			}
		else
			{
			command("say 皇上刚刚去后宫了，过一段时间你再来吧");
			return 1;
			}
	    if(exp>=250000&&exp<500000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIY"大唐将军府偏将军"NOR);
			ob->set("rank",6);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=500000&&exp<1000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIY"大唐将军府威东将军"NOR);
			ob->set("rank",5);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=1000000&&exp<1250000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIW"大唐将军府破虏将军"NOR);
			ob->set("rank",5);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=1250000&&exp<1500000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIW"大唐将军府荡寇将军"NOR);
			ob->set("rank",5);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=1500000&&exp<1750000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIW"大唐将军府奋威将军"NOR);
			ob->set("rank",4);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=1750000&&exp<2000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIG"大唐将军府建威将军"NOR);
			ob->set("rank",4);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=2000000&&exp<2250000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIG"大唐将军府征虏将军"NOR);
			ob->set("rank",4);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=2250000&&exp<2500000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIG"大唐将军府左将军"NOR);
			ob->set("rank",3);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=2500000&&exp<2750000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIB"大唐将军府平东将军"NOR);
			ob->set("rank",3);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=2750000&&exp<3000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIB"大唐将军府安东将军"NOR);
			ob->set("rank",3);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=3000000&&exp<3500000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIC"大唐将军府镇东将军"NOR);
			ob->set("rank",2);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=3500000&&exp<4000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIC"大唐将军府征东将军"NOR);
			ob->set("rank",2);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=4000000&&exp<5000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIC"大唐将军府卫东将军"NOR);
			ob->set("rank",2);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=5000000&&exp<6000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIM"大唐将军府车骑将军"NOR);
			ob->set("rank",1);
            message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users()); 
			return 1;
			} 
	    if(exp>=6000000&&exp<8000000)
			{
			command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
			ob->set("title",HIM"大唐将军府骠骑将军"NOR);
			ob->set("rank",1);
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 
	    if(exp>=8000000)
			{
			if(mpzc>5000&&ob->query("mark/chaotingtask")
			 &&(int)ob->query("mark/chaotingtask")>2)
				{
		       // 野羊山。和全国军事地图。
                	        command("say 佩服！佩服!!!这位"+RANK_D->query_respect(ob)+"，不但对皇上忠心耿耿！");
				command("say 而且战功彪炳。我一定替你在皇上面前美言几句。。。");
				ob->set("title",HIW"大唐将军府兵马大元帅"NOR);
				ob->set("rank",1);
				}
			else
				{
				command("say 好！好！好，我立即奏明皇上，为你加官进爵！！！");
				ob->set("title",HIM"大唐将军府护国大将军"NOR);
				ob->set("rank",1);
				}
			message("vision",HIR"庾子建:皇上御旨,昭封 "+ob->name()+" 为 "+ob->query("title")+"\n"NOR,users());	
			return 1;
			} 

		}
else
		{
		command("say 滚！！！如此贱民也想升官发财？？？");
		return 1;
		}

}
void init()
{
		object ob;
		::init();
if( interactive(ob = this_player()) && !is_fighting() )
	    {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
 if((string)ob->query("family/family_name") != "大唐将军府")
//  if( (int)ob->query("PKS")-ob->query("BCF")*2 > 15 ) 
  if( (int)ob->query("PKS") > 1 )  
	{
        command("say 好个沾满血腥的凶徒，竟敢在此撒野，来人!给我拿下!");
      	kill_ob(ob);
       }
      else {
command("say 尔等如有冤情，可向各地方官申述!");
}
}
int accept_object(object who, object ob)
{
        object gold;
         if((string)who->query("family/family_name") == "大唐将军府"
          && ob->query("军事详图")=="YES"
          && this_object()->query("have_give_gold")!=1
          && ob->query("material")=="copper")
          {
          who->add("mpzc",50);
          gold=new(GOLD_OB);
          gold->set_amount(50);
          gold->move(who);
          if(who->query("mark/chaotingtask"))
	      who->add("mark/chaotingtask",1);
          else who->set("mark/chaotingtask",1);
          set("have_give_gold",1);
          call_out( "todest",1,ob );
          command("say 此乃朝廷急需之物，本部堂即刻奏明圣上，必有旨意！\n");
          return 1;
          }
           }
void todest(object ob)
{
		destruct(ob);
}

