inherit NPC;

#include <ansi.h>

int goto_club();
int give_mark();

void create()
{
        set_name(HIC"持牌人"NOR,({ "chipai ren" , "man" ,"boss" }) );
        set("gender", "男性" );
        set("title", HIW"帮会俱乐部"NOR);
        set("age", 20);
        set("long", HIW"他是这里的持牌人，才二十出头，就把这个俱乐部搞得有声有色。\n"NOR+HIM"  “ask boss about 总坛” 可以去你帮派的总坛。\n"NOR+HIC"  “ask boss about 令牌” 可以要回你帮派的信物。\n"NOR);
        set("attitude", "friendly");
        set("inquiry", ([
        "name": "呵呵……我是这里的老板，你可以叫我BOSS或者什么都可以啦。\n",
        "here": "这里是帮派俱乐部啊！你不知道？\n",
        "club": "看来你还是没有加入什么帮派吧，找个好帮派加入吧。\n",
        "帮派": "看来你还是没有加入什么帮派吧，找个好帮派加入吧。\n",
        "总坛": (:goto_club:),
        "令牌": (:give_mark:),
        ]));
        setup();
}

void init()
{
        object ob, me;
        me=this_object();
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) 
        {
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
        }
        add_action("do_stop", "steal");
        add_action("do_stop", "fight");
        add_action("do_stop", "kill");
        add_action("do_stop", "cast");
        add_action("do_stop", "bian");
        add_action("do_stop", "exert");
        add_action("do_stop", "perform");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(3) )
        {
        case 0:
        say( name()+"笑咪咪地说道：这位" +RANK_D->query_respect(ob)+ "，进来歇歇脚，喝两盅吧。\n");
        break;
        }
}

int do_stop()
{
        object who = this_player();
        command("kok "+who->query("id"));
        command("say 嘿！"+who->query("name")+"！你是不是有点什么问题啊？要不要我带你去看医生？\n");
        return 1;
}

int goto_club()
{
        object who=this_player();
        string club;
        club=who->query("club");
        
        if ( club == 0 )
        {
                command("hehe");
                command("say "+who->query("name")+"还是先去找个自己喜欢的帮派加入啦，别人的总坛可不是轻易让外人进入的啊。\n");
                return 1;
        }

      if (pkerp(who))  
      {
      command("say 通缉不行");
   return 1;
      }
        switch ( club )
        {
                case "天绝帮":
                command("nod "+who->query("id"));
                who->move(__DIR__"tianjue/dayuan");
                break;
                  case "欢乐城":
                  command("nod "+who->query("id"));
                   who->move(__DIR__"happy/dayuan");
                  break;
               case "忘忧谷依轩楼":
                command("nod "+who->query("id"));
                who->move(__DIR__"wangyou/dayuan");
                break;
                case "天涯海阁":
                command("nod "+who->query("id"));
                who->move(__DIR__"tianya/dayuan");
                break;
                case "清风细雨楼":
                command("nod "+who->query("id"));
                who->move(__DIR__"qingfeng/qingfenglou");
                break;
                case "痴心女儿帮":
                command("nod "+who->query("id"));
                who->move(__DIR__"nver/dayuan");
                break;

                
                case "绝情谷":
                command("nod "+who->query("id"));
                who->move(__DIR__"jueqing/dayuan");
                break;

                case "梦回大唐阁":
                command("nod "+who->query("id"));
                who->move(__DIR__"datang/dayuan");
                break;

                case "神州结义帮":
                command("nod "+who->query("id"));
                who->move(__DIR__"jieyi/dayuan");
                break;

                case "碧海阁":
                command("nod "+who->query("id"));
                who->move(__DIR__"bihaige/dayuan");
                break;
 
                case "赛亚异族":
                command("nod "+who->query("id"));
                who->move(__DIR__"saiya/ufo");
                break;
                
                case "无忧宫":
                command("nod "+who->query("id"));
                who->move(__DIR__"wuyou/dayuan");
                break;

                default:
                command("hoho");
                command("say "+who->query("name")+"还是先去找个自己喜欢的帮派加入啦，别人的总坛可不是轻易让外人进入的啊。\n");
                return 1;
        }
        message_vision(who->query("name")+"往"+who->query("club")+"总坛方向走去。\n");
        return 1;
}

