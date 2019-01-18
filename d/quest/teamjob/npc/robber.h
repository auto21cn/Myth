void init()
{
        ::init();
        add_action("do_kill","kill");
        add_action("do_kill","hit");    
        remove_call_out("leave");
        call_out("leave",10);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(HIC "魔界兵团撤退了，迅速消失在迷雾中。\n" NOR,this_object());
                destruct(this_object());
                }
        else call_out("leave",30);
}

int do_kill(string arg)
{
        object who = this_player();
        object me = this_object();
        
        if(!arg || present(arg,environment(me))!=me) return 0;
        if (me->query("ygjg")==who)
                  {
                  message_vision(CYN"$N加油！$N加油！\n"NOR,who);
                  return 1;
                  }
            else if (me->query("ygjg"))
             {
                  tell_object(who,CYN"你还是各司其职，专心对付你的敌人吧。\n"NOR);
                  return 1;
                  }
                   return 0;
} 


