#include <ansi.h>
inherit NPC;
 
void create()
{
        set_name("魔礼寿", ({ "tian wang", "chiguo tianwang", "shou", "tianwang", "wang" }) );
        set("gender", "男性" );
        set("long","
四大天王之一，身担着保护后宫安全的重担，非同小可。他
的武功似乎属佛门一派，护国天王还有另外的杀手绝招，但
没有人知道是什么。也许正因为如此，玉皇才放心让他独担
重任。\n"
        );
        set("class", "xian");
        set("title", "持国天王");
        set("age",43);
        set("str",60);
        set("int",37);
        set("max_kee",5100);
        set("kee",5100);

        set("max_sen",5100);
        set("sen",5100);
        set("combat_exp",4500000);
        set("daoxing",4500000);
        set("force",5500);
        set("max_force",2500);
        set("mana",4500);
        set("max_mana",2250);
        set("force_factor", 270);
        set("mana_factor",220);


        set("eff_dx", 3500000);
        set("nkgain", 800);


        set_skill("unarmed",140);
        set_skill("changquan", 180);
        set_skill("parry",280);
        set_skill("dodge",380);
        set_skill("mace",380);
        set_skill("spells", 180);
        set_skill("wusi-mace",380);
        set_skill("force",380);
        set_skill("moshenbu", 340);
        map_skill("dodge", "moshenbu");
        map_skill("mace","wusi-mace");
        map_skill("parry","lunhui-zhang");
        map_skill("unarmed", "changquan");
        set("inquiry", ([
                "name" : "在下就是持国天王，奉圣谕把守北天门。",
                "here" : "这里就是北天门，里面是后宫禁地。",
        ]) );
        setup();
        carry_object("/d/obj/weapon/mace/copperjian")->wield();
        carry_object("/d/obj/armor/jinjia")->wear();
}


void kill_ob (object ob)
{
  object me = this_object();

  call_out ("huahudiao",5+random(2),me,ob);  
  ::kill_ob(ob);
}



void huahudiao (object me, object ob)
{
  object huobing;
  int damage;

  if (! me)
    return;

  if( !living(me) )
    return;

  if (! ob)
    return;

  if (environment(ob) != environment(me))
    return;

  message_vision (HIY"$N从囊中取出花狐貂，祭在空中，化作一只白象；"
       +"口似血盆，牙如利刀，向$n咬来！\n"NOR,me,ob);

  if ( (ob->query("force")+random(500)) > 4000 )

     message_vision (HIY"$N大喝一声：大胆！\n"
       +"花狐貂吓的连忙钻回$n的囊中。\n"NOR,ob,me);
  else 
    {
     message_vision (HIY"结果$N被咬出一条血肉模糊的口子！\n"NOR,ob,me);
     damage=(me->query("force"))/5; 
     if ( ob->query("kee") < damage ) ob->unconcious();
     else ob->add("kee",-damage);
    } 

  remove_call_out ("huahudiao");  
  call_out ("huahudiao",random(6)+4,me,ob);  
}


void die ()
{
  object me = this_object();
  message_vision (HIY"$N吓得撒腿就跑。\n"NOR,me);
  destruct (this_object());
  return ;
}
