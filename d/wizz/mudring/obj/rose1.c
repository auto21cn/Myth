// rose1.c 红玫瑰

#include <armor.h>
#include <ansi.h>

inherit FINGER;

void create()
{
        set_name(YEL "黄玫瑰" NOR, ({ "yellow rose", "rose", "meigui" }));
        set("weight", 100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", YEL "一朵雪人送的黄玫瑰，带给你一丝温情。\n" NOR);
                set("value", 5000);
                set("wear_msg", HIM "$N嘻嘻一笑，把花儿别在发髻上，有如天女下凡。\n" NOR);
                set("remove_msg", HIM "$N把花儿从发髻取下，深深闻了闻，揣回怀中。\n" NOR);
                set("armor_prop/armor", 10);
        }
        setup();
}

void init()
{
  
  add_action("come_life","wen");
  add_action("come_life","smell");

}
        
int come_life(string arg)
{
    object me;
    me=this_player();

    if(!arg) return 0;
    if(arg == "rose" || arg == "red rose" ) 
      {
        me->delete("oyf_fail");        
        message_vision(YEL"$N用小指轻轻捻住黄玫瑰，拿起来深深地闻了闻。\n"NOR,me);
        tell_object(me, HIY "嗯。。。啊。。。好香呀！\n" NOR);
        message_vision("黄玫瑰渐渐枯萎了。\n",me);
        destruct(this_object());
      }    
    return 1;
}

