-- 界面
local m_Dlg = nil;
local m_uiScrollView = nil; --UnityEngine.GameObject
local m_uiContent = nil; --UnityEngine.GameObject
local m_uiUIP_ChatItem = nil; --UnityEngine.GameObject
local m_uiChannelBtn1 = nil; --UnityEngine.GameObject
local m_uiChannelBtn2 = nil; --UnityEngine.GameObject
local m_uiChatEdit = nil; --UnityEngine.GameObject
local m_uiUIP_ChatItemSelf = nil; --UnityEngine.GameObject
local m_uiInput = nil; --UnityEngine.GameObject
local m_uiUIP_ChatTime = nil; --UnityEngine.GameObject
local m_uiUIP_ChatSystalk = nil; --UnityEngine.GameObject
local m_objectPool = {};
local m_SelectChannel = 0;

-- 打开界面
function ChatDlgOpen()
	m_Dlg = eye.uiManager:Open( "ChatDlg" );
end

-- 隐藏界面
function ChatDlgClose()
	if m_Dlg == nil then
		return;
	end
	
	eye.uiManager:Close( "ChatDlg" );
end

-- 删除界面
function ChatDlgDestroy()
	GameObject.Destroy( m_Dlg );
	m_Dlg = nil;
end

----------------------------------------
-- 事件
----------------------------------------

-- 所属按钮点击时调用
function ChatDlgOnEvent( nType, nControlID, value, gameObject )
	if nType == UI_EVENT_CLICK then
        if nControlID == -1 then
            ChatDlgClose();
		elseif nControlID == 1 then
			ChatDlgSend();
		elseif nControlID == 2 then
		elseif nControlID == 3 then
		elseif nControlID == 4 then
        end
	end
end

-- 载入时调用
function ChatDlgOnAwake( gameObject )
	-- 控件赋值	
	local objs = gameObject:GetComponent( typeof(UISystem) ).relatedGameObject;
	m_uiScrollView = objs[0];
	m_uiContent = objs[1];
	m_uiUIP_ChatItem = objs[2];
	m_uiChannelBtn1 = objs[3];
	m_uiChannelBtn2 = objs[4];
	m_uiChatEdit = objs[5];
	m_uiUIP_ChatItemSelf = objs[6];
	m_uiInput = objs[7];
	m_uiUIP_ChatTime = objs[8];
	m_uiUIP_ChatSystalk = objs[9];
end

-- 界面初始化时调用
function ChatDlgOnStart( gameObject )
	
end

-- 界面显示时调用
function ChatDlgOnEnable( gameObject )
	
end

-- 界面隐藏时调用
function ChatDlgOnDisable( gameObject )
	
end

-- 界面删除时调用
function ChatDlgOnDestroy( gameObject )
	m_Dlg = nil;
end

-- 每帧调用
function ChatDlgOnLogic( gameObject )
	
end


----------------------------------------
-- 自定
----------------------------------------
function ChatDlgShow()
	ChatDlgOpen();
--[[	for i=1, 10, 1 do
		ChatDlgAddMsg( 1, math.random(0,5), math.random(1,100), "wwdadwad", 1, "BloodImage继承至RawImage，所以只能接收Texture类型的图片源，他主要负责的就是根据血条的长度对图片进行循环排版" )
	end--]]
end

-- 添加聊天消息
function ChatDlgAddMsg( recvValue )
	local uiObj = nil;
	if recvValue.m_actorid == GetPlayer().m_actorid then
		uiObj = GameObject.Instantiate( m_uiUIP_ChatItemSelf );
	else
		uiObj = GameObject.Instantiate( m_uiUIP_ChatItem );
	end
	
	local content = uiObj.transform:Find("Content");
	content.transform:Find("Head/Back"):GetComponent( "Image" ).sprite = PlayerHeadSprite( recvValue.m_shape );
	content.transform:Find("Name"):GetComponent( "YlyRichText" ).text = "<emote=001><color=00AE01FF>Lv."..recvValue.m_level.." "..recvValue.m_name.."</color> <color=00FFC0FF>青州</color>"
	content.transform:Find("Text"):GetComponent( "YlyRichText" ).text = recvValue.m_msg
	content.transform:Find("Back"):GetComponent( "UIAutoSize" ):Dirty();
	uiObj.transform:GetComponent( "UIAutoSize" ):Dirty();
	uiObj.transform:SetParent( m_uiContent.transform );
	uiObj.transform.localScale = Vector3.one;
	uiObj.gameObject:SetActive( true );
	
	table.insert( m_objectPool, uiObj );
	m_uiScrollView:GetComponent("ScrollRect"):ResetScroll();
	m_uiScrollView:GetComponent("ScrollRect"):ScrollToBottom();
	
	--recvValue.m_msg = "组件实际文本宽高的获取组件实际文本宽高的获取组件实际文本宽高的获取组件实际文本宽高的获取"
	--ChatDlgAddSysTalk( recvValue )
end

-- 添加系统消息
function ChatDlgAddSysTalk( recvValue )
	local uiObj = GameObject.Instantiate( m_uiUIP_ChatSystalk );
	--uiObj.transform:Find("Content/Name"):GetComponent( "UIText" ).text = "<emote=001><color=00AE01FF>Lv."..recvValue.m_level.." "..recvValue.m_name.."</color> <color=00FFC0FF>青州</color>"
	uiObj.transform:Find("Content/Text"):GetComponent( "UIText" ).text = recvValue.m_msg
	uiObj.transform:Find("Content/Back"):GetComponent( "UIAutoSize" ):Dirty();
	uiObj.transform:GetComponent( "UIAutoSize" ):Dirty();
	uiObj.transform:SetParent( m_uiContent.transform );
	uiObj.transform.localScale = Vector3.one;
	uiObj.gameObject:SetActive( true );
	m_uiScrollView:GetComponent("ScrollRect"):ScrollToBottom();
end

-- 发送消息
function ChatDlgSend()
	local msg = m_uiInput:GetComponent( "UIInputField" ).text;
	if msg == "" then
		return;
	end
	m_uiInput:GetComponent("UIInputField").text = "";
	
	-- GM指令检查
	local cmdsign = string.sub(msg, 1, 1);
    if cmdsign == "." then
        local str = string.sub(msg, 2);
        local strarray = string.split(str, " ");
        if GMCommandCheck(strarray) == true then
            return;
        end
    end
	
	-- 发送
	local sendValue = {};
	sendValue.m_channel = m_SelectChannel;
	sendValue.m_msg = msg;
	sendValue.m_msglen = string.len( msg );
	netsend_chat_C( sendValue );
end

-- 接收消息
-- m_actorid=0,m_shape=0,m_level=0,m_namelen=0,m_name="[m_namelen]",m_frame=0,m_zone=0,m_place=0,m_msglen=0,m_msg="[m_msglen]",m_optime=0,m_channel=0,m_nation=0,
function ChatDlgRecv( recvValue )
	ChatDlgAddMsg( recvValue )
end
