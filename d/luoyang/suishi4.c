inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
һ����ʯС·�����¹��꣬·�濴���������ɾ��ģ�һЩ����������
�Լ��ֵ��߲˵������������˲��Ǻܶ࣬ߺ����������Զ��·������һ��
����ؤ���������޼ҿɹ�������Ĵ��ε�����������Կ�����������һ
�档·�����߶��ǵ��ص�һЩ��լ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"nantou",
                "west" : __DIR__"suishi5",
                "north" : __DIR__"xiaoxiang3",
        ]));

        setup();
        replace_program(ROOM);
}
