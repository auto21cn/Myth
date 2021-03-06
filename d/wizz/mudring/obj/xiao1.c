#include <ansi.h>
#include <command.h>
#include <weapon.h>

inherit F_AUTOLOAD; 
inherit SWORD;
#include "songs.c"

void create()
{
        set_name(HIC"洞箫"NOR,({"dong xiao","xiao"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else{
                set("unit","支");
                set("value",1000);
                set("material","blacksteel");
                set("unique", 1);
                set("treasure", 3);       
                set("sharpness", 5);
                set("rigidity", 8);
                set("weapon_prop/parry", 4);
                set("weapon_prop/sword", 4);
                set("wield_neili", 600);
                set("wield_maxneili", 1500);
                set("long","这是一支用上等"HIG"翡翠"NOR"做成的箫，做工十分精美，
                上面有许多的小字（zi）。\n");
                set("wield_msg",WHT"$N脸庞透过一丝微笑,轻轻从腰间掏出$n"WHT"握在手中。\n"NOR);
                set("unwield_msg",WHT"$N将$n"WHT"在空中舞了一圈，轻轻插回腰间。\n"NOR);
        }
       set("item_desc", ([
       "zi":"往事如寒烟飘渺，明日似骄阳如火。\n",
       "字":"往事如寒烟飘渺，明日似骄阳如火。\n",
       "曲谱":"           《圆圆曲》(yuanyuan_qu)
                《望海潮》(wanghai_chao)
                《问世间  情为何物》(wenshi_jian)
                《蝶恋花》(dielian_hua)
                《波斯小曲》(bosi_xiaoqu)
                《春江花月夜》(chunjiang_huayueye)
                《饮马长城窟行》(yinma_changcheng)
                《将进酒》(jiangjin_jiu)
                《笑傲江湖》(xiaoao_jianghu)
                《白雪歌送武判官回京》(baixue_ge)
                《虞美人》(yu_meiren)\n",

       ]));

        init_sword(150);
        setup();
}


void init()
{
        add_action("do_sing", "chang");
        add_action("do_halt", "ting");
}
int do_halt()
{
        if (find_call_out("sing_stage") < 0) return 0;
        this_player()->delete_temp("qupu");
        message_vision(HIR"\n$N发现大家一脸痛苦的表情，尴尬地咳嗽了两声，停下了噪音。\n"NOR, this_player());
        remove_call_out("sing_stage");
              return 1;
}
int do_sing(string arg)
{
       object me, ob; 
       int i = sizeof(qupu);
       int stage;
       stage = 0;
       me = this_player();
       ob = this_object();
       if (find_call_out("sing_stage") >= 0) return notify_fail("你能同时唱两首曲子吗？\n");
       if(!arg) return notify_fail("你想唱什么？\n");
        while (i--) if (arg == qupu[i]["name"]) break;
        if (i<0) return notify_fail("曲谱里还没有你想唱的曲子。\n");
        if(me->is_busy())
           return notify_fail("你正忙着呢。\n");
        if(me->query_temp("qupu")) return notify_fail("你正在唱着呢。\n");
        if(me->query("gender") != "男性"){
          if(present("dong xiao", me))
             message_vision(MAG
"$N轻捻$n"MAG"，起身盈盈拜起，玉唇含箫，只听：
曲调柔媚宛转，箫声缓缓荡漾，犹似微风起处，荷塘水波轻响。

接着$N微微一笑，曼声开始唱道：\n\n"NOR, me, ob);
          else message_vision("$N轻捻$n，起身盈盈一拜，然后曼声开始唱道：\n\n"NOR, me, ob);
          }
        else {
          if(present("dong xiao", me))
             message_vision(BLU"$N轻捻$n"BLU"，亭亭玉立，将洞箫含放唇边吹起来：\n\n"NOR, me, ob);
          else message_vision("$N轻捻$n，放开歌喉，呀呀呀唱了起来：\n\n"NOR, me, ob);
          }
      me->set_temp("qupu", 1);
      call_out("sing_stage", 2, me, stage, i, sizeof(qupu[i]["context"]));
      return 1;
}

void sing_stage(object me, int stage, int i, int size)
{
   if(stage < size) {
   message_vision(qupu[i]["context"][stage], me);
   me->start_busy(1);
   call_out("sing_stage", 1, me, ++stage, i, size);
   }
   else {
    me->delete_temp("qupu");
    if(me->query("gender") != "男性"){

      if(present("dong xiao", me))
          message_vision(MAG"\n过了一会，$N箫声渐缓渐轻，似乎流水汩汩远去，终于歌完曲终，寂然无声。\n"NOR,me);
      else message_vision("\n$N声调转高，唱完最后一字，歌声却依然曼长不绝，在空中来回荡漾。。。\n", me);
          }
    else {
      if(present("yao qin", me))
         message_vision(BLU"\n只听箫鸣止歇，$N唱完一曲，站起身来，恭身做了个鞠。\n"NOR, me);
      else message_vision("\n$N唱完最后一字，仰天一声长啸，啸声远远传了开去。\n", me);
          }
    }
}

int query_autoload() { return 1; }

