-- ͨ�ö���Ϣ����
NOTIFY_NORMAL 		= 	0	-- ȱʡ������ʾ������˷�����
NOTIFY_TEXTTABLE	=	1	-- 
NOTIFY_ITEM			=	2
NOTIFY_ITEMNUM		=	3
NOTIFY_LOGIN_QUEUE	=	4
NOTIFY_CHANGESHAPE	=	5	-- ���ͷ���޸�

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
    end
end
