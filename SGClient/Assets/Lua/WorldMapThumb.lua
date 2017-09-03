-- �����ͼ����ͼ

WorldMapThumb = {};
WorldMapThumb.m_nMaxWidth 	= 1280;
WorldMapThumb.m_nMaxHeight 	= 640;
WorldMapThumb.m_nZoneID = 0;
WorldMapThumb.m_nLastClickGameCoorX = -1;
WorldMapThumb.m_nLastClickGameCoorY = -1;
-- �����ʾ
WorldMapThumb.clickEffectObj = nil;

-- ��ͼ����ͼ
local WorldMapThumbObject = nil;

-- ��ͼ����ͼ�������
local WorldMapThumbPrefab	= nil;	-- ��ͼ��
local ThumbDisplayPrefab	= nil;	-- ��ͼ��ʾ��
local ThumbCamera			= nil;	-- ��ͼ�����
local ThumbDisplayTownPrefab= nil;

local ThumbInfoCache = nil;

-- ֻ����ʾ���� 
function WorldMapThumb.Show( bShow )
	if WorldMapThumbObject ~= nil then
		WorldMapThumbObject:SetActive( bShow );
	end
end

-- ����
function WorldMapThumb.Create( zoneid )
	WorldMapThumb.m_nZoneID = zoneid
	WorldMapThumbObject = GameObject.Instantiate( LoadPrefab("WorldMapThumb") );
	--fruit.scenceManager.worldMapScence.gameObject:SetActive( false );

    --MainDlgClose();
    --fruit.audioManager:Play(71);
	-- ע�͵�����ֹȥ����ͼ�󷵻ش��ͼ������ʾ����ȷ
    --WorldMapDlgClose(); 
end

-- ����
function WorldMapThumb.Delete()
	if WorldMapThumbObject ~= nil then
		GameObject.Destroy( WorldMapThumbObject );
		WorldMapThumbObject = nil;
	end
	ThumbMaskPrefab		= nil;	
	ThumbDisplayPrefab	= nil;
	ThumbCamera			= nil;
	--fruit.scenceManager.worldMapScence.gameObject:SetActive( true );
	ThumbInfoCache = nil;
	WorldMapThumb.clickEffectObj = nil;
    --fruit.audioManager:Play(72);
    --MainDlgPlayBGM(true);
    --MainDlgOpen();
    --WorldMapDlgOpen();
end

-- �����ͼ����ͼ����
function WorldMapThumb.Start( Prefab )
	-- ��ʼ�����ڵ�
	WorldMapThumbPrefab	= Prefab;
	ThumbDisplayPrefab	= WorldMapThumbPrefab:GetComponent("Transform"):Find( "Display" );
	ThumbCamera			= WorldMapThumbPrefab:GetComponent("Transform"):Find( "ThumbCamera" );

	if WorldMapThumb.clickEffectObj == nil then
		WorldMapThumb.clickEffectObj = GameObject.Instantiate( LoadPrefab("ThumbClickEffect") );
		WorldMapThumb.clickEffectObj.transform:SetParent( ThumbDisplayPrefab );
	end
	
	-- ��ʾ���Լ���λ��
	--WorldMapThumb.SetMyPos();
	
	-- ��ʾ��ǰλ��
	--local thumbX, thumbY = WorldMapThumb.ConvertMapToThumb( WorldMap.m_nLastCameraGameX, WorldMap.m_nLastCameraGameY )
	--WorldMapThumb.SetCurPos( thumbX, thumbY );
	
	-- ��ȡ������Ϣ
	--system_askinfo( ASKINFO_WORLDMAP, "", 10 );
	
	-- ͨ���������ó�����Ϣ
	--WorldMapThumb.SetTownPos( WorldMap.m_cacheTown );
end

