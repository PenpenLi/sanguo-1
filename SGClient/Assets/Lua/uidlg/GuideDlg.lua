-- �����¼�
CMD_TALK = 1         --�Ի���������������Ŀǰ�޸�ͨ����������ʽ���֣���ʱ���������ˣ�
CMD_SPECIAL = 2      --�����ͬһ�������ж���ĸ�����������ָָʾ
CMD_CLICK = 3        --�����ͬһ����û�и���������������

-- ����������
GUIDE_TOCLICKTASK = 1     --ָ������ť��ָ
GUIDE_TECH_SURE = 2      --�о��Ƽ�ȷ��
GUIDE_GOTO_SOCIETY = 3   --���簴ť��ָ
GUIDE_CLCLK_HEAD = 4     --������ͷ��
GUIDE_CLCLK_DRESS = 5    --����·�����
GUIDE_DRESS = 6          --����
GUIDE_GET = 7            --����
GUIDE_RECRUIT = 8        --��ļ
GUIDE_CHOOSE = 9         --ѡ��ŵ�
GUIDE_MAKE = 10          --����ŵ�
GUIDE_CHOOSE_WEAPON = 11 --�����������
GUIDE_CPOY = 12          --������ť��ָ


GUIDE_TASK_FINISH = 111  --������ɣ���Ϊһ�������ı�ʶ


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
	m_uiPos = objs[1];
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
        if GuideCheck( id ) and step == 999 then
			mIsGuiding = false;
            return;
        end   
    end
	
	mIsGuiding = true;
	
	mId = id;
	mStep = step;
	warn(mId);
	warn(step);
	
	if g_guide[mId][mStep].cmd == CMD_SPECIAL then FindCmdTpye(nil) end
end

function GuideNext()
	if table.getn(g_guide[mId]) == mStep then
		mStep = 0;
		Guide( mId + 1, 1);
	--	system_askinfo( ASKINFO_GUAID, "", mId + 1 );
	else
		Guide( mId, mStep + 1 );
	end
	HideGuideFinger();
end

function GuideCheck(id)
	if id == table.getn(g_guide) then 
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

function ShowGuideFinger()
	SetTrue(m_uiFinger.transform);
end

function HideCurrentFinger()
	if currentFinger ~= nil then
		SetFalse(currentFinger.transform);
	end
end

-- ���õ�ǰָ��λ��
function FindCmdTpye(tran)
	cmd = g_guide[mId][mStep].cmd;
	HideCurrentFinger();
	if cmd == 2 then 
		if g_guide[mId][mStep].guideType == GUIDE_TOCLICKTASK then 
			ShowGuideFinger();
			m_uiFinger.transform.position = GetQuestDlgPos();
		elseif g_guide[mId][mStep].guideType == GUIDE_CPOY then 
			ShowGuideFinger();
			m_uiFinger.transform.position = GetCopyPos();
		end
	elseif cmd == 3 then
		HideGuideFinger();
		currentFinger = addChild(tran,m_uiFinger);
		SetParent(currentFinger,tran);
	elseif cmd == 1 then
		HideGuideFinger();
	end
end