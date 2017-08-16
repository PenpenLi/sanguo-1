City = {};
City.m_CameraMain = nil;
City.m_Camera = nil;
City.m_LastSelect = nil;
City.m_BuildingRoot = nil
City.m_BuildingUI = nil
City.m_BuildingTimerMod = nil;
City.m_BuildingFreeMod = nil;
City.m_BuildingOverMod = nil;
City.m_BuildingQuestMod = nil;
City.m_Buildings = {};
City.m_Buildings_res = {};

-- ��ʼ��
function City.Init()
	City.m_Camera = GameManager.MainCity.transform:Find("CityCamera"):GetComponent("CityCamera");
	City.m_CameraMain = GameManager.MainCity.transform:Find("CityCamera"):GetComponent("Camera");
	City.m_BuildingUI = GameManager.MainCity.transform:Find( "BuildingUI" );
	City.m_BuildingTimerMod = GameManager.MainCity.transform:Find( "BuildingUI/BuildingTimerMod" );
	City.m_BuildingFreeMod = GameManager.MainCity.transform:Find( "BuildingUI/BuildingFreeMod" );
	City.m_BuildingOverMod = GameManager.MainCity.transform:Find( "BuildingUI/BuildingOverMod" );
	City.m_BuildingQuestMod = GameManager.MainCity.transform:Find( "BuildingUI/BuildingQuestMod" );
end

-- ���н������ڵ�
function City.BuildingRoot()
	if City.m_BuildingRoot == nil then
		City.m_BuildingRoot = GameManager.MainCity.transform:Find( "Content/Buildings" );
	end
	return City.m_BuildingRoot;
end

-- ѡ����
function City.BuildingSelect( transform )
	if City.m_LastSelect ~= nil then
		-- �����ͬ����ֱ�ӷ���
		--if City.m_LastSelect == transform then
			--return;
		--end
		-- �ر�֮ǰ���䶯��
		--City.m_LastSelect:GetComponent("UITweenColor"):Kill(true);
		City.m_LastSelect = nil;
	end
	
	local building = nil;	
	if transform == nil then
		BuildingOpratorModShow( false, 0, -1, nil );
		return;
	else

		City.m_LastSelect = transform;
		--City.m_LastSelect:GetComponent("UITweenColor"):Play(true);
		building = transform:GetComponent("CityBuilding");
		City.m_Camera:TweenPosToInBound( transform.position, 0.2 );
	end
	
	-- �򿪼��ٽ���	
	if GetPlayer().m_worker_kind == building.kind and GetPlayer().m_worker_offset == building.offset or 
		GetPlayer().m_worker_kind_ex == building.kind and GetPlayer().m_worker_offset_ex == building.offset then
		if GetPlayer().m_worker_kind == building.kind then
			QuickItemDlgShow( 1, building.kind, building.offset, GetPlayer().m_worker_sec );
		else
			QuickItemDlgShow( 1, building.kind, building.offset, GetPlayer().m_worker_sec_ex );
		end
	else
		BuildingOpratorModShow( false, 0, -1, nil );
		if building.kind == BUILDING_Smithy then -- ������
			-- ��������ɵģ�ֱ����ȡ
			if GetPlayer():BuildingOverValue( building.kind ) > 0 then
				City.BuildingHideOver( building.kind )
				system_askinfo( ASKINFO_EQUIPFORGING, "", 4 );
			else
				EquipForgingDlgShow();
			end
		elseif building.kind == BUILDING_Wash then -- ϴ����
			EquipWashDlgShow();
		elseif building.kind == BUILDING_Fangshi then -- ����
			
		elseif building.kind == BUILDING_Shop then -- �̵�
			
		elseif building.kind == BUILDING_Hero then -- ���͹�
			HeroListDlgShow();
			
		elseif building.kind == BUILDING_Wishing then -- �۱���

		elseif building.kind == BUILDING_Help then -- ����
		
		else
			-- �Ƽ�����ɵģ�ֱ����ȡ
			if building.kind == BUILDING_Tech and GetPlayer():BuildingOverValue( building.kind ) > 0 then
				City.BuildingHideOver( building.kind )
				system_askinfo( ASKINFO_TECH, "", 4 );
			
			-- ���Ϲ�������ɵģ�ֱ����ȡ
			elseif building.kind == BUILDING_Craftsman and GetPlayer():BuildingOverValue( building.kind ) > 0 then
				system_askinfo( ASKINFO_MATERIALMAKE, "", 4 );
				
 			-- ļ������ɵģ�ֱ����ȡ
			elseif building.kind >= BUILDING_Infantry and building.kind <= BUILDING_Militiaman_Archer and GetPlayer():BuildingOverValue( building.kind ) > 0 then
				City.BuildingHideOver( building.kind )
				system_askinfo( ASKINFO_TRAIN, "", 4, building.kind );
						
			else
				BuildingOpratorModShow( true, building.kind, building.offset, transform );
			end
		end
	end
