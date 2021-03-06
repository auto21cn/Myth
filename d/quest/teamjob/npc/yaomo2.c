

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("鬼将", ({ "gui jiang", "jiang" }));
        set("gender", "男性" );//性别与上面对应
        set("long",
"一个被打入十八地狱的恶鬼，被魔界提升为小小将领。\n");
        set("family/family_name","阎罗地府");
        set("attitude", "aggressive");
        set("vendetta/authority",1);
        set("title",HIW"魔界小将"NOR);
        set("nickname",HIB"鬼魅人间"NOR);
        set("force_factor",100+random(180));
        set("mana_factor",100+random(180));
        set("max_kee",9000+random(3000));
        set("max_sen",1000+random(990));
        set("max_force",20000+random(5000));
        set("max_mana",20000+random(5000));
        set("force",25000+random(3000));
        set("mana",2500+random(5900));
        set("per", 1);
        set("int", 60);
        set("age", 56);
        set("combat_exp", 5000000+random(2000000));
        set("daoxing", 5000000+random(2000000));
        set("chat_chance_combat", 160);
        set("chat_msg_combat", ({
                (: perform_action, "whip", "biluo" :),
                (: perform_action, "whip", "yanluo" :),
                (: perform_action, "whip", "three" :),
                (: cast_spell, "gouhun" :),
                (: cast_spell, "zhuang" :),
                (: cast_spell, "hunfei" :),
                (: cast_spell, "inferno" :),
        }) );
        set("chat_chance", 5);
        set("chat_msg", ({
                "鬼将长喝道：杀啊！！\n",
                "鬼将长笑道：这次一定要消灭天宫诸仙！\n",
                (: random_move :),
        }) );

        set_skill("unarmed", 150+random(150));
        set_skill("whip", 150+random(150));
        set_skill("parry", 150+random(150));
        set_skill("dodge", 150+random(150));
        set_skill("jinghun-zhang", 150+random(150));
        set_skill("hellfire-whip", 150+random(150));
        set_skill("ghost-steps", 150+random(150));
        set_skill("zhuihun-sword", 150+random(150));
        set_skill("kusang-bang", 150+random(150));
        set_skill("force", 150+random(150));
        set_skill("spells", 150+random(150));
        set_skill("gouhunshu", 150+random(150));
        set_skill("tonsillit", 150+random(150));

        map_skill("whip", "hellfire-whip");
        map_skill("parry", "hellfire-whip");
        map_skill("unarmed", "jinghun-zhang");
        map_skill("dodge", "ghost-steps");
        map_skill("force", "tonsillit");
        map_skill("spells", "gouhunshu");
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 20);

if (random(20)>15)
{
        set_temp("apply/attack", 200);
        set_temp("apply/defense", 200);
        set_temp("apply/armor", 200);
        set_temp("apply/damage", 200);
}

        setup();

        carry_object("d/obj/armor/yinjia")->wear();
        carry_object("d/obj/weapon/whip/fuchen")->wield();
        add_money("silver", 50);
}
void init( )
{
        call_out("hunting",180);
}

void hunting()
{
        object ob=this_object();
        write(HIW"只听天上传来三声令响！魔界鬼将撤出了天宫！\n"NOR);
        destruct(ob);
}

void die()
{
        object ob, me, corpse;
        
        ob = this_object();
        me = query_temp("last_damage_from");
        
        if (me)
        {    
             message_vision(WHT"$N大叫一声,我命休矣！倒地而亡。\n"NOR,ob,me);
             if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
             corpse->move(environment(this_object()));
             if((int)me->query("combat_exp") < 2000000)   
             {
                 message("vision", me->name() + HIG"由于成功的保卫了天宫,增加了400经验,一年道行和200潜能。\n"NOR, me);
                 me->add("combat_exp",400);
                 me->add("daoxing",1000);
                 me->add("potential",200);
                 destruct(ob);
             }
             message("vision", me->name() + HIG"成功的保卫了天宫。\n"NOR, me);
             me->add("weiwang",1);
        
        }
        destruct(ob);
        return;
}

