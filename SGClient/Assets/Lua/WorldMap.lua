-- �����ͼ
MAP_TILEWIDTH 		= 256;	-- һ������ж�������	
MAP_TILEHEIGHT 		= 128;	-- һ������ж�������

TMX_WIDTH 			= 100;  -- һ��tmx��ͼ��С
TMX_HEIGHT 			= 100;  -- һ��tmx��ͼ��С

WORLDMAP_ZORDER_CLICKMOD	=	-1000; 	-- �����ͼѡ���㼶
WORLDMAP_ZORDER_MARCHROUTE	=	-2000;	-- �о�·�߲㼶
WORLDMAP_ZORDER_ARMY		=	-2001;	-- ���Ӳ㼶
WORLDMAP_ZORDER_CAMERA		=	-10000;	-- ������㼶

WORLDMAP_MODE_NORMAL	=	0; -- ȱʡģʽ
WORLDMAP_MODE_FOLLOW	=	1; -- ����ģʽ

-- �����ͼ
WorldMap = {}
WorldMap.m_nMaxWidth 			= 500;    -- �����ͼ��С����������
WorldMap.m_nMaxHeight 			= 500;    -- �����ͼ��С����������
WorldMap.m_nAreaWidth 			= 0;    -- �����С��һ�����򼸸���ͼ���ӣ�
WorldMap.m_nAreaHeight 			= 0;    -- �����С��һ�����򼸸���ͼ���ӣ�
WorldMap.m_nAreaXNum 			= 0;    -- һ����ͼ�ж�������
WorldMap.m_nAreaYNum 			= 0;    -- һ����ͼ�ж�������
WorldMap.m_nLastAreaIndex		= -1;   -- ��һ�η�������
WorldMap.m_nMapUnitList			= {};   -- ��ʾ���󻺴�����
WorldMap.m_nMyCityPosx			= 0;    -- �������λ�ã����ӣ�
WorldMap.m_nMyCityPosy			= 0;    -- �������λ�ã����ӣ�
WorldMap.m_nMyCityCameraX 		= 0;    -- �������λ�ã���Ļ���꣩
WorldMap.m_nMyCityCameraY		= 0;    -- �������λ�ã���Ļ���꣩
WorldMap.m_nMyCityUnitIndex 	= -1;   -- ������ǵ���ʾ����
WorldMap.m_nMyCityState			= 0;	-- �������״̬
WorldMap.m_nLastCameraX 		= 0; 	-- �ϴ������λ�ã���Ļ���꣩
WorldMap.m_nLastCameraY			= 0; 	-- �ϴ������λ�ã���Ļ���꣩
WorldMap.m_nLastCameraGameX 	= -1; 	-- �ϴ������λ�ã��������꣩
WorldMap.m_nLastCameraGameY 	= -1; 	-- �ϴ������λ�ã��������꣩
WorldMap.m_nLastTouchGameCoorX 	= 0; 	-- �ϴε��λ�ã����ӣ�
WorldMap.m_nLastTouchGameCoorY	= 0; 	-- �ϴε��λ�ã����ӣ�
WorldMap.m_nLastTouchUnitIndex	= -1; 	-- �ϴε����λ
WorldMap.m_nLastTouchArmyIndex	= -1; 	-- �ϴε������
WorldMap.m_nLastGotoUnitIndex	= -1;	-- �ȴ���ת������
WorldMap.m_nLastGotoPosX		= -1;	-- �ȴ���ת��λ��
WorldMap.m_nLastGotoPosY		= -1;	-- �ȴ���ת��λ��
WorldMap.m_nZoneID				= 0;	-- ��ǰ��ͼ
WorldMap.m_nMode 				= WORLDMAP_MODE_NORMAL;

local TmxShowThreshold = 24;
local TmxShowList = { 0, 0, 0, 0 };
local TmxLastList = { 0, 0, 0, 0 };
local m_LastPosX;
local m_LastPosY;
local m_Faded = false;
local m_FadeStopCount = 0;
 
-- ��ͼ����
Area = {}
-- �������������ȡ������
function Area.GetIndex( posx, posy )
	local areax, areay;
	if posx >= WorldMap.m_nMaxWidth then
		posx = WorldMap.m_nMaxWidth - 1;
	end
	if posy >= WorldMap.m_nMaxHeight then
		posy = WorldMap.m_nMaxHeight - 1;
	end
	areax = math.modf( (posx+1)/WorldMap.m_nAreaWidth );
	areay = math.modf( (posy+1)/WorldMap.m_nAreaHeight );
	
	if areax >= WorldMap.m_nAreaXNum then
		areax = WorldMap.m_nAreaXNum - 1;
	end
	if areay >= WorldMap.m_nAreaYNum then
		areay = WorldMap.m_nAreaYNum - 1;
	end
		
	return math.modf( areay*(WorldMap.m_nAreaXNum) + areax );
end

-- ��ʾ��Ԫ��������
local procQueue = Queue.new();
-- ���ӵ��ó���һ������
local procQueueArmy = Queue.new();
local m_updateWaitFrame = 0;

-- ��ͼ�������
local WorldMapPrefab	= nil;	-- ��ͼ��
local MapTmxRoot		= nil;	-- tmx��ͼ���ڵ�
MapUnitRoot				= nil;	-- ������ʾ����ĸ��ڵ�
local MapLineRoot		= nil;	-- �����߸��ڵ�
local MapClickEffect	= nil;	-- �����Ч
local MapClickMod		= nil;	-- ��������
local MapCamera 		= nil;	-- ��ͼ�����
local MapTmx            = {};   -- ��ͼ�أ�ֻʵ����4��

