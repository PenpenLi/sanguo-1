-- 界面
local m_Dlg = nil;
local m_DialogFrameMod = nil;

local m_uiNowText = nil; --UnityEngine.GameObject
local m_uiScrollView = nil; --UnityEngine.GameObject
local m_uiContent = nil; --UnityEngine.GameObject
local m_uiUIP_Info = nil; --UnityEngine.GameObject
local m_uiUIP_Visit = nil; --UnityEngine.GameObject

local m_ObjectPool = nil;
local m_uiInfoObjs = nil
local m_recvValue = nil;

-- 打开界面
function NationHeroDlgOpen()
	m_Dlg = eye.uiManager:Open( "NationHeroDlg" );
	m_DialogFrameMod = DialogFrameModOpen( m_Dlg, T(1539), HELP_NationDlg, NationHeroDlgClose );
end

-- 隐藏界面
function NationHeroDlgClose()
	if m_Dlg == nil then
		return;
	end
	DialogFrameModClose( m_DialogFrameMod );
	m_DialogFrameMod = nil;
	eye.uiManager:Close( "NationHeroDlg" );
	m_uiInfoObjs = nil
	m_recvValue = nil;
end

-- 删除界面
function NationHeroDlgDestroy()
	GameObject.Destroy( m_Dlg );
	m_Dlg = nil;
	m_uiInfoObjs = nil
	m_recvValue = nil;
end

----------------------------------------
-- 事件
----------------------------------------

-- 所属按钮点击时调用
function NationHeroDlgOnEvent( nType, nControlID, value, gameObject )
	if nType == UI_EVENT_CLICK then
        if nControlID == -1 then
            NationHeroDlgClose();
		elseif nControlID >= 1000 and nControlID < 2000 then
			NationHeroDlgHeroView( nControlID )
        end
	end
end

-- 载入时调用
function NationHeroDlgOnAwake( gameObject )
	-- 控件赋值	
	local objs = gameObject:GetComponent( typeof(UISystem) ).relatedGameObject;	
	m_uiNowText = objs[0];
	m_uiScrollView = objs[1];
	m_uiContent = objs[2];
	m_uiUIP_Info = objs[3];
	m_uiUIP_Visit = objs[4];
	-- 对象池
	m_ObjectPool = gameObject:GetComponent( typeof(ObjectPoolManager) );
	m_ObjectPool:CreatePool("UIP_Info", 5, 5, m_uiUIP_Info);
	m_ObjectPool:CreatePool("UIP_Visit", 1, 1, m_uiUIP_Visit);
end

-- 界面初始化时调用
function NationHeroDlgOnStart( gameObject )
	
end

-- 界面显示时调用
function NationHeroDlgOnEnable( gameObject )
	
end

-- 界面隐藏时调用
function NationHeroDlgOnDisable( gameObject )
	
end

-- 界面删除时调用
function NationHeroDlgOnDestroy( gameObject )
	m_Dlg = nil;
end

-- 每帧调用
function NationHeroDlgOnLogic( gameObject )
	
end


----------------------------------------
-- 自定
----------------------------------------
function NationHeroDlgShow()
	NationHeroDlgOpen()
	NationHeroDlgClear()
	system_askinfo( ASKINFO_NATIONHERO, "", 0 )
	
	m_uiInfoObjs = {};
	for i=0,4,1 do
		m_uiInfoObjs[i] = NationHeroDlgCreateInfo( i );
	end
end

-- m_count=0,m_list={m_kind=0,m_actorid=0,m_namelen=0,m_name="[m_namelen]",m_level=0,m_posx=0,m_posy=0,m_buypos=0,m_state=0,m_forever=0,m_nation=0,[m_count]},m_nationlevel=0,
function NationHeroDlgRecv( recvValue )
	m_recvValue = recvValue;
	for i=1, recvValue.m_count, 1 do
		NationHeroDlgSetHero( i, recvValue.m_list[i] )
	end
end

-- 创建一个等级信息
function NationHeroDlgCreateInfo( index )
	local uiObj = m_ObjectPool:Get( "UIP_Info" );
	uiObj.transform:SetParent( m_uiContent.transform );
	SetText( uiObj.transform:Find("Level"), F(1884, index+4) )
	return uiObj;
end

-- 设置英雄
function NationHeroDlgSetHero( i, info )
	local level = g_nation_heroinfo[info.m_kind].nationlevel;
	local nation = g_nation_heroinfo[info.m_kind].nation;
	local uiObj = m_uiInfoObjs[ level-4 ]
	local uiHeroList = uiObj.transform:Find( "HeroList" );
	local uiHero = uiHeroList.transform:GetChild( nation - 1 )
	
	local objs = uiHero.transform:GetComponent( typeof(Reference) ).relatedGameObject;
	local uiShape = objs[0]
	local uiColor = objs[1]
	local uiCorps = objs[2]
	local uiLevel = objs[3]
	local uiNation = objs[4]
	local uiWarn = objs[5]
	local uiOwner = objs[6]
	local uiVisitBtn = objs[7]
	
	SetControlID( uiHero, 1000 + i )
	SetImage( uiShape, HeroHeadSprite( info.m_kind ) )
	-- 哪国名将
	SetText( uiNation, T( 1884 + g_nation_heroinfo[info.m_kind].nation ) )
	
	-- 等级不足
	if m_recvValue.m_nationlevel[nation] < level then
		SetTrue( uiWarn )
		SetText( uiWarn, T(1888) )
		SetFalse( uiVisitBtn )
		SetFalse( uiOwner )
	else
		SetFalse( uiWarn )
		
		-- 自已已经通过女将获得	
		if info.m_forever > 0 then
			SetTrue( uiOwner )
			SetText( uiOwner, T(1893) )
			
		-- 无双名将有主人
		elseif info.m_actorid > 0 then
			SetTrue( uiOwner )
			SetText( uiOwner, "["..Nation(info.m_nation).."]"..info.m_name )
			SetFalse( uiVisitBtn )
			
		-- 没获得
		else
			SetTrue( uiOwner )
			SetText( uiOwner, T(1894) )
			SetTrue( uiVisitBtn )
			-- 寻访所需钻石
			if g_nation_heroinfo[info.m_kind].nation == GetPlayer().m_nation then
				SetText( uiVisitBtn.transform:Find("Back/Text"),g_nation_heroinfo[info.m_kind].visit_token  )
			else
				SetText( uiVisitBtn.transform:Find("Back/Text"),g_nation_heroinfo[info.m_kind].other_visit_token  )
			end
		end
	end
end

-- 清空
function NationHeroDlgClear()
	local objs = {};
	for i = 0 ,m_uiContent.transform.childCount - 1 do
		table.insert( objs, m_uiContent.transform:GetChild(i).gameObject )
    end
	for k, v in pairs(objs) do
		local obj = v;
		if obj.name == "UIP_Info(Clone)" then
			m_ObjectPool:Release( "UIP_Info", obj );
		elseif obj.name == "UIP_Visit(Clone)" then
			m_ObjectPool:Release( "UIP_Visit", obj );
		end
    end
end

-- 查看武将
function NationHeroDlgHeroView( index )
	local info = recvValue.m_list[index]
	if info == nil then
		return
	end
end
