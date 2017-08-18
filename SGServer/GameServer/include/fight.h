#ifndef _FIGHT_H_
#define _FIGHT_H_

#define FIGHT_HERO_MAX		256	// ս��˫��Ӣ�������ܺ�
#define FIGHT_TURNS_MAX		8192
#define FIGHT_INT			100
#define FIGHT_FLOAT			100.0f

#define FIGHT_WIN			1	
#define FIGHT_LOSE			2

#define FIGHT_ATTACK		1	
#define FIGHT_DEFENSE		2

#define FIGHTTYPE_STORY		1 // ����ս��

// һ��ս����Ԫ
typedef struct _fighthero
{
	char	type;				// Ӣ��������1���ӣ�2�̶����ض���
	int		index;				// ��������
	short	offset;				

	short	herokind;			// Ӣ������
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
}FightHero;

// ս���ṹ
typedef struct _fight
{
	char	type;							// ս������
	char	result;							// ս�����
	int		turns;							// ��ǰ�غ�
	int		randspeed;						// �������

	int		attack_armyindex;				// ����������������������ֻ���ǲ���
	char	defense_type;					// ���ط����1��ҳǳأ�2���� ...
	int		defense_index;					// ���ط����������ط����

	FightHero attack_hero[FIGHT_HERO_MAX];	// ����������Ӣ��
	FightHero defense_hero[FIGHT_HERO_MAX];	// ����������Ӣ��

	short attack_hero_num;					// ������Ӣ������
	short defense_hero_num;					// ������Ӣ������

	short attack_hero_index;				// ��������ǰ��սӢ��
	short defense_hero_index;				// ��������ǰ��սӢ��

	int attack_total_hp;
	int defense_total_hp;

	int attack_total_maxhp;
	int defense_total_maxhp;

	int attack_total_damage;
	int defense_total_damage;
}Fight;

// ��ս�������һ��Ӣ��
int fight_add_hero( int pos, char type, int index, short herokind, short level, char color, char corps, int attack, int defense, int hp, int troops, short attack_increase, short defense_increase, short assault, short defend, char line, char skillid );

// ս������
int fight_start( int attack_armyindex, char defense_type, int defense_index );

// ս������-����ս��
int fight_start_bystory( int actor_index, SLK_NetC_StoryBattle *pValue, int chapter, int rank );

// ս��ÿһ�غ�
int fight_oneturn();

// ʹ�ü���
int fight_useskill( int pos, FightHero *pHero, FightHero *pTargetHero );

// ��ͨ����
int fight_damage( int pos, FightHero *pHero, FightHero *pTargetHero );

// ��Ѫ
int fight_changehp( int pos, FightHero *pTargetHero, int damage );

// ��һ��Ӣ��
FightHero *fight_nextptr( int pos );

#endif

