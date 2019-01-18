#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL"�ɿ���"NOR, ({ "choclate","qiao ke li","qiao" }) );
        set("long",
HIB"�������Ϊ���׼����ʥ���ɿ����ģ���ɫ���ޣ����˴�������!\n"NOR);
        set("unit", "��");
        set("weight", 300);
        set("value", 0);
	set("no_give",1);
	set("no_put",1);
	set("no_drop",1);
  setup();
}

int init ()  
{   
  add_action ("do_eat", "eat");
  return 1;
}

string rdm(string *strs)
{
  return strs[random(sizeof(strs))];
}

int do_eat (string arg)
{
  string *hows = ({
    "����Ҹ���",
    "���������",
    "��������",
    "�����̵�",
    "��Ϊ�����",
    "��ͷ������",
    "�м����ܵ�",
    "������",
    "�����û���������",
    "ׯ�ϵؿ��Ŵ�ң�Ȼ���¸ҵ�",
    "���������",
    "����������",
    "�������ɵ�",
    "�������ۣ�",
    "ҡͷ���Ե�",
    "����һЦ��",
    "����һ��",
    "���ֱ��ŵ�",
    "��ͷ���Ե�",
    "������Ц����������",
    "�ƿ����ˣ��ںü�ʽ��",
    "��ͷ�����",
    "�˷ܵ���ͷ�󺹣�",
    "��Ƽ��ݵ�",
    "Ĩȥ�۽ǵ��Ứ��",
    "����֣�һ��ţ�",
    "������צ��",
    "ʮ��ǫ���",
    "�ߵ�����ͨ�죬",
  });

  string *manners = ({
    "��$n�������ﷴ�����˼��£�",
    "��$n�ڵ��Ϸ��ض�⣬",
    "��$n��ǽ���ص�һ���ҿ���",
    "��$n���Ŀ���ϸů��һ�£�",
    "��$n���͹���Ѹ��һը��Ȼ��",
    "������$n��",
    "ʹ��˺��$n��һ��һ���",
    "��$n������Ĩ��һ�����ެ�ѽ���",
    "����$nպ�ź��ĺ��ǣ�",
    "��$n������һ����Σ�",
    "��$n���������Ƭ��ƹϣ�",
    "��$n�ڽ�����һպ��Ʒ��ζ",
    "��$n�����������һ�㣬���е�",
    "��$n�ڿ�ˮ��һ�ݣ�����",
    "��$n�ڻ���һ�ǣ��Ͻ�",
    "��һ�������п�$n��",
    "��������$n",
    "��һ�����˾�����$n�ϣ�",
    "��$n������ˮϴ�øɸɾ�����",
    "��$n�����˰��죬",
    "��$n����һ��ե��˿��",
    "��$n�Ϲ�һ��������ң�",
    "��$n�ʹн���ĩ����һ��",
    "��$n���飬�������ˣ�",
    "��$n�г�С�飬���ϼ����������ȵ����͹��ﳴ�ɹ���$n��",
    "��$n�Ž�������Ͻ��ͺ���С�����ɺ���$n��",
    "��$n�����ڹ��ﵹ�������ͳ�һ���Ǵ�$n��",
  });

  string *actions = ({
    "�ſ�ӣ��С��������ȥ",
    "����Ƭ���촽ҧסֻһ����������ȥ",
    "һ�����������ȥ",
    "��������ƹƹ����һ��",
    "����üͷʹ�ļ��׵س�����ȥ",
    "������һ�ӣ�������Ӱȵ�һ����ס",
    "���������ʹ����һ��",
    "Ӳ��ͷƤ����׽���س�����ȥ",
    "��ર����ü���۵س�����ȥ",
    "�������������ݱ�������ڵ�������ȥ",
    "������ζ����ָ��������ȥ",
    "����û�����첱�ڽŵ�������ȥ",
    "�ʷʵ�����һ��",
    "��������Ͳ����������˶���",
    "һ���ҧ�ų��˲�����",
    "�ſ�Ѫ���ڣ�������������һ��",
    "�Ե��񾭴�����ð����",
    "�Ե������񶫵�����",
    "�Ե������������",
    "�Ե����ߵ��������",
    "�Ե÷����������ذ�",
    "���̻��ʵط�����������ҽ�������ȥ",
    "��������ش����������ֻһ�����������������������ȥ",
    "ʹ�಻���س�����ȥ",
  });

   int bonus;
        if( !id(arg) ) return notify_fail("��Ҫ��ʲ�᣿\n");

  message_vision ("$N"+rdm(hows)+rdm(manners)+rdm(actions)+"��\n",
                  this_player(),this_object());
	  bonus=random(this_player()->query("combat_exp")/800);
	if (!this_player()->query_temp("xmas"))
	this_player()->set_temp("xmas",1);
	bonus=bonus/this_player()->query_temp("xmas");
	bonus=bonus*(this_player()->query("kar")/30);
  this_player()->add("potential",bonus);
write(HIR+"��õ���"+chinese_number(bonus)+"��Ǳ��!\n"NOR,
               environment(this_player()), this_player());
   this_player()->add_temp("xmas",1);
  destruct(this_object());
  return 1;
}