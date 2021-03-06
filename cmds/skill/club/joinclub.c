//joinclub.c
//modified buy Wuyou@sk_sjsh 2003-4-9
 
#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string club, id;

        if(!arg) 
                return notify_fail("你要向谁申请入帮派？\n");

        ob = present(arg, environment(me));

        if(!ob) 
                return notify_fail("这里没有这个人。\n");

        if (ob == me)
                return notify_fail("你不能向自己申请帮派。\n");
     
        if (!userp(ob) && !wizardp(me))
                return notify_fail("只能对玩家申请帮派！\n");
         
        if(me->query("club"))  
                return notify_fail("你已经加入某个帮派了。\n");
              
        if(!ob->query("club")) 
                return notify_fail("对方似乎并没有参加帮会。\n");
        
        id = ob->query("id");

        if(me->query_temp("joinclub") == id) 
                return notify_fail("你已经申请过了, 对方正在考虑中。\n");
        message_vision("$N正式向$n提出加入帮会的要求。\n",me,ob);
        tell_object(ob,"如果你同意对方加入, 请用 capprove "+me->query("id")+" 指令收他入帮。\n");
        me->set_temp("joinclub",id);
        return 1;
}
                          
int help(object me)
{
        write(@HELP
指令格式 : 
           joinclub <帮主id> 
           
这个指令可以请求对方收你入帮会。


HELP
    );
    return 1;
}