local m_RecvValue = nil;

-- �����ͼ��Ϣ
function WorldMap.Recv( recvValue )
    m_RecvValue = recvValue;
	if GameManager.currentScence == "worldmap" then
		WorldMap.CameraSetPosition( MAPUNIT_TYPE_CITY, recvValue.m_target_posx, recvValue.m_target_posy );
		--WorldMap.ViewChangeSec();
		return;
	end
	
	WorldMap.m_nAreaWidth			= 	recvValue.m_area_width;
	WorldMap.m_nAreaHeight			= 	recvValue.m_area_height;
	WorldMap.m_nAreaXNum			= 	recvValue.m_map_area_xnum;
	WorldMap.m_nAreaYNum			= 	recvValue.m_map_area_ynum;
	WorldMap.m_nMyCityPosx			= 	recvValue.m_my_city_posx;
	WorldMap.m_nMyCityPosy			= 	recvValue.m_my_city_posy;
	WorldMap.m_nMyCityUnitIndex 	= 	recvValue.m_my_city_unit_index;
	WorldMap.m_nMyMonsterKillLevel	=	recvValue.m_monster_killlevel;
	WorldMap.m_nMyCityState			=	recvValue.m_citystate;
	WorldMap.m_nLastAreaIndex 		= 	-1;
	WorldMap.m_nLastGotoPosX		= 	recvValue.m_target_posx;
	WorldMap.m_nLastGotoPosY		= 	recvValue.m_target_posy;
	WorldMap.m_nMapUnitList			= {};
	MapUnit.init();
	
	-- �ı䳡��
	GameManager.ChangeScence( "worldmap" )
end

-- ���
function WorldMap.Clear()
	WorldMap.m_nLastAreaIndex = -1;
	WorldMap.m_nLastTouchArmyIndex = -1;
	WorldMap.m_nLastTouchUnitIndex = -1;
	WorldMap.m_nLastGotoUnitIndex = -1;
    WorldMap.m_nLastCameraGameX = -1;
    WorldMap.m_nLastCameraGameY = -1;
    WorldMap.m_nMapUnitList = {};
	WorldMap.QueueClear();
	MapUnit.clear();
	MapTile.clear();
	MapMarchRoute.clear();
	MapUnitRoot = nil;
    MapCamera = nil;
	WorldMap.SendAreaIndex( WorldMap.m_nLastAreaIndex, -1, -1 )
    
    m_LastPosX = nil;
    m_LastPosY = nil;
	--collectgarbage("collect");
end

-- ǰ�������ͼ
function WorldMap.GotoWorldMap( posx, posy )
	-- m_to_posx=0,m_to_posy=0,
	local sendValue = {};
	sendValue.m_to_posx = posx;
	sendValue.m_to_posy = posy;
	netsend_worldmapask_C( sendValue )
end

-- ���سǳ�
function WorldMap.ReturnCity()
	GameManager.ChangeScence( "city" )
	TmxLastList = { 0, 0, 0, 0 };
	WorldMap.Clear()
end

-- ���Ϳͻ��˵�ǰ��������
function WorldMap.SendAreaIndex( areaindex, posx, posy )
	-- m_areaindex=0,
	local sendValue = {};
	sendValue.m_areaindex = areaindex;
	sendValue.m_posx = posx;
	sendValue.m_posy = posy;
	netsend_worldmapareaindex_C( sendValue );
end

-- ȷ���ĸ�ͼ��ʾ
function WorldMap.RefreshShow( gamePosX, gamePosY )
    TmxShowList = { 0, 0, 0, 0 };

    -- С������
	local localPosX = math.floor( math.mod( gamePosX, TMX_WIDTH ) );
	local localPosY = math.floor( math.mod( gamePosY, TMX_HEIGHT ) );

    -- �ĸ��ͼ
    local mapX = math.floor( gamePosX / TMX_WIDTH );
    local mapY = math.floor( gamePosY / TMX_HEIGHT );
    TmxShowList[1] = { mapX, mapY };

    local index = 2;
    -- �ж�С���ͼ��Ե
    -- X��
    if localPosX < TmxShowThreshold then
        TmxShowList[index] = { mapX - 1, mapY };
        index = index + 1;
    elseif localPosX > TMX_WIDTH - TmxShowThreshold then
        TmxShowList[index] = { mapX + 1, mapY };
        index = index + 1;
    end
    
    -- Y��
    if localPosY < TmxShowThreshold then
        TmxShowList[index] = { mapX, mapY - 1 };
        index = index + 1;
    elseif localPosY > TMX_HEIGHT - TmxShowThreshold then
        TmxShowList[index] = { mapX, mapY + 1 };
        index = index + 1;
    end
    
    -- XY������
    if localPosX < TmxShowThreshold and localPosY < TmxShowThreshold then
        TmxShowList[index] = { mapX - 1, mapY - 1 };
        index = index + 1;
    elseif localPosX > TMX_WIDTH - TmxShowThreshold and localPosY > TMX_HEIGHT - TmxShowThreshold then
        TmxShowList[index] = { mapX + 1, mapY + 1 };
        index = index + 1;
    end    

    -- XY������
    if localPosX < TmxShowThreshold and localPosY > TMX_HEIGHT - TmxShowThreshold then
        TmxShowList[index] = { mapX - 1, mapY + 1 };
        index = index + 1;
    elseif localPosX > TMX_WIDTH - TmxShowThreshold and localPosY < TmxShowThreshold then
        TmxShowList[index] = { mapX + 1, mapY - 1 };
        index = index + 1;
    end

    -- ˢ�µ�ͼλ��
    local changed = false;
    for i = 1, 4, 1 do
        if TmxShowList[i] ~= 0 and TmxLastList[i] ~= 0 and TmxLastList[i][1] == TmxShowList[i][1] and TmxLastList[i][2] == TmxShowList[i][2] then
			
        elseif TmxShowList[i] ~= 0 then
            MapTmx[i]:SetActive( true );
			MapTmx[i].transform:Find( "road" ).gameObject:SetActive( true );
			local x = WorldMap.m_nMaxWidth * MAP_TILEWIDTH / 2 / 100 + MAP_TILEWIDTH * TMX_WIDTH * ( TmxShowList[i][1] - TmxShowList[i][2] - 1 ) / 2 / 100
			local y = - MAP_TILEHEIGHT * TMX_HEIGHT * ( TmxShowList[i][2] + TmxShowList[i][1] ) / 2 / 100;
			if x >= 511 and x <= 513 and y >= -257 and y <= -255 then
				MapTmx[i].transform:Find( "road" ).gameObject:SetActive( false ); -- �м�
			else
				MapTmx[i].transform:Find( "road" ).gameObject:SetActive( true );
			end
            MapTmx[i].transform.localPosition = Vector3.New( x, y, 0 );

            changed = true;
        else
            MapTmx[i]:SetActive( false );
            changed = true;
        end
    end

    if changed then
        TmxLastList = clone( TmxShowList );
    end
