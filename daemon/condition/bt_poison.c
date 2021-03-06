#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
         if( !living(me) ) return CND_CONTINUE;      
         tell_object(me, HIB "你忽然感到身体僵直，已经不听使唤了。\n" NOR );            
         me->receive_wound("kee", 50);
         if(userp(me))
                 me->receive_wound("sen", 60);
         else me->receive_wound("sen", 80);        
         me->set_temp("death_msg","体内怪蛇之毒发作死了。\n");
      
         if( me->query("sen") > 301)
                 tell_room(environment(me), YEL+me->name()+"突然只膝弯曲，身子慢慢垂下，口中发出似人似兽的荷荷之声。\n" NOR, ({ me }));            
         else if( me->query("sen") < 450 && me->query("sen") > 301)
                 tell_room(environment(me), BLU+me->name()+"忽然满面堆欢裂嘴嘻笑，更显得诡异无伦。\n" NOR,  ({ me }));        
         else if( me->query("sen") < 300 && me->query("sen") > 201)
                 tell_room(environment(me), HIB+me->name()+"此时神智更加胡涂，指东打西，乱□乱咬。\n" NOR,({ me }));           
         else    
                 tell_room(environment(me), HIR+me->name()+"突然缩成一团，滚在地上不停地发颤。\n" NOR,({ me }));

         if( duration < 1 ) return 0;           
         me->apply_condition("bt_poison", duration - 1);
         return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}
