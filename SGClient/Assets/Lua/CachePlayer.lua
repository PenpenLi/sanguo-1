--  ��ɫ������Ϣ
local Player = class("Player");
function Player:ctor()
	self:Init();
end
function Player:Init()
	self.m_usertype			=	0;	-- �û�����
	self.m_createtime		=	0;	-- ����ʱ��
	self.m_config		    =   {};  --������Ϣ
	
	self.m_actorid			=	0;	-- ��ɫ���
	self.m_name				=	"";	-- ��ɫ����
	self.m_nation			=	0;
	self.m_shape			=	0;
	self.m_level			=	0;
	self.m_exp				=	0;
	self.m_exp_max			=	0;
	self.m_token			=	0;
	self.m_viplevel			=	0;
	self.m_vipexp			=	0;
	self.m_vipexp_max		=	0;
	self.m_body				=	0;
	self.m_place			=	0;
	self.m_official			=	0;
	self.m_zone				=	0;
	self.m_battlepower		=	0;
	self.m_silver			=	0;
	self.m_wood				=	0;
	self.m_food				=	0;
	self.m_iron				=	0;
	self.m_infantry_num		=	0;
	self.m_cavalry_num		=	0;
	self.m_archer_num		=	0;
	self.m_mokilllv			=	0;
	self.m_sflag			=	0;
	
	self.m_levynum			=	0;
	self.m_worker_kind		=	0;
	self.m_worker_offset	=	0;
	self.m_worker_sec		=	0;
	self.m_worker_needsec   =	0;
	self.m_worker_kind_ex	=	0;
	self.m_worker_offset_ex	=	0;
	self.m_worker_sec_ex	=	0;
	self.m_worker_needsec_ex=	0;
	self.m_worker_expire_ex	=	0;
	self.m_buildings 		=	{};
	self.m_buildings_res 	=	{};
end

-- ���Ա仯
function Player:Set( recvValue )
	self.m_actorid			=	recvValue.m_actorid;
	self.m_name				=	recvValue.m_name;
	self.m_nation			=	recvValue.m_nation;
	self.m_shape			=	recvValue.m_shape;
	self.m_level			=	recvValue.m_level;
	self.m_exp				=	recvValue.m_exp;
	self.m_exp_max			=	recvValue.m_exp_max;
	self.m_token			=	recvValue.m_token;
	self.m_viplevel			=	recvValue.m_viplevel;
	self.m_vipexp			=	recvValue.m_vipexp;
	self.m_vipexp_max		=	recvValue.m_vipexp_max;
	self.m_body				=	recvValue.m_body;
	self.m_place			=	recvValue.m_place;
	self.m_official			=	recvValue.m_official;
	self.m_zone				=	recvValue.m_zone;
	self.m_battlepower		=	recvValue.m_battlepower;
	self.m_silver			=	recvValue.m_silver;
	self.m_wood				=	recvValue.m_wood;
	self.m_food				=	recvValue.m_food;
	self.m_iron				=	recvValue.m_iron;
	self.m_infantry_num		=	recvValue.m_infantry_num;
	self.m_cavalry_num		=	recvValue.m_cavalry_num;
	self.m_archer_num		=	recvValue.m_archer_num;
	self.m_mokilllv			=	recvValue.m_mokilllv;
	self.m_sflag			=	recvValue.m_sflag;
end

-- 
function Player:SetBuilding( kind, info, active )
	self.m_buildings[kind] = info;
	--
	local unitObj = City.BuildingAdd( info, active );
	
	City.BuildingSetOver( kind );
	return unitObj;
end

function Player:SetBuildingRes( kind, offset, info, active )
	if self.m_buildings_res[kind] == nil then
		self.m_buildings_res[kind] = {};
	end
	self.m_buildings_res[kind][offset] = info;
	--
	local unitObj = City.BuildingAdd( info, active );
	return unitObj;
end

function Player:SetBuildingWorker( recvValue )
	self.m_worker_kind		=	recvValue.m_worker_kind;
	self.m_worker_offset	=	recvValue.m_worker_offset;
	self.m_worker_sec		=	recvValue.m_worker_sec;
	self.m_worker_needsec   =	recvValue.m_worker_needsec;
	self.m_worker_kind_ex	=	recvValue.m_worker_kind_ex;
	self.m_worker_offset_ex	=	recvValue.m_worker_offset_ex;
	self.m_worker_sec_ex	=	recvValue.m_worker_sec_ex;
	self.m_worker_needsec_ex=	recvValue.m_worker_needsec_ex;
	self.m_worker_expire_ex	=	recvValue.m_worker_expire_ex;
end

function Player:SetBuildingLevy( levynum )
	local old 				= 	self.m_levynum;
	self.m_levynum			=	levynum;
	
	--
	if old > levynum then
		local changenum = old - levynum;
		for i=1, changenum, 1 do
			City.BuildingSubLevy();
		end
	else
		local changenum = levynum - old;
		for i=1, changenum, 1 do
			City.BuildingAddLevy();
		end
	end
end

-- ȫ��
G_Player = nil;
function GetPlayer()
	if G_Player == nil then
		G_Player = Player.new();
	end
	return G_Player;
end