end
	
-- �����ͼ����
function WorldMap.Start( Prefab )
	-- ��ʼ�����ڵ�
	WorldMapPrefab	= Prefab;
    MapUnit.unitRoot = Prefab.transform:Find("MapUnitRoot");

	-- ��ȡ���
	MapTmxRoot				= WorldMapPrefab:GetComponent("Transform"):Find( "MapTmxRoot" );
	MapUnitRoot				= WorldMapPrefab:GetComponent("Transform"):Find( "MapUnitRoot" );
	MapLineRoot				= WorldMapPrefab:GetComponent("Transform"):Find( "MapLineRoot" );
	MapClickEffect			= WorldMapPrefab:GetComponent("Transform"):Find( "MapClickEffect" );
	MapClickMod				= WorldMapPrefab:GetComponent("Transform"):Find( "MapClickMod" );
	MapCamera				= WorldMapPrefab:GetComponent("Transform"):Find( "MapCamera" );
	
	-- ���ݵ�ͼ��С��̬����N*N��Tmx��ͼ
	local TmxMapPrefab = LoadPrefab( "TmxMap" );
--	local rownum = math.floor( WorldMap.m_nMaxWidth/TMX_WIDTH );
--	local colnum = math.floor( WorldMap.m_nMaxHeight/TMX_HEIGHT );
--	for j=1, colnum, 1 do
--		for i=1, rownum, 1 do
--			local tmx = GameObject.Instantiate( TmxMapPrefab );
--			tmx.transform:SetParent( MapTmxRoot );
--			tmx.transform.localScale = Vector3.one;
--			tmx.transform.localPosition = Vector3.New( (WorldMap.m_nMaxWidth*MAP_TILEWIDTH)/2/100 + (i-2)*TMX_WIDTH*MAP_TILEWIDTH/2/100 - (j-1)*TMX_WIDTH*MAP_TILEWIDTH/2/100,
--												   -(i-1)*TMX_HEIGHT*MAP_TILEHEIGHT/2/100 - (j-1)*TMX_HEIGHT*MAP_TILEHEIGHT/2/100, 0 );

--		end
--	end

    -- ֻʵ����4��
    for i = 1, 4, 1 do
        MapTmx[i] = GameObject.Instantiate( TmxMapPrefab );
		MapTmx[i].transform:SetParent( MapTmxRoot );
		MapTmx[i].transform.localScale = Vector3.one;
        MapTmx[i].gameObject:SetActive( false );
    end
    	
	-- �����������ʼλ��Ϊ�ҵĳǳ�
	WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY = WorldMap.ConvertGameToCamera( WorldMap.m_nMyCityPosx, WorldMap.m_nMyCityPosy );
	WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY = MapUnit.getGridTrans( MAPUNIT_TYPE_CITY, 0, WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY );
		
	if WorldMap.m_nLastGotoPosX >=0 and WorldMap.m_nLastGotoPosY >= 0 then
		WorldMap.CameraSetPosition( MAPUNIT_TYPE_CITY, WorldMap.m_nLastGotoPosX, WorldMap.m_nLastGotoPosY );
	else
		-- ��ת����ҳ�
		MapCamera.transform.position = Vector3.New( WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY, WORLDMAP_ZORDER_CAMERA );
	end
	
	-- ��ͼ�߽�
	--MapUnit.createMapBorder( 249, 250, 500, false );
	
	-- ����߽�
	for i=1, #g_zoneinfo, 1 do
		MapUnit.createMapBorder( g_zoneinfo[i].center_posx-1, g_zoneinfo[i].center_posy, 100 );
	end
	
	-- ���򶼳����ǵķ�Χ
	for k, v in pairs(g_towninfo) do
		if v.type >= 4 then
			if v.grid == 2 then
				MapUnit.createTownRange( v.grid, v.posx-1, v.posy, v.range );
			elseif v.grid == 3 then
				MapUnit.createTownRange( 2, v.posx-1, v.posy, v.range );
			end
		end
	end
	
	-- ��ʼ���о�·��
	MapMarchRoute.init( MapLineRoot );
	
	-- ��ʼ����ͼ��������
	MapTile.init();
	
	-- ��ʾ�����ͼ����
	MainDlgShowMap();
	
	-- ���ص�ͼ���ݸ�����һ��
	return WorldMap.m_nMaxWidth, WorldMap.m_nMaxHeight, MAP_TILEWIDTH, MAP_TILEHEIGHT
