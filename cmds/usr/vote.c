// By Aeddy, 2004-1-4 20:40

#include <net/dns.h>
#include <ansi.h>
#include <vote.h> 
inherit F_CONDITION;


// int valid_voters(object me);

void create() { seteuid(getuid()); }
int clear_vote(object victim);
int valid_voters(object me);
int vote(object me, object victim);
int main(object me, string victim_name)
{
	object victim;

	if (((int)me->query("age")<16) && !wizardp(me))
	{
		return notify_fail("民主不是儿戏！小孩子一边玩去！\n");
	}
	if (((int)me->query("combat_exp")<1000000) && !wizardp(me))
	{
		return notify_fail("就你这武学也可以投票？\n");
	}

/*
	if ((int)me->query("vote/deprived"))
	{
		return notify_fail("你想起当初玩弄民主、被剥夺投票权的事，追悔莫急。\n");
	}
*/
    if (!victim_name )
    {
		return notify_fail("你要对谁投票关闭他的频道？\n");
    }
    
	
	victim = LOGIN_D->find_body(victim_name);
	if (!victim || !me->visible(victim))
		return notify_fail("你要对谁投票关闭他的频道？\n");
          if (wizardp(victim))
            return notify_fail("你没权利对巫师投票!\n");

	
    if (vote(me, victim) <= 0)
	{
/*		if ((int)me->query("vote/abuse")> 50)
		{
			write( HIG "你因为胡乱投票，投票权被剥夺了！\n" NOR);
			me->set("vote/deprived", 1);
			me->apply_condition("vote_suspension", 120);
			me->delete("vote/abuse");

		}	
		*/
		return 0;
		
	};
	
	return 1;
}


int valid_voters(object me)
{
	object *list;
	int d = 0;
	int j;

    list = users();
    j = sizeof(list);
    while( j-- )
	{
		// Skip those users in login limbo.
        if( !environment(list[j]) ) continue;
        if( !me->visible(list[j]) ) continue;
		if (((int)list[j]->query("age")<16) && !wizardp(list[j])) continue;
		if ((int)list[j]->query("vote/deprived")) continue;
		
		d++;
	}
	
	return d;
}



int vote(object me, object victim)
{
  int reason; // vote for what?
  int vv;	// valid voter numbers
  int vc; 	// vote count;
  int df;
  string channel;
  string *juror, my_id;
  string my_name, v_name;

  if ((reason = (int)victim->query("vote/reason"))>0 && (reason!=V_UNCHBLK))
  {
  	return notify_fail("要把当前的表决完成以后才可以提新的动议。\n");
  }
  
  if (reason <= 0)
  {
  	victim->set("vote/reason", (int)V_UNCHBLK); 
  }
  
  my_id = me->query("id");

  // dont allow me to vote twice for the same issue
  juror = victim->query("vote/juror");
  
  if( !pointerp(juror) )
  {
 	victim->set("vote/juror", ({ my_id }) );
  } else if( member_array(my_id, juror) == -1 ) 
  {
 	victim->set("vote/juror", juror+({ my_id }) );
  } else if(!wizardp(me))
  {
//	me->add("vote/abuse", 10);
  	return notify_fail("一人一票！滥用表决权是要受惩罚的！\n");
  }

  vv = (int) valid_voters(me)/10;
  vc = victim->add("vote/count", 1);

  df = vv - vc;
  if (vv < 4) df = 4 - vc;
  
  my_name = me->name(1);
  if (me == victim) v_name = "自己";
  	else  v_name = victim->name(1);

  if (df>0)
  {
        shout( HIG "【表决】"+my_name+"投票关闭"+v_name+"("+capitalize(victim->query("id"))+")"+"的闲聊频道，还差"
			+chinese_number(df)+"票。\n" NOR);
	write( HIG "【表决】"+my_name+"投票关闭" +v_name +"的闲聊频道，还差"
			+chinese_number(df)+"票。\n" NOR);
    
	victim->apply_condition("vote_clear", 10);
			        
  } else 
  {
  	if (me != victim)
  	{
        shout( HIG "【表决】"+my_name+"投票关闭"+v_name+"("+capitalize(victim->query("id"))+")"+"的闲聊频道。"
		+v_name+"的闲聊频道被关闭了！\n" NOR);
	write( HIG "【表决】"+my_name+"投票关闭" +v_name+"的闲聊频道。"
		+v_name+"的闲聊频道被关闭了！\n" NOR);
	} else 
	{
	shout( HIG "【表决】"+my_name+"投票关闭自己的闲聊频道。"
		+my_name+"的闲聊频道被关闭了！\n" NOR);
	write( HIG "【表决】"+my_name+"投票关闭自己的闲聊频道。"
		+my_name+"的闲聊频道被关闭了！\n" NOR);
	}		
	
	victim->apply_condition("vote_clear", -10);
	victim->set("channel/chblk_rumor",time() + 6000 );
	victim->set("channel/chblk_chat",time() + 6000 );
	victim->set("channel/chblk_sldh",time() + 6000 );
	victim->set("channel/chblk_es",time() + 6000 );
	victim->set("channel/tell_block",time() + 6000 );
  } 
  
  return 1;
}

int help(object me)
{
write(@HELP
指令格式 : vote <某人> 
此指令适合聊天频道被噎死的玩家，
因其他情况而被关闭频道，本指令
不起作用。

参考指令: openchat

HELP
    );
    return 1;
}

