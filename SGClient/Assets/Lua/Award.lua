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
	local color = nil;
	local name = "";
	-- �����
	if awardkind <= AWARDKIND_ITEMBASE then
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		name = T(555)
		
	-- ����
	elseif awardkind <= AWARDKIND_EQUIPBASE then
		sprite = ItemSprite( awardkind );
		color = ItemColorSprite( item_getcolor( awardkind ) );
		name = item_getname( awardkind )
		
	-- װ��
	elseif awardkind <= AWARDKIND_HEROBASE then
		local kind = awardkind-AWARDKIND_EQUIPBASE
		sprite = EquipSprite( kind )
		color = ItemColorSprite( equip_getcolor( kind ) );
		name = EquipName( awardkind )
		
	-- Ӣ��	
	elseif awardkind <= AWARDKIND_BUILDINGBASE then
		local kind = awardkind-AWARDKIND_HEROBASE;
		sprite = HeroHeadSprite( kind )
		color = ItemColorSprite( 0 );
		name = HeroName( kind )
		
	-- ����	
	elseif awardkind <= AWARDKIND_FUNCTION then
		local kind = awardkind-AWARDKIND_BUILDINGBASE;
		sprite = BuildingSprite( awardkind-AWARDKIND_BUILDINGBASE )
		color = ItemColorSprite( 0 );
		name = BuildingName( kind )
		
	elseif awardkind == AWARDKIND_SILVER then -- ����
		sprite = ItemSprite( 120 );
		color = ItemColorSprite( 0 );
		name = T(121)
		
	elseif awardkind == AWARDKIND_WOOD then	-- ľ��
		sprite = ItemSprite( 121 );
		color = ItemColorSprite( 0 );
		name = T(122)
		
	elseif awardkind == AWARDKIND_FOOD then	-- ��ʳ
		sprite = ItemSprite( 122 );
		color = ItemColorSprite( 0 );
		name = T(123)
		
	elseif awardkind == AWARDKIND_IRON then	-- ����
		sprite = ItemSprite( 123 );
		color = ItemColorSprite( 0 );
		name = T(124)
		
	elseif awardkind == AWARDKIND_TOKEN then-- Ԫ��
		sprite = ItemSprite( 124 );
		color = ItemColorSprite( 0 );
		name = T(125)
		
	elseif awardkind == AWARDKIND_BODY then	 -- ����
		sprite = ItemSprite( 126 );
		color = ItemColorSprite( 0 );
		name = T(126)
		
	elseif awardkind == AWARDKIND_INFANTRY then -- ����
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		
	elseif awardkind == AWARDKIND_CAVALRY then -- ���
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		
	elseif awardkind == AWARDKIND_ARCHER then -- ����
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		
	elseif awardkind == AWARDKIND_EXP then	-- ��ɫ����
		sprite = LoadSprite( ItemSprite( 127 ) );
		color = ItemColorSprite( 0 );
		name = T(128)
		
	elseif awardkind == AWARDKIND_VIPEXP then	-- VIP����
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		name = T(190)
		
	elseif awardkind == AWARDKIND_AUTOBUILD	then -- �Զ��������
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		name = T(191)
		
	elseif awardkind == AWARDKIND_LEVYNUM then	 -- ���մ���
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		
	elseif awardkind == AWARDKIND_PEOPLE then	-- �˿�
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		name = T(127)
		
	elseif awardkind == AWARDKIND_PRESTIGE then	-- ����ֵ
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		name = T(152)
		
	elseif awardkind == AWARDKIND_FRIENDSHIP then -- �������
		sprite = LoadSprite( "Char_Default" );
		color = ItemColorSprite( 0 );
		
	end
	
	if sprite == nil then
		sprite = LoadSprite( "Char_Default" );
	end
	if color == nil then
		color = LoadSprite( ItemColorSprite( 0 ) );
	end
	return sprite, color, name;
end

