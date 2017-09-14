-- �ʼ�
local json = require "cjson"
MAIL_TYPE_SYSTEM		=	0	-- ϵͳ��Ϣ�ʼ�
MAIL_TYPE_NOTIFY		=	1	-- �����ʼ��������ⲿhttp��������ȡ
MAIL_TYPE_ACTOR_SEND	=	2	-- ��ҷ����ʼ�
MAIL_TYPE_ACTOR_REPLY	=	3	-- ��һظ��ʼ�
MAIL_TYPE_FIGHT_ENEMY	=	10	-- ����
MAIL_TYPE_FIGHT_CITY	=	11	-- ��ս
MAIL_TYPE_FIGHT_NATION	=	12	-- ��ս
MAIL_TYPE_CITY_SPY		=	13	-- ���
MAIL_TYPE_CITY_BESPY	=	14	-- �����
MAIL_TYPE_GATHER		=	20	-- �ɼ�

TAG_TEXTID = '#$'	  --���Ϊ���ֱ�id
TAG_ITEMID = '$$'     -- ��� ���Ϊ����װ��ID
TAG_POS    = '$#';       -- ��� ���Ϊ����

local Mail = class("Mail");
function Mail:ctor()
    self:Init();
end
function Mail:Init()
	self.m_FileName = ""
    self.m_Mails = {};
	self.m_IncrementID = 0;
    self.m_bIsLoad = false;
	self.m_nNoReadCount = 0;
    self.m_nRecvCount = 0;
	self.m_nMinMailID = int64.new(0);
	self.m_nMaxMailID = int64.new(0);
	self.m_nLastRecvMinMailID = int64.new(0);
	self.m_bLoadNew = false;
	self.m_bLoadAll = false;
end

function Mail:NewIndex()
    self.m_MailIndex = self.m_MailIndex + 1;
    return self.m_MailIndex;
end

-- ��ȡ���ػ���
function Mail:LoadCache()
	-- �����ļ���
--[[    self.m_FileName = PathUtil.GameCachePath() .. "mail_"..Const.serverid .. '_' .. Const.actorid .. ".cache";
	-- ��ȡ����
    local _tableUtil = TableUtil.New();
    local currTime = GetServerTime();
    if _tableUtil:OpenFromTXT( self.m_FileName ) == true then
        local fieldsNum = _tableUtil:GetFieldsNum();
        for records = 0, _tableUtil:GetRecordsNum() -1, 1 do
            local mailid = tonumber(_tableUtil:GetValue(records, 0));
            local type = tonumber(_tableUtil:GetValue(records, 1));
			local title = tostring(_tableUtil:GetValue(records, 2));
            local content = tostring(_tableUtil:GetValue(records, 3));
			local attach = tostring(_tableUtil:GetValue(records, 4));
			local attachget = tostring(_tableUtil:GetValue(records, 5));
			local recvtime = tonumber(_tableUtil:GetValue(records, 6));
			local read = tonumber(_tableUtil:GetValue(records, 7));
			local fightid = tonumber(_tableUtil:GetValue(records, 8));
			local lock = tonumber(_tableUtil:GetValue(records, 9));
			
            if currTime < recvtime + 7*86400 then
                content = string.gsub(content, '\\n', '\n');
                content = string.gsub(content, '\\t', '\t');
				
				table.insert( self.m_Mails, {
                    m_mailid = mailid,
                    m_type = type,
                    m_title = title,
                    m_content = content,
                    m_attach = attach,
                    m_attachget = attachget,
                    m_recvtime = recvtime,
                    m_read = read,
					m_lock = lock,
                    m_fightid = fightid,
                } )
				
				-- ���ո���
				if m_read == 0 then
					self.m_nRecvCount = self.m_nRecvCount + 1;
				end
				
				-- ���id
				if mailid > self.m_nMaxMailID then
					self.m_nMaxMailID = mailid;
				end
				
				-- ��Сid
				if mailid < self.m_nMinMailID or self.m_nMinMailID <= 0 then
					self.m_nMinMailID = mailid;
				end
            end
			
        end
    end
	
	-- ����
	self:Sort();
	self.m_bIsLoad = true;--]]
