#include <ansi.h>

inherit ITEM;

void create()
{
         set_name(HIM"幸运"BLINK+HIW"刮刮卡"NOR, ({ "guagua ka","card" }) );
        set("long",
HIW"一张数码刮刮卡(card)，还不刮刮"HIR"(open)"HIW"看你有什么好运气!\n"NOR);
        set("unit", "张");
        set("weight", 100);
        set("value", 10000);
//        set("no_get","开玩笑吧？这东西你也捡的起来？" );
        set("no_give","不想混了吧？怎么能乱给人？" );
//        set("no_drop","可要想好了，扔掉你就死定了" );
        set("no_put","嘿嘿～你想把这东西放在那里啊？" );
        set("no_sell","小心数码宝贝扁你哦～" );
  setup();
}

int init ()  
{   
  add_action ("do_open", "open");
  return 1;
}

string rdm(string *strs)
{
  return strs[random(sizeof(strs))];
}

int do_open (string arg)
{
  string *hows = ({
    "万般幸福地",
    "鬼鬼祟祟地",
    "红光满面地",
    "乐滋滋地",
    "极为严肃地",
    "板着脸",
    "激动得浑身颤抖，",
    "呲牙咧嘴地",
    "秀里秀气地",
    "满脸狐疑地",
    "翻翻白眼，",
    "摇头晃脑地",
    "抿嘴一笑，",
    "笨手笨脚地",
    "肥头肥脑地",
    "推开众人，摆好架式，",
    "兴奋得满头大汗，",
    "抹去眼角的泪花，",
    "撮撮手，一跺脚，",
    "张牙舞爪地",
  });

  string *manners = ({
    "开始用硬币刮$n",
  });


  message_vision ("$N"+rdm(hows)+rdm(manners)+"。\n",
                  this_player(),this_object());

      if( arg=="gift card" || arg =="数码刮刮卡" || arg =="gift" || arg =="card" ) 
{
  message_vision ("
“噔～噔～噔～噔～～恭喜恭喜”数码刮刮卡中突然蹦出一个迷你数码宝贝
笑嘻嘻的对$N说道“恭喜你中了随机奖！”说罢对$N甜甜一笑，$N觉得
浑身舒服极了。“看看你的奖品吧”\n",
                  this_player(),this_object());

this_player()->add("combat_exp",5000);
this_player()->add("daoxing", 5000);
this_player()->add("potential",5000);
this_player()->save();
write(HIR"你的奖品有:\n
      "HIW"五年道行 5000点潜能 5000点武学 \n
      "HIW" 三界神话全体巫师祝您"BLINK+HIM"中秋快乐\n"NOR,

               environment(this_player()), this_player());
  destruct(this_object());
  return 1;

}
         return 1;
}

