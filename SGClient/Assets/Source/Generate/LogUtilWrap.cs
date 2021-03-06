﻿//this source code was auto-generated by tolua#, do not modify it
using System;
using LuaInterface;

public class LogUtilWrap
{
	public static void Register(LuaState L)
	{
		L.BeginClass(typeof(LogUtil), typeof(System.Object));
		L.RegFunction("GetInstance", GetInstance);
		L.RegFunction("Create", Create);
		L.RegFunction("Close", Close);
		L.RegFunction("WriteGame", WriteGame);
		L.RegFunction("WriteNet", WriteNet);
		L.RegFunction("MarkStart", MarkStart);
		L.RegFunction("MarkEnd", MarkEnd);
		L.RegFunction("New", _CreateLogUtil);
		L.RegFunction("__tostring", ToLua.op_ToString);
		L.EndClass();
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int _CreateLogUtil(IntPtr L)
	{
		try
		{
			int count = LuaDLL.lua_gettop(L);

			if (count == 0)
			{
				LogUtil obj = new LogUtil();
				ToLua.PushObject(L, obj);
				return 1;
			}
			else
			{
				return LuaDLL.luaL_throw(L, "invalid arguments to ctor method: LogUtil.New");
			}
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int GetInstance(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 0);
			LogUtil o = LogUtil.GetInstance();
			ToLua.PushObject(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int Create(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			LogUtil obj = (LogUtil)ToLua.CheckObject(L, 1, typeof(LogUtil));
			string arg0 = ToLua.CheckString(L, 2);
			bool o = obj.Create(arg0);
			LuaDLL.lua_pushboolean(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int Close(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 1);
			LogUtil obj = (LogUtil)ToLua.CheckObject(L, 1, typeof(LogUtil));
			obj.Close();
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int WriteGame(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			LogUtil obj = (LogUtil)ToLua.CheckObject(L, 1, typeof(LogUtil));
			string arg0 = ToLua.CheckString(L, 2);
			obj.WriteGame(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int WriteNet(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			LogUtil obj = (LogUtil)ToLua.CheckObject(L, 1, typeof(LogUtil));
			string arg0 = ToLua.CheckString(L, 2);
			obj.WriteNet(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int MarkStart(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			LogUtil obj = (LogUtil)ToLua.CheckObject(L, 1, typeof(LogUtil));
			string arg0 = ToLua.CheckString(L, 2);
			obj.MarkStart(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int MarkEnd(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			LogUtil obj = (LogUtil)ToLua.CheckObject(L, 1, typeof(LogUtil));
			string arg0 = ToLua.CheckString(L, 2);
			obj.MarkEnd(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}
}