end

-- �浵���ػ���
function Mail:SaveCache()
	--print( PathUtil.GameCachePath() )
	--[[if not Utils.Exists( PathUtil.GameCachePath() ) then
        Utils.CreateDirectory( PathUtil.GameCachePath() )
    end
	
	-- ����ļ�
    local fp = io.open( self.m_FileName, "w+" )
    if fp == nil then
        return;
    end
    fp:close();
	
    -- ���´��ļ�
    fp = io.open( self.m_FileName, "a+b" )
    if fp == nil then
        return;
    end
	
    fp:write( "mailid" .. "\t" 
	.. "type" .. "\t" 
	.. "title" .. "\t" 
	.. "content" .. "\t" 
	.. "attach" .. "\t" 
	.. "attachget" .. "\t" 
	.. "recvtime" .. "\t" 
	.. "read" .. "\t"
	.. "lock" .. "\t"
	.. "fightid" .. "\r\n")
	
	local content = "";
    local serverTime = GetServerTime();
    for k, v in pairs(self.m_Mails) do
        if serverTime < v.m_recvtime + 7*86400 then
            content = string.gsub(v.m_content, '\n', '\\n');
            content = string.gsub(content, '\t', '\\t');
			
            local text = v.m_mailid .. "\t" 
			.. v.m_type .. "\t" 
			.. v.m_title .. "\t" 
			.. v.m_content .. "\t" 
			.. v.m_attach .. "\t" 
			.. v.m_attachget .. "\t" 
			.. v.m_recvtime .. "\t" 
			.. v.m_read .. "\t" 
			.. v.m_lock .. "\t" 
			.. v.m_fightid .. "\r\n";
            fp:write(text)
        end
    end
    fp:close();--]]
end

-- ������������
function Mail:Insert( recvValue )
	local m_content_json = json.decode( recvValue.m_content );
	self.m_IncrementID = self.m_IncrementID + 1
	table.insert( self.m_Mails, {
		m_incrementid = self.m_IncrementID,
		m_mailid = recvValue.m_mailid,
		m_actorid = recvValue.m_actorid,
		m_type = recvValue.m_type,
		m_title = recvValue.m_title,
		m_content = recvValue.m_content,
		m_attach = recvValue.m_attach,
		m_attachget = recvValue.m_attachget,
		m_recvtime = recvValue.m_recvtime,
		m_read = recvValue.m_read,
		m_lock = recvValue.m_lock,
		m_fightid = recvValue.m_fightid,
		m_viewpath = recvValue.m_viewpath,
		m_content_json = m_content_json,
		m_fight_content = "",
		m_delete_toggle = 0,
	} )
		
	-- ���id
	if recvValue.m_mailid > self.m_nMaxMailID then
		self.m_nMaxMailID = recvValue.m_mailid;
	end
	
	-- ��Сid
	if recvValue.m_mailid < self.m_nMinMailID or int64.equals(self.m_nMinMailID, 0) then
		self.m_nMinMailID = recvValue.m_mailid;
	end
	
	-- �ϴν��յ���Сid�������ֵȥ��δ��ȡ�����ʼ�
	if recvValue.m_mailid < self.m_nLastRecvMinMailID or int64.equals( self.m_nLastRecvMinMailID, 0 ) then
		self.m_nLastRecvMinMailID = recvValue.m_mailid;
	end
	
	-- ����
	self:Sort();
end

-- ����
function Mail:Sort()
	table.sort( self.m_Mails, function( a, b )
		if a.m_mailid < b.m_mailid then
			return true;
		else
			return false;
		end
	end )
end

-- �ж������Ƿ���������ʽ
function Mail:IsTag(con, tag)
    local mask = string.sub(con, 1, string.len(tag));
    if mask == tag then
        return true;
    else
        return false;
    end
end

-- ȫ��
G_Mail = nil;
function GetMail()
    if G_Mail == nil then
        G_Mail = Mail.new();
    end
    return G_Mail;
end
