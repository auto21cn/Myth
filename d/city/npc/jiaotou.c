inherit NPC;

void create()
{
        set_name("范芦平", ({"fan luping", "fan"}));
        set("age", 32);
        set("gender", "男性");
        set("long",
"一个精精瘦瘦的小个子，在练一套拳．\n");
	set("title", "武馆教头");
        set("attitude", "peaceful");

        set("combat_exp", 20000);
  set("daoxing", 5000);

        set("shen_type", 1);
	set("max_force", 200);
	set("force", 200);
	set("force_factor", 5);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
	set_skill("force", 30);
        set_skill("parry", 30);
	setup();
        carry_object("/d/obj/cloth/linen")->wear();
}

      void init() 
      { 
              object me,ob; 
              me=this_object(); 
              ob=this_player(); 
              
              ::init(); 
              
/*
              if(ob->query_condition("no_pk_time")) 
                { 
                      message_vision("“杀了人就想到这里避难？！”，$N一把把$n推了出去。\n",me,ob); 
                      ob->move("/d/city/qinglong-e1"); 
                      message_vision("$n被$N飞起一脚踢出了武馆，差点摔倒。\n",me,ob); 
                      ob->start_busy(30); 
                } 
             
                               
             else if( interactive(ob) && !is_fighting() ) { 
                      remove_call_out("greeting"); 
                      call_out("greeting", 1, ob); 
                     
               
              } 
*/
}
int recognize_apprentice(object ob)
{
	return 1;
}

�
