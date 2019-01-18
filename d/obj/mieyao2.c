//负责存放妖。

#include <ansi.h>
#include "place.h"
string* guainame=({
        "野猫怪","yemao guai",
        "野鸡怪","yeji guai",
        "野狗怪","yegou guai",
        "野兔怪","yetu guai",
        "野象怪","yexiang guai",
        "野熊怪","yexiong guai",
        "野猪怪","yezhu guai",
        "蝎子怪","xiezi guai",
        "野猴怪","yehou guai",
"椅妖","yizi yao",
"鬼婆","gui po",
"风妖","feng yao",
"雪精","xue jing",
"蛤蟆怪","hama guai",
"壁虎怪","bihu guai",
"水蛇精","shuishe jing",
"僵尸","jiang shi",
"树妖","shu yao",
"狐狸精","huli jing",
"槐树精","huaishu jing",
"吸血鬼","xixie gui",
"杨树精","yangshu jing",
"吊死鬼","diaosi gui",
"黑无常","heiwu chang",
"白无常","baiwu chang",
"蝴蝶精","hudie jing",
"刑天","xing tian",
"夔","kui",
"蚩尤","chi you",
"水魔兽","shui moshou",
"土魔兽","tu moshou",
"火魔兽","huo moshou",
"蛟怪","jiao guai",
"蛇妖","she yao",
"石矶娘娘","shiji niangniang",
"黑山老妖","heishan laoyao",
"蜈蚣精","wugong jing",
"白骨精","baigu jing",
"蜘蛛精","zhizhu jing",
"蜂妖","feng yao",
"灯笼怪","denglong guai",
"坛子精","tanzi guai",
"扫把精","saoba jing",
});

string* xianname=({
        "仙人","xian ren",
        "仙官","xian guan",
        "仙女","xian nu",
        "仙卿","xian qing",
        "仙将","xian jiang",
        "仙妃","xian fei",
        "大仙","da xian",
        "白云大师","baiyun dashi",
        "燕赤侠","yanchi xia",
        "仙子","xian zi",
        "灭妖专家","secmieyao zhuanjia",
        "菩萨","pu sa",
        "共工","gong gong",
        "祝融","zhu rong",
        "姜子牙","jiang ziya",
        "哪吒","ne zha",
        "木吒","mu zha",
        "金吒","jin zha",
        "托塔天王","tuota tianwang",
        "金刚","jin gang",
        "尊者","zun zhe",
        "赤脚大仙","chijiao daxian",
        "黄飞虎","huangfei hu",
        "广成子","guancheng zi",
        "太乙真人","taiyi zhenren",
        "陆压道人","luya daoren",
        "傀儡生","kuilei sheng",
        "钟馗","zhong kui",
        "罗汉","luo han",
        "剑仙","jian xian",
        "灶王爷","zaowang ye",
        "土地神","tudi shen",
        "财神","cai shen",
        "龙女","long nv",
        "善财童子","shancai tongzi",
        "进宝天尊","jinbao tianzun",
        "天兵","tian bing",
        "天将","tian jiang",
        "巨灵神","juling zhen",
});


int add_new_yao( object me);
void create()
{
    seteuid(getuid());
}

string query_yao(object me)
{
     int i;
     object who=this_player();
     if (!who->query("menpai_task")||!who->query("menpai_t_time")||who->query("menpai_t_time")+900 > time() )
          {
          who->set("menpai_task",1);
              if (who->query("menpai_task")==1)
              {
              who->delete_temp("tongchuan");
              who->clear_condition("tongchuan_job");
              who->clear_condition("job_busy");
              }
          return "/d/quest/xue/xue"->ask_tongchuan(me);
          }
   
     if (who->query("menpai_task")==99 )
             {
                 if (who->query("combat_exp") < 1800000 ) i=random(2)+1;
                 else i=random(2)+1;
              }               
                 else i=who->query("menpai_task");
              
     who->set("menpai_t_time",time());
     
     
     if (i==1) {
     who->set("menpai_task",1);
     return "/d/quest/xue/xue"->ask_tongchuan(me);}
     
     if (i==2) {
     who->set("menpai_task",2);
     if(!who->query("m_mieyao")) 
      {
     
       if(who->query("secmieyao_mudage")+480 < time())
        {
                return("不是让你去杀了"+who->query("secmieyao/place")+"的"+who->query("secmieyao/name")+"么？\n");
        } else {
                who->set("m_mieyao",1);
                who->add("faith",-1);
                who->add("m_shibai",1);
                return ("你真是没用，我再给你一次机会！");
                }
      } 
      else {
        if(time()-who->query("secmieyao_mudage")<120)  
                 return ("干的不错，先下去休息休息吧。\n");
                 else {
                       who->delete("m_mieyao");
                        add_new_yao(who);
        if(who->query("secmieyao/type")=="xian")
                    {
                            return ("现有"+who->query("secmieyao/name")+"("+who->query("secmieyao/id")+")在"+who->query("secmieyao/place")+"为非作歹，\n你马上去灭了他，以尽除妖灭魔的义务！\n");
                     } else {
                            return ("听说"+who->query("secmieyao/name")+"("+who->query("secmieyao/id")+")最近在"+who->query("secmieyao/place")+"一带修行，\n你马上去吃了他，扬我魔族气势！\n");
                            }
                       }
             }
                }
           

}


int add_new_yao( object me)
{
    string my_id,my_cls,type;
    string sname;

    string* yaoname;
    int my_exp,index,i;
    mapping skill_status;
    mapping secmieyao;
    object where,yao;

    my_exp=me->query("combat_exp");
    my_cls=me->query("class");

     if(my_cls=="xian"||my_cls=="taoist"||my_cls=="dragon"||my_cls=="bonze"||my_cls=="fighter"){
        type="xian";
        yaoname=guainame;
    }
    else {
        type="mo";
        yaoname=xianname;
    }

    index=random(sizeof(yaoname)/2)*2;

    secmieyao=(["type" : type]);
    secmieyao+=(["id" : yaoname[index+1] ]);

    if(my_exp<10000)
    {
    sname="小小 "+yaoname[index];
    i = 0;
    }
    else if(my_exp<100000)
    {
    sname="十年 "+yaoname[index];
    i = 1;
    }
    else if(my_exp<1000000)
    {
    sname="百年 "+yaoname[index];
    i = 2;
     }
    else if(my_exp<10000000)
     {
     i = 3;
    sname="千年 "+yaoname[index];
     }
else
{
sname="得道 "+yaoname[index];
 i = 4;
}

    secmieyao+=(["name" : sname]);

    if (skill_status = me->query_skills() ) {
      yaoname  = keys(skill_status);
      my_exp = 0;
      for(index=0; index<sizeof(skill_status); index++) {
        if(skill_status[yaoname[index]]>my_exp &&(string)SKILL_D(yaoname[index])->type()=="martial")
           my_exp=skill_status[yaoname[index]];
      }
    }

    index=random(sizeof(place))+1;
    yaoname=place[index];
    secmieyao+=(["place" :yaoname[sizeof(yaoname)-1] ]);
    index=random(sizeof(yaoname)-2);
    sname=yaoname[sizeof(yaoname)-2]+yaoname[index];
    secmieyao+=(["location" : sname]);
    me->set("secmieyao_mudage",time());
    me->set("secmieyao",secmieyao);

    if(!(where=find_object(secmieyao["location"])))
             where=load_object(secmieyao["location"]);

    switch(i)
        {
        case 0:
        yao=new("/d/obj/npc/yao0");
        break;
        case 1:
        yao=new("/d/obj/npc/yao0");
        break;
        case 2:
        yao=new("/d/obj/npc/yao");
        break;
        case 3:
        yao=new("/d/obj/npc/yao1");
        break;
        case 4:
        yao=new("/d/obj/npc/yao1");
        break;
        }
    yao->set("taskguai", 1);
    yao->move(where);
    yaoname=explode(secmieyao["id"]," ");
    yaoname=({secmieyao["id"]})+yaoname;
    if( me->query_temp("apply/name") )
        me->delete_temp("apply/name");
    yao->set_name(me->name()+"的 "+secmieyao["name"],yaoname);
    yao->set("pre_killer",me);
    yao->init_skill(me->query("combat_exp"),my_exp,
         me->query("max_kee"),me->query("max_force"),
         me->query("max_sen"),me->query("max_mana"),secmieyao["type"]);
}

int query_killyao(object me,string loc,string yaoid)
{
    string* loclist;
    string* loclist2;
    mapping secmieyao=me->query("secmieyao");

    if(!mapp(secmieyao))return 0;
    loclist=explode(secmieyao["location"],"/");
    loclist2=explode(loc,"/");
    return (loclist[sizeof(loclist)-2]==loclist2[sizeof(loclist2)-2]&&secmieyao["id"]==yaoid);
    return 0;
}


////////////////////////////////////////////

 
int do_task2() 
{ 
    object me = this_player(); 
    object guai; 
    string where; 
    int tt; 
 

 
    if (me->query_condition("baohu_job")) 
    { 
        write(CYN"姜子牙脸色一沉：事关人命，火速行动！\n"NOR); 
        return 1; 
    } 
 
    if (me->query_condition("job_busy")) 
    { 
        write("姜子牙拿起通天镜一看，近来魔教没有采取什么行动，大家相安无事。\n"); 
        return 1; 
    } 
 
    me->command("say 最近可有魔贼做乱？"); 
 
    guai = NPC_D->task_npc(); 
    where = guai->query("place"); 
    me->delete_temp("dajiu"); 
    me->set_temp("dajiu/get", 1); 
    me->set_temp("dajiu/id", guai->query("id")); 
    me->set_temp("dajiu/name", guai->query("name")); 
    me->set_temp("dajiu/where", where); 
    me->delete_temp("dajiu/kk"); 
    me->apply_condition("baohu_job", 35); // 5 min 
    me->apply_condition("job_busy", 35 + random(10)); // 5 min 
 
    write(CYN"姜子牙说道：夜观天象，最近魔教有可能对" + guai->query("name") + 
        "("+ guai->query("id") + ")不利，你速去" + where + "保护其安全！\n"NOR); 
/* 
    this_object()->command("job " + me->name() +  
        "接到一个保护" + guai->name() + "的任务。"); 
*/ 
    me->start_busy(1); 
    if (me->query("id") == "mudring") me->move(guai->query("where")); 
 
    return 1; 
} 
 
int do_cancel2() 
{ 
    object me = this_player(); 
 
    if (!me->query_condition("baohu_job")) 
    { 
        tell_object(me,"你没有任务在身。\n"); 
        return 1; 
    } 
 
    me->command("say 这个任务弟子恐怕无能为力保护。"); 
    message_vision(CYN"姜子牙说道：好吧，那我另派神仙去保护。\n"NOR, me); 
    me->delete_temp("dajiu"); 
    me->clear_condition("baohu_job"); 
    me->apply_condition("job_busy", 10 + random(5)); // added 60-90 sec 
    me->start_busy(1); 
} 
 
 

