#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
         if( !living(me) ) {
                 message("vision", me->name() + "痛苦地哼了一声。\n", environment(me), me);
         }
         else {
                 tell_object(me, HIB "忽然一阵刺骨的奇寒袭来，你中的毒发作了！\n" NOR );
                 message("vision", me->name() + "的身子突然晃了两晃，牙关格格地响了起来。\n",environment(me), me);
         }
         me->receive_damage("kee", 25);
         if(userp(me))
                 me->receive_wound("sen", 35);
         else me->receive_wound("sen", 50);      
         me->apply_condition("xx_poison", duration - 1);
         if( duration < 1 ) return 0;
         return CND_CONTINUE;
}
