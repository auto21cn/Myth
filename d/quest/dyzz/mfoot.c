// Room: /d/quest/dyzz/mfoot.c

#include <ansi.h>
inherit ROOM;
#include "banned.h"

void create()
{
        set("short", "山脚");
        set("long", @LONG
沼泽到了这里似乎已经被西边的山冈挡住了。这里虽然也是光秃秃的，
可是地上已经开始长出青草，地面也很干燥，再也见不到潮湿的土地。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"zhaoze10",
        ]));

        set("alternative_die",1);
        set("dyzzroom",1); 
        setup();
}

void init()
{          
        object me = this_player();
        add_action("do_quit",banned_action);  
        add_action("do_cast","cast");
        add_action("do_exert","exert");
        if (me->query("env/invisibility"))  
            me->delete("env/invisibility");
       
        if( !wizardp(me) && userp(me) ) {        
                remove_call_out("kick_ob");
                call_out("kick_ob",60);
        }        
}

void kick_ob()
{
        object room,*obj;
        int i;

        obj=deep_inventory(this_object());
        if (!sizeof(obj))   return;
        for (i=0;i<sizeof(obj);i++){
                if (interactive(obj[i]) && (time()-obj[i]->query_temp("dyzz_enter_time"))>1800){
                        message_vision(CYN"一阵清风吹来,清烟消散,$N也随着清烟散去！\n"NOR,obj[i]);
                        if (!room=find_object("/d/city/kezhan") )
                                room=load_object("/d/city/kezhan");
                        obj[i]->move(room);
                        obj[i]->dismiss_team(); 
                        message("vision",CYN"一个人影随着一阵清烟从魔幻世界飘了出来!\n"NOR,room,({obj[i]}));
                        call_out("kick_ob",60);
                        return;
                }
        }
        call_out("kick_ob",60);
}

int do_quit(string arg) 
{  
        write("进来了就老老实实的吧，你只有一条路可走。\n");  
        if (wizardp(this_player())) write("禁止使用此命令。\n");  
                return 1;  
}   

int do_cast(string arg) { 
        if(!arg) return 0;
        if(arg !="transfer" ) write("你不能在这里用这条命令。\n");    
        command("cast transfer");
        return 1;
}

int do_exert(string arg) { 
        if(!arg) return 0;
        if(arg !="recover" && arg != "heal" && arg != "refresh") return 0;
        command("exert "+arg);  
}

void alternative_die(object who)  
{  
        object killer,corpse;
        killer = who->query_temp("last_damage_from");  
   
        if (userp(who)) {  
                message_vision("$N死了。\n",who);  
                who->set("kee",10); who->set("sen",10);  
                if(who->query("eff_kee")<10) who->set("eff_kee",10);  
                if(who->query("eff_sen")<10) who->set("eff_sen",10);           
                if(!killer) killer=who; 
//        if( objectp(corpse = CHAR_D->make_corpse(who, killer)) )  
//                corpse->move(this_object());  
                all_inventory(this_object())->remove_killer(who);               
                who->remove_ride();  
                who->dismiss_team();  
                who->delete_temp("last_fainted_from");  
                who->move("/d/city/kezhan");  
        }  
        else {  
                if( objectp(corpse = CHAR_D->make_corpse(who, killer)) )  
                        corpse->move(this_object());  
                message_vision("$N死了。\n",who);  
                who->reward();    
                destruct(who);  
        }  
}