// 赛亚异族信物
#include <ansi.h>
#include <weapon.h>
#include <combat.h>
#define CLUB_NAME "赛亚异族"
#define CLUB_ID "saiya"
#define CLUB_CHANNEL "saiya"
#define CLUB_MARK "saiya tanceqi"
inherit SWORD;
private string *members_level = ({
        "新新人类", //0
        "新新行动组", //1
        "赛亚人族", //2
        "赛亚组长", //3
        "赛亚队长", //4
        "赛亚头领", //5
        "赛亚长老", //6
        "赛亚金牌杀手", //7
        "赛亚副酋长", //8
        "赛亚女酋长", //9
        "赛亚酋长", //10
});
void create()
{
        set_name(HIR"赛亚"HIW"探测器"NOR,({"saiya tanceqi","tanceqi","club_mark"}));
        set_weight(0);
        if( clonep() ) set_default_object(__FILE__);
        else
        {
                set("value",0);
                set("material","gold");
                set("no_drop",1);
                set("no_sell",1);
                set("no_sac",1);
                set("unit","个");
        set("long",@LONG
        ||——————|=====|——————||
        ||           |====|           ||
        ||——————|=====|——————||
这是一个赛亚人用的探测器，外星人精密的仪器，不知道时候他们入侵了三界神话。
赛亚人的必备之物。
你可以用(help saiya)来查看有什么赛亚异族指令。若想了解赛亚异族
的历史可以用(about saiya)来取得进一步的资料。

LONG
);
        }
        set("club_id",CLUB_ID);
        set("club",CLUB_NAME);
        set("sub_club",({"赛亚族","巫神组","天神族","地球族","魔神族","未来族","博士族","阎罗族"}));
        set("club_max_level",10);
        init_sword(2);
        setup();
        set("volume",1);
}

//int query_autoload() { return 1; } //save_item

void init()
{
 mapping info;
 int level;
 if(environment(this_object())!=this_player()) return;
 level=CLUB_D->check_member(CLUB_ID,getuid(this_player()));
 if(level==0)
 {
        if(wizardp(this_player()))
        {
                 info = ([
                 "level": wiz_level(this_player()),
                 "title": "赛亚异族荣誉巫神",
                 "info1": "无",
                 "info2": ctime(time()),
                 "info3": ""
                 ]);
                 CLUB_D->add_member(CLUB_ID,getuid(this_player()),info);
        }
        else 
        {
                tell_object(this_player(),this_object()->name()+"突然从你身上飞出，渐渐消失在远方。\n");
                this_player()->delete("club");
                destruct(this_object());
                return;
        }
 }
 switch(level)
 {
  case 10:
                add_action("do_handover","handover");
  case 8:
                add_action("no_suicide","suicide"); //防止自杀
  case 7:
                add_action("do_givepower","givepower");
                add_action("do_listmember","listmember");
  case 6:
                add_action("do_accept","jieshou");
                add_action("do_kickout","kickout");
                add_action("do_subleader","subleader");
                add_action("do_retire","retire");
                add_action("do_scan","scan");
  case 5:
                add_action("do_include","include");
                add_action("do_dismiss","dismiss");
  default:
                add_action("do_help","help");
                add_action("do_about","about");
                add_action("do_members","members");
                add_action("do_leaveclub","leaveclub");
                
 }
}

int filter_members(object ppl,string *list)
{
        if( !environment(ppl) ) return 0;
        if( member_array(getuid(ppl),list)!=-1 ) return 1;
        return 0;
}

string show_level(object user)
{
 int level,rank;
 mapping info;
 string str;
 if(wizardp(user)) return "【荣誉会员】赛亚异族荣誉帮众  ";
 level=user->query("combat_exp")/100000;
 if(level>100)  str = "【????????】";
 else if(level<11)      str = "【第 "+chinese_number(level)+" 级】";
 else if(level<21)      str = "【第"+chinese_number(level)+"级】";
 else if(level%10==0)   str = "【第"+chinese_number(level)+"级】";
 else str = "【"+chinese_number(level)+"级】";
 info=CLUB_D->query_member_info(CLUB_ID,getuid(user));
 rank=info["level"];
 switch(rank)
 {
        case 10: str+="赛亚异族酋长  "; break;
        case 9: str+="赛亚异族女酋长  "; break;
        case 8: str+="赛亚异族副酋长    "; break;
        case 7: str+="赛亚异族金牌杀手  "; break;
        case 6: str+="赛亚异族资深长老  "; break;
        case 5: str+=info["info1"]+"赛亚头领    "; break;
        case 4: str+=info["info1"]+"赛亚队长  "; break;
        case 3: str+="赛亚组长  "; break;
        case 2: str+="赛亚人族  "; break;
        
        default: 
                if(info["info1"]!="无")
                {
                       str+=info["info1"]+"堂员      "; break;
                } else str+="赛亚异族行动组员  ";
 }
 return str;
}


