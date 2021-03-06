// natured.c
//
// this code copy from hellcode
// added some job for sjsh mud
// modify by mudring May/10/2002

#pragma optimize
//#pragma save_binary

#include <ansi.h>
#include <localtime.h>

#define YAOGUAI "/d/quest/baoshi/yaoguai"
#define FEIZEI "/d/quest/baoshi/feizei2"
#define REMEMBER_CHAR           '#'
#define GAME_TIME(t)            (t - 971000000)
#define DATE_SCALE              365

nosave int current_day_phase = -1;
mapping *day_phase;

mapping *read_table(string file);

void select_day_phase();

mixed *query_localtime(int t)
{
        mixed *lt;

        t = GAME_TIME(t);
        if (t < 1) t = 1;
        lt = localtime((t % 86400) * 365);
        lt[LT_MON];
        lt[LT_YEAR] = t / 86400;
        return lt;
}

int query_hour()        { return query_localtime(time())[LT_HOUR]; }
int query_day()         { return query_localtime(time())[LT_MDAY]; }
int query_month()       { return query_localtime(time())[LT_MON] + 1; }
int query_year()        { return query_localtime(time())[LT_YEAR]; }

void create()
{
        day_phase = read_table("/adm/etc/nature/day_phase");
        select_day_phase();
}

void update_day_phase()
{
        string msg;

        msg = color_filter(HIR"〖"HIG"三界天色"HIR"〗"NOR + day_phase[current_day_phase]["outcolor"] +
                           day_phase[current_day_phase]["time_msg"] + "\n" NOR);
        message("outdoor:vision", msg, users());
        if (! undefinedp(day_phase[current_day_phase]["event_fun"]))
                call_other(this_object(), day_phase[current_day_phase]["event_fun"]);
}

void select_day_phase()
{
        mixed *lt;
        int i, t, n;

        remove_call_out("select_day_phase");

        // Get minutes of today.
        lt = query_localtime(time());
        lt[LT_MON]++;
        t = lt[LT_HOUR];

        // Find the day phase for now.
        for (i = 0; i < sizeof(day_phase) - 1; i++)
                if (t < day_phase[i + 1]["hour"]) break;

        if (i >= sizeof(day_phase) - 1)
        {
                // the last hour
                n = 24 - t;
                i = 0;
        } else
                n = day_phase[i + 1]["hour"] - t;

        // calculate the call out time
        n = n * 60 - lt[LT_MIN];
        n = n * 60 / 365 + 1;
        if (n < 1) n = 1;
        call_out("select_day_phase", n);

        if (i != current_day_phase)
        {
                current_day_phase = i;
                update_day_phase();
        }
}


void event_morning()
{
        object badguy;
        object room;
/*
        if (random(12) == 1)
        {
                if(objectp(room=load_object("/d/death/walk3")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 洞府得找几个门卫了！");
                message_job( "元始天尊："HIW + "阴曹地府"HIM + "近日常有鬼卒失踪,疑是妖怪所为！");
        }
        if (random(12) == 2)
        {
                if(objectp(room=load_object("/d/qujing/wuzhuang/gate")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 肚子有点饿了,找点活物过早！");
                message_job( "元始天尊："HIW + "五庄观"HIM + "近日常有道童失踪,疑是妖怪所为！");
        }
        if (random(12) == 3)
        {
                if(objectp(room=load_object("/d/jjf/side_keting")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 好个秦琼,居然伤了我的手下！");
                message_job( "元始天尊："HIW + "将军府"HIM + "近日常有士兵失踪,疑是妖怪所为！");
        }
        if (random(12) == 4)
        {
                if(objectp(room=load_object("/d/moon/huilang")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 听说月宫有秘传的养颜术！");
                message_job( "元始天尊："HIW + "广寒宫"HIM + "近日常有少女失踪,疑是妖怪所为！");
        }
        if (random(12) == 5)
        {
                if(objectp(room=load_object("/d/city/center")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 听说大唐皇宫宝物不少?");
                message_job( "元始天尊："HIW + "大唐皇宫"HIM + "近日常有珠宝失踪,疑是妖怪所为！");
        }
        if (random(12) == 6)
        {
                if(objectp(room=load_object("/d/nanhai/road11")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 九头驸马的老丈人死了,得找几个和尚超度超度！");
                message_job( "元始天尊："HIW + "南海普托"HIM + "近日常有僧侣失踪,疑是妖怪所为！");
        }
        if (random(12) == 7)
        {
                if(objectp(room=load_object("/d/xueshan/shanpo")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 昨天不小心把侍从给吃了,我晕！");
                message_job( "元始天尊："HIW + "大雪山"HIM + "近日常有侍者失踪,疑是妖怪所为！");
        }
        if (random(12) == 8)
        {
                if(objectp(room=load_object("/d/shushan/shanjiao")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 蜀山的那几个小剑童眉清目秀的,真是想死我了！");
                message_job( "元始天尊："HIW + "蜀山"HIM + "近日常有剑童失踪,疑是妖怪所为！");
        }
        if (random(12) == 9)
        {
                if(objectp(room=load_object("/d/qujing/wudidong/square2")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 过两天要去参加牛魔王的大宴,得抓几个小妖充充门面！");
                message_job( "元始天尊："HIW + "无底洞"HIM + "近日常有小妖失踪,疑是妖怪所为！");
        }
        if (random(12) == 10)
        {
                if(objectp(room=load_object("/d/qujing/wuji/shandao5")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 前两天火并,死了几个手下,哎！");
                message_job( "元始天尊："HIW + "火云洞"HIM + "近日常有健将失踪,疑是妖怪所为！");
        }
        if (random(12) == 11)
        {
                if(objectp(room=load_object("/d/lingtai/baixi")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 修炼可真辛苦,吃几个道士加点道行！");
                message_job( "元始天尊："HIW + "方寸山"HIM + "近日常有道士失踪,疑是妖怪所为！");
        }
        if (random(12) == 0)
        {
                if(objectp(room=load_object("/d/sea/huilang8")) && 
                objectp(badguy = new(YAOGUAI)))
                badguy->move(room);
                badguy->command("job 洞府里的宫娥不够了,嗯！");
                message_job( "元始天尊："HIW + "东海龙宫"HIM + "近日常有宫娥失踪,疑是妖怪所为！");
        }
*/
}

void event_night()
{
        object badguy;
        object room;
/*
        if (random(12) == 1)
        {
                if(objectp(room=load_object("/d/city/qinglong-e1")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "长安城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 2)
        {
                if(objectp(room=load_object("/d/kaifeng/yao3")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "开封城中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 3)
        {
                if(objectp(room=load_object("/d/qujing/qinfa/jiedao1")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "钦法国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 4)
        {
                if(objectp(room=load_object("/d/qujing/fengxian/jiedao7")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "凤仙郡中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 5)
        {
                if(objectp(room=load_object("/d/qujing/zhuzi/zhuzi5")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "朱紫国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 6)
        {
                if(objectp(room=load_object("/d/qujing/jisaiguo/east1")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "祭赛国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 7)
        {
                if(objectp(room=load_object("/d/qujing/baoxiang/bei3")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "宝象国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 8)
        {
                if(objectp(room=load_object("/d/qujing/wuji/estreet2")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "乌鸡国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 9)
        {
                if(objectp(room=load_object("/d/qujing/chechi/jieshi6")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "车迟国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 10)
        {
                if(objectp(room=load_object("/d/qujing/nuerguo/towna3")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "女儿国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 11)
        {
                if(objectp(room=load_object("/d/qujing/tianzhu/jiedao14")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "天竺国中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
        if (random(12) == 0)
        {
                if(objectp(room=load_object("/d/qujing/jinping/xiaojie1")) && 
                objectp(badguy = new(FEIZEI)))
                badguy->move(room);
                message_job( HIW "官府通告："HIR + "金平府中今夜有飞贼横行，良民百姓请闭门不出，切莫自误！");
        }
*/
}
void event_afternoon()
{
        object *ob_list;
        int i;  
        ob_list = children(YAOGUAI);
                for(i=0; i<sizeof(ob_list); i++) 
                if(environment(ob_list[i]))
                {
                message_vision("$N说道：今天吃了不少鲜活人肉,我闪！\n",ob_list[i]);
                        destruct(ob_list[i]);
                }

}

void event_dawn()
{
        object *ob_list;
        int i;
        ob_list = children(FEIZEI);
                for(i=0; i<sizeof(ob_list); i++) 
                if(environment(ob_list[i]))
                {
                        message_vision("$N笑道：天亮了，东西也到手了，我闪！\n",ob_list[i]);
                        destruct(ob_list[i]);
                }
}

void event_midnight()
{
        string msg;
        int m, d;

        m = query_month();
        d = query_day();

        msg = 0;
        switch (m * 100 + d)
        {
        case  321:
                msg = HIG "春天终于到了，经过了漫长的冬季，万物开始复苏。\n" NOR;
                break;
        case  622:
                msg = HIR "夏天来临了，天气越来越热，所有的生物都异常活跃。\n" NOR;
                break;
        case  923:
                msg = HIY "已然是秋天了，大地一片金黄，正是收获的时期。\n" NOR;
                break;
        case 1222:
                msg = HIW "来自北方的寒流扫过大地，万物又开始了寂静的休眠。\n" NOR;
                break;
        }

        if (msg)
                message("vision", HIR"〖"HIG"三界天色"HIR"〗"NOR + msg,
//118                          msg, all_interactive());
                        msg, users());

        switch(m)
        {
        //spring weather
        case 3: case 4: case 5:
                switch(random(3))
                {
                case 0:
                        day_phase = read_table("/adm/etc/nature/spring_rain");
                        break;
                case 1:
                        day_phase = read_table("/adm/etc/nature/spring_sun");
                        break;
                case 2:
                        day_phase = read_table("/adm/etc/nature/spring_wind");
                        break;
                }
                break;
        //summer weather
        case 6: case 7: case 8:
                switch(random(3))
                {
                case 0:
                        day_phase = read_table("/adm/etc/nature/summer_rain");
                        break;
                case 1:
                        day_phase = read_table("/adm/etc/nature/summer_sun");
                        break;
                case 2:
                        day_phase = read_table("/adm/etc/nature/summer_wind");
                        break;
             }
             break;
        //autumn weather
        case 9: case 10: case 11:
                switch(random(3))
                {
                case 0:
                        day_phase = read_table("/adm/etc/nature/autumn_rain");
                        break;
                case 1:
                        day_phase = read_table("/adm/etc/nature/autumn_sun");
                        break;
                case 2:
                        day_phase = read_table("/adm/etc/nature/autumn_wind");
                        break;
                }
                break;
        //winter weather
        case 12: case 1: case 2:
                switch(random(3))
                {
                case 0:
                        day_phase = read_table("/adm/etc/nature/winter_rain");
                        break;
                case 1:
                        day_phase = read_table("/adm/etc/nature/winter_sun");
                        break;
                case 2:
                        day_phase = read_table("/adm/etc/nature/winter_wind");
                        break;
                }
                break;
        default:
                day_phase = read_table("/adm/etc/nature/day_phase");
        }
}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_evening()  //Aeddy
{
        object area,who;
        mixed file,dir;
        int amount,i;
          dir=get_dir("/data/city/");
       if(!dir) return; 
 	
	for(i=0;i<sizeof(dir);i++)
      if( sscanf(dir[i], "%s.o", file) ) {
      area=new("/obj/area1.c");
      area->create(file);
      if(area->query("no_use"))
   {
      destruct(area);

      continue;
    } 

     if(area->query("owner"))  
{
amount=area->query("people")*(area->query("farm")+area->query("trade"))*area->query("tax")/1000;
if(amount <=0) return;

    who=find_player(area->query("owner"));
    if(who) {
	who->add("balance",amount);
	if(!who->save()) {
	    log_file("city_log","Failed to return "+amount+
		    " coin to "+area->query("owner")+"\n");
	    return;
	}
	log_file("city_log","pay "+amount+" to "+area->query("owner")+"\n");
 tell_object(who,HIW+BLINK+area->query("short")+"税收"+MONEY_D->money_str(amount)+",已经存入你的户头。\n"NOR);

    } else {
	who=new(USER_OB);
	who->set("id",area->query("owner"));
	if(!who->restore()) {
	    log_file("city_log","Failed to return "+amount+
		    " coin to "+area->query("owner")+"\n");
	    destruct(who);
	    return;
	} else {
	    who->add("balance",amount);
	    if(!who->save(1)) { // save(1) will not erase autoload.
		log_file("city_log","Failed to return "+amount+
			" coin to "+area->query("owner")+"\n");
		destruct(who);
		return;
	    } 
	    log_file("city_log","pay "+amount+" to "+area->query("owner")+"\n");
	    destruct(who);
	    }
    }

}
}
        return;
}

