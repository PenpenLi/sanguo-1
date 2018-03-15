-- �����¼�
CMD_TALK = 1         --����������ָ
CMD_SPECIAL = 2      --�������ϵ�ָ��
CMD_CLICK = 3        --����ҳ���ϵ�ָ��

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
GUIDE_MAKE = 10          --����
GUIDE_CHOOSE_WEAPON = 11 --�����������
GUIDE_CPOY = 12          --������ť��ָ
GUIDE_BACK = 13          --�سǰ�ť��ָ
GUIDE_UPGRADE = 14       --��������
GUIDE_CHOOSE_MA = 15     --ѡ����
GUIDE_DRESS_MA = 16      --�������
GUIDE_GET_HERO = 17      --��ļ�佫
GUIDE_CLCLK_ZL = 18      --�������ͷ��
GUIDE_CHOOSE_CLOUTH = 19 --ѡ�����Ӽ�
GUIDE_CHOOSE_HEAD = 20   --ѡ������
GUIDE_MAKE_CHOOSE = 21   --ѡ������
GUIDE_MAKE_UP = 22       --��������
GUIDE_DRESS_HEAD = 23    --���ͷ������
GUIDE_AUTOBUILDING = 24  --�Զ�����


GUIDE_TASK_FINISH = 111  --������ɣ���Ϊһ�������ı�ʶ
GUIDE_END = 999          --ָ��������ʶ

local m_uiFinger = {nil,nil,nil,nil}; --UnityEngine.GameObject

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
	m_uiFinger[1] = objs[0];
	m_uiFinger[2] = objs[1];
	m_uiFinger[3] = objs[2];
	m_uiFinger[4] = objs[3];	
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
        if GuideCheck( id ) and g_guide[mId][mStep].guideType == 999 then
			mIsGuiding = false;
            return;
        end   
    end
	
	mIsGuiding = true;
	
	mId = id;
	mStep = step;
	warn(mId);
	warn(step);
	
	HideGuideFinger();
	HideCurrentFinger();
	
	if g_guide[mId][mStep].cmd == CMD_SPECIAL or g_guide[mId][mStep].cmd == CMD_TALK then FindCmdTpye(nil) end
end

function GuideNext()
	if table.getn(g_guide[mId]) == mStep then
		mStep = 0;
		system_askinfo( ASKINFO_GUAID, "", mId + 1 );
		Guide( mId + 1, 1);
	else
		Guide( mId, mStep + 1 );
	end
end

function ForceGuideNext()
	mStep = 0;
	system_askinfo( ASKINFO_GUAID, "", mId + 1 );
	Guide( mId + 1, 1);
end

function GuideCheck(id)
	if id == table.getn(g_guide) then 
		HideGuideFinger();
		HideCurrentFinger();
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

function GetGuideSpecialEvent()
	return g_guide[mId][mStep].isSpecial
end
function HideGuideFinger()
	for i = 1, table.getn(m_uiFinger), 1 do 
		if m_uiFinger[i] then
			SetFalse(m_uiFinger[i].transform);
		end
	end
end

function ShowGuideFinger(pi)
	HideGuideFinger();
	if m_uiFinger[pi] then
		SetTrue(m_uiFinger[pi].transform);
	end
end

function HideCurrentFinger()
	if currentFinger ~= nil then
		SetFalse(currentFinger.transform);
		currentFinger = nil;
	end
end

-- ���õ�ǰָ��λ��
function FindCmdTpye(tran)
	cmd = g_guide[mId][mStep].cmd;
	point = g_guide[mId][mStep].point;
	deviation = Vector3.New(g_guide[mId][mStep].x,g_guide[mId][mStep].y,0);
	if cmd == 2 then 
		if g_guide[mId][mStep].guideType == GUIDE_TOCLICKTASK then 
			ShowGuideFinger(point);
			m_uiFinger[point].transform.position = GetQuestDlgPos() + deviation;
		elseif g_guide[mId][mStep].guideType == GUIDE_CPOY then 
			ShowGuideFinger(point);
			m_uiFinger[point].transform.position = GetCopyPos() + deviation;
		elseif g_guide[mId][mStep].guideType == GUIDE_BACK then
			ShowGuideFinger(point);
			m_uiFinger[point].transform.position = GetBackPos() + deviation;
		elseif g_guide[mId][mStep].guideType == GUIDE_AUTOBUILDING then
			ShowGuideFinger(point);
			m_uiFinger[point].transform.position = GetAutoBuildPos() + deviation;
		end
	elseif cmd == 3 then
		if currentFinger == nil then
			currentFinger = addChild(tran,m_uiFinger[point]);
			currentFinger.transform.position = currentFinger.transform.position + deviation;
		end
	elseif cmd == 1 then
		
	end
end

