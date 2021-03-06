﻿//this source code was auto-generated by tolua#, do not modify it
using System;
using LuaInterface;

public class FileUtilWrap
{
	public static void Register(LuaState L)
	{
		L.BeginClass(typeof(FileUtil), typeof(System.Object));
		L.RegFunction("GetInstance", GetInstance);
		L.RegFunction("DestroyInstance", DestroyInstance);
		L.RegFunction("GetDataFromFile", GetDataFromFile);
		L.RegFunction("GetDataFromWWW", GetDataFromWWW);
		L.RegFunction("WriteFile", WriteFile);
		L.RegFunction("IsFileExist", IsFileExist);
		L.RegFunction("CopyDir", CopyDir);
		L.RegFunction("__tostring", ToLua.op_ToString);
		L.EndClass();
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int GetInstance(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 0);
			FileUtil o = FileUtil.GetInstance();
			ToLua.PushObject(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int DestroyInstance(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 0);
			FileUtil.DestroyInstance();
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int GetDataFromFile(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			FileUtil obj = (FileUtil)ToLua.CheckObject(L, 1, typeof(FileUtil));
			string arg0 = ToLua.CheckString(L, 2);
			byte[] o = obj.GetDataFromFile(arg0);
			ToLua.Push(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int GetDataFromWWW(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			FileUtil obj = (FileUtil)ToLua.CheckObject(L, 1, typeof(FileUtil));
			string arg0 = ToLua.CheckString(L, 2);
			byte[] o = obj.GetDataFromWWW(arg0);
			ToLua.Push(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int WriteFile(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 3);
			FileUtil obj = (FileUtil)ToLua.CheckObject(L, 1, typeof(FileUtil));
			string arg0 = ToLua.CheckString(L, 2);
			string arg1 = ToLua.CheckString(L, 3);
			obj.WriteFile(arg0, arg1);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int IsFileExist(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			FileUtil obj = (FileUtil)ToLua.CheckObject(L, 1, typeof(FileUtil));
			string arg0 = ToLua.CheckString(L, 2);
			bool o = obj.IsFileExist(arg0);
			LuaDLL.lua_pushboolean(L, o);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int CopyDir(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			string arg0 = ToLua.CheckString(L, 1);
			string arg1 = ToLua.CheckString(L, 2);
			FileUtil.CopyDir(arg0, arg1);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}
}

