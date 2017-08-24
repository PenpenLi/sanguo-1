-- 世界地图操作
local m_Mod				= nil;
local m_uiEmptyInfo 	= nil; --UnityEngine.GameObject

local m_LastRecvValue = nil

-- 移动距离
local uiButtonOffset = 155;

-- 移动距离
local uiButtonOffsetX = 100;
local uiButtonOffsetY = 155;

-- 所属按钮点击时调用
function MapClickModOnEvent( nType, nControlID, value, gameObject )
	if nType == UI_EVENT_CLICK then
		
		-- 我的详情
		if nControlID == 1 then
		else	
		end

		if m_Mod then
			m_Mod:SetActive( false );
		end
		WorldMap.ClickEffect().gameObject:SetActive( false );
	elseif nType == UI_EVENT_PRESS then
		
	end
end

-- 载入时调用
function MapClickModOnAwake( gameObject )
	m_Mod = gameObject;
	local objs = gameObject:GetComponent("UIMod").relatedGameObject;
	m_uiEmptyInfo = objs[0];

end

-- 界面初始化时调用
function MapClickModOnStart( gameObject )
	
end

-- 界面显示时调用
function MapClickModOnEnable( gameObject )
	m_LastRecvValue = nil;
	local unit_index = WorldMap.m_nLastTouchUnitIndex;
	local gameCoorX  = WorldMap.m_nLastTouchGameCoorX;
	local gameCoorY  = WorldMap.m_nLastTouchGameCoorY;

    -- 显示坐标
    MapClickModCoordinate( gameCoorX, gameCoorY );

	if unit_index == -2 then
		-- 不允许操作的空地
		MapClickModOpenNull();
		
	elseif unit_index < 0 then
		-- 空地
		MapClickModOpenEmpty( recvValue );
		
	else
		local recvValue = WorldMap.m_nMapUnitList[unit_index];
		-- 空地
		if recvValue == nil then
			MapClickModOpenEmpty( recvValue )
			
		-- 城池
		elseif recvValue.m_type == MAPUNIT_TYPE_CITY then
			MapClickModOpenCity( recvValue )
			
		
			
		-- 资源
		elseif recvValue.m_type == MAPUNIT_TYPE_RES then
			MapClickModOpenRes( recvValue )	
		
		-- 城镇
		elseif recvValue.m_type == MAPUNIT_TYPE_TOWN then
			MapClickModOpenTown( recvValue )
		
		
		end
	end
end

-- 界面隐藏时调用
function MapClickModOnDisable( gameObject )
	
end

-- 界面删除时调用
function MapClickModOnDestroy( gameObject )
	m_Mod = nil;
end

-- 每帧调用
function MapClickModOnLogic( gameObject )
	
end


----------------------------------------
-- 自定
----------------------------------------
-- 更新坐标
function MapClickModCoordinate( gameCoorX, gameCoorY )
	if WorldMap.MapClickMod().gameObject.activeSelf == false then
		return;
	end
	SetText( m_uiEmptyInfo.transform:Find("Pos"), "["..gameCoorX..","..gameCoorY.."]" )	
end

-- 点击不允许操作的地面
function MapClickModOpenNull()
end

-- 点击空地显示的操作界面
function MapClickModOpenEmpty( recvValue )
	
end

-- 点击城市显示的操作界面
function MapClickModOpenCity( recvValue )
	
end

-- 点击城镇显示的操作界面
function MapClickModOpenTown( recvValue )
	
end

-------------------------------
-- 按钮表现
-------------------------------
local m_ButtonPos = 
{
    [1] = { Vector3.New( 0, uiButtonOffset, 0 ) },
    [2] = { Vector3.New( -uiButtonOffset, 0, 0 ), Vector3.New( uiButtonOffset, 0, 0 ) },
    [3] = { Vector3.New( -uiButtonOffset, 0, 0 ), Vector3.New( 0, uiButtonOffset, 0 ), Vector3.New( uiButtonOffset, 0, 0 ) },
    [4] = { Vector3.New( -uiButtonOffset, 0, 0 ), Vector3.New( -uiButtonOffset / 2, uiButtonOffset, 0 ), Vector3.New( uiButtonOffset / 2, uiButtonOffset, 0 ), Vector3.New( uiButtonOffset, 0, 0 ) },
    [5] = { Vector3.New( -uiButtonOffset, 0, 0 ), Vector3.New( -uiButtonOffset * 3 / 4, uiButtonOffset * 3 / 4, 0 ), Vector3.New( 0, uiButtonOffset, 0 ), Vector3.New( uiButtonOffset * 3 / 4, uiButtonOffset * 3 / 4, 0 ), Vector3.New( uiButtonOffset, 0, 0 ) },
}
function MapClickModButton( buttonList )
    for i = 1, #buttonList, 1 do
        buttonList[i].gameObject:SetActive( true );
        buttonList[i]:GetComponent("UITweenLocalPosition").to = m_ButtonPos[ #buttonList ][i];
        buttonList[i]:GetComponent("UITweenLocalPosition"):Play( true );
    end
end

-- 点击资源点显示的操作界面
function MapClickModOpenRes( recvValue )
	
end

-------------------------------
-- 功能
-------------------------------
-- 点击-攻击
function MapClickModAttack()
	
	local cacheValue = WorldMap.m_nMapUnitList[WorldMap.m_nLastTouchUnitIndex];
    if cacheValue == nil then
        return;
    end
	if cacheValue.m_type == MAPUNIT_TYPE_CITY or cacheValue.m_type == MAPUNIT_TYPE_ARMY or cacheValue.m_type == MAPUNIT_TYPE_RES then
		local buff = GetCity().BuffDuration[1];
		if buff and ( buff.endtime - GetServerTime() > 0 ) then
			MsgBox( GetLocalizeText(9004), function() TroopDlgOpenWithAction( ARMY_ACTION_FIGHT ) end );
			return
		end
	end
	TroopDlgOpenWithAction( ARMY_ACTION_FIGHT );
end

-- 点击-侦查
function MapClickModSpy()
	
	-- 通灵眼检查
	local building = GetCity():GetBuildingByKind( BUILDING_SPY )
    if building == nil or building.m_level < 1 then
        return;
    end
	
	local recvValue = WorldMap.m_nMapUnitList[WorldMap.m_nLastTouchUnitIndex];
	if recvValue == nil then
		return;
	end
	-- 城池
	if recvValue.m_type == MAPUNIT_TYPE_CITY then
        SpyDlgOnShow( recvValue.m_name, recvValue.m_prefix );
		
	-- 部队
	elseif recvValue.m_type == MAPUNIT_TYPE_ARMY then
		if m_LastRecvValue then
            SpyDlgOnShow( m_LastRecvValue.m_name, m_LastRecvValue.m_prefix );
		end
		
	-- 资源
	elseif recvValue.m_type == MAPUNIT_TYPE_RES then
		if m_LastRecvValue then
            SpyDlgOnShow( m_LastRecvValue.m_name, m_LastRecvValue.m_prefix );
		end
	end
end