end


-- ���������=����Ϸ����(���θ�)
function WorldMap.ConvertCameraToGame( cameraPosX, cameraPosY )
	local screen_x = math.modf(cameraPosX * 100) - WorldMap.m_nMaxWidth/2 * MAP_TILEWIDTH;
	local screen_y = math.modf(cameraPosY * 100) + WorldMap.m_nMaxHeight/2 * MAP_TILEHEIGHT;
	local logic_ptx = math.modf(screen_x - math.modf(MAP_TILEWIDTH*screen_y/MAP_TILEHEIGHT));
	local logic_pty = -math.modf(screen_x + math.modf(MAP_TILEWIDTH*screen_y/MAP_TILEHEIGHT));
	if logic_ptx < 0 then
		logic_ptx = logic_ptx - MAP_TILEWIDTH;
	end
	if logic_pty < 0 then
		logic_pty = logic_pty - MAP_TILEWIDTH;
	end
	local gameCoorX = math.modf(logic_ptx/MAP_TILEWIDTH) + WorldMap.m_nMaxWidth/2;
	local gameCoorY = math.modf(logic_pty/MAP_TILEWIDTH) + WorldMap.m_nMaxHeight/2;
	return gameCoorX, gameCoorY 
end

-- ��Ϸ����(���θ�)=�����������
function WorldMap.ConvertGameToCamera( gameCoorX, gameCoorY )
    if gameCoorX == nil then
        return;
    end
	local px  = ( MAP_TILEWIDTH/2/100 ) * ( gameCoorX - gameCoorY );
    local py  = 0 -( MAP_TILEHEIGHT/2/100 ) * ( gameCoorX + gameCoorY );
	return px + WorldMap.m_nMaxWidth*MAP_TILEWIDTH/2/100, py
end

-- ��ӵ�Ԫ
function WorldMap.AddMapUnit( recvValue )
	-- �����ʾ����
	MapUnit.add( MapUnitRoot, recvValue );
	
	-- ��Ӹ�������
	MapTile.add( recvValue );
	
	-- ���յ����������ݲ��뻺��
	WorldMap.m_nMapUnitList[recvValue.m_unit_index] = recvValue;
	
	-- ��Ҫ��ת
	if WorldMap.m_nLastGotoUnitIndex == recvValue.m_unit_index then
		WorldMap.OnSelect( MapUnit.cache[recvValue.m_unit_index], recvValue.m_posx, recvValue.m_posy, recvValue.m_unit_index );
		WorldMap.m_nLastGotoUnitIndex = -1;
	end
end

-- �Ƴ���Ԫ
function WorldMap.DelMapUnit( recvValue )
	-- �Ƴ���ʾ����
	MapUnit.del( recvValue.m_unit_index )
	
	-- �Ƴ���������
	MapTile.del( WorldMap.m_nMapUnitList[recvValue.m_unit_index] )
	
	-- �Ƴ����յ��Ļ�������
	WorldMap.m_nMapUnitList[recvValue.m_unit_index] = nil;
	
	-- ���������ʾ��������
	if recvValue.m_unit_index == WorldMap.m_nLastTouchUnitIndex then
		WorldMap.OnClickClose();
		WorldMap.m_nLastTouchUnitIndex = -1;
	end
end

-- ���µ�Ԫ
function WorldMap.UpdateMapUnit( recvValue )
	-- ���֮ǰ�ǲ��ӣ�������פ��״̬�����ڲ�פ����
	--[[local oldCache = WorldMap.m_nMapUnitList[recvValue.m_unit_index];
	if oldCache ~= nil and oldCache.m_type == MAPUNIT_TYPE_ARMY then
		if oldCache.m_state == ARMY_STATE_OCCUPY and recvValue.m_state ~= ARMY_STATE_OCCUPY then
			-- �Ƴ���������
			MapTile.del( WorldMap.m_nMapUnitList[recvValue.m_unit_index] )
		end
	end--]]

	-- ���
	WorldMap.AddMapUnit( recvValue );
	
	-- ���������ʾ��������
	--[[if recvValue.m_unit_index == WorldMap.m_nLastTouchUnitIndex then
		WorldMap.OnClickClose();
		GatherInfoDlgClose();
		MonsterInfoDlgClose();
		if oldCache ~= nil and oldCache.m_type == MAPUNIT_TYPE_ARMY then
			WorldMap.m_nLastTouchUnitIndex = -1;
		end
	end--]]
end

-- �ƶ���Ԫ
function WorldMap.MoveMapUnit( recvValue )
	if WorldMap.m_nMapUnitList[recvValue.m_unit_index] == nil then
		return;
	end
	-- �Ƴ���������
	if WorldMap.m_nMapUnitList[recvValue.m_unit_index].m_type ~= MAPUNIT_TYPE_ARMY then
		MapTile.del( WorldMap.m_nMapUnitList[recvValue.m_unit_index] );
	end
    WorldMap.m_nMapUnitList[recvValue.m_unit_index].m_posx = recvValue.m_posx;
    WorldMap.m_nMapUnitList[recvValue.m_unit_index].m_posy = recvValue.m_posy;
	
	
	if WorldMap.m_nMapUnitList[recvValue.m_unit_index].m_type ~= MAPUNIT_TYPE_ARMY then
		-- ��Ӹ�������
		MapTile.add( WorldMap.m_nMapUnitList[recvValue.m_unit_index] );
		WorldMap.UpdateMapUnit( WorldMap.m_nMapUnitList[recvValue.m_unit_index] ); 
	end
