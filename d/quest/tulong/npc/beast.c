inherit NPC;

void create()
{
  set_name("观想兽", ({"beast"}));
  set("gender", "雄性");
  set("age", 10);
  set("long","由人的杂念绮思所形成的观想兽，会缠住人的魂魄。\n");
  set("attitude", "aggressive");
  set("combat_exp", 51100000);
  set("max_kee",9000);
  set("kee",9000);
  set("max_sen",9000);
  set("sen",9000);
  set("max_force",9000);
  set("force",18000);
  set("force_factor",200); 
  set_temp("apply/damage", 250);
  set_temp("apply/armor", 200);
  setup();
}

void die ()
{
  object me = this_object();
  object where = environment (me);

  message_vision ("\n$N倒了下去，化为一缕轻烟。\n",me);  
  if (! present("beast 4",where) &&
      where->query("short")=="迷雾")
  {
    object ob = new ("/d/quest/tulong/npc/beast");
    ob->move(where);
    message_vision ("\n突然，迷雾中又出现一只观想兽！\n",me);   
  }
  destruct (me);  
}

void unconcious ()
{
  die();
}


