ACTOR_GIRL_MAX = 80

-- һ��Ӣ�۽ṹ
SLK_Girl = class("SLK_Girl")
function SLK_Girl:ctor()
	self:empty();
end

function SLK_Girl:empty()
	self.m_kind  		= 	0;-- ����
	self.m_color		=	0;-- ��ɫ
	self.m_sflag		=	0;-- ���
	self.m_soul			=	0;-- ��ǰ��Ƭ
	self.m_love_exp		=	0;-- ���ܶ�
	self.m_love_level	=	0;-- ���ܵȼ�
	self.m_love_today	=	0;-- �����Ƿ����ܹ�
	self.m_herokind		=	0;-- �������佫
	return self;
end

function SLK_Girl:Set( recvValue )
	self.m_kind  		= 	recvValue.m_kind;-- ����
	self.m_color		=	recvValue.m_color;-- ��ɫ
	self.m_sflag		=	recvValue.m_sflag;-- ���
	self.m_soul			=	recvValue.m_soul;-- ��ǰ��Ƭ
	self.m_love_exp		=	recvValue.m_love_exp;-- ��ǰ���ܶ�
	self.m_love_level	=	recvValue.m_love_level;-- ���ܵȼ�
	self.m_love_today	=	recvValue.m_love_today;-- �����ȡ���ܶ�
	self.m_love_today_max	=	recvValue.m_love_today_max;-- �������ܶ�����
	self.m_herokind		=	recvValue.m_herokind;-- �������佫
end

-- Ů�����ֿͻ��˻���
local Girl = class("Girl")
function Girl:ctor()
	self:ResetAll();
end

-- ��ջ���
function Girl:ResetAll()
	-- Ů���б�
	self.m_Girl = {};
	for i=1,ACTOR_GIRL_MAX,1 do
		self.m_Girl[i] = SLK_Girl.new();
	end
end

-- ����Ů��
function Girl:SetGirl( nKind, pGirl )
	if pGirl ~= nil then
		self.m_Girl[nKind] = clone(pGirl); -- ����ط��Ƿ�Ҫ�õ����
	else
		self.m_Girl[nKind]:empty(); -- ������Ů��
	end
end

-- �Ƿ�������Ů��
function Girl:HasGirl( nKind )
	if nKind <= 0 or nKind >= ACTOR_GIRL_MAX then
		return false;
	end
	if self.m_Girl[nKind].m_kind <= 0 then
		return false;
	end
	return true;
end

-- ����kind��ȡ
function Girl:GetPtr( nKind )
	if nKind <= 0 or nKind >= ACTOR_GIRL_MAX then
		return nil;
	end
	return self.m_Girl[nKind]
end

-- ȫ��
local G_Girl = nil;
function GetGirl()
	if G_Girl == nil then
		G_Girl = Girl.new();
	end
	return G_Girl;
end

function girlconfig( kind, color )
	if g_girlinfo[kind] == nil then
		return nil;
	end
	return g_girlinfo[kind][color]
end