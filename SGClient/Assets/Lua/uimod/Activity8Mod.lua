local m_Mod;
local m_uiBack = nil; --UnityEngine.GameObject
local m_uiActivityVip = nil; --UnityEngine.GameObject
local m_uiActivityOpenBtn = nil; --UnityEngine.GameObject
local m_uiContent = nil; --UnityEngine.GameObject
local m_uiUIP_Mission = nil; --UnityEngine.GameObject
local m_uiAwardDescLayer = nil; --UnityEngine.GameObject
local m_AwardDescLayerShow = false
local m_ObjectPool = nil
local m_recvIsOpen = nil;
local m_recvState = nil;
local m_red = 0;
----------------------------------------
-- 事件
----------------------------------------

-- 所属按钮点击时调用
function Activity8ModOnEvent( nType, nControlID, value, gameObject )
	if nType == UI_EVENT_CLICK then
		print( "Button Clicked, nControlID:" .. nControlID );
		if nControlID == -2 then
			Activity8ModAwardDescLayer();
		elseif nControlID == 1 then
		   Activity8ModActivityOpen()
		elseif nControlID >= 1000 and nControlID <= 2000 then
			Activity8ModSelect( nControlID-1000 )
		elseif nControlID >= 1000000 and nControlID < 2000000 then
			Activity8ModClickItem( nControlID-1000000, value )
		end
	elseif nType == UI_EVENT_PRESS then
		if value == 0 then
			--print( "Button Pressed Down, nControlID:" .. nControlID );
		elseif value == 1 then
			--print( "Button Pressed UP, nControlID:" .. nControlID);
		end
	elseif nType == UI_EVENT_SCROLLDRAG then
		if nControlID == 1 then
			if m_AwardDescLayerShow == true then
				Activity8ModAwardDescLayer()
			end
		end
	end
end

-- 载入时调用
function Activity8ModOnAwake( gameObject )
	m_Mod = gameObject;
	local objs = gameObject:GetComponent( "UIMod" ).relatedGameObject;
	m_uiBack = objs[0];
	m_uiActivityVip = objs[1];
	m_uiActivityOpenBtn = objs[2];
	m_uiContent = objs[3];
	m_uiUIP_Mission = objs[4];
	m_uiAwardDescLayer = objs[5];
	-- 对象池
	m_ObjectPool = gameObject:GetComponent( typeof(ObjectPoolManager) );
	m_ObjectPool:CreatePool("UIP_Mission", 12, 12, m_uiUIP_Mission);
end

-- 界面初始化时调用
function Activity8ModOnStart( gameObject )
	system_askinfo( ASKINFO_ACTIVITY, "", ACTIVITY_8, 0 )
	ResourceManager.LoadAssetBundle( "_ab_activity_pic_2" )
	ResourceManager.LoadAssetBundle( "_ab_activity_back_5" )
	
	SetImage( m_uiBack, LoadSprite("activity_pic_2") )
	m_AwardDescLayerShow = false
end

-- 界面显示时调用
function Activity8ModOnEnable( gameObject )
	
end

-- 界面隐藏时调用
function Activity8ModOnDisable( gameObject )
	
end

-- 界面删除时调用
function Activity8ModOnDestroy( gameObject )
	m_Mod = nil
	m_recvIsOpen = nil;
	m_recvState = nil 
	ResourceManager.UnloadAssetBundle( "_ab_activity_pic_2" )
	ResourceManager.UnloadAssetBundle( "_ab_activity_back_5" )
end

-- 每帧调用
function Activity8ModOnLogic( gameObject )
	
end

function Activity8ModGet()
	return m_Mod;
end
----------------------------------------
-- 自定
----------------------------------------
function Activity8ModRecv( isopen, state )
	if m_Mod == nil then
		return
	end
	m_red = 0;
	if isopen == 0 then
		SetTrue( m_uiActivityVip )
		SetTrue( m_uiActivityOpenBtn )
	else
		SetFalse( m_uiActivityVip )
		SetFalse( m_uiActivityOpenBtn )
	end
	m_recvIsOpen = isopen
	m_recvState = state
	Activity8ModClear()
	
	-- 已完成的排序后面
	local tmptable = {}
	for i=1, #g_activity_08, 1 do
		local state = Utils.get_int_sflag( state, i )
		table.insert( tmptable, {state=state, rank=-1000*state-g_activity_08[i].id, info=g_activity_08[i]} )
	end
	table.sort( tmptable, function(a,b) 
		if a.rank > b.rank then
			return true
		else
			return false
		end
	end )

	for i=1, #tmptable, 1 do
		Activity8ModCreate( tmptable[i].info, tmptable[i].state )
	end
	
	-- 红点
	ActivityDlgChangeRed( ACTIVITY_8, m_red )
end

