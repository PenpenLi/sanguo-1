-- �����¼�
CMD_TALK = 1         --�Ի�������������
CMD_CLICK = 2        --������̶�λ�õ��

-- ����������
GUIDE_GETTASKREWARD = 1   --��ȡ������ť����
GUIDE_GETNEW_BUILDING = 2 --����½���
GUIDE_TOCLICKTASK = 3     --ָ������ť��ָ
GUIDE_BUILDINGUPDATE = 4  --����������ť����
GUIDE_CREATENAME = 5      --���ƴ�����ť����
GUIDE_SOLVE = 6           --���ͷ�����Ӣ�ۣ�������Ч����
GUIDE_TALKCLICK = 7       --�Ի��ĵ����ť����
GUIDE_GETHERO = 8         --����佫�ĵ����ť����
GUIDE_AUTOMATIC = 9       --�Զ�����ͼ�����
GUIDE_TEACHER = 10        --�о�Ժ��Ӷ��ť��ָ
GUIDE_TECH = 11           --�о����Ľ��밴ť
GUIDE_TECH_SURE = 12      --�о���������ȷ��
GUIDE_GOTO_SOCIETY = 13   --���簴ť��ָ
GUIDE_ENEMY_ATTACK = 14   --���ܽ�����ť��������ָ
GUIDE_ADD_ARMY = 15       --���������ť����
GUIDE_HERO_ATTACK = 16    --�佫������ť����
GUIDE_CLCLK_HEAD = 17     --������ͷ��
GUIDE_CLCLK_DRESS = 18    --����·�����
GUIDE_DRESS = 19          --����
GUIDE_BACK = 20           --�س�
GUIDE_UPGRADE = 21        --������ť
GUIDE_FREE = 22           --�����Ѱ�ť
GUIDE_TALK = 23           --�Ի�
GUIDE_ATTACK = 24         --Χ�����Ҿ�������ɽ��
GUIDE_TEACH_GET = 25      --�����ȡ��ѧϰ�ĿƼ�


-- ���ؽ���
function GuideDlgClose()
	if m_Dlg == nil then
		return;
	end
	eye.uiManager:Close( "GuideDlg" );
end

-- ɾ������
function GuideDlgDestroy()
	GameObject.Destroy( m_Dlg );
	m_Dlg = nil;
end

----------------------------------------
-- �¼�
----------------------------------------

-- ������ť���ʱ����
function GuideDlgOnEvent( nType, nControlID, value, gameObject )
end

-- ����ʱ����
function GuideDlgOnAwake( gameObject )
	-- �ؼ���ֵ	
	local objs = gameObject:GetComponent( typeof(UISystem) ).relatedGameObject;	
	m_uiFinger = objs[0];

end

-- �����ʼ��ʱ����
function GuideDlgOnStart( gameObject )
	
end

-- ������ʾʱ����
function GuideDlgOnEnable( gameObject )
	
end

-- ��������ʱ����
function GuideDlgOnDisable( gameObject )
	
end

-- ����ɾ��ʱ����
function GuideDlgOnDestroy( gameObject )
	m_Dlg = nil;
end

-- ÿ֡����
function GuideDlgOnLogic( gameObject )
	
end

mId = 0
mStep = 0
mIsGuiding = false


-- �򿪽���
function Guide(id, step, force)
	m_Dlg = eye.uiManager:Open( "GuideDlg" );	
	if force ~= true then
        if id == 0 then                   -- ��������״̬
            if step ~= 1 then
                return;
            end
        else
            if id ~= id then              -- �ڽ�����������
                return;
            elseif step ~= mStep + 1 then  -- ���費��
                return;
            end
        end

        -- ��������Ƿ����
        if GuideCheck( id ) and step == 1 then
            return;
        end   
    end
	
	mIsGuiding = true;
	
	mId = id;
	mStep = step;
	
	if g_guide[mId][mStep].cmd == CMD_TALK then FindCmdTpye(nil) end
	--[[" if then
		
		m_uiFinger.transform.position = GetQuestDlgPos();"]]
end

function GuideNext()
    Guide( mId, mStep + 1 );
	HideGuideFinger();
end

function GuideCheck(id)
	if id == 999 then 
		mIsGuiding = false;
		return true
	else 
		return false
	end
end

function IsGuiding()
	return mIsGuiding
end

function GetCurrentGuideType()
	return g_guide[mId][mStep].guideType
end

function HideGuideFinger()
	SetFalse(m_uiFinger.transform);
end


-- ���õ�ǰָ��λ��
function FindCmdTpye(pos)
	cmd = g_guide[mId][mStep].cmd;
	if cmd == 1 then 
		if g_guide[mId][mStep].guideType == GUIDE_TOCLICKTASK then 
			SetTrue(m_uiFinger);
			m_uiFinger.transform.position = GetQuestDlgPos();
		elseif g_guide[mId][mStep].guideType == GUIDE_GOTO_SOCIETY then
			SetTrue(m_uiFinger);
			m_uiFinger.transform.position =  GetWorldPos();
		else
			SetFalse(m_uiFinger);
			m_uiFinger.transform.localPosition = Vector3.New(0,0,0);
		end
	elseif cmd == 2 then
		SetTrue(m_uiFinger);
		m_uiFinger.transform.position = pos;
		--[["
		if g_guide[mId][mStep].guideType == GUIDE_GETTASKREWARD then
			m_uiFinger.transform.position = pos;
		elseif g_guide[mId][mStep].guideType == GUIDE_BUILDINGUPDATE then 
			m_uiFinger.transform.position = pos;
		elseif g_guide[mId][mStep].guideType == GUIDE_CREATENAME then
			m_uiFinger.transform.position = pos;   
		end
		"]]
	end
end