end

-- �����ȡ�ĵ�Ԫ
function WorldMap.RandMapUnit( recvValue )
	-- ���յ����������ݲ��뻺��
	WorldMap.m_nMapUnitList[recvValue.m_unit_index] = recvValue;
	WorldMap.m_nLastTouchUnitIndex = recvValue.m_unit_index;
	if recvValue.m_type == MAPUNIT_TYPE_MONSTER then
		--MonsterInfoDlgOnClick( recvValue, true );
	elseif recvValue.m_type == MAPUNIT_TYPE_RES then
		WorldMap.GotoUnit( recvValue.m_unit_index );
	end
end

-- ֡�߼�
function WorldMap.Update()
	WorldMap.QueueFetchArmy();
	
	m_updateWaitFrame = m_updateWaitFrame + 1;
	if m_updateWaitFrame > 90 then
		if Queue.has( procQueue ) == false then
			--WorldMapDlgWaiting( false );
			return;
		end
	end

	-- һ֡����һ������
	WorldMap.QueueFetch();
end

--  ÿ��֪ͨ2��λ�ñ仯��-�����������
function WorldMap.ViewChangeSec()
    --if MainDlgCutSceneIsPlaying() then
        --return;
    --end

	local cameraPosX = MapCamera:GetComponent("Transform").position.x;
	local cameraPosY = MapCamera:GetComponent("Transform").position.y;


	-- ���������������
	local gameCoorX, gameCoorY = WorldMap.ConvertCameraToGame( cameraPosX, cameraPosY );
    WorldMap.RefreshShow( gameCoorX, gameCoorY );

	local now_areaindex = Area.GetIndex( gameCoorX, gameCoorY );
	if now_areaindex < 0 or now_areaindex == WorldMap.m_nLastAreaIndex then
		return
	end
	
	WorldMap.m_nLastAreaIndex = now_areaindex;
	WorldMap.SendAreaIndex( now_areaindex, gameCoorX, gameCoorY )
	--WorldMapDlgWaiting( true );
	m_updateWaitFrame = 0;
end

--  ÿ��֪ͨ30��λ�ñ仯��-�������ͷ�λ
function WorldMap.ViewChangeFrame()
    if MapCamera == nil then
        return;
    end
	local cameraPosX = MapCamera:GetComponent("Transform").position.x;
	local cameraPosY = MapCamera:GetComponent("Transform").position.y;
    
    m_LastPosX = cameraPosX;
    m_LastPosY = cameraPosY;
	
	-- λ��û�仯�Ͳ�������
	if cameraPosX == WorldMap.m_nLastCameraX and cameraPosY == WorldMap.m_nLastCameraY then
		return;
	end
	WorldMap.m_nLastCameraX = cameraPosX;
	WorldMap.m_nLastCameraY	= cameraPosY;
    -- ��������
	local gameCoorX, gameCoorY = WorldMap.ConvertCameraToGame( cameraPosX, cameraPosY );
    WorldMap.m_nLastCameraGameX = gameCoorX;
    WorldMap.m_nLastCameraGameY = gameCoorY;
	
	-- ���ƶ���Ϊ�͹ر�
	if MapClickEffect.gameObject.activeSelf == true or MapClickMod.gameObject.activeSelf == true then
		WorldMap.OnClickClose();
	end
	
	-- ���������������
	--MapClickModCoordinate( gameCoorX, gameCoorY );
	
	-- ���¼�ͷ����
    --WorldMap.UpdateArrow();
end

-- ���¼�ͷ����
function WorldMap.UpdateArrow()

    -- ��ͷλ��
	--[[local arrowPos = WorldMapDlgArrowPosition();
	-- �����Լ������뵱ǰ�ӿ����ĵķ�λ�;���
	local cityPos = cc.p( WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY );
	local cameraPos = cc.p( WorldMap.m_nLastCameraX, WorldMap.m_nLastCameraY );
	
	-- ת������Ϸ����
	local cityGameCoorX, cityGameCoorY = WorldMap.ConvertCameraToGame( WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY );
	local cameraGameCoorX, cameraGameCoorY = WorldMap.ConvertCameraToGame( WorldMap.m_nLastCameraX, WorldMap.m_nLastCameraY );
	
	-- ����
	local distance = math.sqrt( ( cameraGameCoorX - cityGameCoorX )*( cameraGameCoorX - cityGameCoorX ) + ( cameraGameCoorY - cityGameCoorY )*( cameraGameCoorY - cityGameCoorY ) );
	
	-- �Ƕ�
	local o = cameraPos.x + arrowPos.x - cityPos.x;
	local a = cameraPos.y + arrowPos.y - cityPos.y;
	local angle = math.deg( math.atan( o/a ) );
	if a < 0 then
		if o < 0 then
			angle = 180 + math.abs(angle);
		else
			angle = 180 - math.abs(angle);
		end 
	end
	
	WorldMapDlgOnDirectionArrow( distance, 180-angle, cc.p( WorldMap.m_nLastCameraGameX, WorldMap.m_nLastCameraGameY ) );--]]
end

