-- �����ͼ�о�·��

-- �о�·����ԴͼƬ��Ϣ
local MarchRouteSpriteWidth = 0.28/2;
local MarchRouteSpriteHeight = 0.66/2;

-- ·�߼���
MapMarchRoute = {};

-- ����
MapMarchRoute.cache = {};

-- �о�·��Prefab
MapMarchRoute.prefab = nil;

-- ���ڵ�
MapMarchRoute.root = nil;

-- ·�߶����
MapMarchRoute.objectPool = {};

-- ��ʼ��
function MapMarchRoute.init( MapLineRoot )
	MapMarchRoute.root = MapLineRoot;
	MapMarchRoute.prefab = LoadPrefab( "MarchRoute" );
end

-- ���
function MapMarchRoute.clear()
	MapMarchRoute.cache = {};
	MapMarchRoute.objectPool = {};
end

-- ����о�·��
function MapMarchRoute.add( recvValue )
	
	-- ������
	local cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( recvValue.m_from_posx, recvValue.m_from_posy );
	local fposx, fposy = MapUnit.getGridTrans( recvValue.m_from_type, recvValue.m_from_index, cameraPosX, cameraPosY );
	
	-- Ŀ�ĵ�
	cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( recvValue.m_to_posx, recvValue.m_to_posy );
	local tposx, tposy = MapUnit.getGridTrans( recvValue.m_to_type, recvValue.m_to_index, cameraPosX, cameraPosY );

	-- �����ߵ���ɫ
	local color = 0;
	if recvValue.m_action == ARMY_ACTION_GROUP_START and recvValue.m_state == ARMY_STATE_GROUP_START then 
		-- ���𼯽��в��һ�û��ʼ�ƶ�
		if recvValue.m_from_cityid == GetCity().m_cityid then
			color = 3;
		elseif recvValue.m_from_clubid > 0 and recvValue.m_from_clubid == GetCity().m_clubid then
			color = 3;
		elseif recvValue.m_to_cityid == GetCity().m_cityid then
			color = 2;
		elseif recvValue.m_to_clubid > 0 and recvValue.m_to_clubid == GetCity().m_clubid then
			color = 2;
		end
	else
		if recvValue.m_from_cityid == GetCity().m_cityid then
			color = 1;
		elseif recvValue.m_from_clubid > 0 and recvValue.m_from_clubid == GetCity().m_clubid then
			color = 1;
		elseif recvValue.m_to_cityid == GetCity().m_cityid and ( recvValue.m_action == ARMY_ACTION_FIGHT or recvValue.m_action == ARMY_ACTION_BESIEGED ) then
			color = 2;
		elseif recvValue.m_to_clubid > 0 and recvValue.m_to_clubid == GetCity().m_clubid then
			color = 2;
		end
	end
	
	-- ������������У���ô�͸���
	local obj = MapMarchRoute.draw( MapMarchRoute.cache[recvValue.m_army_index], Vector3.New( fposx, fposy, 0 ), Vector3.New( tposx, tposy, 0 ), recvValue.m_state, color, MapMarchRoute.root )
	
	-- ���뻺��
	-- �����������Ա�ɾ��
	if obj ~= nil then
		obj.gameObject:SetActive( true );
		MapMarchRoute.cache[recvValue.m_army_index] = obj;
	end
end

-- ɾ���о�·��
function MapMarchRoute.del( army_index )
	if  MapMarchRoute.cache[army_index] == nil then
		return;
	end
	
	local obj = MapMarchRoute.cache[army_index];
	if obj ~= nil then
		obj.gameObject:SetActive( false );
		MapMarchRoute.cache[army_index] = nil; 
	end
	
end

-- �����о�·��
function MapMarchRoute.draw( obj, from, to, state, color, parent )
	if obj == nil then
		
		-- �ڻ��������һ���Ѿ������õģ����þ�OK
		for index, unit in pairs( MapMarchRoute.objectPool ) do
			if unit and unit.gameObject.activeSelf == false then
				obj = unit;
				break;
			end
		end
		
		-- û�п���ľ��´���һ��
		if obj == nil then
			obj = GameObject.Instantiate( MapMarchRoute.prefab );
			obj.transform:SetParent( MapMarchRoute.root );
			table.insert( MapMarchRoute.objectPool, obj );
		end
	
	end
	
	local plane = obj:GetComponent( "GizmoPlane" );
	-- �෴
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
		plane:SetColor( Color.green );
    elseif color == 2 then
        plane:SetColor( Color.red );
	elseif color == 3 then
        plane:SetColor( Color.yellow );
	else
		plane:SetColor( Color.white );
	end
	plane:Set();
	return obj;
end
