
local m_Mod = nil;
local m_PrefabTab = {};
local m_IsTalkShow = false;

-- ������ť���ʱ����
function PatrolModOnEvent( nType, nControlID, value )
    if nType == UI_EVENT_CLICK then
		
    elseif nType == UI_EVENT_TWEENFINISH then
		PatrolModWaitPlay(nControlID);		
    elseif nType == UI_EVENT_TIMECOUNTEND then
		if nControlID >= 10 and nControlID <= 20 then 
			PatrolModRePlay(nControlID-10)
		elseif nControlID >= 100 and nControlID <= 110 then 
			m_IsTalkShow = false;
			PatrolModShowTalk(nControlID -100,m_IsTalkShow)
		end
    end
end

-- ����ʱ����
function PatrolModOnAwake( gameObject )
	m_Mod = gameObject;
	local objs = gameObject:GetComponent( "UIMod" ).relatedGameObject;
	for i = 0,7 do 
		local prefab = objs[i];
		table.insert(m_PrefabTab,prefab);
		SetFalse(m_PrefabTab[i+1]);
	end
end

-- �����ʼ��ʱ����
function PatrolModOnStart( gameObject )
	
end

-- ������ʾʱ����
function PatrolModOnEnable( gameObject )
	
end

-- ��������ʱ����
function PatrolModOnDisable( gameObject )
	
end

-- ����ɾ��ʱ����
function PatrolModOnDestroy( gameObject )
	
end

-- ÿ֡����
function PatrolModOnLogic( gameObject )
end

-- ��ʼ��
function PatrolModInit()
	PatrolModPlay();
end

-- �л���ͼ������ͣ
function PatrolModStop()
	for i = 1,#g_patrol_path do 
		SetFalse(m_PrefabTab[i]);
		local unitTween = m_PrefabTab[i].transform:GetComponent( "UITweenMove" );
		unitTween:Kill(false);
	end
end
-- ���ò㼶
function PatrolModSetSiblingIndex()
	m_Mod.transform:SetSiblingIndex(1001)
end
function PatrolModPlay()
	for i = 1,5 do 
		if g_patrol_path[i].level <= GetPlayer().m_level then 
			PatrolModTween(g_patrol_path[i].path);
		end
	end	
end
function PatrolModTween(PathData)
	SetTrue(m_PrefabTab[PathData.id])
	local unitTween = m_PrefabTab[PathData.id].transform:GetComponent( "UITweenMove" );
	local unitRect = m_PrefabTab[PathData.id].transform:GetComponent( "RectTransform" );
	unitRect.localScale = Vector3.New( PathData.scale, PathData.scale, PathData.scale );
	startPos = Vector2.New( PathData.bx, PathData.by );
	targetPos = Vector2.New( PathData.ex, PathData.ey );
	unitTween.from = startPos;
	unitTween.to = targetPos;
	unitTween.duration = PathData.sec;
	unitTween:Play(true);
	if m_IsTalkShow == false then 
		PatrolModShowTalk(PathData.id);
	end
end
function PatrolModRePlay(id)		
	PatrolModTween(g_patrol_path[id].path);
end
function PatrolModWaitPlay(id)
	SetFalse(m_PrefabTab[id]);
	local unitTween = m_PrefabTab[id].transform:GetComponent( "UITweenMove" );
	unitTween:Kill(false);
	local NextId = PatrolModGetNextID(id);	
	local Delay = g_patrol_path[NextId].Delay;
	SetTimer(m_PrefabTab[id],Delay,GetServerTime()+Delay,NextId+10);
end

-- ��ȡ��һ·��ID
function PatrolModGetNextID(id )
	local NextID = nil;
	if id <= 2 then 
		NextId = id;
	elseif id == 3 then  
		NextId = 6;
	elseif id == 4 then  
		NextId = 7;
	elseif id == 5 then  
		NextId = 8;
	elseif id == 6 then  
		NextId = 3;
	elseif id == 7 then  
		NextId = 4;
	elseif id == 8 then  
		NextId = 5;
	end
	return NextId;
end

--
function PatrolModShowTalk(PathID,bShow)
	local uiObj = m_PrefabTab[PathID];
	local objs = uiObj.transform:GetComponent( typeof(Reference) ).relatedGameObject;
	local uiTipWnd = objs[0];
	local uiText = objs[1];
	if bShow ==  false then 
		SetFalse(uiTipWnd);
	else
		local TalkID = PatrolModGetTalkID();	
		SetTrue(uiTipWnd)
		SetText(uiText,g_patrol_talk[TalkID].str);
		local Delay = g_patrol_talk[TalkID].sec;
		SetTimer(uiTipWnd,Delay,GetServerTime()+Delay,PathID+100);
		m_IsTalkShow = true;
	end
	
end

-- ��ȡ�Ի�ID
function PatrolModGetTalkID()
	return custom.rand( 1, #g_patrol_talk );
end

-- �Ƿ��жԻ�
function PatrolModIsTalkShow()
	return m_IsTalkShow;
end