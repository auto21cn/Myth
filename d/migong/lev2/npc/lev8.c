// migong lev2
#include <ansi.h>

inherit NPC;

void create()
{
        string str;
        set_name("黑寡妇", ({"hei guafu","guafu"}));
        set("race", "野兽");
        set("long",
"一只巨毒蜘蛛，一般人只闻其名，未见国真正的黑寡妇蜘蛛。\n");
        set("age", 40+random(51));
        set("combat_exp", 1200000+random(800001));
        set("daoxing", 1200000+random(800001));
        set("limbs", ({ "头部", "身体", "前爪", "尾巴", "肚皮", "后爪"}) );
        set("verbs", ({ "bite", "claw"}) );
        set("attitude", "aggressive");
        set("per", 10);
        set_skill("parry", 250);
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("blade", 250);
        set("max_sen",7500);
        set("max_kee",7500);
        set("force",5000);
        set("max_force",2500);
        set("max_mana",2500);
        set("mana",5000);
        set("mana_factor",120);
        set("force_factor",120);
        add_temp("apply/damage", 100);
        add_temp("apply/attack", 100);
        add_temp("apply/defense", 100); 
        add_temp("apply/armor", 200);  
        setup();
        carry_object("/d/obj/cloth/shoupiqun")->wear();
        carry_object("/d/qujing/jilei/obj/armor")->wear();
}


void init( )

{
        object ob;      
        remove_call_out("hunting");
        if( interactive(ob = this_player())  ) {
        call_out("hunting",1);
        }
        if(!environment()->query("no_fight") && random(10) < 5)
        call_out("hunting",1);
}

void hunting()
{
        int i;
        object *ob;
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
        if( !ob[i]->is_character() || ob[i]==this_object() || !living(ob[i])) continue;
        if(ob[i]->query("vendetta/authority")) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
}

void die()
{
        object ob, me, corpse;
        
        ob = this_object();
        me = query_temp("last_damage_from");
        
        message_vision(WHT"$N一声惨叫,砰然倒地，化为一股青烟消散了。\n"NOR,ob,me);
        if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
                corpse->move(environment(this_object()));
        if((int)me->query("combat_exp") < 600000)   {
                message("vision", me->name() + "成功消灭迷宫妖兽增加了40经验,二十天道行,20潜能。\n", me);
                me->add("combat_exp",40);
                me->add("daoxing",80);
                me->add("potential",20);
                destruct(ob);
        }

   
        destruct(ob);
        return;
}

int hit_ob(object me, object ob, int damage)
{
        ob->apply_condition("zhizhu_poison", 30);
        tell_object(ob, HIR "你觉得被咬中的地方一阵痛痒！\n" NOR );
        
}