int sort_member(object ob1, object ob2)
{
        int lv1,lv2;
        lv1=CLUB_D->check_member(CLUB_ID,getuid(ob1));
        lv2=CLUB_D->check_member(CLUB_ID,getuid(ob2));
        if(lv1 == lv2) return (int)ob1->query("level") - (int)ob2->query("level");
        else return (lv1 - lv2);
}

int do_members(string arg)
{
        object *users,me;
        string str,*list;
        int i,ppl_cnt,idle;
        me=this_player();
        users = CLUB_D->find_online_members(CLUB_ID);
        str = "◎ "+CLUB_NAME+": \n";
        str += "─────────────────────────────────────\n";

        users = sort_array(users, "sort_member", this_object());

        ppl_cnt = 0;
        i = sizeof(users);
        while( i-- )
        {
                        // Skip those users in login limbo.
                        if(!me->visible(users[i]) && wizardp(users[i]) ) continue;
                        str = sprintf("%s%12s%-16s %s(%s)",
                                str,
                                show_level(users[i]),
                                RANK_D->query_level(users[i]),
                                users[i]->name(1),
                                users[i]->query("id"),
                        );
                        if(users[i]->query_temp("killer")) str+=HIR" [杀人犯]"NOR;
                        idle=query_idle(users[i]);
                        if(users[i]->query_temp("invis")) str+=HIB"(隐形)"NOR;
                        if(users[i]->query_temp("netdead")) str+=HIG"<断线中>"NOR;
                        if(idle>60) str +=sprintf(HIY" (发呆%d分钟)"NOR,idle/60);
                        str +=sprintf("\n"NOR);
                        ppl_cnt++;
        }
        str += "─────────────────────────────────────\n";
        str = sprintf("%s目前共有 %d 位成员在线上.\n", str, ppl_cnt);
        this_player()->start_more(str);
        return 1;
}

int do_include(string arg)
{
        string sub;
        object ob,me;
        mapping me_info,ob_info;
        me=this_player();
        
        if(!arg) return notify_fail("include <人名>\n");
        else
        {
                ob = present(arg, environment(me));
                if(!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me ) return notify_fail("这里有这个人吗？\n");
                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
                if(sizeof(ob_info))
                {
                        if(me_info["level"] != 5 ) return notify_fail("只有分族头领能将帮众收入分族。\n");
                        if(!stringp(sub=me_info["info1"])) return notify_fail("只有分族头领能将帮众收入分族。\n");
                        if(ob_info["level"] != 2 || ob_info["info1"]!="无")
                                return notify_fail("只有一般帮众可以收入你的分族。\n");
                        ob_info["info1"]=sub;
                        CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
                        message_vision("$N将$n收入"+sub+", 并拍拍$n的肩膀说: 今后就看你的表现了。\n",me,ob);
                        ob->save();
                        return 1;
                }
                 else return notify_fail("对方并没有加入"+CLUB_NAME+"。\n");
        }
        return 1;
}