-- ����ͼ���꣨�������=��������ͼ����(���θ�)
function WorldMapThumb.ConvertThumbToZone( thumbX, thumbY )
	local worldCameraX = thumbX * (WorldMap.m_nMaxWidth * MAP_TILEWIDTH) / WorldMapThumb.m_nMaxWidth;
	local worldCameraY = thumbY * (WorldMap.m_nMaxHeight * MAP_TILEHEIGHT) / WorldMapThumb.m_nMaxHeight;
	
	local gameCoorX, gameCoorY = WorldMap.ConvertCameraToGame( worldCameraX, worldCameraY );
	gameCoorX = WorldMap.m_nMaxWidth + gameCoorX;
	
	gameCoorX = math.floor(gameCoorX/5) + g_zoneinfo[WorldMapThumb.m_nZoneID].top_left_posx;
	gameCoorY = math.floor(gameCoorY/5) + g_zoneinfo[WorldMapThumb.m_nZoneID].top_left_posy;
	print( gameCoorX ..","..gameCoorY )
	return gameCoorX, gameCoorY;
end

-- ���ͼ����(���θ�)=������ͼ���꣨�������
function WorldMapThumb.ConvertMapToThumb( gameCoorX, gameCoorY )
	local cameraPosX, cameraPosY = WorldMap.ConvertGameToCamera( gameCoorX, gameCoorY );
	local thumbX = cameraPosX/ ((WorldMap.m_nMaxWidth * MAP_TILEWIDTH) / WorldMapThumb.m_nMaxWidth) - WorldMapThumb.m_nMaxWidth/2/100;
	local thumbY = cameraPosY/ ((WorldMap.m_nMaxHeight * MAP_TILEHEIGHT) / WorldMapThumb.m_nMaxHeight) + WorldMapThumb.m_nMaxHeight/2/100;
	return thumbX, thumbY;
end

-- ���������ͼ
function WorldMapThumb.OnClick( obj, touchpos )
	if obj == nil then
		print("obj == nil")
		return;
	end
	local gameCoorX = -1; 
	local gameCoorY = -1;
	local shareData = obj:GetComponent("ShareData");
	if shareData and ThumbInfoCache then
		local posType = tonumber( shareData:GetValue( "PosType" ) );
		local posIndex = tonumber( shareData:GetValue( "PosIndex" ) );
		-- ����������Լ�λ��
		if posType == 1 then
			gameCoorX = WorldMap.m_nMyCityPosx;
			gameCoorY = WorldMap.m_nMyCityPosy;

		-- �����������λ��
		elseif posType == 2 then
			gameCoorX = ThumbInfoCache.m_leader_pos.m_posx;
			gameCoorY = ThumbInfoCache.m_leader_pos.m_posy;
			
		-- ����������˳�Աλ��		
		elseif posType == 3 then
			gameCoorX = ThumbInfoCache.m_member_pos[posIndex].m_posx;
			gameCoorY = ThumbInfoCache.m_member_pos[posIndex].m_posy;
		
		-- ����������˽���λ��		
		elseif posType == 4 then
			gameCoorX = ThumbInfoCache.m_building_pos[posIndex].m_posx;
			gameCoorY = ThumbInfoCache.m_building_pos[posIndex].m_posy;
		
		-- ������ǳ���λ��		
		elseif posType == 5 then
			if WorldMap.m_cacheTown then
				gameCoorX = WorldMap.m_cacheTown.m_list[posIndex].m_posx;
				gameCoorY = WorldMap.m_cacheTown.m_list[posIndex].m_posy;
			end
		end	
		if gameCoorX < 0 or gameCoorY < 0 then
			gameCoorX = 480;
			gameCoorY = 480;
		end
		touchpos.x, touchpos.y = WorldMapThumb.ConvertMapToThumb( gameCoorX, gameCoorY );
		
	else
		
		-- ��Ļ����ת������������
		touchpos = ThumbCamera:GetComponent("Camera"):ScreenToWorldPoint( touchpos );
		touchpos = obj.transform:InverseTransformPoint( touchpos );
		-- ����ͼת���ͼ����
		gameCoorX, gameCoorY = WorldMapThumb.ConvertThumbToZone( touchpos.x, touchpos.y );
	end
	
	if gameCoorX < 0 or gameCoorX >= WorldMap.m_nMaxWidth or
		gameCoorY < 0 or gameCoorY >= WorldMap.m_nMaxHeight then
		return;
	end	
	
	-- ˫��λ��
	if gameCoorX >= WorldMapThumb.m_nLastClickGameCoorX - 2 and gameCoorX <= WorldMapThumb.m_nLastClickGameCoorX + 2 and
		gameCoorY >= WorldMapThumb.m_nLastClickGameCoorY - 2 and gameCoorY <= WorldMapThumb.m_nLastClickGameCoorY + 2 then
		-- �رս���
		MapZoneDlgClose();
		-- ��ת��λ��
		WorldMap.GotoCoor( WorldMapThumb.m_nLastClickGameCoorX, WorldMapThumb.m_nLastClickGameCoorY )
	else
		WorldMapThumb.m_nLastClickGameCoorX = gameCoorX;
		WorldMapThumb.m_nLastClickGameCoorY = gameCoorY;
		-- �����ʾ
		WorldMapThumb.SetCurPos( touchpos.x, touchpos.y );
	end
		
	
	
	-- ������ƶ�
	--ThumbCamera:GetComponent("WorldMapThumbCamera"):TweenPosTo( Vector3.New( touchpos.x, touchpos.y, 0 ), 0.5 );
	--ThumbCamera:GetComponent("WorldMapThumbCamera"):TweenSizeTo( 1, 0.5 );
	--Invoke( WorldMapThumb.Goto, 0.5, Vector3.New( gameCoorX, gameCoorY, 0 ) );
	
