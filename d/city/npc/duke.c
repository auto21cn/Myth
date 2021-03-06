/***************************************
MUDLIB：Biographies         〓悟空传〓  
Created Admin By Waiwai@2001/02/18
Admin Email：wkzstory@21cn.com         
****************************************/
// Update by waiwai@2001/04/17

inherit NPC;

#include <ansi.h>

#define NULL  0
#define WHITE 1
#define BLACK 2
#define NULL2 3

#define END     0
#define OK      1
#define KEEP    2
#define CANNOTPUT       -1


class ISimple {
    int ComputerRun();
    int WhiteCount;
    int BlackCount;
    void NewGame(int ComputColor,int Difficult,int TimeOut);
    int CanPut(int x,int y);
    int GetPiece(int x,int y);
    int Put(int x,int y);
} = "{B3C3EDB1-E735-11D1-BF0B-0000B4560A15}";



class ISimple ab;
int savex,savey;

int NewGame(int Color,int Difficult,int TimeOut)
{
    ab->NewGame(Color,Difficult,TimeOut);
    savex=-1;savey=-1;
}


string PrintPad()
{
    int i,j;
    string ret;

    ret= "\n　y ０　１　２　３　４　５　６　７　\n";
    ret+="x ╔═╤═╤═╤═╤═╤═╤═╤═╗\n";
    for (i=0;i<8;i++)
    {
        ret=ret+i+" ║";
        for (j=0;j<8;j++)
        {
            if ((savex>=0)&&(savex==i)&&(savey==j))
            {
                switch (ab->GetPiece(i,j))
                {
                case WHITE:
                    ret+=HIY "●" NOR;
                    break;
                case BLACK:
                    ret+=HIY "〇" NOR;
                    break;
                default:
                    ret+=HIY "  " NOR;
                }
            }
            else
            {
                switch (ab->GetPiece(i,j))
                {
                case WHITE:
                    ret+="●";
                    break;
                case BLACK:
                    ret+="〇";
                    break;
                default:
                    ret+="  ";
                }
            }
            ret+="║";
        }
        if (i!=7)
            ret+="\n　╟═┼═┼═┼═┼═┼═┼═┼═╢\n";
        else
            ret+="\n　╚═╧═╧═╧═╧═╧═╧═╧═╝\n";
    }
    return ret;
}

int ComputerRun()
{
    int ret=ab->ComputerRun();
    if (ret>=0)
    {
        savey=ret%8;
        savex=(ret/8)%8;
    }
    return ret;
}

int Put(int x,int y)
{
    int ret;
    ret = ab->Put(x,y);
    savex=x;
    savey=y;
    return ret;
}

int WhiteCount()
{
    return ab->WhiteCount;
}

int BlackCount()
{
    return ab->BlackCount;
}

InitGame()
{
    ab=new(class ISimple);
}




int Do_New();
int Do_Stop();
int Do_Think(object ob);
int Do_Put(string arg);

void create()
{
    set_name("空色", ({ "duke"}) );
    set("title", "人智牛人");
    set("gender", "男性" );
    set("age", 18);
    set("int", 26);
    set("long",
        "空色是个博学多闻的牛人，你可以和他下棋(play)。\n");
    set("attitude", "peaceful");
//    set_skill("literate", 60);
//    set_skill("computer", 500);
    set("combat_exp", 500000);
    set("hasgame",0);
    InitGame();
    setup();
}

int init()
{
    ::init();
    add_action("Do_Put","put");
    add_action("Do_New","play");
    add_action("Do_View","view");
    add_action("Do_Stop","giveup");
}

int Do_Judge(object ob)
{
    set("hasgame",0);
    message_vision("空色对$N说:我有"+WhiteCount()+"子,你有"+BlackCount()+"子.\n",ob);
    if (WhiteCount()>BlackCount())
    {
        message_vision("空色对$N说:你回去再练几年吧!\n",ob);
        command("idiot "+ob->query("id"));
        return 1;
    }
    if (WhiteCount()==BlackCount())
    {
        message_vision("空色对$N说:你还行!\n",ob);
        command("nod "+ob->query("id"));
        return 1;
    }
    message_vision("空色对$N说:你真行!\n",ob);
    command("admire "+ob->query("id"));
    return 1;
}