int do_dismiss(string arg)
{
        string sub;
        object ob,me;
        mapping me_info,ob_info;
        me=this_player();
        
        if(!arg) return notify_fail("dismiss <人名>\n");
        else
        {
                ob = present(arg, environment(me));
                if(!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me ) return notify_fail("这里有这个人吗？\n");
                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));          
                if(sizeof(ob_info))
                {
                        if(!sub=me_info["info1"] || me_info["level"]!=5 ) return notify_fail("只有分族头领能免除族员职务\n");
                        if(ob_info["level"] != 1 ) return notify_fail("你不够资格解除对方的职务。\n");
                        if(ob_info["info1"] != sub) return notify_fail("对方并不属于你的分族。\n");
                        ob_info["info1"]="无";
                        CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
                        message_vision("$N解除了$n在"+sub+"的职务, 摇摇头说: 又少了一个人才...真是可惜啊。\n",me,ob);
                        ob->save();
                        return 1;
                }
                 else return notify_fail("对方并没有加入"+CLUB_NAME+"。\n");
        }
        return 1;
}
//收人
int do_accept(string arg)
{
        string *clubs;
        object ob,mark,me;
        mapping info;
        me=this_player();
        if(!arg) return notify_fail("你要让谁加入"+CLUB_NAME+"？\n");
        else
        {
                ob = present(arg, environment(me));
                if (!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me ) return notify_fail("这里有这个人吗？\n");
                if(ob->query_temp("joinclub") != me->query("id") )
                {
                        return notify_fail("对方并没有向你申请入会(joinclub).\n");
                }
                clubs=CLUB_D->find_player_club(getuid(ob));
                if(sizeof(clubs)>0)
                {
                        if(clubs[0]==CLUB_ID) return notify_fail("对方已经是"+CLUB_NAME+"的一份子了。\n");
                        else return notify_fail("对方已经加入了别的帮派。\n");
                }
                 else
                {
                 mark=new(base_name(this_object()));
                 if(!mark) return notify_fail("赛亚异族信物取得失败。\n");
                 message_vision("$N给了$n一"+mark->query("unit")+mark->query("name")+", 并隆重的迎接$n成为"+CLUB_NAME+"的一份子。\n",me,ob);
                 info = ([
                 "level": 1,
                 "title": "赛亚异族行动组员",
                 "info1": "无",
                 "info2": ctime(time()),
                 "info3": me->name_id(1),
                 ]);
                 CLUB_D->add_member(CLUB_ID,getuid(ob),info);
                 mark->move(ob);
                 ob->add("channels", ({"saiya"}));
                 ob->add("club", "赛亚异族");
                 ob->save();
                }
        }
        return 1;
}

int do_kickout(string arg)
{
        string *tuned_ch;
        object ob,mark,me;
        mapping me_info,ob_info;
        me=this_player();
        
        if(!arg) return notify_fail("你要将谁踢出"+CLUB_NAME+"？\n");
        else
        {
                ob = present(arg, environment(me));
                if (!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me ) return notify_fail("这里有这个人吗？\n");
                                
                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));  
                
                if(sizeof(ob_info))
                {
                        if(ob_info["level"] >= me_info["level"])
                                return notify_fail("你不够资格将对方踢出"+CLUB_NAME+"。\n");
                        if( wiz_level(ob) > wiz_level(me) && wizardp(ob))
                                return notify_fail("你不够资格将对方踢出"+CLUB_NAME+"。\n");
                        tuned_ch = ob->query("channels");
                        if( pointerp(tuned_ch) && member_array(CLUB_CHANNEL, tuned_ch)!=-1 )
                        {
                                tuned_ch -= ({ CLUB_CHANNEL });
                                ob->set("channels", tuned_ch);
                        }
                        ob->delete("club");
                        if(!mark=present(CLUB_MARK,ob))
                        {
                                write("赛亚异族信物取得失败。\n");
                        }
                        else
                        {
                                message_vision("$N没收了$n的"+mark->query("name")+", 并强制$n退出"+CLUB_NAME+"。\n",me,ob);
                                destruct(mark);
                        }
                        CLUB_D->remove_member(CLUB_ID,getuid(ob));
                        ob->save();
                        return 1;
                }
                 else return notify_fail("对方并没有加入"+CLUB_NAME+"。\n");
        }
        return 1;
}

int do_subleader(string arg)
{
        string id,sub;
        object ob,me,mark;
        mapping me_info,ob_info;
        me=this_player();
        
        if(!arg) return notify_fail("subleader <人名> to <分族名>\n");
        else
        {
                if( sscanf(arg, "%s to %s", id, sub)!=2 ) return notify_fail("subleader <人名> to <分族名>\n");
                ob = present(id, environment(me));
                if(!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me ) return notify_fail("这里有这个人吗？\n");

                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));  
                
                if(sizeof(ob_info))
                {
                        if(ob_info["level"] != 2)
                                return notify_fail("只有一般帮众可以成为分族头领。\n");
                        if( (int) member_array(sub, query("sub_club"))<0 )
                                return notify_fail("目前可用的分族为 《赛亚族--巫神组---天神族--地球族---魔神族--未来族--博士族--阎罗族》\n");
                        ob_info["level"]=5;
                        ob_info["info1"]=sub;
                        CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
                        if(!mark=present(CLUB_MARK,ob))
                        {
                                write("赛亚异族信物取得失败。\n");
                        }
                        else
                        {
                                message_vision("$N将$n提升为"+sub+"分族头领, 并和$n握手勉励一番。\n",me,ob);
                                mark->move(ob);
                        }
                        ob->save();
                        return 1;
                }
                 else return notify_fail("对方并没有加入"+CLUB_NAME+"。\n");
        }
        return 1;
}