end

-- ����յؿ�
function City.BuildingLandSelect( transform )
	if City.m_LastSelect ~= nil then
		-- �����ͬ����ֱ�ӷ���
		if City.m_LastSelect == transform then
			return;
		end
		-- �ر�֮ǰ���䶯��
		City.m_LastSelect:GetComponent("UITweenColor"):Kill(true);
		City.m_LastSelect = nil;
	end
	
	local buildingLand = nil;	
	if transform == nil then
		return;
	else
		buildingLand = transform:GetComponent("CityLand");
		BuildingCreateDlgShow( buildingLand.buildingkinds, buildingLand.offset );
		City.m_Camera:TweenPosToInBound( transform.position, 0.2 );
	end
end

-- ȡ��ѡ��
function City.BuildingUnSelect()
	-- �ر�֮ǰ���䶯��
	if City.m_LastSelect ~= nil then
		City.m_LastSelect:GetComponent("UITweenColor"):Kill(true);
		City.m_LastSelect = nil;
	end
end

-- ��ȡ��������
function City.GetBuilding( kind, offset )
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		return City.m_Buildings_res[kind][offset];
	else
		return City.m_Buildings[kind];
	end
end

-- �Ƶ��ƶ�����
function City.Move( kind, offset, select )
	local unitObj = City.GetBuilding( kind, offset )
	if unitObj == nil then
		return;
	end
	City.m_Camera:TweenPosToInBound( unitObj.position, 0.2 );
	if select == true then
		Invoke( function() 
			City.BuildingSelect( unitObj )
		end, 0.3 );
	end
end

-- ��ӽ���
function City.BuildingAdd( info, active )
	local kind = info.m_kind;
	local offset = info.m_offset
	local landname = "";
	
	-- ���˾��޸�
	local unitObj = nil;
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		if City.m_Buildings_res[kind] ~= nil then
			unitObj = City.m_Buildings_res[kind][offset];
		end
	else
		unitObj = City.m_Buildings[kind];
	end
	
	-- û�оʹ���
	if unitObj == nil then
		if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
			landname = BuildingPrefab[kind].land..offset;
		else
			landname = BuildingPrefab[kind].land;
		end
		
		local land = City.BuildingRoot().transform:Find( landname );
		local prefab = LoadPrefab( BuildingPrefab[kind].prefab );
		unitObj = GameObject.Instantiate( prefab ).transform;
		unitObj:SetParent( City.BuildingRoot().transform );
		unitObj.localScale = Vector3.one;
		unitObj.position = land.transform.position;
		unitObj.localPosition = Vector3.New( unitObj.localPosition.x, unitObj.localPosition.y, 0 );
		
		if active ~= nil and active == false then
			unitObj.gameObject:SetActive(false);
		else
			unitObj.gameObject:SetActive(true);
		end
		
		land.gameObject:SetActive(false);
		
		if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
			if City.m_Buildings_res[kind] == nil then
				City.m_Buildings_res[kind] = {};
			end
			City.m_Buildings_res[kind][offset] = unitObj;	
		else
			City.m_Buildings[kind] = unitObj;
		end
		unitObj:GetComponent("CityBuilding").offset = offset;
	end
	
	City.BuildingSetName( info );
	City.BuildingSetTimer( info );
	City.BuildingHideFree( kind, offset )
	return unitObj;
end

-- ɾ������
function City.BuildingDel( info )
	local kind = info.m_kind;
	local offset = info.m_offset;	
	local unitObj = nil;
	local landname = "";
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		landname = BuildingPrefab[kind].land..offset;
		unitObj = City.m_Buildings_res[kind][offset];
	else
		landname = BuildingPrefab[kind].land;
		unitObj = City.m_Buildings[kind];
	end
	
	GameObject.Destroy( unitObj );
	
	local land = City.BuildingRoot().transform.Find( landname );
	land:SetActive(true);
	
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		City.m_Buildings_res[kind][offset] = nil;	
	else	
		City.m_Buildings[kind] = nil;		
	end
end

-- ˢ��
function City.BuildingRefurbish( info ) 
	City.BuildingSetName( info );
	City.BuildingSetTimer( info );
end

-- ��������
function City.BuildingSetName( info )
	local kind = info.m_kind;
	local offset = info.m_offset;
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		unitObj = City.m_Buildings_res[kind][offset];
	else
		unitObj = City.m_Buildings[kind];
	end

	if kind <= BUILDING_Militiaman_Archer then
		unitObj:Find("panel/name"):GetComponent( typeof(UIText) ).text = T(kind).." "..info.m_level;
	elseif kind <= BUILDING_Iron then
		unitObj:Find("panel/name"):GetComponent( typeof(UIText) ).text = "Lv."..info.m_level;
	else
		unitObj:Find("panel/name"):GetComponent( typeof(UIText) ).text = T(kind)
	end
