#ifndef __SYSTEM_ASKINFO_H
#define __SYSTEM_ASKINFO_H
// �ͻ��˷������ļ�����

#define ASKINFO_NORMAL			0
#define ASKINFO_CHANGESHAPE		1
#define ASKINFO_CHANGENAME		2 // �޸�����
#define ASKINFO_CITYGUARD		3 // ��ǽ����
#define ASKINFO_QUEST			4 // ����
#define ASKINFO_BUILDING		5 // ����
#define ASKINFO_LEVY			6 // ����
#define ASKINFO_TRAIN			7 // ѵ��
#define ASKINFO_EQUIPFORGING    8  // װ������
#define ASKINFO_EQUIPWASH       9  // װ��ϴ��
#define ASKINFO_EQUIP			10 // װ��
#define ASKINFO_ITEM			11 // ����
#define ASKINFO_HERO			12 // Ӣ��
#define ASKINFO_TECH			13 // �Ƽ�
#define ASKINFO_GOV				14 // �ٸ� 
#define ASKINFO_OFFICIALHIRE	15 // ��Ӷ 
#define ASKINFO_QUICK			16 // ����
#define ASKINFO_ACTOR			17 // ��ɫ����

int system_askinfo( int actor_index, int msgid, char *pstr, int *pvalue );

#endif
