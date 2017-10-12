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
NOTIFY_ACTOR		=	9	-- ��ɫ
NOTIFY_ACTORSFLAG	=	10	-- ��ɫ��־λ
NOTIFY_WORLDMAP		=	11	-- �����ͼ
NOTIFY_VALUECHANGE	=	12	-- ֵ�ı�
NOTIFY_MAIL			=	13	-- �ʼ�
NOTIFY_ALERT		=	14	-- ��Ϣȷ����

-- ������յ�����Ϣ
function RecvActorNotify(recvValue)
    local msgid = recvValue.m_msgid;
    local value = recvValue.m_value;
    local msg = recvValue.m_msg;
    
    if msgid == NOTIFY_NORMAL then
		pop(T(value[1]))
		
	-- ����ʹ�õ���
	elseif msgid == NOTIFY_ITEM then
		if value[1] == 0 then
			pop( T(753)..": "..item_getname(value[2]).."x"..value[3] )
		elseif value[1] == 1 then
			-- ���߼���
			if value[2] > 0 then
				pop( T(759)..zhtime(value[2]) )
				QuickItemDlgSet( value[2], 1 )
			else
				QuickItemDlgClose();
				TrainDlgClose();
			end
		end
	
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
	
	-- ��ɫ	
	elseif msgid == NOTIFY_ACTOR then
		-- ��������ѯ��
		if value[1] == 0 then
			MsgBox( F( 783, value[2] ), function()
				system_askinfo( ASKINFO_ACTOR, "", 0, 0 );
			end )
		
		-- �����þ�
		elseif value[1] == 1 then
			AlertMsg( T(784) )
	
		end
	
	-- ��ɫ��־λ	
	elseif msgid == NOTIFY_ACTORSFLAG then
		GetPlayer().m_actor_sflag = value[1]
	
	-- �����ͼ	
	elseif msgid == NOTIFY_WORLDMAP then
		 -- Ǩ�����
        if value[1] == 1 then
            WorldMap.OnCityMoved(value[2], value[3], value[4]);
		-- ���»�ɱ����
		elseif value[1] == 2 then
			GetPlayer().m_mokilllv = value[2];
		end
	
	-- ֵ�ı�	
	elseif msgid == NOTIFY_VALUECHANGE then
		-- ϴ�����
		if value[1] == 1 then
			pop( T(120)..": "..T(1100).."x"..value[2] ) 
		-- ϴ������
		elseif value[1] == 2 then
			pop( T(120)..": "..T(1101).."x"..value[2] ) 
		end
	
	-- �ʼ�	
	elseif msgid == NOTIFY_MAIL then
		-- �ʼ�����
		if value[1] == 1 then
			MainDlgSetMailNum( value[2] )
		-- ��������
		elseif value[1] == 2 then
			if value[2] == 0 or value[2] == 1 then
				MailDlgMailRecvOver( value[2], value[3] );
			end
		end
		
	-- ��Ϣȷ����
	elseif msgid == NOTIFY_ALERT then
		if recvValue.m_msg_length > 1 then
			local json = require "cjson"
			local msgjson = json.decode( recvValue.m_msg );
			local msg = "";
			if msgjson["v1"] ~= nil and msgjson["v2"] ~= nil then
				local v1_str = GetMail():GetString( msgjson["v1"] );
				local v2_str = GetMail():GetString( msgjson["v2"] );
				msg = F( value[1], v1_str, v2_str )
			
			elseif msgjson["v1"] ~= nil then
				local v1_str = GetMail():GetString( msgjson["v1"] );
				msg = F( value[1], v1_str )
				
			else
				msg = T(value[1])
			end
			AlertMsg( msg )
		else
			AlertMsg( T(value[1]) )
		end
    end
end