int give_mark()
{
        object who, tianjuepai, jueqingpai,yihuapai,qingfengpai,chixinpai,wuyoupai,tianyapai,wangyoupai,saiyaqi,jieyipai,bihaigepai,datangpai;
        string club;
        who=this_player();
        club=who->query("club");
        tianjuepai=new("/d/obj/club/tianjue_mark");
        wangyoupai=new("/d/obj/club/wangyou_mark");
        jieyipai=new("/d/obj/club/jieyi_mark");
        jueqingpai=new("/d/obj/club/jueqing_mark");
        bihaigepai=new("/d/obj/club/bihaige_mark");
        yihuapai=new("/d/obj/club/yihua_mark");
        wuyoupai=new("/d/obj/club/wuyou_mark");
        qingfengpai=new("/d/obj/club/qingfeng_mark");
        datangpai=new("/d/obj/club/datang_mark");
        saiyaqi=new("/d/obj/club/saiya_mark");
        chixinpai=new("/d/obj/club/chixin_mark");
        tianyapai=new("/d/obj/club/tianya_mark");
        if ( club == 0 )
        {
                command("hehe");
                command("say "+who->query("name")+"不能随便拿别人帮派的信物哦。\n");
                return 1;
        }
        
        switch ( club )
        {
                case "天绝帮":
                command("nod "+who->query("id"));
                tianjuepai->set("obj_owner",who->query("id"));
                tianjuepai->move(who);
                break;
                
                case "无忧宫":
                command("nod "+who->query("id"));
                wuyoupai->set("obj_owner",who->query("id"));
                wuyoupai->move(who);
                break;

                case "绝情谷":
                command("nod "+who->query("id"));
                jueqingpai->set("obj_owner",who->query("id"));
                jueqingpai->move(who);
                break;
                
                case "梦回大唐阁":
                command("nod "+who->query("id"));
                datangpai->set("obj_owner",who->query("id"));
                datangpai->move(who);
                break;

                case "忘忧谷依轩楼":
                command("nod "+who->query("id"));
                wangyoupai->set("obj_owner",who->query("id"));
                wangyoupai->move(who);
                break;

                case "神州结义帮":
                command("nod "+who->query("id"));
                jieyipai->set("obj_owner",who->query("id"));
                jieyipai->move(who);
                break;

                case "清风细雨楼":
                command("nod "+who->query("id"));
                qingfengpai->set("obj_owner",who->query("id"));
                qingfengpai->move(who);
                break;
                case "痴心女儿帮":
                command("nod "+who->query("id"));
                chixinpai->set("obj_owner",who->query("id"));
                chixinpai->move(who);
                break;
                case "移花宫":
                command("nod "+who->query("id"));
                yihuapai->set("obj_owner",who->query("id"));
                yihuapai->move(who);
                break;

                case "碧海阁":
                command("nod "+who->query("id"));
                bihaigepai->set("obj_owner",who->query("id"));
                bihaigepai->move(who);
                break;

                case "无忧宫":
                command("nod "+who->query("id"));
                wuyoupai->set("obj_owner",who->query("id"));
                wuyoupai->move(who);
                break;
                case "天涯海阁":
                command("nod "+who->query("id"));
                tianyapai->set("obj_owner",who->query("id"));
                tianyapai->move(who);
                break;

                case "赛亚异族":
                command("nod "+who->query("id"));
                saiyaqi->set("obj_owner",who->query("id"));
                saiyaqi->move(who);
                break;
                default:
                command("hoho");
                command("say "+who->query("name")+"不能随便拿别人帮派的信物哦。\n");
                return 1;
        }
        message_vision(who->query("name")+"得到一块帮派信物。\n");
        return 1;
}