end

-- ������ʱ��
function City.BuildingSetTimer( info )
	local kind = info.m_kind;
	local offset = info.m_offset;
	if info.m_sec == nil then
		return;
	end
	local unitObj = nil;
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		unitObj = City.m_Buildings_res[kind][offset];
	else
		unitObj = City.m_Buildings[kind];
	end
	local timerObj = unitObj:GetComponent("CityBuilding").BuildingTimerMod;
	if timerObj == nil and info.m_sec > 0 then
		timerObj = GameObject.Instantiate( City.m_BuildingTimerMod );
		timerObj.transform:SetParent( City.m_BuildingUI );
		timerObj.transform.position = unitObj.transform.position;
		timerObj.transform.localPosition = Vector3.New( timerObj.transform.localPosition.x, timerObj.transform.localPosition.y-50, 0 );
		timerObj.transform.localScale = Vector3.one;
		unitObj:GetComponent("CityBuilding").BuildingTimerMod = timerObj;
	end
	
	if timerObj ~= nil then
		if info.m_sec <= 0 then
			timerObj.gameObject:SetActive(false);
		else
			timerObj.gameObject:SetActive(true);
		end

		--timerObj.transform:Find( "Icon" ):GetComponent( "Image" ).sprite;
		local timer = timerObj.transform:Find( "Text" ):GetComponent( "UITextTimeCountdown" );
		timer.controlID = 1;
		timer.uiMod = timerObj.transform:GetComponent("UIMod");
		timer.uiProgress = timerObj.transform:Find( "Progress" ):GetComponent( "UIProgress" );
		timer:SetTime( info.m_needsec, info.m_needsec-info.m_sec );
	end
end

-- ������ʱ��
function City.BuildingSetUpgradeing( kind, offset, needsec, sec )
	local unitObj = nil;
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		unitObj = City.m_Buildings_res[kind][offset];
	else
		unitObj = City.m_Buildings[kind];
	end
	
	local timerObj = unitObj:GetComponent("CityBuilding").BuildingTimerMod;
	if timerObj == nil then
		timerObj = GameObject.Instantiate( City.m_BuildingTimerMod );
		timerObj.transform:SetParent( City.m_BuildingUI );
		timerObj.transform.position = unitObj.transform.position;
		timerObj.transform.localPosition = Vector3.New( timerObj.transform.localPosition.x, timerObj.transform.localPosition.y-50, 0 );
		timerObj.transform.localScale = Vector3.one;
		unitObj:GetComponent("CityBuilding").BuildingTimerMod = timerObj;
	end
	if sec <= 0 then
		timerObj.gameObject:SetActive(false);
		--timerObj.transform:Find( "Icon" ):GetComponent( "Image" ).sprite;
		local timer = timerObj.transform:Find( "Text" ):GetComponent( "UITextTimeCountdown" );
		timer.controlID = 0;
		timer.uiMod = timerObj.transform:GetComponent("UIMod");
		timer.uiProgress = timerObj.transform:Find( "Progress" ):GetComponent( "UIProgress" );
		timer:SetTime( 0, 0 );
	else
		timerObj.gameObject:SetActive(true);
		--timerObj.transform:Find( "Icon" ):GetComponent( "Image" ).sprite;
		local timer = timerObj.transform:Find( "Text" ):GetComponent( "UITextTimeCountdown" );
		timer.controlID = 1;
		timer.uiMod = timerObj.transform:GetComponent("UIMod");
		timer.uiProgress = timerObj.transform:Find( "Progress" ):GetComponent( "UIProgress" );
		timer:SetTime( needsec, needsec-sec );
	end
end

-- �������
function City.BuildingWorker()
	if GetPlayer().m_worker_kind > 0 then
		City.BuildingSetUpgradeing( 
		GetPlayer().m_worker_kind, 
		GetPlayer().m_worker_offset, 
		GetPlayer().m_worker_needsec,
		GetPlayer().m_worker_sec );
		
		if GetPlayer().m_worker_free > 0 then
			City.BuildingSetFree( GetPlayer().m_worker_kind, GetPlayer().m_worker_offset );
		end	
	end
	
	if GetPlayer().m_worker_kind_ex > 0 then
		City.BuildingSetUpgradeing( 
		GetPlayer().m_worker_kind_ex, 
		GetPlayer().m_worker_offset_ex, 
		GetPlayer().m_worker_needsec_ex,
		GetPlayer().m_worker_sec_ex );
		
		if GetPlayer().m_worker_free_ex > 0 then
			City.BuildingSetFree( GetPlayer().m_worker_kind_ex, GetPlayer().m_worker_offset_ex );
		end
	end