int do_retire(string arg)
{
        string sub;
        object ob,me,mark;
        mapping me_info,ob_info;
        me=this_player();
        
        if(!arg) return notify_fail("retire <人名> \n");
        else
        {
                ob = present(arg, environment(me));
                if(!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me) return notify_fail("这里有这个人吗？\n");
                
                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
                
                if(sizeof(ob_info))
                {
                        if(ob_info["level"] != 5) return notify_fail("对象并不是分族头领。\n");
                        sub=ob_info["info1"];

                        ob_info["level"]=1;
                        ob_info["info1"]="无";
                        CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);

                        if(!mark=present(CLUB_MARK,ob))
                        {
                                write("赛亚异族信物取得失败。\n");
                        }
                        else
                        {
                                message_vision("$N免除了$n的"+sub+"分族头领职务。\n",me,ob);
                                mark->move(ob);
                        }
                        ob->save();
                        return 1;
                }
                 else return notify_fail("对方并没有加入"+CLUB_NAME+"。\n");
        }
        return 1;
}

int do_givepower(string arg)
{
        string id,type,res;
        int level;
        object ob,me,mark;
        mapping me_info,ob_info;
        me=this_player();
        
        if(!arg) return notify_fail("givepower <人名> to <等级>\n");
        else
        {
                if( sscanf(arg, "%s to %d", id, level)!=2 ) return notify_fail("givepower <人名> to <等级>\n");
                ob = present(id, environment(me));
                if(!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me) return notify_fail("这里有这个人吗？\n");
                
                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
                
                if(sizeof(ob_info))
                {
                        if(ob_info["level"] >= me_info["level"]) return notify_fail("你没有资格改变对方的职务等级。\n");
                        if( wiz_level(ob) > wiz_level(me) && wizardp(ob))
                                        return notify_fail("你没有资格改变对方的职务等级。\n");
                        if(level >= me_info["level"])
                                return notify_fail("你没有资格提升对方的职务等级到这个等级。\n");
                        if(level == ob_info["level"])
                                return notify_fail("对方已经是"+(string)members_level[level]+"了。\n");
                        if(level > 9 || level < 1 )
                                return notify_fail("目前等级分为 1:<新新行动组> <2:赛亚人族><3:赛亚组长><4:赛亚队长><5:赛亚头领><6:赛亚长老><7:赛亚金牌杀手> <8:赛亚副酋长><9:赛亚女酋长><10:赛亚酋长>。\n");
                        if( level > ob_info["level"] )
                        {
                                type="提升";
                                res ="并和$n握手勉励一番";
                        }
                        else
                        {
                                type = "降";
                                res ="并拍拍$n的肩膀期勉$n能将功\折罪";
                        }
                        switch(level)
                        {
                                case 1:
                                        ob_info["level"]=1;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 2:
                                        ob_info["level"]=2;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 3:
                                        ob_info["level"]=3;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 4:
                                        ob_info["level"]=4;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 5:
                                        return notify_fail("请用subleader指令来指定一个分旗。\n");
                                        break;
                                case 6:
                                        ob_info["level"]=6;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 7:
                                        ob_info["level"]=7;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 8:
                                        ob_info["level"]=8;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 9:
                                        ob_info["level"]=9;
                                        ob_info["info1"]="无";
                                        ob_info["info2"]=ctime(time());
                                        ob_info["info3"]=me->name_id(1);
                                        break;
                                case 10:
                                        return notify_fail("请用handover指令做指挥权移交。\n");
                                        break;
                                default: return notify_fail("参数错误。\n");
                                
                        }
                        CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
                        if(!mark=present(CLUB_MARK,ob))
                        {
                                write("赛亚异族信物取得失败。\n");
                        }
                        else
                        {
                                message_vision("$N将$n的职位等级"+type+"为"+(string)members_level[level]+"(等级"+(string)level+"), "+res+"。\n",me,ob);
                                mark->move(ob);
                        }
                        ob->save();
                        return 1;
                }
                 else return notify_fail("对方并没有加入"+CLUB_NAME+"。\n");
        }
        return 1;
}

