// clone.c
#include <ansi.h>
#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string file)
{
        object obj;
        string err, msg;

        seteuid( geteuid(me) );

       if (me != this_player()) return 0;

     if (! SECURITY_D->valid_grant(me, "(wizard)"))
             return 0;
        if (!file) file = me->query("cwf");
        if (!file)
                return notify_fail("��Ҫ����ʲ�������\n");

        file = resolve_path(me->query("cwd"), file);
        if( sscanf(file, "%*s.c") != 1 ) file += ".c";
        me->set("cwf", file);

        if( file_size(file) < 0 )
                return notify_fail("û���������(" + file + ")��\n");

        if( !find_object(file) ) {
                err = catch(call_other(file, "???"));
                if (err) {
                        write("����ʧ�ܣ�" + err + "\n");
                        return 1;
                }
        }

        err = catch(obj = new(file));
        if (err) {
                write("����ʧ�ܣ�" + err + "\n");
                return 1;
        }

        obj->set("clone_by_wizard", getuid(me));
        if( !stringp(msg = me->query("env/msg_clone")) )
                msg = "ֻ��$N�������һָ�������$n��\n";
        log_file("static/CLONE","["+ctime(time())+"] "+sprintf("%s(%s) clone %O\n",
         me->query("name"),me->query("id"),
         obj));

        if ( !is_root(me) ) {

        shout(HIR"��Clone���顿��������(Faguan)����˵"+ me->query("name") + "������ "HIW + obj->query("name") +" ��\n"NOR);
        write(HIR"��Clone���顿��������(Faguan)����˵"+ me->query("name") + "������ "HIW + obj->query("name") +" ��\n"NOR);
        }
        if( !obj->is_character() && obj->move(me) ) {
                write(obj->query("name") + "���Ƴɹ������������Ʒ����\n");
        message_vision(msg + "\n", me, obj);
                return 1;
        }
        if( obj->move(environment(me)) ) {
                write(obj->query("name") + "���Ƴɹ�������������䡣\n");
        message_vision(msg + "\n", me, obj);
                return 1;
        }
        if ( !is_root(me) ) {
        shout(HIR"��Clone���顿��������(Faguan)����˵"+ me->query("name") + "������ "HIW + obj->query("name") +" ��\n"NOR);
        write(HIR"��Clone���顿��������(Faguan)����˵"+ me->query("name") + "������ "HIW + obj->query("name") +" ��\n"NOR);
        }
        destruct(obj);
        return notify_fail("�޷����Ʋ����ƶ������(" + file + ")��\n");
}

int help(object me)
{
  write(@HELP
ָ���ʽ : clone <����>
���ô�ָ��ɸ����κ����ƶ�֮���(������)��
HELP
    );
    return 1;
}