end

-- ���ͷ
function City.BuildingSetFree( kind, offset )
	local unitObj = nil;
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		unitObj = City.m_Buildings_res[kind][offset];
	else
		unitObj = City.m_Buildings[kind];
	end
	local freeObj = unitObj:GetComponent("CityBuilding").BuildingFreeMod;
	if freeObj == nil then
		freeObj = GameObject.Instantiate( City.m_BuildingFreeMod );
		freeObj.transform:SetParent( City.m_BuildingUI );
		freeObj.transform.position = unitObj.transform.position;
		freeObj.transform.localPosition = Vector3.New( freeObj.transform.localPosition.x, freeObj.transform.localPosition.y+80, 0 );
		freeObj.transform.localScale = Vector3.one;
		unitObj:GetComponent("CityBuilding").BuildingFreeMod = freeObj;
	end
	local ShareData = freeObj.transform:GetComponent("ShareData");
	ShareData.intValue[0] = kind;
	ShareData.intValue[1] = offset;
	freeObj.gameObject:SetActive(true);
end

function City.BuildingHideFree( kind, offset )
	local unitObj = nil;
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		unitObj = City.m_Buildings_res[kind][offset];
	else
		unitObj = City.m_Buildings[kind];
	end
	local freeObj = unitObj:GetComponent("CityBuilding").BuildingFreeMod;
	if freeObj == nil then
		return
	end
	freeObj.gameObject:SetActive(false);
end

-- ��ɱ��
function City.BuildingSetOver( kind )
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		return;
	end
	local unitObj = City.m_Buildings[kind];
	local overObj = unitObj:GetComponent("CityBuilding").BuildingOverMod;
	if overObj == nil then
		overObj = GameObject.Instantiate( City.m_BuildingOverMod );
		overObj.transform:SetParent( City.m_BuildingUI );
		overObj.transform.position = unitObj.transform.position;
		overObj.transform.localPosition = Vector3.New( overObj.transform.localPosition.x, overObj.transform.localPosition.y, 0 );
		overObj.transform.localScale = Vector3.one;
		unitObj:GetComponent("CityBuilding").BuildingOverMod = overObj;
	end
	local ShareData = overObj.transform:GetComponent("ShareData");
	ShareData.intValue[0] = kind;
	overObj.gameObject:SetActive(true);
end

-- ��ɱ������
function City.BuildingHideOver( kind )
	if kind >= BUILDING_Silver and kind <= BUILDING_Iron then
		return;
	end
	local unitObj = City.m_Buildings[kind];
	local overObj = unitObj:GetComponent("CityBuilding").BuildingOverMod;
	if overObj == nil then
		return
	end
	overObj.gameObject:SetActive(false);
end

-- ���մ���
function City.BuildingAddLevy()	
	for i=21, 24, 1 do
		if City.m_Buildings_res[i] then
			for k, v in pairs( City.m_Buildings_res[i] ) do
				local obj = v:Find("LevyMod").gameObject;
				if obj and obj.activeSelf == false then
					obj:SetActive( true );
					break;
				end
			end
		end
	end
end

function City.BuildingSubLevy()
	for i=21, 24, 1 do
		if City.m_Buildings_res[i] then
			for k, v in pairs( City.m_Buildings_res[i] ) do
				local obj = v:Find("LevyMod").gameObject;
				if obj and obj.activeSelf == true then
					obj:SetActive( false );
					break;
				end
			end
		end
	end
end

-- ����������
function City.GoToWorker()
	-- �ƶ���ѡ��
	if GetPlayer().m_worker_kind > 0 then
		City.Move( GetPlayer().m_worker_kind, GetPlayer().m_worker_offset, true )
		return;
	end
	
	-- �ҵ�һ������������
	
end

-- ��������������
function City.GoToWorkerEx()
	-- �ƶ���ѡ��
	if GetPlayer().m_worker_kind_ex > 0 then
		City.Move( GetPlayer().m_worker_kind_ex, GetPlayer().m_worker_offset_ex, true )
		return
	end
	
	-- �򿪹������ý���ӽ���
	if GetPlayer().m_worker_expire_ex <= 0 then
		-- 
		BuyWorkerDlgShow();
	end
	
	-- �ҵ�һ������������
	
end

-- ����ͼ��
function City.BuildingQuestMod( questid )
	City.m_BuildingQuestMod.gameObject:SetActive(true);
	local ShareData = City.m_BuildingQuestMod.transform:GetComponent("ShareData");
	ShareData.intValue[0] = questid;
end