int do_handover(string arg)
{
        object ob,mark,me;
        mapping me_info,ob_info;
        me=this_player();
        if(!arg) return notify_fail("你要将大权移交给谁？\n");
        else
        {
                ob = present(arg, environment(me));
                if (!ob) return notify_fail("这里有这个人吗？\n");
                if(!userp(ob) || ob==me) return notify_fail("这里有这个人吗？\n");
                
                if(CLUB_D->query_club_leader(CLUB_ID)!=getuid(me)) return notify_fail("你不是真正的赛亚异族领导人。\n");
                
                me_info=CLUB_D->query_member_info(CLUB_ID,getuid(me));
                ob_info=CLUB_D->query_member_info(CLUB_ID,getuid(ob));
                if(sizeof(ob_info))
                {
                        CLUB_D->set_club_leader(CLUB_ID,getuid(ob));
                        
                        ob_info["level"]=10;
                        ob_info["info1"]="无";
                        ob_info["info2"]=ctime(time());
                        ob_info["info3"]=me->name_id(1);
                        CLUB_D->set_member(CLUB_ID,getuid(ob),ob_info);
                        
                        me_info["level"]=7;
                        me_info["info1"]="无";
                        me_info["info2"]=ctime(time());
                        me_info["info3"]=me->name_id(1);
                        CLUB_D->set_member(CLUB_ID,getuid(me),me_info);
                       
                        mark=present(CLUB_MARK, me);
                        if(!mark)
                           {
                                write("赛亚异族信物取得失败。\n");
                        }
                        
                        else
                         {
                        
                                mark->move(me);
                        
                         }
                        mark=present(CLUB_MARK, ob);
                        if(!mark)
                         {
                        
                                write("赛亚异族信物取得失败。\n");
                        
                         }
                        else
                         {
                                mark->move(ob);
                         }
                        message_vision("$N将"+CLUB_NAME+"的总指挥权移交给$n。\n",me,ob);
                        message( "channel:saiya",CYN"【"+CLUB_NAME+"】"+me->name(1)+"("+capitalize(me->query("id"))+")将"+CLUB_NAME+"指挥权移交给"+ob->name(1)+"("+capitalize(ob->query("id"))+")。\n"NOR, users() );
                        ob->save();
                        me->save();
                        return 1;
                
                }
                 else return notify_fail("对方并不是"+CLUB_NAME+"的一份子。\n");
        
       }
        return 1;
}

int do_leaveclub(string arg)
{
        string *tuned_ch;
        object mark,me;
        me=this_player();
        
        if(CLUB_D->query_club_leader(CLUB_ID)==getuid(me))
                return notify_fail("你必须先将大权转移才能离开"+CLUB_NAME+"。\n");
        CLUB_D->remove_member(CLUB_ID,getuid(me));
        message_vision("$N主动退出了"+CLUB_NAME+"。\n",me);
        message( "channel:saiya",CYN"【"+CLUB_NAME+"】"+me->name(1)+"("+capitalize(me->query("id"))+")主动退出了"+CLUB_NAME+"。\n"NOR, users() );
        tuned_ch = me->query("channels");
        if( pointerp(tuned_ch) && member_array(CLUB_CHANNEL, tuned_ch)!=-1 )
        {
                        tuned_ch -= ({ CLUB_CHANNEL });
                        me->set("channels", tuned_ch);
        }
        me->delete("club");
        if(!mark=present(CLUB_MARK,me))
        {
                write("赛亚异族信物取得失败。\n");
        } else destruct(mark);
        me->save();
        return 1;
}

int no_suicide(string arg)
{
        if(CLUB_D->query_club_leader(CLUB_ID)==getuid(this_player()))
        {
                write("身为"+CLUB_NAME+"高级长官, 交出指挥权之前不可轻生, 以免后继无人。\n");
                return 1;
        }
        return 0;
}