-- ���������ͼ
function WorldMap.OnClick( obj, touchpos, unit_index )
	if MapClickEffect.gameObject.activeSelf == true or MapClickMod.gameObject.activeSelf == true then
		WorldMap.OnClickClose();
		return;
	end
	
	-- ��Ļ����ת������������
	local touchpos = Camera.main:ScreenToWorldPoint( touchpos );
	local gameCoorX, gameCoorY = WorldMap.ConvertCameraToGame( touchpos.x, touchpos.y );
    if gameCoorX < 0 or gameCoorX >= WorldMap.m_nMaxWidth or
       gameCoorY < 0 or gameCoorY >= WorldMap.m_nMaxHeight then
       return;
    end

    -- �����Ǩ��״̬��ȡ��Ǩ��
    --[[if MapCityMove.enable and unit_index == -1 then
        MapCityMove.close();
        return;
    end--]]
	
	-- ѡ��
	WorldMap.OnSelect( obj, gameCoorX, gameCoorY, unit_index );
end

-- ѡ��Ԫ
function WorldMap.OnSelect( unit, gameCoorX, gameCoorY, unit_index )
	--if WorldMap.m_nMode == WORLDMAP_MODE_MOVECITY then
		--return;
	--end
	if MapClickEffect.gameObject.activeSelf == true or MapClickMod.gameObject.activeSelf == true then
		WorldMap.OnClickClose();
	end

	-- ֻ��army�����д�����,����ֻ���ƶ��еĲ��ж���Ч
	--[[if unit_index >= 0 then
		local recvValue = WorldMap.m_nMapUnitList[unit_index];
		if recvValue ~= nil then
			if recvValue.m_type == MAPUNIT_TYPE_ARMY then
				if recvValue.m_state == ARMY_STATE_MARCH or recvValue.m_state == ARMY_STATE_REBACK then
                    -- ������Ч
                    
					-- ��¼�������ʾ��Ԫ����
					WorldMap.m_nLastTouchUnitIndex = unit_index;
					-- ��¼����Ĳ��ӵ�Ԫ����
					WorldMap.m_nLastTouchArmyIndex = recvValue.m_int_value[1];
					-- 	��������
					WorldMap.StartFollow( unit_index );
					return;
				end
			end
		end
	end--]]
	
	-- ��¼һ�µ�����������
	WorldMap.m_nLastTouchGameCoorX = gameCoorX;
	WorldMap.m_nLastTouchGameCoorY = gameCoorY;
	
	-- ��Ϸ��������ת�������������
	local cameraPosX = 0;
	local cameraPosY = 0;
	
	-- ����ĸ����Ƿ��л�������
	unit_index = MapTile.get( gameCoorX, gameCoorY );  

    -- ����
	if unit_index >= 0 then
		-- ��������
		local recvValue = WorldMap.m_nMapUnitList[unit_index];
		if recvValue == nil then
			return;
		end
		
		-- �����Դ��ɼ��ȼ�,�������ʾ
		--[[if recvValue.m_type == MAPUNIT_TYPE_RES then
			local limitlevel = recvValue.m_char_value[3];
			if GetCity().BuildingList[1].m_level < -limitlevel then
				Notify( 173, { -limitlevel, GetResNameByType( recvValue.m_char_value[1] ) } )
				return;
			end
		end--]]
	
		-- ��������
		local grid = 1;
		if recvValue.m_type == MAPUNIT_TYPE_TOWN then
			local townid 	= recvValue.m_short_value[1];
			local grid 		= g_towninfo[townid].grid
			grid = MapUnit.getGrid( recvValue.m_type, grid );
		else
			grid = MapUnit.getGrid( recvValue.m_type, 0 );
		end
		MapClickEffect.transform.localScale = Vector3.New( grid, grid, grid );
		-- ת����������
		cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( recvValue.m_posx, recvValue.m_posy );
		cameraPosX, cameraPosY = MapUnit.getGridTrans( recvValue.m_type, recvValue.m_grid, cameraPosX, cameraPosY );
	else
		-- ��������
		MapClickEffect.transform.localScale = Vector3.New( 1, 1, 1 );
		-- ת����������
		cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( gameCoorX, gameCoorY );
		cameraPosX, cameraPosY = MapUnit.getGridTrans( 0, 0, cameraPosX, cameraPosY );
	end
	
	-- ��¼�������ʾ��Ԫ����
	WorldMap.m_nLastTouchUnitIndex = unit_index;
	WorldMap.m_nLastTouchArmyIndex = -1;
	-- ѡ���
	MapClickEffect.transform.localPosition = Vector3.New( cameraPosX, cameraPosY, WORLDMAP_ZORDER_CLICKMOD );
	MapClickEffect.gameObject:SetActive( true );
	
	-- ��������
	local recvValue = WorldMap.m_nMapUnitList[unit_index];
	if recvValue then
		if recvValue.m_type == MAPUNIT_TYPE_ARMY then
			WorldMap.m_nLastTouchArmyIndex = recvValue.m_int_value[1];
		
		-- ����
		elseif recvValue.m_type == MAPUNIT_TYPE_TOWN then
			print( "MAPUNIT_TYPE_TOWN" )
			return
			
		-- Ұ��
		elseif recvValue.m_type == MAPUNIT_TYPE_ENEMY then
			MapClickEffect.gameObject:SetActive( false );
			MapEnemyDlgShow( recvValue )
			return;	
		
		-- ��Դ��		
		elseif recvValue.m_type == MAPUNIT_TYPE_RES then
			MapClickEffect.gameObject:SetActive( false );
			MapResDlgShow( recvValue )
			return;	
		
		-- ����¼�	
		elseif recvValue.m_type == MAPUNIT_TYPE_EVENT then
			MapClickEffect.gameObject:SetActive( false );
			MapEventDlgShow( recvValue )
			return
		end
	end
	
	-- ������
	MapClickMod.transform.localPosition = Vector3.New( cameraPosX, cameraPosY, WORLDMAP_ZORDER_CLICKMOD );
	MapClickMod.gameObject:SetActive( true );
