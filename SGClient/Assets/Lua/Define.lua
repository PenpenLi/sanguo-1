---------------------- UI�¼� ----------------------
UI_EVENT_CLICK 			    = 0;		-- UIButton����				�޲�
UI_EVENT_PRESS 			    = 1;		-- UIButton����				0 ���£�1 ̧��
UI_EVENT_INPUTSUBMIT	    = 2;		-- UIInputField�ύ			�޲�
UI_EVENT_TWEENFINISH	    = 3;		-- UITween�������			0 ���������1 ����
UI_EVENT_SCROLLDRAG		    = 4;		-- UIScrollRect�϶�			0 ��ʼ�϶���1 �϶��У�2 �����϶�
UI_EVENT_SLIDERVALUECHANGE  = 5;		-- UISliderֵ�ı�			slider valueֵ
UI_EVENT_CENTERCHILD	    = 6;		-- UIScrollRing�Ӿ���		��index
UI_EVENT_TIMECOUNTEND       = 7;        -- UITextTimeCountdown      ��ʱ����
UI_EVENT_DRAGSENSOR         = 8;        -- UIDragSensor��ק�¼�
UI_EVENT_RICHTEXTSETEND     = 9;        -- UIRcihText��ǵ��
UI_EVENT_RICHTEXTMASKCLICK  = 10;       -- UIRcihText��ǵ��
UI_EVENT_INPUTVALUECHANGED  = 11;       -- UIInputField�����޸�		��ǰinputfield����
UI_EVENT_TIMECOUNTCHANGED   = 12;       -- �����޸�
UI_EVENT_VOICE              = 13;       -- UIVoice
UI_EVENT_UIDRAG             = 14;       -- UIDRAG�¼�            0 ��ʼ�϶���1 �����϶�
UI_EVENT_UIDROP             = 15;       -- UIDROP�¼�			dragger ID
UI_EVENT_INPUTSUBMITEX      = 16;		-- UIInputField�ύ		�޲�
UI_EVENT_TOGGLEVALUECHANGE	= 17;
UI_EVENT_PUSHEVENT		    = 1000;		-- UIͨ���¼������붨�����¼�����			    ����

-- ����������ͨ����
BUILDING_Main           = 1  -- ����
BUILDING_Wall           = 2  -- ��ǽ
BUILDING_StoreHouse     = 3  -- �ֿ�
BUILDING_Tech           = 4  -- ̫ѧԺ
BUILDING_Craftsman      = 5  -- ��������
BUILDING_Cabinet        = 6  -- �ڸ�

-- ��Ӫ
BUILDING_Infantry       		= 11  -- ����Ӫ
BUILDING_Cavalry        		= 12  -- ���Ӫ
BUILDING_Archer         		= 13  -- ����Ӫ
BUILDING_Militiaman_Infantry	= 14  -- ���Ӫ-����
BUILDING_Militiaman_Cavalry		= 15  -- ���Ӫ-���
BUILDING_Militiaman_Archer		= 16  -- ���Ӫ-����

-- ��Դ����
BUILDING_Silver		    =  21	-- ����
BUILDING_Wood		    =  22	-- ľ��
BUILDING_Food		    =  23	-- ʳ��
BUILDING_Iron		    =  24   -- ����

-- ����ڽ���
BUILDING_Smithy		    =  31	-- ������
BUILDING_Wash		    =  32	-- ϴ����
BUILDING_Fangshi	    =  33	-- ����
BUILDING_Shop		    =  34	-- �̵�
BUILDING_Hero		    =  35	-- ���͹�
BUILDING_Wishing	    =  36	-- �۱���
BUILDING_Help		    =  37	-- ����

-- �������
CITY_FUNCTION_SMITHY		=0	-- ������
CITY_FUNCTION_WASH			=1	-- ϴ����
CITY_FUNCTION_FANGSHI		=2	-- ����
CITY_FUNCTION_SHOP			=3	-- �̵�
CITY_FUNCTION_HERO			=4	-- ���͹�
CITY_FUNCTION_WISHING		=5	-- �۱���
CITY_FUNCTION_NATION		=10	-- ����
CITY_FUNCTION_WORLD			=11	-- ����
CITY_FUNCTION_STORY			=12	-- ����
CITY_FUNCTION_MAIL			=13	-- �ʼ�
CITY_FUNCTION_FRIEND		=14	-- ����
CITY_FUNCTION_NATIONEQUIP	=15	-- ����
CITY_FUNCTION_RANK			=16	-- ���а�
CITY_FUNCTION_AUTOBUILD		=17	-- �Զ�����
CITY_FUNCTION_CHAT			=18	-- ����
CITY_FUNCTION_WARKEREX		=19	-- ��ҵ�����

