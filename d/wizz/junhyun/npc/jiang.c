inherit NPC;
string gloat();
string ask_me();

void create()
{
  set_name("姜子牙", ({ "jiang ziya", "jiang" }));
  set("title", "情人的敌人->情敌");
  set("gender", "男性");
  set("age", 65);
  set("str", 100);
  set("per", 100);
  set("cor", 100);
  set("cps", 100);
  set("long","

");
  set("combat_exp", 3000000);
  set("daoxing", 2000000);

 set("family/family/name", "轩辕古墓"); 
  set_skill("unarmed", 100);
  set_skill("force", 250);
  set_skill("jiuyin-force", 250);
  set_skill("mace", 300);
  set_skill("dodge", 300);
  set_skill("parry", 300);
  set_skill("spells", 80);
  set_skill("yinlei-mace", 250);
  set_skill("youming-spells", 40);
  set_skill("kongming-steps", 240);
  map_skill("force", "jiuyin-force");
  map_skill("spells", "youming-spells");
  map_skill("mace", "yinlei-mace");
  map_skill("parry", "yinlei-mace");
  map_skill("dodge", "kongming-steps");
  set_temp("apply/armor", 600);
    set_temp("apply/damage", 350); 
    set_temp("apply/dodge", 350); 
  set("max_sen", 3000);
  set("max_kee", 5000);
  set("force", 3000); 
  set("max_force", 3000);
  set("force_factor", 250);
  set("max_mana", 3000);
  set("mana", 3000);
  set("mana_factor", 500);
  set("inquiry", ([
        "name"     : "老夫就是姜子牙。",
        "王贵人"     : (: gloat :),
        "打神鞭"     : (: ask_me :),
]) );


  setup();
  carry_object("/d/obj/weapon/mace/yuxian")->wield();
  carry_object("/d/obj/armor/tongjia")->wear();
}

string gloat()
{
    command("say 当年老夫游历朝歌，见到她已经知道她非常类。");
    command("say 听说他和妲己从封神台跑出来了，唉……");
    return "你可要小心，不要被这种妖精迷惑啊。";
}
string ask_me()
{
    command("smile");
    command("say 想拿老夫的打神鞭？果然是后生可畏啊。");
    command("haha");
    command("say 只要你能接我三鞭，我便将这打神鞭送于你。");
    this_player()->add_temp("pending/jjf/to_be_hit", 1);
    return "你可愿意一试？(yuanyi)";
}

void init()
{
    ::init();

    add_action("do_agree", "yuanyi");
    add_action("do_agree", "agree");
}

int do_agree(string arg)
{
    object me=this_player(), npc=this_object(), ob;
           object mace;
    string myname=me->name(), myrude=RANK_D->query_rude(me);

    if (!me->query_temp("pending/jjf/to_be_hit"))
        return 0;
    me->delete_temp("pending/jjf/to_be_hit");
    set("force", 2*query("max_force"));
    set("force_factor", 250);
    if (!(ob=query_temp("weapon"))
     || ob->query_temp("skill_type") != "mace")
    {
        destruct(ob);
        ob=new("/d/obj/weapon/mace/yuxian");
        ob->move(npc);
        command("wield mace");
    }
    command("say 好，好，好，年轻人有胆量！看好了这第一鞭。\n");
    COMBAT_D->do_attack(npc, me, query_temp("weapon"));
    if(me->query("kee") < 0
    || !present(me, environment()))
    {
        command("say 唉，"+myname+"一下都经不住，还是回去多练两年吧！\n");
        return 1;
    }
    command("say 不错，不错，看看这第二鞭的厉害。\n");
    COMBAT_D->do_attack(npc, me, query_temp("weapon"));
    if(me->query("kee") < 0
    || !present(me, environment()))
    {
        command("say "+myname+"能经住这打神鞭一下子已经不容易了，年轻人还需努力啊！\n");
        return 1;
    }
    command("say 好样的！能挨两记打神鞭！看好这第三鞭．．．\n");
    COMBAT_D->do_attack(npc, me, query_temp("weapon"));
    if(me->query("kee") < 0
    || !present(me, environment()))
    {
        command("say 唉，"+myname+"难为你了，回去养伤吧，下次我们再切磋切磋。\n");
        return 1;
    }
    command("say "+myname+"不错，不错，真是长江后浪推前浪啊，我老了．．．．．．\n");
    command("say  唉 后人果然厉害啊，我便将这打神鞭送于你，切忌不要做伤天害理的事情啊，否则上天定不饶你
。\n");
    mace=new("/d/wizz/junhyun/obj/mace.c"); 
   mace->move(me);
    return 1;
}
/*
int accept_fight(object me)
{
  command("say 老夫久未和江湖人动手过招了，今日也不想破例。");
  return 0;
}

void attempt_apprentice(object me)
{
  int effstr=(int)(me->query("str"));
  int myuna=me->query_skill("unarmed", 1)/10-2;
  string myrude=RANK_D->query_rude(me);

  if (myuna < 0) myuna=0;
  effstr+=myuna;
  if (effstr<30)
    {
      command("say "+myrude+"这点劲连只蚂蚁都捏不死，还能抡斧头？");
      return 0;
    }
  if (me->query_cor()<30)
    {
      command("say "+myrude+"见了血，还不得吓破了胆儿？不收！");
      return 0;
    }
  command("ah");
  command("say 想不到我老程这三脚猫本事也能收徒。\n");
  command("recruit " + me->query("id") );
  return;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "fighter");
}
int prevent_learn(object me, string skill)
{
  if (skill =="spells" || skill == "baguazhou")
    {
      command("say 老夫自己也搞不清楚怎么回事，哪里能教你呢？");
//      return notify_fail("看来从程咬金这里学不到这项本领了。");
      return 1;
    }
  return 0;
}

*/