end

-- �رղ�������
function WorldMap.OnClickClose()
	if MapClickEffect ~= nil and MapClickEffect.gameObject ~= nil then
		MapClickEffect.gameObject:SetActive( false );
	end
	if MapClickMod ~= nil and MapClickMod.gameObject ~= nil then
		MapClickMod.gameObject:SetActive( false );
	end
	WorldMap.StopFollow();
end

-- ������ק����
function WorldMap.OnDrag( touchpos )
	--MapCityMove.OnDrag( touchpos )
end

-- ���������λ��
function WorldMap.CameraSetPosition( unittype, gameCoorX, gameCoorY )
	-- λ��
    local cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( gameCoorX, gameCoorY );
	local posx, posy = MapUnit.getGridTrans( unittype, 0, cameraPosX, cameraPosY );
	if MapCamera then
		MapCamera.transform.position = Vector3.New( posx, posy, WORLDMAP_ZORDER_CAMERA );
		WorldMap.m_nLastCameraX 	 = posx;
		WorldMap.m_nLastCameraY		 = posy;
		WorldMap.m_nLastCameraGameX  = gameCoorX;
		WorldMap.m_nLastCameraGameY  = gameCoorY;
	end

    WorldMap.RefreshShow( gameCoorX, gameCoorY );
    
    m_LastPosX = nil;
    m_LastPosY = nil;
end

-- �����������
function WorldMap.TweenPosition( unittype, gameCoorX, gameCoorY, time )
	-- λ��
    local cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( gameCoorX, gameCoorY );
	local posx, posy = MapUnit.getGridTrans( unittype, 0, cameraPosX, cameraPosY );
	if MapCamera then
		MapCamera:GetComponent( "Camera2D" ):TweenPosTo( Vector3.New( posx, posy, WORLDMAP_ZORDER_CAMERA ), time );
		WorldMap.m_nLastCameraX 	 = posx;
		WorldMap.m_nLastCameraY		 = posy;
		WorldMap.m_nLastCameraGameX  = gameCoorX;
		WorldMap.m_nLastCameraGameY  = gameCoorY;
	end
end

-- ��ת��unitλ��
function WorldMap.GotoUnit( unit_index )
	local recvValue = WorldMap.m_nMapUnitList[unit_index];
	if recvValue == nil then
		system_askinfo( ASKINFO_WORLDMAP, "", 6, unit_index );
	else
		WorldMap.CameraSetPosition( recvValue.m_type, recvValue.m_posx, recvValue.m_posy );
		WorldMap.OnSelect( MapUnit.cache[unit_index], recvValue.m_posx, recvValue.m_posy, unit_index );
	end
    
    m_LastPosX = nil;
    m_LastPosY = nil;
end

-- ���������صĵ�unitλ��
function WorldMap.GotoUnitAsyn( recvValue )
	WorldMap.m_nLastGotoUnitIndex = recvValue.m_unit_index;
	WorldMap.CameraSetPosition( recvValue.m_type, recvValue.m_posx, recvValue.m_posy );
	--WorldMap.ViewChangeSec();
end

-- ��ת��λ��
function WorldMap.GotoCoor( gameCoorX, gameCoorY )
	if GameManager.currentScence == "city" then
		WorldMap.GotoWorldMap( gameCoorX, gameCoorY )
    elseif GameManager.currentScence == "worldmap" then
		WorldMap.CameraSetPosition( MAPUNIT_TYPE_CITY, gameCoorX, gameCoorY );
		--WorldMap.ViewChangeSec();
	end
    
    m_LastPosX = nil;
    m_LastPosY = nil;
end

-- �ҵĳǳ�
function WorldMap.GotoMyCity()
	WorldMap.GotoCoor( WorldMap.m_nMyCityPosx, WorldMap.m_nMyCityPosy )
end

-- �������������ģʽ
function WorldMap.StartFollow( unit_index )
    if WorldMap.m_nMode == WORLDMAP_MODE_NORMAL then
		local unit = MapUnit.cache[unit_index];
		if unit == nil then
			return;
		end
		
		-- �����������
		MapClickMod.gameObject:SetActive( true );	
        MapClickMod.transform:SetParent( unit.transform );
		MapClickMod.transform.localPosition = Vector3.New( 0, 0, WORLDMAP_ZORDER_CLICKMOD );
        MapClickMod.transform.localScale = Vector3.New( 0.01, 0.01, 1 );
		
		-- ���������
        local unitPos = unit.transform.position;
        MapCamera.transform.position= Vector3.New( unitPos.x, unitPos.y, WORLDMAP_ZORDER_CAMERA );
        MapCamera.transform:SetParent( unit.transform );
        MapCamera:GetComponent("WorldMapCamera").IsCanMoved = false;
		
		WorldMap.m_nMode = WORLDMAP_MODE_FOLLOW;
    end
end

-- �رո���ģʽ
function WorldMap.StopFollow()
    --if WorldMap.m_nMode == WORLDMAP_MODE_FOLLOW then
		-- ��������ֹͣ����
        MapClickMod.transform:SetParent( WorldMapPrefab.transform );
		MapClickMod.transform.localPosition = Vector3.New( 0, 0, WORLDMAP_ZORDER_CLICKMOD );
		
		-- �����ֹͣ����
        MapCamera.transform:SetParent( WorldMapPrefab.transform );
		--MapCamera:GetComponent("WorldMapCamera").IsCanMoved = true;
		
		WorldMap.m_nMode = WORLDMAP_MODE_NORMAL;
    --end
