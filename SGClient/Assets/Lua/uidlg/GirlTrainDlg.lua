-- ����
local m_Dlg = nil;
local m_DialogFrameMod = nil;

local m_uiHeroPageL = nil;
local m_uiHeroPageR = nil;
local m_uiUIP_HeroHead = nil;
local m_uiContent = nil;
local m_uiIntimacy = nil;
local m_uiHeroChild = nil;
local m_uiAddDesc = nil;
local m_uiText = nil;
local m_uiNextBtn = nil;
local m_uiAddBtn = nil;
local m_uiChildNextBtn = nil;
local m_uiTitle = nil;
local m_uiUIP_ChildHead = nil;
local m_uiLeftHero = nil;
local m_uiRightHero = nil;
local m_uiBreakBtn = nil;

local m_ObjectPool = nil;


-- �򿪽���
function GirlTrainDlgOpen()
	m_Dlg = eye.uiManager:Open( "GirlTrainDlg" );
	m_DialogFrameMod = DialogFrameModOpen( m_Dlg, T(34), HELP_GirltrainDlg, GirlTrainDlgClose );
end

-- ���ؽ���
function GirlTrainDlgClose()
	if m_Dlg == nil then
		return;
	end
	DialogFrameModClose( m_DialogFrameMod );
	m_DialogFrameMod = nil;
	eye.uiManager:Close( "GirlTrainDlg" );
end

-- ɾ������
function GirlTrainDestroy()
	GameObject.Destroy( m_Dlg );
	m_Dlg = nil;
end

----------------------------------------
-- �¼�
----------------------------------------

-- ������ť���ʱ����
function GirlTrainDlgOnEvent( nType, nControlID, value, gameObject )
	if nType == UI_EVENT_CLICK then
		if nControlID == 1 then
			--ͻ��
		else
			
		end
	end
end

-- ����ʱ����
function GirlTrainDlgOnAwake( gameObject )
	-- �ؼ���ֵ	
	local objs = gameObject:GetComponent( typeof(UISystem) ).relatedGameObject;	
	m_uiHeroPageL = objs[0];
	m_uiHeroPageR = objs[1];
	m_uiUIP_HeroHead = objs[2];
	m_uiContent = objs[3];
	m_uiIntimacy = objs[4];
	m_uiHeroChild = objs[5];
	m_uiAddDesc = objs[6];
	m_uiText = objs[7];
	m_uiNextBtn = objs[8];
	m_uiAddBtn = objs[9];
	m_uiChildNextBtn = objs[10];
	m_uiTitle = objs[11];
	m_uiUIP_ChildHead = objs[12];
	m_uiLeftHero = objs[13];
	m_uiRightHero = objs[14];
	m_uiBreakBtn = objs[15];
	
	-- �����
	m_ObjectPool = gameObject:GetComponent( typeof(ObjectPoolManager) );
	m_ObjectPool:CreatePool("UIP_HeroHead", 4, 4, m_uiUIP_HeroHead);
	
	
	GirlTrainInit();
end

-- �����ʼ��ʱ����
function GirlTrainDlgOnStart( gameObject )
	
end

-- ������ʾʱ����
function GirlTrainDlgOnEnable( gameObject )
	
end

-- ��������ʱ����
function GirlTrainDlgOnDisable( gameObject )
	
end

-- ����ɾ��ʱ����
function GirlTrainDlgOnDestroy( gameObject )
	m_Dlg = nil;
end

-- ÿ֡����
function GirlTrainDlgOnLogic( gameObject )
	
end

function GirlTrainInit()
	GirlHeadInit();
	HeroInfoSet();
	GirlInfoSet();
end

function GirlHeadInit()
	for i = 1, 4, 1 do
		local uiHeroObj = m_ObjectPool:Get( "UIP_HeroHead" );
		uiHeroObj.transform:SetParent( m_uiContent.transform );
		uiHeroObj:GetComponent("UIButton").controlID = 10000 + i;
		local objs = uiHeroObj.transform:GetComponent( typeof(Reference) ).relatedGameObject;

		local uiShape = objs[0];
		local uiColor = objs[1];
		local uiCorps = objs[2];
		local uiName = objs[3];
		local uiSelect = objs[4];
		local uiType = objs[5];
		
		
	end
end

function HeroInfoSet()
	local objs = m_uiLeftHero.transform:GetComponent( typeof(Reference) ).relatedGameObject;
	local uiQuality = objs[0];
	local uiName = objs[1];
	local uiShape = objs[2];
	
end

function GirlInfoSet()
	local objs = m_uiRightHero.transform:GetComponent( typeof(Reference) ).relatedGameObject;
	local uiQuality = objs[0];
	local uiName = objs[1];
	local uiShape = objs[2];
	
end