void event_noon()
{
        object *ob;
        int i, skill;

        ob = users();
        for(i=0; i<sizeof(ob); i++) {
                if( !environment(ob[i]) ) continue;
                if( !environment(ob[i])->query("outdoors") ) continue;
                if( !ob[i]->query("mana") ) continue;
                if( !(skill = ob[i]->query_skill("spells", 1) )) {
                        tell_object(ob[i], "你觉得一阵晕眩，好像有一股能量从身上被人吸走了。\n");
                        ob[i]->set("mana", 0);
                        ob[i]->receive_damage("sen", 0);
                } else if( skill < 25 ) {
                        tell_object(ob[i], "随着太阳升到天空的正中央，你觉得你的法力开始消失了。\n");
                        ob[i]->set("mana", (int)ob[i]->query("mana") * skill / 25 );
                }
        }
}

string outdoor_room_description()
{
        return color_filter(day_phase[current_day_phase]["outcolor"] + "    " +
                            day_phase[current_day_phase]["desc_msg"] + "。\n" NOR);
}

string game_time()
{
        mixed *lt;
        string *ms = ({ "冬", "春", "夏", "秋", });

        lt = query_localtime(time());

        return sprintf("%s年%s%s月%s日%s时", 
                       chinese_number(lt[LT_YEAR]),
                       ms[((lt[LT_MON] + 1) % 12) / 3],
                       chinese_number(lt[LT_MON] + 1),
                       chinese_number(lt[LT_MDAY]),
                       chinese_number(lt[LT_HOUR]), );
}

int to_game_time(int t)
{
        return GAME_TIME(t);
}

mapping *read_table(string file)
{
        string *line, *field, *format;
        mapping *data;
        int i, rn, fn;

        line = explode(read_file(file), "\n");
        data = ({});
        for(i = 0; i < sizeof(line); i++)
        {
                if (line[i] == "" || line[i][0] == REMEMBER_CHAR) continue;
                if (! pointerp(field))
                {
                        field = explode(line[i], ":");
                        continue;
                }
                if (! pointerp(format))
                {
                        format = explode(line[i], ":");
                        continue;
                }
                break;
        }

        for( rn = 0, fn = 0; i < sizeof(line); i++)
        {
                if (line[i] == "" || line[i][0] == REMEMBER_CHAR ) continue;
                if (! fn) data += ({ allocate_mapping(sizeof(field)) });
                sscanf(line[i], format[fn], data[rn][field[fn]]);
                fn = (++fn) % sizeof(field);
                if (! fn) ++rn;
        }
        return data;
}

mapping *query_day_phase() { return day_phase; }
int query_current_day_phase() {return current_day_phase;} 