end

-- ������ק����
function WorldMapThumb.OnDrag( touchpos )
end

-- ��ת
function WorldMapThumb.Goto( gameCoor )
	WorldMapThumb.Delete();
	WorldMap.CameraSetPosition( 0, gameCoor.x, gameCoor.y );
end

-- ��ʾ��ǰλ��
function WorldMapThumb.SetCurPos( x, y )
	-- �����ʾ
	if WorldMapThumb.clickEffectObj == nil then
		WorldMapThumb.clickEffectObj = GameObject.Instantiate( LoadPrefab("ThumbClickEffect") );
		WorldMapThumb.clickEffectObj.transform:SetParent( ThumbDisplayPrefab );
	end
	WorldMapThumb.clickEffectObj.transform.localPosition = Vector3.New( x, y, -1 );
end

-- �������Լ���λ��
function WorldMapThumb.SetMyPos()
	local thumbX, thumbY = WorldMapThumb.ConvertMapToThumb( WorldMap.m_nMyCityPosx, WorldMap.m_nMyCityPosy );
	local thumbObj = GameObject.Instantiate( LoadPrefab("ThumbDisplayMy") );
	thumbObj.transform:SetParent( ThumbDisplayPrefab );
	thumbObj.transform.localPosition = Vector3.New( thumbX, thumbY, 0 );
	thumbObj.transform:GetComponent("ShareData"):AddValue( "PosType", 1 );
		
	Invoke( function()
        if ThumbCamera ~= nil then
		    ThumbCamera:GetComponent("WorldMapThumbCamera"):TweenPosToInBound( Vector3.New( thumbX, thumbY, 0 ), 0.5 );
        end
	end, 0.1 )
end

-- ��������λ����Ϣ
function WorldMapThumb.SetOtherPos( recvValue )
	ThumbInfoCache = recvValue;
	WorldMapThumb.SetClubLeaderPos( recvValue );
	WorldMapThumb.SetClubMemberPos( recvValue );
	WorldMapThumb.SetClubBuildingPos( recvValue );
end

-- ����������λ��
function WorldMapThumb.SetClubLeaderPos( recvValue )
	if ThumbDisplayPrefab == nil then
		return;
	end
	if recvValue.m_leader_pos.m_posx <= 0 and recvValue.m_leader_pos.m_posy <= 0 then
		return;
	end
	local thumbX, thumbY = WorldMapThumb.ConvertMapToThumb( recvValue.m_leader_pos.m_posx, recvValue.m_leader_pos.m_posy );
	local thumbObj = GameObject.Instantiate( LoadPrefab("ThumbDisplayClubLeader") );
	thumbObj.transform:SetParent( ThumbDisplayPrefab );
	thumbObj.transform.localPosition = Vector3.New( thumbX, thumbY, 0 );
	thumbObj.transform:GetComponent("ShareData"):AddValue( "PosType", 2 );
end

