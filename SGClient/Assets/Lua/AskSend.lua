-- ͨ�ö���Ϣ����
ASKINFO_NORMAL		= 	0
ASKINFO_CHANGESHAPE	=	1 -- �޸�ͷ��
ASKINFO_CHANGENAME	=	2 -- �޸�����
ASKINFO_CITYGUARD	=	3 -- ��ǽ����
ASKINFO_QUEST		=	4 -- ����
ASKINFO_BUILDING	=	5 -- ����
ASKINFO_LEVY		=	6 -- ����
ASKINFO_TRAIN		=	7 -- ѵ��
ASKINFO_EQUIPFORGING	=	8  -- װ������
ASKINFO_EQUIPWASH		=	9  -- װ��ϴ��
ASKINFO_EQUIP			=	10 -- װ��
ASKINFO_ITEM			=	11 -- ����  
ASKINFO_HERO			=	12 -- Ӣ��
ASKINFO_TECH			=	13 -- �Ƽ�
ASKINFO_GOV				=	14 -- �ٸ� 
ASKINFO_OFFICIALHIRE	=	15 -- ��ְ��Ӷ
ASKINFO_QUICK			=	16 -- ����
ASKINFO_ACTOR			=	17 -- ��ɫ����
ASKINFO_MATERIALMAKE	=	18 -- ��������
ASKINFO_STORY			=	19 -- ����
ASKINFO_WORLDMAP		=	20 -- �����ͼ
ASKINFO_MAP_EVENT		=	21 -- �����ͼ����¼�

function system_askinfo( msgid, msg, ... )
	-- δ������Ϸ��������ͨ�ö�Э��
	if Const.NetStatus < 3 then
		return
	end
	-- m_msgid=0,m_valuenum=0,m_value={}[m_valuenum],m_msg_length=0,m_msg="[m_msg_length]",
	local arg={...}
	local sendValue = {};
	sendValue.m_msgid = msgid;
	sendValue.m_msg = msg;
	sendValue.m_msg_length = string.len( sendValue.m_msg );
	sendValue.m_valuenum = #arg;
	sendValue.m_value={};
	for i,v in ipairs(arg) do
		sendValue.m_value[i] = v;
   	end	
	netsend_askinfo_C( sendValue );
end



-- ����Э������
-- ����һ����Ϣ��������ֻ�����ĵ��û�������Ϣ
function SubscribeCmd( cmd )
	system_askinfo( ASKINFO_SUBSCRIBE, "", 1, cmd );
end

-- ȡ������һ����Ϣ
function SubscribeCmdCancel( cmd )
	system_askinfo( ASKINFO_SUBSCRIBE, "", 2, cmd );
end
