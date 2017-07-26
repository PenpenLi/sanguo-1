-- ͨ�ö���Ϣ����
NOTIFY_NORMAL 		= 	0	-- ȱʡ������ʾ������˷�����
NOTIFY_TEXTTABLE	=	1	-- 
NOTIFY_ITEM			=	2
NOTIFY_ITEMNUM		=	3
NOTIFY_LOGIN_QUEUE	=	4
NOTIFY_CHANGESHAPE	=	5	-- ���ͷ���޸�
NOTIFY_CHANGENAME	=	6	-- ����޸�����
NOTIFY_NPCTALK		=	7	-- NPC�Ի�
NOTIFY_EQUIP		=	8	-- װ��

-- ������յ�����Ϣ
function RecvActorNotify(recvValue)
    local msgid = recvValue.m_msgid;
    local value = recvValue.m_value;
    local msg = recvValue.m_msg;
    
    if msgid == NOTIFY_NORMAL then
		
	-- ͷ��ı�
	elseif msgid == NOTIFY_CHANGESHAPE then
		GetPlayer().m_shape = value[2];
		MainDlgSetHead();
		PlayerDlgSet();
	
	-- NPC�Ի�	
	elseif msgid == NOTIFY_NPCTALK then
		if BuildingGetDlgIsShow() == true then
			BuildingGetDlgWait( NpcTalkID, value[1] )
		else
			NpcTalkID( value[1] )
		end
	
	-- װ��	
	elseif msgid == NOTIFY_EQUIP then
		if value[1] == 0 then
			GetPlayer().m_equipext = value[2];
			BagDlgEquipExtSet();
		end
    end
end
