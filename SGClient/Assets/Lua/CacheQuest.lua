-- ��������
QUEST_DATAINDEX_ACTOR_LEVEL			=1	-- �����ȼ� datatype=1 datakind=0 needvalue=�ȼ�
QUEST_DATAINDEX_BUILDING_LEVEL		=2	-- �����ȼ� datatype=2 datakind=����kind dataoffset=��Դ������� needvalue=�����ȼ�
QUEST_DATAINDEX_BUILDING_SILVER		=3	-- N����ӴﵽN�� datatype=3 datakind=�ȼ� needvalue=��������
QUEST_DATAINDEX_BUILDING_WOOD		=4	-- N��ľ���ﵽN�� datatype=4 datakind=�ȼ� needvalue=��������
QUEST_DATAINDEX_BUILDING_FOOD		=5	-- N��ũ��ﵽN�� datatype=5 datakind=�ȼ� needvalue=��������
QUEST_DATAINDEX_BUILDING_IRON		=6	-- N���󳡴ﵽN�� datatype=6 datakind=�ȼ� needvalue=��������
QUEST_DATAINDEX_LEVYNUM				=7	-- ���մ��� datatype=7 datakind=0 needvalue=����
QUEST_DATAINDEX_HISTORY				=8	-- ���� datatype=8 datakind=������� needvalue=1
QUEST_DATAINDEX_KILLMONSTER			=9	-- ������N�� datatype=9 datakind=0 needvalue=����
QUEST_DATAINDEX_KILLMONSTER_LEVEL	=10	-- ������N��N�� datatype=10 datakind=�ȼ� needvalue=����
QUEST_DATAINDEX_EQUIP_FORGING		=11	-- ����Nװ��N���� datatype=11 datakind=װ��kind needvalue=����
QUEST_DATAINDEX_EQUIP_WASH			=12	-- װ��ϴ������ datatype=12 datakind=0 needvalue=����
QUEST_DATAINDEX_EQUIP_COLORWASH		=13	-- ��NƷ��װ��������ϴ�������� datatype=13 datakind=��ɫ needvalue=1
QUEST_DATAINDEX_TRAIN				=14	-- ļ��N����N���� datatype=14 datakind=���֣�1��2��3�� needvalue=����
QUEST_DATAINDEX_TRAINCOUNT			=15	-- ļ��N�� datatype=15 datakind=0 needvalue=����
QUEST_DATAINDEX_CITY_TECH			=16	-- �о�N�Ƽ�N�� datatype=16 datakind=�Ƽ�ID needvalue=�ȼ�
QUEST_DATAINDEX_CITY_TECHONE		=17	-- �о�һ��N�Ƽ� datatype=17 datakind=�Ƽ�ID needvalue=1
QUEST_DATAINDEX_HERO_WASHCOUNT		=18	-- �佫ϴ��N�� datatype=18 datakind=0 needvalue=����
QUEST_DATAINDEX_HERO_COLORWASH		=19	-- ��һ��NƷ�ʵ��佫����ϴ�� datatype=19 datakind=��ɫ needvalue=1
QUEST_DATAINDEX_HERO_CALL			=20	-- ��ļN���佫 datatype=20 datakind=0 needvalue=����
QUEST_DATAINDEX_WISHING				=21	-- �۱���N�� datatype=21 datakind=0 needvalue=����
QUEST_DATAINDEX_CITYFIGHT			=22	-- �ɹ�����N���й���� datatype=22 datakind=0 needvalue=����
QUEST_DATAINDEX_CREATENAME			=50	-- ��������

-- ���񻺴�
CacheQuest = {};
function CacheQuestClear()
	CacheQuest = {};
end

-- m_count=0,m_list={m_questid=0,m_flag=0,m_datatype=0,m_datakind=0,m_dataoffset=0,m_value=0,m_needvalue=0,m_awardkind={[5]},m_awardnum={[5]},m_nameid=0,[m_count]},
function CacheQuestSet( recvValue )
	CacheQuest = recvValue;
end

