MainCity = {};
MainCity.m_Camera = nil;
MainCity.m_LastSelect = nil;

-- ��ʼ��
function MainCity.Init()
	
end

-- ѡ����
function MainCity.BuildingSelect( transform )
	if MainCity.m_LastSelect ~= nil then
		-- �����ͬ����ֱ�ӷ���
		if MainCity.m_LastSelect == transform then
			return;
		end
		-- �ر�֮ǰ���䶯��
		MainCity.m_LastSelect:GetComponent("UITweenColor"):Kill(true);
		MainCity.m_LastSelect = nil;
	end
	
	local building = nil;	
	if transform == nil then
		
		return;
	else

		building = transform:GetComponent("CityBuilding");
		MainCity.m_LastSelect = transform;
		MainCity.m_LastSelect:GetComponent("UITweenColor"):Play(true);
	end
	
	
end