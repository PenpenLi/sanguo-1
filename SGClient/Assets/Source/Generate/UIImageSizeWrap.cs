﻿//this source code was auto-generated by tolua#, do not modify it
using System;
using LuaInterface;

public class UIImageSizeWrap
{
	public static void Register(LuaState L)
	{
		
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int Dirty(IntPtr L)
	{
		try
		{
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
	static int get_uitext(IntPtr L)
	{
		object o = null;

		try
		{

			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index uitext on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_uitext(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);

			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index uitext on a nil value" : e.Message);
		}
	}
}

