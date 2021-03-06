//By Aeddy 2004-1-6
//xiaoer.c
#include <ansi.h>
inherit F_VENDOR_SALE;
string season  = NATURE_D->check_season();
string seasonF  = NATURE_D->check_seasonF();
void clear_room();

void create()
{
       reload("city_xiaoer");
       set_name("店小二", ({"xiao er","xiaoer","xiao","waiter","er"}));
       set("shop_id",({"waiter","xiaoer","xiao","er"}));
       set("shop_title","店小二");
       set("gender", "男性");
        set("combat_exp", 1000);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 10);
       set("max_price",20);
        set("vendor_goods", ([
                "tu": "/d/city/obj/tasktu",
           "lei lingzhu": "/d/obj/baowu/leizhu.c",
                "jiudai": "/d/moon/obj/jiudai",
           "deng":"/d/wizz/liwu/obj/deng2",
                "gourou": "/d/ourhome/obj/gourou",
                "pillow": "/d/obj/misc/pillow",
              //  "mao": "/d/lingtai/obj/shengmao",
                "cloth": "/d/obj/armor/gold-chanyi",
                "fire": "/obj/fire",
                "jitui": "/d/ourhome/obj/jitui",
                "ball":"/d/obj/misc/crystalball",
                "jinpai" : "/d/city/obj/jinpai" ,
                "candle":"/d/city/npc/obj/candle",
                "huasheng": "/d/ourhome/obj/huasheng",
                "zhinan": "/d/obj/misc/xiaqi-zhinan",
                "saozhou": "/d/quest/small/saozhou",
                "brush": "/d/quest/small/brush",
                "shoeshine": "/d/quest/small/shoeshine",
        ]) );

  //      if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
       setup();

       carry_object("/d/obj/cloth/linen")->wear();
       add_money("silver", 1);
        remove_call_out("clear_room");
        call_out("clear_room",300);
}

void init()
{
        object me,ob;
        object *inv;
        int i;
        me=this_object();
        ob=this_player();
       
        ::init();

// added by mudring.
        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (
                    !playerp(inv[i])
                    )
                    continue;
                message_vision("“想贩卖人口不成？？!”，$N一把把$n推了出去。\n",me,ob);
                ob->move("/d/city/zhuque-s1");
                message_vision("$N被人一把推了过来，差点摔倒在地。\n",ob);
                ob->start_busy(5);
        }
       
        if (ob->query_condition("no_pk_time") || 
            ob->is_zombie() || 
            ob->query("name") == "名字待定")
          {
                message_vision("“杀人在逃期间不要来影响我做生意!”，$N一把把$n推了出去。\n",me,ob);
                ob->move("/d/city/zhuque-s1");
                message_vision("$N被人一把推了过来，差点摔倒在地。\n",ob);
                ob->start_busy(5);
          }      
                        
        else if( interactive(ob) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
              
        
        }
        add_action("do_vendor_list", "list");
}

//Added by Aeddy@2004-1-6
//一天中各个时辰的问话变化
void greeting(object ob)
{
       string time, respect;
	string banghui;
	object lp;

       if( !ob || !visible(ob) || environment(ob) != environment() ) return;

       if( ob->query("env/invisibility") ) return;

	time = NATURE_D->outdoor_room_event(); // 调用
	respect=RANK_D->query_respect(ob); 

	banghui=(string)ob->query("banghui");
//	lp=new("/obj/lingpai");
//	lp->create(banghui);
//	destruct(lp);

       if(!banghui || query("banghui")!=banghui) { //非同帮会的人的反馈信息
              switch(time) {  // 使用switch 判断当前时间                         
                      case "event_sunrise": // 早上
                              message_vision(WHT"$N笑着对$n说道：「这位" + respect 
                      + "，今儿可真早啊，欢迎光临。」\n", this_object(),ob);  
                              break; 
 
                      case "event_noon":   // 中午
                              message_vision(WHT"$N跑过来对$n说道：「这位" + respect 
                      + "，用过午饭了吗？快请坐。」\n", this_object(),ob);  
                              break; 

                     case "event_evening": // 傍晚
                              message_vision(WHT"$N笑嘻嘻地对$n说道：「这位" + respect 
                      + "，天快黑了，还是来小店歇歇吧，今天瞧把您给累的。」\n", this_object(),ob);  
                             break; 

                     case "event_night": // 初夜
                             message_vision(WHT"$N对$n说道：「这位" + respect 
                     + "，用过晚饭了吗？快进来喝杯茶歇会吧。」\n", this_object(),ob); 
                             break; 

                     case "event_midnight": // 午夜
                             message_vision(WHT"$N揉着惺忪的眼睛地对$n说道：「这位" + respect 
                     + "，这么晚了，您还不歇息啊？」\n", this_object(),ob); 
                             break; 

                     default : // 缺省的信息
                             message_vision(WHT"$N笑咪咪地对$n说道：「这位" + respect 
                     + "，进来喝杯香茶吧。」\n", this_object(),ob); 
			     break;
             }
		return;
	} else 
//		if((string)lp->query("bangzhu_id")==ob->query("id")) {//对帮主的特殊问候信息
//		command("say 原来是"+log_id(ob)+"帮主驾临寒店，请上房歇息如何？小的伺候着！\n");
//		command("bow "+ob->query("id"));
//		destruct(lp);
//		return;
//		}
//	else
	command("say 这位"+RANK_D->query_respect(ob)+"，帮主最近身体可好？\n");//对一般帮众的问候信息
//	destruct(lp);
	return;
}

void clear_room()
{
        string *place1 = 
        ({"/d/city/zhuque-s1","/d/city/center","/d/city/xuanwu-n1",
        "/d/city/baihu-w1","/d/city/qinglong-e1",});
        string room;
        int race, obj,i;
        object *inv;    
        race = 0;
        obj = 0;        
        if(environment(this_object())){
        inv = all_inventory(environment(this_object()));
        say(name()+"抱歉地说道：“小店清扫，各位客官原谅则个。”\n");
        for (i = 0;i <sizeof(inv);i++)
        {
                if(inv[i]->query("race")=="野兽") 
                {
                        room = place1[random(5)];
                        say(inv[i]->query("name")+"被"+name()+"用扫帚赶了出去。\n");
                        inv[i]->set_temp("no_return",0);
                        inv[i]->set_temp("rider",0);
                        inv[i]->move(room);
                        tell_room(environment(inv[i]), inv[i]->query("name")+"被"+name()+"从客栈赶了出来。\n");
                        race++;
                }
                else if(!inv[i]->is_character()&&!inv[i]->query("board_id"))
                 {obj++; 
                 destruct(inv[i]);}
                else if(inv[i]->query_temp("ridee"))
                {
                        inv[i]->set_temp("ridee",0);
                        inv[i]->add_temp("apply/dodge",-inv[i]->query_temp("ride/dodge"));
   
                 }
        }
     }
      remove_call_out("clear_room");
      call_out("clear_room",600);
}
int accept_object(object who, object ob)
{
    int value;

        if (ob->query("money_id") && (value=ob->value()) >= 300) 
        {
                tell_object(who, name()+
                        "一哈腰，说道：多谢您老，客官请上房歇息。\n");
                who->set_temp("rent_paid",1);
                take_money(value, 300);
                return 1;
        }
        return 0;
}