int Do_View()
{
    printf(PrintPad());
    return 1;
}

int Do_Stop()
{
    if (query("player")!=this_player()->query("id"))
        return 0;
    set("hasgame",0);
    message_vision("空色对$N说:这样就认输了?\n",this_player());
    command("sigh "+this_player()->query("id"));
    return 1;
}

int Do_New()
{
    object ob=this_player();

    if (query("hasgame"))
    {
        message_vision("空色对$N说:我正下着呢!不过你可以看(view).\n",ob);
        return 1;
    }
    NewGame(1,2,1000);
    set("hasgame",1);
    set("player",ob->query("id"));
    printf(PrintPad());
    message_vision("空色对$N说:让你先下(put),弃权也可以(giveup)!\n",ob);

    remove_call_out("think");
    call_out("think", 30);
    ob->set_temp("marks/空色",0);
    return 1;
}

int Do_Think(object ob)
{
    int ret=100;

    for (;ret>=64;)
    {
        ret=ComputerRun();
        if (ret>128)
        {
            printf(PrintPad());
            Do_Judge(ob);
            return 0;
        }
        if (ret==-1)
            return -1;
        if (ret==-2)
            return -1;
        printf(PrintPad());
        if (ret>64)
            message_vision("空色对$N说:我继续 :).\n",ob);
    }
    message_vision("空色对$N说:该你了.\n",ob);
    return 1;
}

void think()
{
    object ob;
    int idlecount;
    object env;
    mapping exits;
    string* key;

    if (!query("hasgame")) return;
    env=environment(this_object());
    ob=find_player(query("player"));

    if (ob&&(!userp(ob)))
    {
        command("say 这家伙居然跑了,太面了");
        set("hasgame",0);
    }
    else if (environment(ob)!=environment(this_object()))
    {
        command("say 这家伙居然跑了,太面了");
        set("hasgame",0);
    }
    else
    {
        idlecount=ob->query_temp("marks/空色");
        if (idlecount>5)
        {
            set("hasgame",0);
            remove_call_out("think");
            message_vision("空色对$N说:我没空和你闲坐,滚!\n",ob);
            message_vision("$N被空色一脚踹了出去!\n",ob);
            exits=env->query("exits");
            if (!exits||!mapp(exits)) return;
            key=keys(exits);

            ob->move(exits[key[random(sizeof(exits))]]);
            return;
        }
        ob->set_temp("marks/空色",idlecount+1);
        message_vision("空色对$N说:你倒是下啊.\n",ob);
        remove_call_out("think");
        call_out("think", 30);
    }
}

int Do_Put(string arg)
{
    int ret,x,y;
    string Pad;
    object ob=this_player();

    if (query("player")!=this_player()->query("id"))
        return 0;
    if (!arg)
    {
        message_vision("空色对$N说:用put x y.\n",ob);
        return 1;
    }

    if (!query("hasgame"))
    {
        message_vision("空色对$N说:我没跟你下啊?\n",ob);
        return 1;
    }
    if (sscanf(arg,"%d%d",x,y)!=2)
    {
        message_vision("空色对$N说:用put x y.\n",ob);
        return 1;
    }
    ret=Put(x,y);
    switch (ret)
    {
    case END:
        Pad=PrintPad();
        printf(Pad);
        Do_Judge(ob);
        break;
    case OK:
        Pad=PrintPad();
        printf(Pad+"\n");
        message_vision("空色对$N说:该我下了.\n",ob);
        Do_Think(ob);
        break;
    case KEEP:
        Pad=PrintPad();
        printf(Pad+"\n");
        message_vision("空色对$N说:我先不走,你继续 :(.\n",ob);
        break;
    case CANNOTPUT:
        message_vision("空色对$N说:你会不会啊?\n",ob);
        command("idiot "+ob->query("id"));
        break;
    }
    remove_call_out("think");
    call_out("think", 30);
    ob->set_temp("marks/空色",0);
    return 1;
}


