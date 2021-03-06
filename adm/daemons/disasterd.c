// disasterd.c
// rewritten by mudring
 
#include <ansi.h> 
inherit F_DBASE; 

#define HAOJIE_DIR "/d/quest/haojie/"
 
string *factions=({ 
    "三界山", "火云洞", "蜀山剑派", "五庄观", 
    "大雪山", "南海普陀山", "月宫", "阎罗地府", 
    "东海龙宫", "陷空山无底洞", "盘丝洞", 
    "方寸山三星洞", "将军府", "轩辕古墓", 
}); 
string faction;
int count; 

void create() 
{ 
    seteuid(getuid()); 
    remove_call_out("disaster"); 
    call_out("disaster",30,0);    
} 

void announce(string str)
{
    message("system", HIR"【天地劫】"HIW + str + "\n"NOR, users()); 
}

void disaster(int count) 
{ 
    if (count == 0)
    { 
        announce("太白金星：凡间的欲念太重了，致使心魔重生！"); 
        announce("太白金星：看来天地间一场浩劫在所难免！"); 
    }        
    faction = factions[count]; 
    announce("魔教的第" + chinese_number(count+1) + "个目标是血洗【"HIR + faction + HIW"】。"); 
    call_out("copy_npc", 11, count); 
} 

int filter_user(object ob)
{
    if (!ob || wizardp(ob))
        return 0; 

    if (ob->query("family/family_name") != faction)
        return 0;

    if (ob->query("combat_exp") < 30000)
        return 0;

    return 1;
}
 
void copy_npc(int count) 
{ 
    object ob, *user; 
    object site; 
    string leader;
    int i, j; 
    int t = 0; 

    leader = STATU_D->family_master(faction);
    site = STATU_D->family_place(faction);

    user = filter_array(users(), (: filter_user :));
    j = sizeof(user); 

    for (i = 0; i < j; i++)
    { 
reset_eval_cost();
        ob = new(HAOJIE_DIR + "yg-" + STATU_D->family_id(faction));
        ob->copy_status(ob, user[i]); 
        ob->move(site); 
        tell_object(user[i], HIY"" + leader + "告诉你:魔教挑衅本门,速回本门助战！\n"); 
        message_vision("$N凶神恶煞的走了过来。\n", ob); 
        t++; 
    } 

    if (t == 0)
    { 
        if (count < 13)
        { 
            announce("由于" + faction + "门下空无一人，魔教不战而胜，一举拿下了" 
                     + faction + "。"); 
            announce("魔教教主心魔老祖大笑道：没想到如此轻易得手，真是天助我也，哈。哈。哈。"
                     "下一个！"); 
            call_out("disaster",11,count+1); 
        } else
        { 
            announce("虽然各派奋力杀敌，击退魔教，无奈损失太大，一时间腥风血雨，三界一片混暗。"); 
            announce("太白金星：魔教虽然暂时退了，但不知什么时候又会卷土重来！"); 
            call_out("disaster",3600,0); 
            call_out("juedou",5); 
        } 
    } else
    { 
        call_out("verdict_time", 600, t, count); 
    } 
} 

void verdict_time(int t, int count) 
{ 
    object *user; 
    int i, j, exp; 

    if (DISASTER_D->query("xinmo_die") < t)
    { 
        user = filter_array(users(), (: filter_user :));
        j = sizeof(user); 
        for (i = 0; i < j; i++) 
        { 
            exp = (int)user[i]->query("daoxing") / 100; 
            if (exp > 1000) exp = 1000; 
            user[i]->add("daoxing", -exp); 
            tell_object(user[i], HIC"魔教血洗" + faction
                + "得手,你护派无力，失去了" + chinese_daoxing(exp) + "道行！\n"); 
        } 
        announce(faction + "弟子力战之下，伤亡惨重，从此消声匿迹。"); 
    } else
    { 
        announce(faction+"弟子力战之下，击退了魔教，避免了这场浩劫。"); 
    } 
    DISASTER_D->delete("xinmo_die"); 
    if (count < 13) 
    { 
        announce("魔教教主心魔老祖冷哼一声：下一个！"); 
        call_out("disaster", 11, count + 1); 
    } else
    { 
        announce("虽然各派奋力杀敌，击退魔教，无奈损失太大，一时间腥风血雨，三界一片混暗。"); 
        announce("太白金星：魔教虽然暂时退了，但不知什么时候又会卷土重来！"); 
        call_out("disaster", 3600, 0); 
    } 
} 