-- 创建
function Activity8ModCreate( info, state )
	local uiObj = m_ObjectPool:Get("UIP_Mission");
	uiObj.transform:SetParent( m_uiContent.transform );
	uiObj.transform.localScale = Vector3.one;
	
	local objs = uiObj.transform:GetComponent( typeof(Reference) ).relatedGameObject;
	local uiName = objs[0]
	local uiValue = objs[1]
	local uiAwardList = objs[2]
	local uiStateBtn = objs[3]
	local uiBack = objs[4]
	local uiState = objs[5]
	
	SetControlID( uiStateBtn, 1000 + info.id )
	SetImage( uiBack, LoadSprite("activity_back_5") )
	SetText( uiName, F(2459, info.level) )
	SetText( uiValue, GetPlayer().m_level.."/"..info.level )
	
	if GetPlayer().m_level >= info.level then
		if state == 1 then-- 完成已经领取
			SetText( uiStateBtn.transform:Find("Back/Text"), T(1109) )
			SetFalse( uiStateBtn )
			SetTrue( uiState )
		else -- 完成没有领取
			SetText( uiStateBtn.transform:Find("Back/Text"), T(1351) )
			SetTrue( uiStateBtn )
			SetButtonTrue( uiStateBtn )
			SetFalse( uiState )
			m_red = 1
		end
	else
		SetText( uiStateBtn.transform:Find("Back/Text"), T(2452) )
		SetTrue( uiStateBtn )
		SetButtonFalse( uiStateBtn )
		SetFalse( uiState )
	end
	
	-- 奖励
	local awardkind = { info.awardkind0, info.awardkind1, info.awardkind2, info.awardkind3, info.awardkind4 }
	local awardnum = { info.awardnum0, info.awardnum1, info.awardnum2, info.awardnum3, info.awardnum4 }
	for i=1, 4, 1 do
		local awardObj = uiAwardList.transform:GetChild(i-1);
		if awardkind[i] > 0 then
			local sprite, color, name = AwardInfo( awardkind[i] )
			SetTrue( awardObj )
			SetControlID( awardObj, 1000000+awardkind[i] )
			SetImage( awardObj.transform:Find("Shape"), sprite );
			if awardnum[i] > 1 then
				SetText( awardObj.transform:Find("Num"), "x"..knum(awardnum[i]) );
			else
				SetText( awardObj.transform:Find("Num"), "" );
			end
		else
			SetFalse( awardObj )
		end
	end
end

--清空
function Activity8ModClear()
	local objs = {};
	for i=0,m_uiContent.transform.childCount-1 do
		table.insert(objs,m_uiContent.transform:GetChild(i).gameObject);
	end
	for k, v in pairs(objs) do
		local obj = v;
		if obj.name == "UIP_Mission(Clone)" then
			m_ObjectPool:Release( "UIP_Mission", obj );
		end
	end
end

function Activity8ModActivityOpen()
	if GetPlayer().m_viplevel < global.activity08_viplevel then
		JumpVip( global.activity08_viplevel )
		return
	end
	MsgBox( T(2458), function()
		system_askinfo( ASKINFO_ACTIVITY, "", ACTIVITY_8, 1 )
	end )
end

-- 领取奖励
function Activity8ModSelect( id )
	if GetPlayer().m_level < g_activity_08[id].level then
		return	
	end
	if m_recvIsOpen == 0 then
		pop(T(2460))
		return
	end
	if Utils.get_int_sflag( m_recvState, id ) == 1 then
		return
	end
	system_askinfo( ASKINFO_ACTIVITY, "", ACTIVITY_8, 2, id )
end

-- 奖励描述
function Activity8ModAwardDescLayer()
	SetFalse( m_uiAwardDescLayer )
	m_AwardDescLayerShow = false
end
function Activity8ModClickItem( awardkind, uiObj )
	Activity8ModAwardDescLayer()
	if awardkind > AWARDKIND_HEROBASE and awardkind < AWARDKIND_BUILDINGBASE then
		local herokind = awardkind - AWARDKIND_HEROBASE
		local color = hero_getnormalcolor( herokind )
		HeroConfigDlgShow( g_heroinfo[herokind][color], 0 );
	else
		m_uiAwardDescLayer.transform:SetParent( uiObj.transform )
		m_uiAwardDescLayer.transform.anchoredPosition = Vector2( 0, 80 )
		m_uiAwardDescLayer.transform:SetParent( m_Mod.transform )
		local _, _, name, c, desc = AwardInfo( awardkind )
		SetText( m_uiAwardDescLayer.transform:Find("Name"), name, NameColor(c) )	
		local _desc = string.split( desc, "\n")
		if _desc ~= nil and _desc[1] ~= nil then
			SetText( m_uiAwardDescLayer.transform:Find("Desc"), _desc[1] )
		else
			SetText( m_uiAwardDescLayer.transform:Find("Desc"), desc )
		end
		SetText( m_uiAwardDescLayer.transform:Find("Warn"), "" )
		SetTrue( m_uiAwardDescLayer )
		m_AwardDescLayerShow = true
	end
end