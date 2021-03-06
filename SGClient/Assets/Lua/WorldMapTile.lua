-- 世界地图格子数据

-- 格子集合
MapTile = {};

-- 格子数据
MapTile.data = {};

MapTile.tiledMap = {};
MapTile.forest = nil

-- 初始化
function MapTile.init()
	MapTile.tiledMap = require("config/conf_worldmap");
	MapTile.forest = {}
end

-- 向格子里添加数据
function MapTile.add( recvValue )
	-- 只有驻扎的部队才添加
	if recvValue.m_type == MAPUNIT_TYPE_ARMY then
		if recvValue.m_state ~= ARMY_STATE_OCCUPY then
			return;
		end
	end
	
	local posx = recvValue.m_posx;
	local posy = recvValue.m_posy;
	local unittype = recvValue.m_type;
	local grid = 1;
	if recvValue.m_type == MAPUNIT_TYPE_TOWN then
		local townid 	= recvValue.m_short_value[1];
		grid = MapUnit.getGrid( recvValue.m_type, g_towninfo[townid].grid );
		--print( "posx:"..posx..",posy:"..posy.." unittype:"..unittype.." grid:"..grid )
	else
		grid = MapUnit.getGrid( recvValue.m_type, 0 );
	end
		
	-- 占1*1格子的情况
	if grid == 1 then
		local x = posx;
		local y = posy;
		if MapTile.data[x] == nil then
			MapTile.data[x] = {};
		end
		if MapTile.data[x][y] == nil then 
			MapTile.data[x][y] = {};
		end
		MapTile.data[x][y]["unit_type"] = recvValue.m_type
		MapTile.data[x][y]["unit_index"] = recvValue.m_unit_index;
		
		-- 格子添加对象就删除这个格子的森林
		if recvValue.m_unit_index >= 0 then
			MapTile.DelForest( x, y )
		end
	
	-- 占2*2格子的情况
	elseif grid == 2 then
		local offset = { { x=0, y=0 },{ x=0, y=-1 },{ x=1, y=-1 },{ x=1, y=0 },}
		for i=1, 4, 1 do
			local x = posx + offset[i]["x"];
			local y = posy + offset[i]["y"];
			if MapTile.data[x] == nil then
				MapTile.data[x] = {};
			end
			if MapTile.data[x][y] == nil then 
				MapTile.data[x][y] = {};
			end
			MapTile.data[x][y]["unit_type"] = recvValue.m_type
			MapTile.data[x][y]["unit_index"] = recvValue.m_unit_index;
			--print( "x:"..x..",y:"..y..",recvValue.m_unit_index:"..recvValue.m_unit_index )
			
			-- 格子添加对象就删除这个格子的森林
			if recvValue.m_unit_index >= 0 then
				MapTile.DelForest( x, y )
			end
		end
		
	-- 占3*3格子的情况
	elseif grid == 3 then
		local offset = { { x=0, y=0 },{ x=-1, y=0 },{ x=-1, y=-1 },{ x=0, y=-1 },{ x=1, y=-1 },{ x=1, y=0 },{ x=1, y=1 },{ x=0, y=1 },{ x=-1, y=1 },}
		for i=1, 9, 1 do
			local x = posx + offset[i]["x"];
			local y = posy + offset[i]["y"];
			if MapTile.data[x] == nil then
				MapTile.data[x] = {};
			end
			if MapTile.data[x][y] == nil then 
				MapTile.data[x][y] = {};
			end
			MapTile.data[x][y]["unit_type"] = recvValue.m_type
			MapTile.data[x][y]["unit_index"] = recvValue.m_unit_index;
			
			-- 格子添加对象就删除这个格子的森林
			if recvValue.m_unit_index >= 0 then
				MapTile.DelForest( x, y )
			end
		end
	end
end

-- 删除格子数据
function MapTile.del( recvValue )
	if recvValue == nil then
		return;
	end
	local info = clone(recvValue);
	info.m_unit_index = -1;
	MapTile.add( info )
end

-- 清空数据
function MapTile.clear()
	MapTile.data = {};
	MapTile.forest = nil
end

-- 获取点击的格子数据
function MapTile.get( posx, posy )
	
	-- 优先选择对象格子，如果没有对象格子，检查地图阻挡格子
	if MapTile.data[posx] == nil or MapTile.data[posx][posy] == nil then
		if MapTile.block( posx, posy ) < 0 then
			return -2;
		end
		return -1;
	end

	return MapTile.data[posx][posy]["unit_index"];
end

-- 地图阻挡
function MapTile.block( posx, posy )    
    -- 范围
	if posx < 0 or posy < 0 or posx >= 500 or posy >= 500 then
		return -1;
	end
	return 0;
end

-- 获取森林池对象
function MapTile.GetForestObj( id )
	local offset = id - 21;
	return MapForestRootObjectPool:Get( "MapForest"..offset );
end

-- 获取森林池对象
function MapTile.ReleaseForestObj( id, unitObj )
	local offset = id - 21;
	MapForestRootObjectPool:Release( "MapForest"..offset, unitObj );
end

-- 创建森林
function MapTile.AddForest( posx, posy )
	-- 先转换成一小块地图的坐标，因为地图是N*N的拼起来的
	local localposx = math.floor( math.mod( posx, TMX_WIDTH ) );
	local localposy = math.floor( math.mod( posy, TMX_HEIGHT ) );
	local index = localposx + localposy*TMX_HEIGHT + 1;
	
	local id = MapTile.tiledMap.layers[3].data[index];
	if id == 0 then
		return
	end
	
	if MapTile.forest[posx] ~= nil and MapTile.forest[posx][posy] ~= nil then
		return
	end
	
	if MapTile.data[posx] and MapTile.data[posx][posy] then
		if MapTile.data[posx][posy]["unit_index"] >= 0 then
			return
		end
	end
	
	local unitObj = MapTile.GetForestObj( id )
	
	-- 位置
	local cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( posx, posy );
	local x, y = MapUnit.getGridTrans( MAPUNIT_TYPE_CITY, 0, cameraPosX, cameraPosY );
	unitObj.transform.localPosition = Vector3.New( x, y, 0 );
	unitObj.transform:SetParent( MapForestRoot.transform );
	unitObj.transform.localScale = Vector3.one;
	unitObj.gameObject:SetActive( true );
	
	-- 缓存起来
	if MapTile.forest[posx] == nil then
		MapTile.forest[posx] = {};
	end
	if MapTile.forest[posx][posy] == nil then 
		MapTile.forest[posx][posy] = nil;
	end
			
	MapTile.forest[posx][posy] = unitObj;
end

-- 删除森林
function MapTile.DelForest( posx, posy )
	local localposx = math.floor( math.mod( posx, TMX_WIDTH ) );
	local localposy = math.floor( math.mod( posy, TMX_HEIGHT ) );
	local index = localposx + localposy*TMX_HEIGHT + 1;
	
	local id = MapTile.tiledMap.layers[3].data[index];
	if id == 0 then
		return
	end
	
	if MapTile.forest[posx] == nil or MapTile.forest[posx][posy] == nil then
		return
	end

	MapTile.ReleaseForestObj( id, MapTile.forest[posx][posy] )
	MapTile.forest[posx][posy] = nil;
end


