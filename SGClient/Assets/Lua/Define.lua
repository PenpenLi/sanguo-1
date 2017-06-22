---------------------- UI�¼� ----------------------
UI_EVENT_CLICK 			    = 0;		-- UIButton����				�޲�
UI_EVENT_PRESS 			    = 1;		-- UIButton����				0 ���£�1 ̧��
UI_EVENT_INPUTSUBMIT	    = 2;		-- UIInputField�ύ			�޲�
UI_EVENT_TWEENFINISH	    = 3;		-- UITween�������			0 ���������1 ����
UI_EVENT_SCROLLDRAG		    = 4;		-- UIScrollRect�϶�			0 ��ʼ�϶���1 �϶��У�2 �����϶�
UI_EVENT_SLIDERVALUECHANGE  = 5;		-- UISliderֵ�ı�			slider valueֵ
UI_EVENT_CENTERCHILD	    = 6;		-- UIScrollRing�Ӿ���		��index
UI_EVENT_TIMECOUNTEND       = 7;        -- UITextTimeCountdown      ��ʱ����
UI_EVENT_DRAGSENSOR         = 8;        -- UIDragSensor��ק�¼�
UI_EVENT_RICHTEXTSETEND     = 9;        -- UIRcihText��ǵ��
UI_EVENT_RICHTEXTMASKCLICK  = 10;       -- UIRcihText��ǵ��
UI_EVENT_INPUTVALUECHANGED  = 11;       -- UIInputField�����޸�		��ǰinputfield����
UI_EVENT_TIMECOUNTCHANGED   = 12;       -- �����޸�
UI_EVENT_VOICE              = 13;       -- UIVoice
UI_EVENT_PUSHEVENT		    = 1000;		-- UIͨ���¼������붨�����¼�����			    ����

-- ����������ͨ����
BUILDING_Main           = 1  -- ����
BUILDING_Wall           = 2  -- ��ǽ
BUILDING_StoreHouse     = 3  -- �ֿ�
BUILDING_Tech           = 4  -- ̫ѧԺ
BUILDING_Craftsman      = 5  -- ��������
BUILDING_Cabinet        = 6  -- �ڸ�

-- ��Ӫ
BUILDING_Infantry       		= 11  -- ����Ӫ
BUILDING_Cavalry        		= 12  -- ���Ӫ
BUILDING_Archer         		= 13  -- ����Ӫ
BUILDING_Militiaman_Infantry	= 14  -- ���Ӫ-����
BUILDING_Militiaman_Cavalry		= 15  -- ���Ӫ-���
BUILDING_Militiaman_Archer		= 16  -- ���Ӫ-����

-- ��Դ����
BUILDING_Silver		    =  21	-- ����
BUILDING_Wood		    =  22	-- ľ��
BUILDING_Food		    =  23	-- ʳ��
BUILDING_Iron		    =  24   -- ����

-- ����ڽ���
BUILDING_Smithy		    =  31	-- ������
BUILDING_Wash		    =  32	-- ϴ����
BUILDING_Fangshi	    =  33	-- ����
BUILDING_Shop		    =  34	-- �̵�
BUILDING_Hero		    =  35	-- ���͹�
BUILDING_Wishing	    =  36	-- �۱���
BUILDING_Help		    =  37	-- ����
		
-- ���ֱ�
-- ��ȡ���ػ�����
function GetLocalizeText( id )
    if id == nil then
        return "";
    end
	return Localization.text( id );
end
function T( nameid )
    return GetLocalizeText( nameid );
end
function zh( text )
    return text;
end
-- дgamelog
function gamelog( msg )
	LogUtil.GetInstance():WriteGame( msg );
end

-- дnetlog
function netlog( msg )
	LogUtil.GetInstance():WriteNet( msg );
end

-- ��������ӽڵ�
function clearChild( object )
	for i = 0 ,object.transform.childCount - 1 do
        GameObject.Destroy( object.transform:GetChild(i).gameObject );
    end
end

-- ��ʱִ��
function Invoke(func, delay, param, name)
    if param == nil then
        param = 0;
    end
    if name == nil then
        name = "";
    end
    eye.gameManager.delayExecute = func;
    eye.gameManager:GameInvoke(delay, param, name);
end
-- ֹͣ��ʱִ��
function InvokeStop(name)
    eye.gameManager:GameInvoke_Stop(name);
end
