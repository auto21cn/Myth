// xiaohuandan.c 小还丹
// Created by kuku@sjsh 2003.2

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"小还丹"NOR, ({ "xiaohuan dan","dan" }) );        
        set("weight", 50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","一颗灵药，其色碧绿。耗损真气后服此药，丹田热气升起，精力弥漫，可助功力的恢复。\n");
                set("unit", "颗");
                set("value", 2000);
                set("drug_type", "补品");
        }
        set("is_monitored",1);
        setup();        
}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_drop","drop");
}

int do_eat(string arg)
{
        object ob;
        ob=this_player();    
        
        if (arg!="dan" && arg!="xiaohuan dan")
                return 0;
        if (arg!="dan" ) return 0;   
        
        ob->set("kee",(int)ob->query("max_kee"));
        ob->set("gin",(int)ob->query("max_gin"));
        ob->set("sen",(int)ob->query("max_sen"));
        ob->set("eff_kee",(int)ob->query("max_kee"));
        ob->set("eff_gin",(int)ob->query("max_gin"));
        ob->set("eff_sen",(int)ob->query("max_sen"));

        ob->set("food",(int)ob->max_food_capacity());
        ob->set("water",(int)ob->max_water_capacity());

        write(HIG+"你拿出一颗小还丹，放入口中，吞了下去，顿时有一种飘飘欲仙的感觉，身上病痛、疲劳似乎一下子都消失了。\n"NOR);

        message("vision", HIG + ob->name() + "拿出一颗小还丹，放入口中，吞了下去，顿时有一种飘飘欲仙
的感觉，身上病痛、疲劳似乎一下子都消失了。\n"+NOR,environment(ob), ob);
        destruct(this_object());
        return 1;
}

int do_drop(string arg)
{
        object ob = this_object();
        object me = this_player();
        
        if(arg == "xiaohuan dan" || arg == "dan"){
                message_vision("好可惜呀，这么珍贵的药就这样被"+me->query("name")+"随手扔掉了，"+ob->query("name")+"转眼间就消失的无影无踪。\n",me,ob); 
                destruct(ob);
        }
        return 1;
}
