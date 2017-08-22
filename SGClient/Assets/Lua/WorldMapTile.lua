-- �����ͼ��������

-- ���Ӽ���
MapTile = {};

-- ��������
MapTile.data = {};

-- tiledmap����
MapTile.tiledMap = {};

-- ��ͻ����
MapTile.clash = {};

-- ��ʼ��
function MapTile.init()
	MapTile.tiledMap = require("logic/mapdata");
end

-- ��������������
function MapTile.add( recvValue )
	-- ֻ��פ���Ĳ��Ӳ����
	if recvValue.m_type == MAPUNIT_TYPE_ARMY then
		if recvValue.m_state ~= ARMY_STATE_OCCUPY then
			return;
		end
	end
	
	local posx = recvValue.m_posx;
	local posy = recvValue.m_posy;
	local unittype = recvValue.m_type;
	local grid = MapUnit.getGrid( MapUnit.typeTotype( recvValue ) );
	
	-- ռ1*1���ӵ����
	if grid == 1 then
		local x = posx;
		local y = posy;
		if MapTile.data[x] == nil then
			MapTile.data[x] = {};
		end
		if MapTile.data[x][y] == nil then 
			MapTile.data[x][y] = {};
		end
		MapTile.data[x][y]["unit_index"] = recvValue.m_unit_index;
	
	-- ռ2*2���ӵ����
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
			MapTile.data[x][y]["unit_index"] = recvValue.m_unit_index;
		end
		
	-- ռ3*3���ӵ����
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
			MapTile.data[x][y]["unit_index"] = recvValue.m_unit_index;
		end
	end
	
	-- ���ó�ͻ����
	if recvValue.m_type == MAPUNIT_TYPE_CLUB_TOWN then
		
	end
end

-- ɾ����������
function MapTile.del( recvValue )
	if recvValue == nil then
		return;
	end
	local info = clone(recvValue);
	info.m_unit_index = -1;
	MapTile.add( info )
end

-- �������
function MapTile.clear()
	MapTile.data = {};
end

-- ��ȡ����ĸ�������
function MapTile.get( posx, posy )
	
	-- ����ѡ�������ӣ����û�ж�����ӣ�����ͼ�赲����
	if MapTile.data[posx] == nil or MapTile.data[posx][posy] == nil then
		if MapTile.block( posx, posy ) < 0 then
			return -2;
		end
		return -1;
	end

	return MapTile.data[posx][posy]["unit_index"];
end

-- ��ͼ�赲
function MapTile.block( posx, posy )    
    -- ��Χ
	if posx < 0 or posy < 0 or posx >= 960 or posy >= 960 then
		return -1;
	end
	
	-- ��������
	if posx >= 477 and posx <= 483 and posy >= 477 and posy <= 483 then
		return -1;
	end
	
	-- ����������Ĭ��û���赲����
	if posx >= 455 and posx <= 505 and posy >= 455 and posy <= 505 then
		return 0;
	end
	
	-- ��ת����һС���ͼ�����꣬��Ϊ��ͼ��N*N��ƴ������
	local localposx = math.floor( math.mod( posx, TMX_WIDTH ) );
	local localposy = math.floor( math.mod( posy, TMX_HEIGHT ) );

	local index = localposx + localposy*TMX_HEIGHT + 1;
	
	-- �ر������
	local groundData = MapTile.tiledMap.layers[1].data[index];
	if groundData == nil then
		return -1;
	end
	
	-- �ر������
	local groundData = MapTile.tiledMap.layers[1].data[index];
	if groundData >= 17 and groundData <= 46 or 
	   groundData >= 65 and groundData <= 77 or 
	   groundData >= 79 and groundData <= 84 or 
	   groundData >= 86 and groundData <= 105 or 
	   groundData == 109 or 
	   groundData == 110 then
		return -1;
	end
	
	-- װ�β�����
	local decorateData1 = MapTile.tiledMap.layers[2].data[index];
	if decorateData1 >= 17 and decorateData1 <= 46 or 
	   decorateData1 >= 65 and decorateData1 <= 77 or 
	   decorateData1 >= 79 and decorateData1 <= 84 or 
	   decorateData1 >= 86 and decorateData1 <= 104 or 
	   decorateData1 == 109 or 
	   decorateData1 == 110 then
		return -1;
	end
	
	local decorateData2 = MapTile.tiledMap.layers[3].data[index];
	if decorateData2 >= 17 and decorateData2 <= 46 or 
	   decorateData2 >= 65 and decorateData2 <= 77 or 
	   decorateData2 >= 79 and decorateData2 <= 84 or 
	   decorateData2 >= 86 and decorateData2 <= 104 or 
	   decorateData2 == 109 or 
	   decorateData2 == 110 then
		return -1;
	end
	
	return 0;
end

function MapTile.addclash( x, y, r, v )
	local range = 2*r+1;
	for i=0, range, 1 do
		for j=0, range, 1 do
			local x_index = x-r+i;
			local y_index = y-r+j;
			
			if MapTile.clash[x_index] == nil then
				MapTile.clash[x_index] = {};
			end
			if MapTile.clash[x_index][y_index] == nil then
				MapTile.clash[x_index][y_index] = {};
			end
			
			MapTile.clash[x_index][y_index] = v;
		end
	end 
	
end
