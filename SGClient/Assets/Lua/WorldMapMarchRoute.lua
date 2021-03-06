-- 世界地图行军路线

-- 行军路线资源图片信息
local MarchRouteSpriteWidth = 0.16;
local MarchRouteSpriteHeight = 0.14;

-- 路线集合
MapMarchRoute = {};

-- 缓存
MapMarchRoute.cache = {};

-- 行军路线Prefab
MapMarchRoute.prefab = nil;

-- 根节点
MapMarchRoute.root = nil;

-- 路线对象池
MapMarchRoute.objectPool = {};

MarchRouteMatGreen = nil
MarchRouteMatRed = nil
MarchRouteMatYellow = nil

-- 初始化
function MapMarchRoute.init( MapLineRoot )
	MapMarchRoute.root = MapLineRoot;
	MapMarchRoute.prefab = LoadPrefab( "MarchRoute" );
	MarchRouteMatGreen =  ResourceManager.LoadMaterial( "MarchRouteMatGreen" );
	MarchRouteMatRed =  ResourceManager.LoadMaterial( "MarchRouteMatRed" );
	MarchRouteMatYellow =  ResourceManager.LoadMaterial( "MarchRouteMatYellow" );
end

-- 清空
function MapMarchRoute.clear()
	MapMarchRoute.cache = {};
	MapMarchRoute.objectPool = {};
	MarchRouteMatGreen = nil
	MarchRouteMatRed = nil
	MarchRouteMatYellow = nil
end

-- 添加行军路线
function MapMarchRoute.add( recvValue )
	if recvValue.m_action == ARMY_ACTION_HELP_TROOP then
		if recvValue.m_from_nation ~= GetPlayer().m_nation then
			return
		end
	end
		
	-- 出发点
	local cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( recvValue.m_from_posx, recvValue.m_from_posy );
	local fposx, fposy = MapUnit.getGridTrans( recvValue.m_from_type, recvValue.m_from_grid, cameraPosX, cameraPosY );
	
	-- 目的点
	cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( recvValue.m_to_posx, recvValue.m_to_posy );
	local tposx, tposy = MapUnit.getGridTrans( recvValue.m_to_type, recvValue.m_to_grid, cameraPosX, cameraPosY );

	-- 计算线的颜色
	-- 1．自己的行军路线：绿色。MarchRouteMatGreen
	-- 2．非我国的行军路线：红色。MarchRouteMatRed
	-- 3．同国的行军路线：黄色。MarchRouteMatYellow
	--print("from_actorid:"..recvValue.m_from_actorid..",from_nation:"..recvValue.m_from_nation..",to_nation:"..recvValue.m_to_nation..",state:"..recvValue.m_state)
	local color = 0;
	if recvValue.m_from_actorid == GetPlayer().m_actorid then
		color = 1; -- 自己的
		
	elseif recvValue.m_state == ARMY_STATE_MARCH then
		if recvValue.m_from_nation == GetPlayer().m_nation then
			-- 同国行军
			color = 3; 
		else
			color = 2;
		end
	elseif recvValue.m_state == ARMY_STATE_REBACK then
		if recvValue.m_from_nation == GetPlayer().m_nation then
			color = 3;
		else
			color = 2;
		end
	else
		color = 2;
	end
	
	-- 如果缓存里面有，那么就更新
	local obj = MapMarchRoute.draw( MapMarchRoute.cache[recvValue.m_army_index], Vector3.New( fposx, fposy, 0 ), Vector3.New( tposx, tposy, 0 ), recvValue.m_state, color, MapMarchRoute.root )
	
	-- 插入缓存
	-- 缓存起来，以便删除
	if obj ~= nil then
		obj.gameObject:SetActive( true );
		MapMarchRoute.cache[recvValue.m_army_index] = obj;
	end
end

-- 删除行军路线
function MapMarchRoute.del( army_index )
	if MapMarchRoute.cache[army_index] == nil then
		return;
	end
	local obj = MapMarchRoute.cache[army_index];
	if obj ~= nil then
		obj.gameObject:SetActive( false );
		MapMarchRoute.cache[army_index] = nil; 
	end
	
end

-- 绘制行军路线
function MapMarchRoute.draw( obj, from, to, state, color, parent )
	if obj == nil then
		
		-- 在缓存池里找一个已经创建好的，复用就OK
		for index, unit in pairs( MapMarchRoute.objectPool ) do
			if unit and unit.gameObject.activeSelf == false then
				obj = unit;
				break;
			end
		end
		
		-- 没有空余的就新创建一个
		if obj == nil then
			obj = GameObject.Instantiate( MapMarchRoute.prefab );
			obj.transform:SetParent( MapMarchRoute.root );
			table.insert( MapMarchRoute.objectPool, obj );
		end
	
	end

	local plane = obj:GetComponent( "GizmoPlane" );
	-- 相反
	if state == ARMY_STATE_REBACK then
		from, to = to, from;
	end
	local length = ( from - to ):Magnitude();
	plane.vertices[0] = Vector3.New( -MarchRouteSpriteWidth / 2, 0, 0 );
	plane.vertices[1] = Vector3.New( -MarchRouteSpriteWidth / 2, length, 0 );
	plane.vertices[2] = Vector3.New( MarchRouteSpriteWidth / 2, 0, 0 );
	plane.vertices[3] = Vector3.New( MarchRouteSpriteWidth / 2, length, 0 );

	plane.uv[1] = Vector2.New( 0, length / MarchRouteSpriteHeight );
	plane.uv[3] = Vector2.New( 1, length / MarchRouteSpriteHeight );

	obj.transform:SetParent( parent );
	obj.transform.localScale = Vector3.one;
	obj.transform.localPosition = Vector3.New( from.x, from.y, WORLDMAP_ZORDER_MARCHROUTE );
	
	local offset = ( to - from ).x >= 0 and -1 or 1;
	obj.transform.localEulerAngles = Vector3.New( 0, 0, Vector3.Angle( Vector3( 0, 1, 0 ), to - from ) * offset );
	if color == 1 then
		plane:SetMaterial( MarchRouteMatGreen );
    elseif color == 2 then
        plane:SetMaterial( MarchRouteMatRed );
	elseif color == 3 then
        plane:SetMaterial( MarchRouteMatYellow );
	else
		plane:SetMaterial( MarchRouteMatYellow );
	end
	plane:Set();
	return obj;
end
