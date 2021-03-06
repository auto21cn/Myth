// Update by waiwai@2001/06/13
// Update by waiwai@2002/12/05
// 增加特殊武功对于环境的影响，配合动态房间应用

#include <ansi.h>
inherit SSERVER;

string get_name(string str)
{
        str="百鸟朝凤";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｃｈａｏｆｅｎｇ\n"
        +"百鸟朝凤的命中率和威力已经加强。";
        return str;
}

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ii, req, num_anqi, num_hit; 
        int max_hit, hitt, damage, op, opfa, remain, t;
        string anqi_type, b_unit;

        string *list, s_room;
        object other, env;
        mapping exit;
        int i;

        int wound=0;

        if( !target ) target = offensive_target(me);
        
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要攻击谁？\n");
        
        weapon = me->query_temp("weapon");

        req=(int)me->query_skill("sword", 1)+(int)me->query_skill("bainiao-jian", 1)+
                         (int)me->query_skill("throwing", 1); 

        if(!weapon || (string)weapon->query("skill_type") != "sword")
                return notify_fail(WHT"你必须装备剑才能使用「百鸟朝凤」\n"NOR);

        if(weapon) {
                if(weapon->query("anqi/allow") != 1) num_anqi=0;
                        else num_anqi=weapon->query("anqi/now");
        }

        if( userp(me) ) {
                if(me->query_skill_mapped("force")!="ningxie-force")
                        return notify_fail("百鸟朝凤必须配合冰谷凝血功才能使用。\n");

                if(me->query_skill_mapped("throwing")!="bainiao-jian")
                        return notify_fail("百鸟朝凤必须配合暗器使用才能使用。\n");

        if(req < 120) return notify_fail("你剑中打暗器的功夫还不到火候！\n");
        }

        if(req < 150 && weapon->query("anqi/now") ==0)
                return notify_fail("你剑中没有暗器可打！\n");

        if (me->query("force")<200)
                return notify_fail("你内力不继，难以御剑飞针。\n");
/*
        if( ((t=(int)me->query_temp("chaofeng_time")) <= time() )
            && (time()<t+4) ) 
        {  
                return notify_fail(CYN"出奇才能制胜，百鸟朝凤多使就不灵了。\n"NOR);
        } else me->delete_temp("chaofeng_time");
*/
        
        if( time()-(int)me->query_temp("chaofeng_time") < 3 )            
                return notify_fail("出奇才能制胜，百鸟朝凤多使就不灵了。\n");
                
        if (!PFM_D->valid_family(me, "大雪山"))
                return notify_fail("你不是大雪山弟子，怎么能使用大雪山绝技？\n");
                
        me->add("force", -100);

        if(num_anqi <=0) 
        { 
                anqi_type="剑气"; 
                damage=me->query("force_factor")+10; 
        }
        else if (req < 150)
        { 
                anqi_type=weapon->query("anqi/type"); 
                damage=me->query_temp("apply/damage");
        }
        else 
        { 
                anqi_type=weapon->query("anqi/type")+HIR"夹着剑气"NOR;
                damage=me->query_temp("apply/damage")+me->query("force_factor")+10;
        }
         
        msg = HIW"只见$N手中"+weapon->query("name")+NOR HIW"急颤，幻出满天剑芒，无数"
                 +anqi_type+HIW"有如 "HIR"百"HIB"鸟"HIY"投"HIM"林"HIW" 般袭向$n \n" NOR;


        // Added by waiwai@2002/12/05
        // 以下综合增加特殊武功对于环境的影响
        env=environment(me);

        exit=env->query("exits");

        if( exit ) {
                list=keys(exit);

                for(i=0;i<sizeof(list);i++) {
                        s_room=env->query("exits/"+list[i]);
                        if(!other=find_object(s_room))  other=load_object(s_room);
                        tell_object(other,WHT"附近突然传来阵阵的撕杀声，似乎是雪山派的百鸟剑气直逼你而来。。。\n"NOR);
                }
        }



        if (num_anqi > 10 || num_anqi == 0) max_hit=10;
        else max_hit=weapon->query("anqi/now");

        num_hit=random(max_hit/2)+(max_hit/2);

        if (!target->is_fighting(me)) opfa=40;
        else opfa=20;

        if (target->query("combat_exp")  !=0 ) 
               op= me->query("combat_exp")*opfa/target->query("combat_exp");
        else op=10;
        hitt=0; 
        for (ii=1;ii<=num_hit;ii++)  
        {
                if (op > random(60)) hitt++;
        }

        if (weapon->query("anqi/type")=="孔雀翎") b_unit="支";
        else b_unit="根";
        if (weapon->query("anqi/now") != 0) remain=weapon->query("anqi/now")-num_hit;
        else remain=0;
        weapon->set("anqi/now",remain);
        if (weapon->query("anqi/now") == 0) 
        {
                weapon->delete("anqi/type");  
                weapon->set("long",weapon->query("orilong"));
        }
        else weapon->set("long",weapon->query("orilong")+"里面已经装了"
           +chinese_number(weapon->query("anqi/now"))+b_unit+weapon->query("anqi/type")+"\n"); 

        if (hitt==0) {
                msg += HIY"$n"HIY"连忙身行一转，连退数步，闪过了这满天花雨般的一击。\n"NOR;
                message_vision(msg, me, target);
                me->start_busy(random(2));
        } else {
                // By waiwai@2001/05/05 changed.
                damage=damage*hitt+random(req);
                target->receive_damage("kee",damage,me,"pfm");
                if(damage>target->query_temp("apply/armor")) 
                {
                        target->receive_wound("kee",damage-target->query_temp("apply/armor"),me,"pfm");
//                        target->receive_wound("kee",damage,me,"pfm");
                        wound=1;
                }

        if (weapon->query("anqi/type")=="寒毒针") 
                target->apply_condition("ice_poison", 3);

        msg += HIR "\n$n"HIR"躲闪不及，身上 "HIW+chinese_number(hitt)+HIR " 处中了"+anqi_type+"！\n\n"NOR;
                message_vision(msg, me, target);
                me->set_temp("chaofeng_time",time());
//                me->start_busy(1);
                COMBAT_D->report_status(target,wound);
                if(!target->is_busy()) target->start_busy(2+random(3));
        }

        msg = HIG"$n"HIG"对着$N"HIG"高声骂道：好啊，敢放暗器，看我怎么收拾你！\n" NOR;     
        message_vision(msg, me, target);
        me->kill_ob(target);

        return 1;
}