-- �����˳�Ա��λ��
function WorldMapThumb.SetClubMemberPos( recvValue )
	if ThumbDisplayPrefab == nil then
		return;
	end
	for tmpi=1, recvValue.m_member_count, 1 do
		if recvValue.m_member_pos[tmpi].m_posx >= 0 and recvValue.m_member_pos[tmpi].m_posy >= 0 then
			local thumbX, thumbY = WorldMapThumb.ConvertMapToThumb( recvValue.m_member_pos[tmpi].m_posx, recvValue.m_member_pos[tmpi].m_posy );
			local thumbObj = GameObject.Instantiate( LoadPrefab("ThumbDisplayClubMember") );
			thumbObj.transform:SetParent( ThumbDisplayPrefab );
			thumbObj.transform.localPosition = Vector3.New( thumbX, thumbY, 0 );
			thumbObj.transform:GetComponent("ShareData"):AddValue( "PosType", 3 );
			thumbObj.transform:GetComponent("ShareData"):AddValue( "PosIndex", tmpi );
		end
	end
end

-- �������˽�����λ��
function WorldMapThumb.SetClubBuildingPos( recvValue )
	if ThumbDisplayPrefab == nil then
		return;
	end
	for tmpi=1, recvValue.m_building_count, 1 do
		local thumbX, thumbY = WorldMapThumb.ConvertMapToThumb( recvValue.m_building_pos[tmpi].m_posx, recvValue.m_building_pos[tmpi].m_posy );
		local thumbObj = GameObject.Instantiate( LoadPrefab("ThumbDisplayClubBuilding") );
		thumbObj.transform:SetParent( ThumbDisplayPrefab );
		thumbObj.transform.localPosition = Vector3.New( thumbX, thumbY, 0 );
		thumbObj.transform:GetComponent("ShareData"):AddValue( "PosType", 4 );
		thumbObj.transform:GetComponent("ShareData"):AddValue( "PosIndex", tmpi );
	end
end

-- ���ó����λ��
function WorldMapThumb.SetTownPos( recvValue )
	if recvValue == nil then
		system_askinfo( ASKINFO_WORLDMAP, "", 14 );
		return;
	end
	if ThumbDisplayPrefab == nil then
		return;
	end
	for tmpi=1, recvValue.m_count, 1 do
		-- ��ʱҪ������ʾ
		if recvValue.m_list[tmpi].m_townid < 8 then
			local thumbX, thumbY = WorldMapThumb.ConvertMapToThumb( recvValue.m_list[tmpi].m_posx, recvValue.m_list[tmpi].m_posy );

            -- ����/����
            if recvValue.m_list[tmpi].m_townid == 1 then
                ThumbDisplayPrefab:FindChild( "ThumbDisplayMain" ):GetComponent("ShareData"):AddValue( "PosType", 5 );
                ThumbDisplayPrefab:FindChild( "ThumbDisplayMain" ):GetComponent("ShareData"):AddValue( "PosIndex", tmpi );
            else

--			    if ThumbDisplayTownPrefab == nil then
--				    ThumbDisplayTownPrefab = LoadPrefab("ThumbDisplayTown");
--			    end
--			    local thumbObj = GameObject.Instantiate( ThumbDisplayTownPrefab );
--			    thumbObj.transform:SetParent( ThumbDisplayPrefab );
--			    thumbObj.transform.localPosition = Vector3.New( thumbX, thumbY, 0 );
--			    thumbObj.transform:GetComponent("ShareData"):AddValue( "PosType", 5 );
--			    thumbObj.transform:GetComponent("ShareData"):AddValue( "PosIndex", tmpi );

--                if recvValue.m_list[tmpi].m_townid  < 8 then
--                    thumbObj.transform:FindChild( "Icon" ):GetComponent( "SpriteRenderer" ).sprite = GetResSpriteByType( 3 );
--                else
--                    thumbObj.transform:FindChild( "Icon" ):GetComponent( "SpriteRenderer" ).sprite = GetResSpriteByType( 2 );
--                end
            end
		end
	end
end

-- ��ʾ�ر��ɰ�
function WorldMapThumb.MaskVisible( visible )
	if ThumbMaskPrefab then
		ThumbMaskPrefab.gameObject:SetActive( visible );
	end
end