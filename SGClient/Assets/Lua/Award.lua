--
AWARDKIND_ITEMBASE		=	0	  -- ���ߣ�0+���߱�ţ�
AWARDKIND_EQUIPBASE		=	10000 -- װ����10000+װ����ţ�
AWARDKIND_HEROBASE		=	20000 -- Ӣ�ۣ�20000+Ӣ�۱�ţ�
AWARDKIND_BUILDINGBASE	=	30000 -- ������30000+������ţ�
AWARDKIND_FUNCTION		=	40000 -- ���ܣ�40000+���ܱ�ţ�
AWARDKIND_VALUEBASE		=	50000 -- ��ֵ
AWARDKIND_SILVER		=	50001 -- ����
AWARDKIND_WOOD			=	50002 -- ľ��
AWARDKIND_FOOD			=	50003 -- ��ʳ
AWARDKIND_IRON			=	50004 -- ����
AWARDKIND_TOKEN			=	50005 -- Ԫ��
AWARDKIND_BODY			=	50006 -- ����
AWARDKIND_INFANTRY		=	50007 -- ����
AWARDKIND_CAVALRY		=	50008 -- ���
AWARDKIND_ARCHER		=	50009 -- ����
AWARDKIND_EXP			=	50010 -- ��ɫ����
AWARDKIND_VIPEXP		=	50011 -- VIP����
AWARDKIND_AUTOBUILD		=	50012 -- �Զ��������
AWARDKIND_LEVYNUM		=	50013 -- ���մ���
AWARDKIND_PEOPLE		=	50014 -- �˿�
AWARDKIND_PRESTIGE		=	50015 -- ����ֵ
AWARDKIND_FRIENDSHIP	=	50016 -- �������


-- ��������
function AwardInfo( awardkind )
	local sprite = nil;
	local name = "";
	-- �����
	if awardkind <= AWARDKIND_ITEMBASE then
		sprite = LoadSprite( "Char_Default" );
	
	-- ����
	elseif awardkind <= AWARDKIND_EQUIPBASE then
		sprite = ItemSprite( awardkind );
		
	-- װ��
	elseif awardkind <= AWARDKIND_HEROBASE then
		sprite = EquipSprite( awardkind-AWARDKIND_EQUIPBASE ), T()
		
	-- Ӣ��	
	elseif awardkind <= AWARDKIND_BUILDINGBASE then
		sprite = HeroHeadSprite( awardkind-AWARDKIND_HEROBASE )
	
	-- ����	
	elseif awardkind <= AWARDKIND_FUNCTION then
		sprite = BuildingSprite( awardkind-AWARDKIND_BUILDINGBASE )
		
	elseif awardkind == AWARDKIND_SILVER then -- ����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_WOOD then	-- ľ��
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_FOOD then	-- ��ʳ
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_IRON then	-- ����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_TOKEN then-- Ԫ��
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_BODY then	 -- ����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_INFANTRY then -- ����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_CAVALRY then -- ���
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_ARCHER then -- ����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_EXP then	-- ��ɫ����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_VIPEXP then	-- VIP����
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_AUTOBUILD	then -- �Զ��������
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_LEVYNUM then	 -- ���մ���
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_PEOPLE then	-- �˿�
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_PRESTIGE then	-- ����ֵ
		sprite = LoadSprite( "Char_Default" );
	elseif awardkind == AWARDKIND_FRIENDSHIP then -- �������
		sprite = LoadSprite( "Char_Default" );
	end
	
	if sprite == nil then
		sprite = LoadSprite( "Char_Default" );
	end
	return sprite, name;
end

