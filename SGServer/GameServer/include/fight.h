#ifndef _FIGHT_H_
#define _FIGHT_H_

#define FIGHT_UNIT_MAX		256	// ս��˫����Ԫ����
#define FIGHT_TURNS_MAX		8192
#define FIGHT_INT			100
#define FIGHT_FLOAT			100.0f

#define FIGHT_WIN			1	
#define FIGHT_LOSE			2

#define FIGHT_ATTACK		1	
#define FIGHT_DEFENSE		2

#define FIGHT_UNITTYPE_HERO		1 // ���Ӣ��
#define FIGHT_UNITTYPE_GUARD	2 // ��ҳ�ǽ����
#define FIGHT_UNITTYPE_MONSTER	3 // �����

#define FIGHTTYPE_STORY		1 // ����ս��
#define FIGHTTYPE_CITY		2 // ��ս
#define FIGHTTYPE_NATION	3 // ��ս
#define FIGHTTYPE_ENEMY		4 // ����
#define FIGHTTYPE_RES		5 // ��Դ������

// һ��ս����Ԫ
typedef struct _fightunit
{
	short	offset;
	int		army_index;			// ������������
	char	type;				// 1���Ӣ�ۣ�2��ǽ������3monster
	int		city_index;			// ��������
	int		index;				// (type=1 kind=Ӣ������) (type=2 kind=��������)
	int		kind;				// (type=1 kind=Ӣ��kind) (type=2 kind=����kind) (type=3 kind=monsterid)

	short	shape;				// ����
	short	level;				// �ȼ�
	char	color;				// ��ɫ
	char	corps;				// ����
	int		attack;				// ����
	int		defense;			// ����
	int		hp;					// ��ǰѪ
	int		maxhp;				// ��սʱѪ
	int		troops;				// Ѫ����
	short	attack_increase;	// ������ǿ
	short	defense_increase;	// ������ǿ
	short	assault;			// ����
	short	defend;				// �س�
	char	line;				// ��������
	char	skillid;			// �佫��

	char	line_left;			// ��ǰʣ������
	int		line_hp;			// ��ǰ��ʣ�����
	int		damage;				// ���˺�
	int		prestige;			// ����
}FightUnit;

// ս���ṹ
typedef struct _fight
{
	char	type;							// ս������
	char	result;							// ս�����
	int		turns;							// ��ǰ�غ�
	int		randspeed;						// �������

	int		attack_armyindex;				// ����������������������ֻ���ǲ���
	char	attack_type;
	char	defense_type;					// ���ط����1��ҳǳأ�2���� ...
	int		defense_index;					// ���ط����������ط����

	FightUnit attack_unit[FIGHT_UNIT_MAX];	// ��������Ԫ�б�
	FightUnit defense_unit[FIGHT_UNIT_MAX];	// ��������Ԫ�б�

	short attack_unit_num;					// ��������Ԫ����
	short defense_unit_num;					// ��������Ԫ����

	short attack_unit_index;				// ��������ǰ��ս��Ԫ
	short defense_unit_index;				// ��������ǰ��ս��Ԫ

	int attack_total_hp;
	int defense_total_hp;

	int attack_total_maxhp;
	int defense_total_maxhp;

	int attack_total_damage;
	int defense_total_damage;

	char unit_json[8192];	// ��Ԫjson�ַ���
}Fight;

// ��ս�������һ��Ӣ��
int fight_add_hero( int pos, int army_index, char type, int city_index, int index, int kind, short shape, short level, char color, char corps, int attack, int defense, int hp, int troops, short attack_increase, short defense_increase, short assault, short defend, char line, char skillid );

// ս������
int fight_start( int attack_armyindex, char defense_type, int defense_index );

// ս������-��ս
int fight_start_armygroup( int group_index );

// ս������-����ս��
int fight_start_bystory( int actor_index, SLK_NetC_StoryBattle *pValue, int chapter, int rank );

// ս��ÿһ�غ�
int fight_oneturn();

// ʹ�ü���
int fight_useskill( int pos, FightUnit *pUnit, FightUnit *pTargetUnit );

// ��ͨ����
int fight_damage( int pos, FightUnit *pUnit, FightUnit *pTargetUnit );

// ��Ѫ
int fight_changehp( int pos, FightUnit *pTargetUnit, int damage );

// ��һ��Ӣ��
FightUnit *fight_nextptr( int pos );

// ��ȡ˫���ǳ�ָ��
City *fight_getcityptr( int pos );

// ս������
int fight_lost_calc();

// ս����Ϣ
int fight_unit2json();
#endif

