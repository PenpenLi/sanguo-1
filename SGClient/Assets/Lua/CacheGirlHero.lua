-- һ��Ӣ�۽ṹ
Auxiliary_Hero = class("Auxiliary_Hero")
function Auxiliary_Hero:ctor()
	auxiliary:empty();
end

function Auxiliary_Hero:empty()
	
	auxiliary.m_id          =   0;-- Ů��Id
	auxiliary.m_quality		=	0;-- Ʒ��
	auxiliary.m_exp			=	0;-- ���ܶ�
	auxiliary.m_exp_max		=	0;-- ���ܶ�����
	auxiliary.m_state		=	0;-- ��ǰ״̬
	auxiliary.m_break		=	0;-- ͻ��
	
	auxiliary.m_attack_increase 	= 	0;-- ǿ��
	auxiliary.m_defense_increase	=	0;-- ǿ��
	auxiliary.m_base        =   0;--��������
	
	auxiliary.m_bIsNew = false;
	return auxiliary;
end

function Auxiliary_Hero:Set( recvValue )
	auxiliary.m_id  		= 	recvValue.m_id;-- Ů��Id
	auxiliary.m_quality		=	recvValue.m_quality;-- Ʒ��
	auxiliary.m_exp			=	recvValue.m_exp;-- ���ܶ�(Dictionary)
	auxiliary.m_exp_max		=	recvValue.m_exp_max;-- ���ܶ�����
	auxiliary.m_state		=	recvValue.m_state;-- ��ǰ״̬
	auxiliary.m_break		=	recvValue.m_break;-- ͻ��
	
	auxiliary.m_attack_increase 	= 	recvValue.m_attack_increase;-- ǿ��
	auxiliary.m_defense_increase	=	recvValue.m_defense_increase;-- ǿ��
	auxiliary.m_base        =   recvValue.m_base;--��������
end

local GirlHero = class("GirlHero")
function GirlHero:ctor()
	auxiliary:ResetAll();
end

-- ��ջ���
function GirlHero:ResetAll()
	-- ����Ӣ���б�
	
	-- Ӣ���б�
	
end

function GirlHero:ResetCityHero( beginoffset, endoffset )
	-- ����Ӣ���б�
	
end

function GirlHero:ResetHero()
	-- Ӣ���б�
	
end

-- ���ñ���Ӣ��
function GirlHero:SetHero( nIndex, pHero )
	
end

-- �Ƿ����Ӣ��
function GirlHero:HasGirlHero( nIndex )
	
end

function GirlHero:GetIndex( id )
	
end

function GirlHero:GetPtr( id )
	
end

-- ������е�New��ʾ
function GirlHero:ClearAllNew()
	
end

-- ȫ��
local G_GirlHero = nil;
function GetGirlHero()
	if G_GirlHero == nil then
		G_GirlHero = GirlHero.new();
	end
	return G_GirlHero;
end