BuildingPrefab={
[BUILDING_Main] = { prefab = "BUILDING_Main", land="BuildingLand0" },
[BUILDING_Wall] = { prefab = "BUILDING_Wall", land="BuildingLand1" },
[BUILDING_StoreHouse] = { prefab = "BUILDING_StoreHouse", land="BuildingLand2" },
[BUILDING_Tech] = { prefab = "BUILDING_Tech", land="BuildingLand3" },
[BUILDING_Craftsman] = { prefab = "BUILDING_Craftsman", land="BuildingLand4" },
[BUILDING_Cabinet] = { prefab = "BUILDING_Cabinet", land="BuildingLand5" },
[BUILDING_Infantry] = { prefab = "BUILDING_Infantry", land="BuildingLand6" },
[BUILDING_Cavalry] = { prefab = "BUILDING_Cavalry", land="BuildingLand7" },
[BUILDING_Archer] = { prefab = "BUILDING_Archer", land="BuildingLand8" },
[BUILDING_Militiaman_Infantry] = { prefab = "BUILDING_Militiaman_Infantry", land="BuildingLand9" },
[BUILDING_Militiaman_Cavalry] = { prefab = "BUILDING_Militiaman_Cavalry", land="BuildingLand9" },
[BUILDING_Militiaman_Archer] = { prefab = "BUILDING_Militiaman_Archer", land="BuildingLand9" },
[BUILDING_Silver] = { prefab = "BUILDING_Silver", land="ResLand" },
[BUILDING_Wood] = { prefab = "BUILDING_Wood", land="ResLand" },
[BUILDING_Food] = { prefab = "BUILDING_Food", land="ResLand" },
[BUILDING_Iron] = { prefab = "BUILDING_Iron", land="ResLand" },
[BUILDING_Smithy] = { prefab = "BUILDING_Smithy", land="BuildingLand12" },
[BUILDING_Wash] = { prefab = "BUILDING_Wash", land="BuildingLand13" },
[BUILDING_Fangshi] = { prefab = "BUILDING_Fangshi", land="BuildingLand14" },
[BUILDING_Shop] = { prefab = "BUILDING_Shop", land="BuildingLand15" },
[BUILDING_Hero] = { prefab = "BUILDING_Hero", land="BuildingLand16" },
[BUILDING_Wishing] = { prefab = "BUILDING_Wishing", land="BuildingLand17" },
[BUILDING_Help] = { prefab = "BUILDING_Help", land="BuildingLand18" },
} 
--[[
	if kind == BUILDING_Main then
	elseif kind == BUILDING_Wall then
	elseif kind == BUILDING_StoreHouse then
	elseif kind == BUILDING_Tech then
	elseif kind == BUILDING_Craftsman then
	elseif kind == BUILDING_Cabinet then
	elseif kind == BUILDING_Infantry then
	elseif kind == BUILDING_Cavalry then
	elseif kind == BUILDING_Archer then
	elseif kind == BUILDING_Militiaman_Infantry then
	elseif kind == BUILDING_Militiaman_Cavalry then
	elseif kind == BUILDING_Militiaman_Archer then
	elseif kind == BUILDING_Silver then
	elseif kind == BUILDING_Wood then
	elseif kind == BUILDING_Food then
	elseif kind == BUILDING_Iron then
	elseif kind == BUILDING_Smithy then
	elseif kind == BUILDING_Wash then
	elseif kind == BUILDING_Fangshi then
	elseif kind == BUILDING_Shop then
	elseif kind == BUILDING_Hero then
	elseif kind == BUILDING_Wishing then
	elseif kind == BUILDING_Help then
	end
--]]
-- ;��
PATH_SYSTEM						=	1	-- ϵͳ
PATH_GM							=	2	-- GM
PATH_PAY						=	3	-- ��ֵ
PATH_ITEMUSE					=	4	-- ����ʹ��
PATH_TOKENITEMUSE				=	5	-- ��ʯֱ��ʹ��
PATH_SELL						=	6	-- ��������
PATH_BUILDING_UPGRADE			=	7	-- ����
PATH_QUEST						=	8	-- ����
PATH_GUARD_UPGRADE				=	9	-- ��������
PATH_LEVY						=	10	-- ����
PATH_TRAIN						=	11	-- ѵ��
PATH_RESOLVE					=	12	-- �ֽ�
PATH_EQUIPEXT					=	13	-- ����װ������
PATH_TECH_UPGRADE				=	14	-- �Ƽ�����
PATH_TECH_FINISH				=	15	-- �Ƽ����
PATH_TECH_GET					=	16	-- �Ƽ���ȡ
PATH_TECH_QUICK					=	17	-- �Ƽ�����
PATH_TECH_FREEQUICK				=	18	-- �Ƽ���Ѽ���
PATH_HIRE_FORGING				=	19	-- ��Ӷ
PATH_HIRE_GOV					=	20	-- ��Ӷ
PATH_HIRE_TECH					=	21	-- ��Ӷ
PATH_BUILDING_WORKER			=	22	-- ���ý������
PATH_TRAIN_QUEUE				=	23	-- ��ļ����
PATH_TRAIN_LONG					=	24	-- ѵ��ʱ��
PATH_TRAIN_GET					=	25	-- ѵ����ȡ
PATH_TRAIN_CANCEL				=	26	-- ȡ����ļ
PATH_EQUIP_FORGING				=	27	-- װ������
PATH_FORGING_QUICK				=	28	-- �������
PATH_FORGING_FREEQUICK			=	29	-- ��������
PATH_BODYBUY					=	30	-- ��������
PATH_CHANGENAME					=	31	-- ����
PATH_GUARD_LIFE					=	32	-- ������Ѫ
PATH_EQUIP_UP					=	33	-- װ����
PATH_EQUIP_DOWN					=	34	-- װ����
PATH_HERO_ADDEXP				=	35	-- ��Ӣ�۾���
PATH_HERO_ADDSOLDIERS			=	36	-- ����
PATH_HERO_SOLDIERS_EQUIP		=	37	-- ��жװ�������ı�����ʧ
PATH_HERO_WASH					=	38	-- Ӣ��ϴ��
PATH_EQUIP_WASH					=	39	-- װ��ϴ��
PATH_MATERIALMAKE_QUEUE			=	40	-- �����������
PATH_MATERIALMAKE				=	41	-- ��������

-- ���ֱ�
-- ��ȡ���ػ�����
function GetLocalizeText( id )
    if id == nil then
        return "";
    end
	return Localization.text( id );
end
function T( nameid )
    return GetLocalizeText( nameid );
end
function zh( text )
    return text;
end

function F( nameid, ... )
	return Utils.StringFormat( Localization.text( nameid ), ... );
end

function FQUEST( nameid, ... )
	return Utils.StringFormat( Localization.text_quest( nameid ), ... );
end

function Hex2Color( hex )
	return Utils.HexColor( hex )
end

function Hex2Color32( hex )
	return Utils.HexColor32( hex )
end

function zhtime( second )
	
	local day = math.floor( second / 86400 );
	local hour = math.floor(second / 3600) % 24;
	local min = math.floor(second / 60) % 60;
	local sec = math.floor(second % 60);
	local szmsg = "";
	if day > 0 then
        szmsg = day..T(156)
        if hour > 0 then
            szmsg = szmsg..hour..T(155)
            if min > 0 then
                szmsg = szmsg..min..T(154)
            end
        end
		return szmsg
    end
	
	if hour > 0 then
        szmsg = szmsg..hour..T(155)
        if min > 0 then
            szmsg = szmsg..min..T(154)
        end
		if sec > 0 then
            szmsg = szmsg..sec..T(153)
        end
		return szmsg
    end
	
	if min > 0 then
        szmsg = szmsg..min..T(154)
		if sec > 0 then
            szmsg = szmsg..sec..T(153)
        end
		return szmsg
    end
       
    return sec..T(153)
end

-- дgamelog
function gamelog( msg )
	LogUtil.GetInstance():WriteGame( msg );
end

-- дnetlog
function netlog( msg )
	LogUtil.GetInstance():WriteNet( msg );
end

-- ��ʱִ��
function Invoke(func, delay, param, name)
    if param == nil then
        param = 0;
    end
    if name == nil then
        name = "";
    end
    eye.gameManager.delayExecute = func;
    eye.gameManager:GameInvoke(delay, param, name);
end

-- ֹͣ��ʱִ��
function InvokeStop(name)
    eye.gameManager:GameInvoke_Stop(name);
end

-- ��ȡ��������
function Nation( nation )
	return T(nation+100);
end

function NationEx( nation )
	return T(nation+110);
end

-- ��ȡ��������
function BuildingName( kind, offset )
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron and offset ~= nil then
		return F( 99, offset+1, T( kind ) )
	else
		return T(kind);
	end
end

-- ��ȡ�������ƴ��ȼ�
function BuildingNameLv( kind, offset, level )
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron and offset ~= nil then
		return "Lv."..level.." "..F( 99, offset+1, T( kind ) )
	else
		return "Lv."..level.." "..T(kind);
	end
end

-- ��ȡӢ������
function HeroName( kind )
	return Localization.text_item(kind+3000);
end

-- ��ȡӢ�����ƴ��ȼ�
function HeroNameLv( kind, level )
	return "Lv."..level.." "..HeroName( kind );
end

-- Ӣ��״̬����
function HeroState( state )
	if state == 0 then
		return T(141);
	elseif state == 1 then
		return T(142);
	end
end

