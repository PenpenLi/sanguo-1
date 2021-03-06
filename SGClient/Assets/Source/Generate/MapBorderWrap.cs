﻿//this source code was auto-generated by tolua#, do not modify it
using System;
using LuaInterface;

public class MapBorderWrap
{
	public static void Register(LuaState L)
	{
		L.BeginClass(typeof(MapBorder), typeof(UnityEngine.MonoBehaviour));
		L.RegFunction("PlaySize", PlaySize);
		L.RegFunction("SetSize", SetSize);
		L.RegFunction("SetColor", SetColor);
		L.RegFunction("Stop", Stop);
		L.RegFunction("__eq", op_Equality);
		L.RegFunction("__tostring", ToLua.op_ToString);
		L.RegVar("cellSize", get_cellSize, set_cellSize);
		L.RegVar("speed", get_speed, set_speed);
		L.RegVar("waitOnMax", get_waitOnMax, set_waitOnMax);
		L.RegVar("space", get_space, set_space);
		L.EndClass();
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int PlaySize(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			MapBorder obj = (MapBorder)ToLua.CheckObject(L, 1, typeof(MapBorder));
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			obj.PlaySize(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int SetSize(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			MapBorder obj = (MapBorder)ToLua.CheckObject(L, 1, typeof(MapBorder));
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			obj.SetSize(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int SetColor(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			MapBorder obj = (MapBorder)ToLua.CheckObject(L, 1, typeof(MapBorder));
			UnityEngine.Color arg0 = ToLua.ToColor(L, 2);
			obj.SetColor(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int Stop(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 1);
			MapBorder obj = (MapBorder)ToLua.CheckObject(L, 1, typeof(MapBorder));
			obj.Stop();
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int op_Equality(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			UnityEngine.Object arg0 = (UnityEngine.Object)ToLua.ToObject(L, 1);
			UnityEngine.Object arg1 = (UnityEngine.Object)ToLua.ToObject(L, 2);
			bool o = arg0 == arg1;
			LuaDLL.lua_pushboolean(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_cellSize(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			UnityEngine.Vector2 ret = obj.cellSize;
			ToLua.Push(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index cellSize on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_speed(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			float ret = obj.speed;
			LuaDLL.lua_pushnumber(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index speed on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_waitOnMax(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			float ret = obj.waitOnMax;
			LuaDLL.lua_pushnumber(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index waitOnMax on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_space(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			float ret = obj.space;
			LuaDLL.lua_pushnumber(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index space on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_cellSize(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			UnityEngine.Vector2 arg0 = ToLua.ToVector2(L, 2);
			obj.cellSize = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index cellSize on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_speed(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			obj.speed = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index speed on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_waitOnMax(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			obj.waitOnMax = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index waitOnMax on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_space(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			MapBorder obj = (MapBorder)o;
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			obj.space = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index space on a nil value" : e.Message);
		}
	}
}