-- ��������
function QuestName( type, recvValue )
	local name = "";
	if type == 0 then
		name = name.."["..T(522).."]"
	elseif type == 1 then
		name = name.."["..T(521).."]"
	end
	
	local datatype = recvValue.m_datatype;
	local datakind = recvValue.m_datakind;
	local dataoffset = recvValue.m_dataoffset;
	local value = recvValue.m_value;
	local needvalue = recvValue.m_needvalue;
	if datatype == QUEST_DATAINDEX_ACTOR_LEVEL then-- �����ȼ� datatype=1 datakind=0 needvalue=�ȼ�
		name = name..FQUEST( 1, value );
	elseif datatype == QUEST_DATAINDEX_BUILDING_LEVEL then-- �����ȼ� datatype=2 datakind=����kind dataoffset=��Դ������� needvalue=�����ȼ�
		name = name..FQUEST( 2, F(99, dataoffset+1, BuildingName(datakind) ), needvalue );
	elseif datatype == QUEST_DATAINDEX_BUILDING_SILVER then-- N����ӴﵽN�� datatype=3 datakind=�ȼ� needvalue=��������
		name = name..FQUEST( 3, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_BUILDING_WOOD then-- N��ľ���ﵽN�� datatype=4 datakind=�ȼ� needvalue=��������
		name = name..FQUEST( 4, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_BUILDING_FOOD then-- N��ũ��ﵽN�� datatype=5 datakind=�ȼ� needvalue=��������
		name = name..FQUEST( 5, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_BUILDING_IRON then-- N���󳡴ﵽN�� datatype=6 datakind=�ȼ� needvalue=��������
		name = name..FQUEST( 6, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_LEVYNUM then-- ���մ��� datatype=7 datakind=0 needvalue=����
		name = name..FQUEST( 7, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_HISTORY then-- ���� datatype=8 datakind=������� needvalue=1
		name = name..FQUEST( 8, datakind );
	elseif datatype == QUEST_DATAINDEX_KILLMONSTER then-- ������N�� datatype=9 datakind=0 needvalue=����
		name = name..FQUEST( 9, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_KILLMONSTER_LEVEL then-- ������N��N�� datatype=10 datakind=�ȼ� needvalue=����
		name = name..FQUEST( 10, datakind, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_EQUIP_FORGING then-- ����Nװ��N���� datatype=11 datakind=װ��kind needvalue=����
		name = name..FQUEST( 11, EquipName(datakind), value, needvalue );
	elseif datatype == QUEST_DATAINDEX_EQUIP_WASH then-- װ��ϴ������ datatype=12 datakind=0 needvalue=����
		name = name..FQUEST( 12, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_EQUIP_COLORWASH then-- ��NƷ��װ��������ϴ�������� datatype=13 datakind=��ɫ needvalue=1
		name = name..FQUEST( 13, datakind );
	elseif datatype == QUEST_DATAINDEX_TRAIN then-- ļ��N����N���� datatype=14 datakind=���֣�1��2��3�� needvalue=����
		name = name..FQUEST( 14, CorpsName(datakind-1), value, needvalue );
	elseif datatype == QUEST_DATAINDEX_TRAINCOUNT then-- ļ��N�� datatype=15 datakind=0 needvalue=����
		name = name..FQUEST( 15, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_CITY_TECH then-- �о�N�Ƽ�N�� datatype=16 datakind=�Ƽ�ID needvalue=�ȼ�
		name = name..FQUEST( 16, TechName(datakind), value, needvalue );
	elseif datatype == QUEST_DATAINDEX_CITY_TECHONE	 then-- �о�һ��N�Ƽ� datatype=17 datakind=�Ƽ�ID needvalue=1
		name = name..FQUEST( 17, TechName(datakind) );
	elseif datatype == QUEST_DATAINDEX_HERO_WASHCOUNT then-- �佫ϴ��N�� datatype=18 datakind=0 needvalue=����
		name = name..FQUEST( 18, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_HERO_COLORWASH then-- ��һ��NƷ�ʵ��佫����ϴ�� datatype=19 datakind=��ɫ needvalue=1
		name = name..FQUEST( 19, datakind );
	elseif datatype == QUEST_DATAINDEX_HERO_CALL then-- ��ļN���佫 datatype=20 datakind=0 needvalue=����
		name = name..FQUEST( 20, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_WISHING then	-- �۱���N�� datatype=21 datakind=0 needvalue=����
		name = name..FQUEST( 21, value, needvalue );
	elseif datatype == QUEST_DATAINDEX_CITYFIGHT then-- �ɹ�����N���й���� datatype=22 datakind=0 needvalue=����
		name = name..FQUEST( 22, value, needvalue );
	else
		name = Localization.text_quest( recvValue.m_nameid );
	end
	return name;
end

-- ��ת
function QuestGoto( index )
	if CacheQuest == nil or CacheQuest.m_list[index] == nil then
		return
	end

	local datatype = CacheQuest.m_list[index].m_datatype;
	local datakind = CacheQuest.m_list[index].m_datakind;
	local dataoffset = CacheQuest.m_list[index].m_dataoffset;
	local value = CacheQuest.m_list[index].m_value;
	local needvalue = CacheQuest.m_list[index].m_needvalue;

	if datatype == QUEST_DATAINDEX_ACTOR_LEVEL then
	elseif datatype == QUEST_DATAINDEX_BUILDING_LEVEL then-- �����ȼ� datatype=2 datakind=����kind dataoffset=��Դ������� needvalue=�����ȼ�
		local offset = 0;
		if datakind == BUILDING_Silver then
			offset = dataoffset;
		elseif datakind == BUILDING_Wood then
			offset = dataoffset+16;
		elseif datakind == BUILDING_Food then
			offset = dataoffset+32;
		elseif datakind == BUILDING_Iron then
			offset = dataoffset+48;
		end
		City.Move( datakind, offset, true )
		
	elseif datatype == QUEST_DATAINDEX_BUILDING_SILVER then-- N����ӴﵽN�� datatype=3 datakind=�ȼ� needvalue=��������
		local offset =  GetPlayer():BuildingResMinLevel( BUILDING_Silver );
		if offset >= 0 then
			City.Move( BUILDING_Silver, offset, true )
		end
		
	elseif datatype == QUEST_DATAINDEX_BUILDING_WOOD then-- N��ľ���ﵽN�� datatype=4 datakind=�ȼ� needvalue=��������
		local offset =  GetPlayer():BuildingResMinLevel( BUILDING_Wood );
		if offset >= 0 then
			City.Move( BUILDING_Wood, dataoffset, true )
		end
		
	elseif datatype == QUEST_DATAINDEX_BUILDING_FOOD then-- N��ũ��ﵽN�� datatype=5 datakind=�ȼ� needvalue=��������
		local offset =  GetPlayer():BuildingResMinLevel( BUILDING_Food );
		if offset >= 0 then
			City.Move( BUILDING_Food, dataoffset, true )
		end
		
	elseif datatype == QUEST_DATAINDEX_BUILDING_IRON then-- N���󳡴ﵽN�� datatype=6 datakind=�ȼ� needvalue=��������
		local offset =  GetPlayer():BuildingResMinLevel( BUILDING_Iron );
		if offset >= 0 then
			City.Move( BUILDING_Iron, dataoffset, true )
		end
		
	elseif datatype == QUEST_DATAINDEX_LEVYNUM then-- ���մ��� datatype=7 datakind=0 needvalue=����
		
	end
end
