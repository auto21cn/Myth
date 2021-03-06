// edit.c
// Modified by mudring@sjsh

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string file)
{
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! file)
                return notify_fail("指令格式：edit <档名>\n");

        if (in_edit(me))
                return notify_fail("你已经在使用编辑器了。\n");

        seteuid(geteuid(me));
        file = resolve_path(me->query("cwd"), file);

        if (!(int)SECURITY_D->valid_write(file,me,"write"))
                return notify_fail("你没有足够的读写权利。\n");

        foreach (object user in users())
        if (file == "/"+in_edit(user) )
                return notify_fail("共享冲突："+user->name(1)+"("+capitalize(user->query("id"))+")"+"正在编辑该文件("+file+")。\n");

        MONITOR_D->report_adm_object_msg(me,HIR" edit " + file + "!"NOR); 
        log_file("cmds/edit/"+geteuid(me), sprintf("edit %s at %s from %s.\n",
                                        file, log_time(),
                                        query_ip_number(me)));

        printf("编辑文件：%s\n",file);
        me->set("cwf", file);
        SECURITY_D->backup_file(file);
        ed(file);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : edit <档名>, edit here

利用此一指令可直接在线上编辑档案。

HELP );
        return 1;
}

