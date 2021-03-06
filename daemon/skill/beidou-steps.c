// Beidou-steps.c  【倒转北斗挪移大法】
// BY Cigar 2002.04.19
inherit SKILL;

string *dodge_msg = ({
        "$n一招「天玑离枢戏七星」轻轻巧巧地避了开去。\n",
        "只见$n身影一晃，一式「天璇乱步踏星辰」早已避在七尺之外。\n",
        "$n使出「倒转北斗七星轮回」，轻轻松松地闪过。\n",
        "$n左足一点，一招「挪移逐影天枢转」腾空而起，避了开去。\n",
        "可是$n使一招「风动玉衡星辰碎」，身子轻轻飘了开去。\n",
        "$n身影微动，已经藉一招「开阳薄雾邀月明」轻轻闪过。\n",
        "但是$n一招「瑶光音迟炎日淡」使出，早已绕到$N身後！\n"
        "$n身形陡地变得飘忽不定，令$N无法看清。\n",
        "$n双脚点地，全身化为一道白影，急速绕着$N打了几转。\n",
        "$n如一阵清风，舒缓地闪过了$N的凌厉攻势。\n",
        "$n便如闲庭信步，在弹指间已然退出丈外。\n",
        "可是$n左一转，右一绕，身影已消失不见。\n",
});

int valid_enable(string usage)
{
        return (usage=="dodge");
}

int valid_learn(object me)
{
        if( (int)me->query("max_force") < 50 )
                return notify_fail("你的内力不够，没有办法练倒转北斗挪移大法。\n");

        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
              if (me->query("class") != "lunhui") 
                      return notify_fail("你非神族怎能练倒转北斗挪移大法？\n"); 
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return notify_fail("你的气或内力不够，不能练倒转北斗挪移大法。\n");
        me->receive_damage("kee", 30);
        me->add("force", -3);
        return 1;
}

/*
      mapping query_action(object me, object weapon) 
      { 
       int i; 
       mapping* m_actions; 
       i=me->query_action("beidou_perform"); 
       if( ! me->query_temp("beidou_perform")) 
            { 
           if(me->query("skill_beidou-steps")==0) return action[random(5)]; 
           if(random(2))return action[random(5)]; 
           m_actions=me->query("skill_beidou-steps"); 
           return m_actions[random(sizeof(m_actions))]; 
            } 
          else  
         { 
        return action[5]; 
        } 
         return action[random(sizeof(action))]; 
      }
*/
string perform_action_file(string action)
{
        return CLASS_D("lunhui") + "/beidou-steps/" + action;
}