-- ��������
function CorpsName( corps )
	return T(134+corps);
end

-- ��������
function CorpsNameEx( buildingkind )
	local corps = 0;
	if buildingkind == BUILDING_Infantry or buildingkind == BUILDING_Militiaman_Infantry then
		corps = 0
	elseif buildingkind == BUILDING_Cavalry or buildingkind == BUILDING_Militiaman_Cavalry then
		corps = 1
	elseif buildingkind == BUILDING_Archer or buildingkind == BUILDING_Militiaman_Archer then
		corps = 2
	end
	return CorpsName( corps );
end

-- ��ȡװ������
function EquipName( kind )
	return Localization.text_item(kind+2000);
end

-- ��ȡ�Ƽ�����
function TechName( kind )
	return Localization.text_item(kind+4000);
end

-- ��ȡ�Ƽ�����
function TechDesc( kind )
	return Localization.text_item(kind+4100);
end

-- ��ȡ�Ƽ�����
function TechDescUp( kind )
	return Localization.text_item(kind+4200);
end

-- ��ȡ�Ƽ�����
function ResName( restype )
	return T(120+restype)
end

-- ��ȡ��ͼ��������
function MapZoneName( id )
	return Localization.text_item(14000+id);
end

-- ��ȡ��ͼ�ǳ�����
function MapTownName( id )
	return Localization.text_item(14100+id);
end

-- ������ɫ
function NameColor( color )
	local c = { 0xf7f3bbff, 0x25c9ffff, 0x03de27ff, 0xffde00ff, 0xe80017ff, 0xd95df4ff, 0x9b8869ff, 0x9b8869ff, 0x9b8869ff, 0x9b8869ff }
	return Hex2Color( c[color+1] )
end

-- ��ɫ����
function ColorName( color )
	return T( 157+color )
end

-- ��������ӽڵ�
function clearChild( object )
	--for i = 0 ,object.transform.childCount - 1 do
       -- GameObject.Destroy( object.transform:GetChild(i).gameObject );
    --end
	Utils.ClearChild( object.transform );
end


-- ��ӽڵ�
function addChild( object, prefab )
	local obj = GameObject.Instantiate( prefab );
	obj.transform:SetParent( object.transform );
	obj.transform.localPosition = Vector3.zero;
	obj.transform.localScale = Vector3.one;
	obj.gameObject:SetActive( true );
	return obj;
end

-- ��ӽڵ�
function addObj( object, prefab )
	local obj = GameObject.Instantiate( prefab );
	obj.transform:SetParent( object.transform );
	obj.transform.position = object.transform.position;
	obj.transform.localScale = Vector3.one;
	return obj;
end

function SetParent( obj, parent )
	obj.transform:SetParent( parent.transform );
	obj.transform.localPosition = Vector3.zero;
	obj.transform.localScale = Vector3.one;
	obj.gameObject:SetActive( true )
end

function SetImage( transform, sprite )
	transform:GetComponent( typeof(Image) ).sprite = sprite;
end

function SetText( transform, text, color )
	local uiComponent = transform:GetComponent( typeof(UIText) );
	uiComponent.text = text;
	if color ~= nil then
		uiComponent.color = color;
	end
end

function SetLevel( transform, level, color )
	SetText( transform, "Lv."..level, color )
end

function SetTextColor( transform, color )
	transform:GetComponent( typeof(UIText) ).color = color;
end

function SetRichText( transform, text )
	transform:GetComponent( typeof(YlyRichText) ).text = text;
end

function SetControlID( transform, controlID )
	transform:GetComponent( typeof(UIButton) ).controlID = controlID;
end

function SetTimer( transform, sec, needsec, controlID, formatText )
	local timer = transform:GetComponent( typeof(UITextTimeCountdown) )
    timer:SetTime( needsec, needsec-sec );
	if sec == 0 and needsec == 0 then
		timer:Stop()
	end
	if controlID ~= nil then
		timer.controlID = controlID;
	end
	if formatText ~= nil then
		timer.formatText = formatText;
	end
end

function SetProgress( transform, value )
	transform:GetComponent( typeof(UIProgress) ):SetValue(value);
end

function SetSlider( transform, value )
	transform:GetComponent( typeof(UISlider) ).value = value;
end

function SetTrue( transform )
	transform.gameObject:SetActive( true )
end

function SetFalse( transform )
	transform.gameObject:SetActive( false )
end

function SetShow( transform, active )
	transform.gameObject:SetActive( active )
end

function IsActive( transform )
	return transform.gameObject.activeSelf
end

function SetGray( transform, gray )
	if gray == true then
		transform:GetComponent( typeof(Image) ).material = ResourceManager.LoadMaterial( "UI_Mat_SpriteGray" );
	else
		transform:GetComponent( typeof(Image) ).material = nil;
	end
end