end

-- ����ѡ����Ч
function WorldMap.ClickEffect()
	return MapClickEffect
end
function WorldMap.MapClickMod()
	return MapClickMod;
end

-- ��ӵ���������
function WorldMap.QueueAdd( operation, recvValue )
	
	local unittype = 0;
	if operation == 1 then
		
		unittype = recvValue.m_type;
		
	elseif operation == 2 then
	
		local unit = WorldMap.m_nMapUnitList[recvValue.m_unit_index];
		if unit then
			unittype = unit.m_type;
		end
		
	elseif operation == 3 then
	
		unittype = recvValue.m_type;
		
	elseif operation == 4 then
	
		local unit = WorldMap.m_nMapUnitList[recvValue.m_unit_index];
		if unit then
			unittype = unit.m_type;
		end
		
	end
	
	if unittype == MAPUNIT_TYPE_ARMY then
		Queue.pushBack( procQueueArmy, { op=operation, value = recvValue } );		
	else
		Queue.pushBack( procQueue, { op=operation, value = recvValue } );
	end
	
	m_updateWaitFrame = m_updateWaitFrame - 1;
	if m_updateWaitFrame < 0 then
		m_updateWaitFrame = 0;
	end
end

-- ��մ�������
function WorldMap.QueueClear()
	Queue.clear( procQueue );
	Queue.clear( procQueueArmy );
end

-- ��������ȡ��һ��
function WorldMap.QueueFetch()
	
	-- ��ͨ����
	for tmpi=1, 6, 1 do
		local v = Queue.popFirst( procQueue );
		if v == nil then
			return;
		end
		if v.op == 1 then
			WorldMap.AddMapUnit( v.value );
		elseif v.op == 2 then
			WorldMap.DelMapUnit( v.value );
		elseif v.op == 3 then
			WorldMap.UpdateMapUnit( v.value );
		elseif v.op == 4 then
			WorldMap.MoveMapUnit( v.value );
		elseif v.op == 5 then
			MapMarchRoute.add( v.value );
		elseif v.op == 6 then
			MapMarchRoute.del( v.value );
		end
		m_updateWaitFrame = m_updateWaitFrame + 1;
	end
	
end

-- ��������ȡ��һ��
function WorldMap.QueueFetchArmy()
	
	-- ���Ӷ���
	for tmpi=1, 3, 1 do
		local v = Queue.popFirst( procQueueArmy );
		if v == nil then
			return;
		end
		if v.op == 1 then
			WorldMap.AddMapUnit( v.value );
		elseif v.op == 2 then
			WorldMap.DelMapUnit( v.value );
		elseif v.op == 3 then
			WorldMap.UpdateMapUnit( v.value );
		elseif v.op == 4 then
			WorldMap.MoveMapUnit( v.value );
		end
	end
	
end

-- �����о�ʱ��
function WorldMap.MarchTime(fposx, fposy, tposx, tposy)
    local distance = math.abs(fposx - tposx) + math.abs(fposy - tposy);
    local speed = global.army_move;
    if speed <= 0 then
        return 0;
    end
    local duration = math.floor(distance) * speed;
    duration = math.ceil(duration*( 1.0-GetPlayer().m_attr.m_movespeed_per[1]/100)*( 1.0-GetPlayer().m_attr.m_movespeed_per[2]/100)*( 1.0-GetPlayer().m_attr.m_movespeed_per[3]/100) );
    duration = math.max(duration, speed);
    return duration;
end

-- Ǩ�����
function WorldMap.OnCityMoved( unit_index, gameCoorX, gameCoorY )
	if GameManager.currentScence == "worldmap" then
		WorldMap.m_nMyCityUnitIndex = unit_index;
		WorldMap.m_nMyCityPosx = gameCoorX;
		WorldMap.m_nMyCityPosy = gameCoorY;
		WorldMap.CameraSetPosition( MAPUNIT_TYPE_CITY, gameCoorX, gameCoorY );	
		WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY = WorldMap.ConvertGameToCamera( WorldMap.m_nMyCityPosx, WorldMap.m_nMyCityPosy );
		WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY = MapUnit.getGridTrans( MAPUNIT_TYPE_CITY, 0, WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY );
		WorldMap.UpdateArrow();
		GetPlayer().m_posx = gameCoorX;
		GetPlayer().m_posy = gameCoorY;

        -- ��Ч
        --local obj = GameObject.Instantiate( LoadPrefab( "Effect_City_Change_Position_Smoke" ) );
        --obj.transform.position = Vector3.New( WorldMap.m_nMyCityCameraX, WorldMap.m_nMyCityCameraY, WorldMap.m_nMyCityCameraY );
        --GameObject.Destroy( obj, 5 );
	end
end

-- ��������
function WorldMap.GetCamera()
    return MapCamera;
end

-- ����UI
function WorldMap.UIFade( fade )
    --if m_Faded == fade then
        --return;
    --end
    --m_Faded = fade;
    --local tween = fruit.uiManager:GetLayer( 0 ):GetComponent( UITweenFade.GetClassType() );
    --tween:Play( fade );
    --fruit.uiManager:GetLayer( 0 ):GetComponent( "CanvasGroup" ).blocksRaycasts = fade == false;
    -- MainDlgGetClubBtn().gameObject:SetActive( fade == false );
end