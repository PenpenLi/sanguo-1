﻿//this source code was auto-generated by tolua#, do not modify it
using System;
using LuaInterface;

public class UIProgressWrap
{
	public static void Register(LuaState L)
	{
		L.BeginClass(typeof(UIProgress), typeof(UnityEngine.MonoBehaviour));
		L.RegFunction("SetValue", SetValue);
		L.RegFunction("Play", Play);
		L.RegFunction("Stop", Stop);
		L.RegFunction("OverPlay", OverPlay);
		L.RegFunction("Update", Update);
		L.RegFunction("__eq", op_Equality);
		L.RegFunction("__tostring", ToLua.op_ToString);
		L.RegVar("progress", get_progress, set_progress);
		L.RegVar("fullProgress", get_fullProgress, set_fullProgress);
		L.RegVar("mode", get_mode, set_mode);
		L.RegVar("callback", get_callback, set_callback);
		L.RegFunction("LuaCallback", UIProgress_LuaCallback);
		L.EndClass();
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int SetValue(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 2);
			UIProgress obj = (UIProgress)ToLua.CheckObject(L, 1, typeof(UIProgress));
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			obj.SetValue(arg0);
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int Play(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 5);
			UIProgress obj = (UIProgress)ToLua.CheckObject(L, 1, typeof(UIProgress));
			float arg0 = (float)LuaDLL.luaL_checknumber(L, 2);
			float arg1 = (float)LuaDLL.luaL_checknumber(L, 3);
			float arg2 = (float)LuaDLL.luaL_checknumber(L, 4);
			short arg3 = (short)LuaDLL.luaL_checknumber(L, 5);
			obj.Play(arg0, arg1, arg2, arg3);
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
			UIProgress obj = (UIProgress)ToLua.CheckObject(L, 1, typeof(UIProgress));
			obj.Stop();
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int OverPlay(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 1);
			UIProgress obj = (UIProgress)ToLua.CheckObject(L, 1, typeof(UIProgress));
			obj.OverPlay();
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int Update(IntPtr L)
	{
		try
		{
			ToLua.CheckArgsCount(L, 1);
			UIProgress obj = (UIProgress)ToLua.CheckObject(L, 1, typeof(UIProgress));
			obj.Update();
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
	static int get_progress(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UnityEngine.UI.Image ret = obj.progress;
			ToLua.Push(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index progress on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_fullProgress(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UnityEngine.UI.Image ret = obj.fullProgress;
			ToLua.Push(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index fullProgress on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_mode(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UIProgress.ProgressMode ret = obj.mode;
			ToLua.Push(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index mode on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int get_callback(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UIProgress.LuaCallback ret = obj.callback;
			ToLua.Push(L, ret);
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index callback on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_progress(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UnityEngine.UI.Image arg0 = (UnityEngine.UI.Image)ToLua.CheckUnityObject(L, 2, typeof(UnityEngine.UI.Image));
			obj.progress = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index progress on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_fullProgress(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UnityEngine.UI.Image arg0 = (UnityEngine.UI.Image)ToLua.CheckUnityObject(L, 2, typeof(UnityEngine.UI.Image));
			obj.fullProgress = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index fullProgress on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_mode(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UIProgress.ProgressMode arg0 = (UIProgress.ProgressMode)ToLua.CheckObject(L, 2, typeof(UIProgress.ProgressMode));
			obj.mode = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index mode on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int set_callback(IntPtr L)
	{
		object o = null;

		try
		{
			o = ToLua.ToObject(L, 1);
			UIProgress obj = (UIProgress)o;
			UIProgress.LuaCallback arg0 = null;
			LuaTypes funcType2 = LuaDLL.lua_type(L, 2);

			if (funcType2 != LuaTypes.LUA_TFUNCTION)
			{
				 arg0 = (UIProgress.LuaCallback)ToLua.CheckObject(L, 2, typeof(UIProgress.LuaCallback));
			}
			else
			{
				LuaFunction func = ToLua.ToLuaFunction(L, 2);
				arg0 = DelegateFactory.CreateDelegate(typeof(UIProgress.LuaCallback), func) as UIProgress.LuaCallback;
			}

			obj.callback = arg0;
			return 0;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e, o == null ? "attempt to index callback on a nil value" : e.Message);
		}
	}

	[MonoPInvokeCallbackAttribute(typeof(LuaCSFunction))]
	static int UIProgress_LuaCallback(IntPtr L)
	{
		try
		{
			int count = LuaDLL.lua_gettop(L);
			LuaFunction func = ToLua.CheckLuaFunction(L, 1);

			if (count == 1)
			{
				Delegate arg1 = DelegateFactory.CreateDelegate(typeof(UIProgress.LuaCallback), func);
				ToLua.Push(L, arg1);
			}
			else
			{
				LuaTable self = ToLua.CheckLuaTable(L, 2);
				Delegate arg1 = DelegateFactory.CreateDelegate(typeof(UIProgress.LuaCallback), func, self);
				ToLua.Push(L, arg1);
			}
			return 1;
		}
		catch(Exception e)
		{
			return LuaDLL.toluaL_exception(L, e);
		}
	}
}