int do_listmember(string arg)
{
        string *list,*members,temp,output;
        int i,j;
        mapping club;
        list=CLUB_D->club_members(CLUB_ID);
        club=CLUB_D->query_club_record(CLUB_ID);
        members=keys(club);
        output="\n目前"+CLUB_NAME+"登记有案的成员有:\n";
        if(arg=="long")
        {
                for(i=this_object()->query("club_max_level");i>0;i--)
                {
                        for(j=0;j<sizeof(members);j++)
                        {
                                if(club[members[j]]["level"]==i) output=sprintf("%s %12s 赛亚异族等级: %d\n",output,members[j],i);
                        }
                }
                output=sprintf("%s \n目前%s共计有: %d 名成员。\n",output,CLUB_NAME,sizeof(members));
                write(output);
                return 1;
        }
        temp=CLUB_D->query_club_leader(CLUB_ID);
        output=sprintf("%s 领导人: %12s\n",output,temp);
        list-=({temp});
        output=sprintf("%s 其他:\n",output,temp);
        output+=CLUB_D->show_club_members(CLUB_ID);
        output=sprintf("%s目前%s共计有: %d 名成员。\n",output,CLUB_NAME,sizeof(members));
        write(output);
        return 1;
}

int do_scan(string arg)
{
   object ob,weapon;
        string line,skill_type;
   int attack_points, dodge_points, parry_points;
 if(!arg) return notify_fail("你要探测谁？\n"); 
               ob = present(arg, environment(this_player()));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的状态？\n");
               if( objectp(weapon = ob->query_temp("weapon")) )
                skill_type = weapon->query("skill_type");
        else
                skill_type = "unarmed";

       attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
        parry_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_DEFENSE);
        dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

        line = sprintf("\n 战斗攻击力 " HIW "%d (+%d)" NOR "\t\t战斗防御力 " HIW "%d (+%d)\n\n" NOR,
        attack_points/100 + 1, ob->query_temp("apply/damage"),
                (dodge_points + (weapon? parry_points: 
                (parry_points/10)))/100 + 1, ob->query_temp("apply/armor"));
        line+=sprintf(" 兵器伤害力： ["HIR"%d"NOR"]" NOR "\t\t盔甲保护力： ["HIG"%d"NOR"]\n\n" NOR,
        ob->query_temp("apply/damage"),
        ob->query_temp("apply/armor"));
          write(line+BBLK);
          return 1;
}
        
int do_help(string arg)
{
 if(arg=="saiya")
 {
  write(@HELP

       　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
                              赛亚异族信物的辅助说明                        
       ┌───────────────┬─────────┬──────┐
       │  指令格式                    │说明              │权限        │
       ├───────────────┼─────────┼──────┤
       │  help plate                  │本辅助讯息        │帮众        │
       │  club <你的讯息>             │赛亚异族专用频道      │帮众        │
       │  members                     │列出线上赛亚异族成员  │帮众        │
       │  leaveclub                   │主动退出赛亚异族      │帮众        │
       │  include <人名>              │将某人收入分族    │堂主专用    │
       │  dismiss <人名>              │取消某人分族职务  │堂主专用    │
       │  accept <人名>               │让某人加入赛亚异族    │长老以上    │
       │  kickout <人名>              │将某人逐出赛亚异族    │长老以上    │
       │  subleader <人名> to <分族名>│升级某人为分族头领  │长老以上    │
       │  retire <人名>               │撤除某人分族头领职位│长老以上    │
       │  givepower <人名> to <等级>  │改变某人的职位    │杀手以上    │
       │  handover <人名>             │掌门职务交接      │帮主        │
       │  listmember                  │赛亚异族名册          │杀手以上    │
       └───────────────┴─────────┴──────┘
         ◎ 使用 accept 指令必须对方先用 joinclub 指令申请才能生效。
         ◎ 赛亚异族目前有八个分族: 
                                --赛亚族--巫神组--天神族--地球族--魔神族--未来族--博士族--阎罗族"
         ◎ 等级分为: <1:新新行动组> <2:赛亚人族>     <3:赛亚组长>   <4:赛亚队长>    <5:赛亚头领>
                     <6:赛亚长老>   <7:赛亚金牌杀手> <8:赛亚副酋长>  <9:赛亚女酋长> <10:赛亚酋长>。

HELP
  );
  return 1;
 }
 return 0;
}
int do_about(string arg)
{
 if(arg=="saiya")
 {
  write(@ABOUT

●赛亚异族信物——赛亚探测器

据说赛亚人入侵地球，悟空等七个人，竭力阻止了地球的毁灭，但是某天突然时空扭转，他们的时空
于是和三界神话空间叠合了。

赛亚人信物——赛亚探测器，赛亚探测器就此流入人间天界。

ABOUT
  );
  return 1;
 }
 return 0;
}

