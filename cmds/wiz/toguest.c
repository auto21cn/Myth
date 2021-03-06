// toguest.c
// mon 8/3/99
// modify by mudring

inherit F_CLEAN_UP;

string JAIL="/d/wiz/guest";
int help(object me);

int main(object me, string arg)
{
    int online, howlong;
    object who, env;
    string id;

    seteuid(geteuid(me));

    if (!arg) return notify_fail("你想要将谁送入迎客厅？\n");
    arg=replace_string(arg,"#"," ");
    arg=replace_string(arg,"."," ");

    if(sscanf(arg, "%s for %d", id, howlong)==2) {
        if(howlong<1) return notify_fail("天数应该至少为一天。\n");
    } else {
        id=arg;
        howlong=2;
    }

    who = UPDATE_D->global_find_player(id);

    if (env=environment(who))
        message_vision("天空中探出一只大手将$N抓起来不见了。\n", who);
        
    who->set("banned_approved",time()+24*3600*howlong);
    who->move(JAIL);
    who->set("startroom",JAIL);
    log_file("cmds/to_guest",
        sprintf("%s send %s to guestroom for %d (days) at %s.\n",
            getuid(this_player()), getuid(who), howlong, log_time()));
        write("你将"+who->query("name")+"("+id+")送进了迎客厅，"+
            chinese_number(howlong)+"天后释放。\n");

    UPDATE_D->global_destruct_player(who, 1);
    return 1;
}

int help(object me)
{
write(@HELP
指令格式：toguest id               -- send to guest for 2 days.
          toguest id for <number>  -- send to guest for <number> days.
          
          e.g.: toguest id for 7 

Send <id> to xyj guest room.
HELP
    );
    return 1;
}
