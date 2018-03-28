-- �򿪽���
function GirlTrainDlgOpen()
	m_Dlg = eye.uiManager:Open( "GirlTrainDlg" );
	m_DialogFrameMod = DialogFrameModOpen( m_Dlg, T(34), HELP_GirltrainDlg, GirlTrainDlgClose );
end

-- ���ؽ���
function GirlTrainDlgClose()
	if m_Dlg == nil then
		return;
	end
	DialogFrameModClose( m_DialogFrameMod );
	m_DialogFrameMod = nil;
	eye.uiManager:Close( "GirlTrainDlg" );
end

-- ɾ������
function GirlTrainDestroy()
	GameObject.Destroy( m_Dlg );
	m_Dlg = nil;
end

----------------------------------------
-- �¼�
----------------------------------------

-- ������ť���ʱ����
function GirlTrainDlgOnEvent( nType, nControlID, value, gameObject )
	
end

-- ����ʱ����
function GirlTrainDlgOnAwake( gameObject )
	-- �ؼ���ֵ	
	local objs = gameObject:GetComponent( typeof(UISystem) ).relatedGameObject;	
	
end

-- �����ʼ��ʱ����
function GirlTrainDlgOnStart( gameObject )
	
end

-- ������ʾʱ����
function GirlTrainDlgOnEnable( gameObject )
	
end

-- ��������ʱ����
function GirlTrainDlgOnDisable( gameObject )
	
end

-- ����ɾ��ʱ����
function GirlTrainDlgOnDestroy( gameObject )
	m_Dlg = nil;
end

-- ÿ֡����
function GirlTrainDlgOnLogic( gameObject )
	
end