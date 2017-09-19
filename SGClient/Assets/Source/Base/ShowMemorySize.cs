﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShowMemorySize : MonoBehaviour {

	public Text m_uiText;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		//m_uiText.text = Profiler.GetRuntimMemorySize（);

		/*UnityEngine.Object[] textures = Resources.FindObjectsOfTypeAll(typeof(Texture));
		UnityEngine.Object[] audioclips = Resources.FindObjectsOfTypeAll(typeof(AudioClip));
		UnityEngine.Object[] meshes = Resources.FindObjectsOfTypeAll(typeof(Mesh));

		for (int i = 0; i < textures.Length; ++i)
		{
			texturesMemSize += UnityEngine.Profiling.Profiler.GetRuntimeMemorySize(textures[i]);
		}

		for (int i = 0; i < audioclips .Length; ++i)
		{
			audioMemSize += UnityEngine.Profiling.Profiler.GetRuntimeMemorySize(audioclips [i]);
		}

		for (int i = 0; i < meshes .Length; ++i)
		{
			meshesMemSize += UnityEngine.Profiling.Profiler.GetRuntimeMemorySize(meshes [i]);
		}

		Debug.Log("AUDIO Memory Impact:" + audioMemSize.ToString("#,##0"));
		Debug.Log("MESHES Memory Impact:" + meshesMemSize.ToString("#,##0"));
		Debug.Log("TEXTURES Memory Impact:" + texturesMemSize.ToString("#,##0"));

		Debug.Log("Total usedHeapSize:" + UnityEngine.Profiling.Profiler.usedHeapSize.ToString("#,##0"));*/
	}

	//Memory
	private string sUserMemory;
	private string s;
	public bool OnMemoryGUI;
	private uint MonoUsedM;
	private uint AllMemory;
	[Range(0, 100)]
	public int MaxMonoUsedM = 50;
	[Range(0, 400)]
	public int MaxAllMemory = 200;
	void UpdateUsed()
	{
		sUserMemory = "";
		MonoUsedM = UnityEngine.Profiling.Profiler.GetMonoUsedSize() / 1000000;
		AllMemory = UnityEngine.Profiling.Profiler.GetTotalAllocatedMemory() / 1000000;


		sUserMemory += "MonoUsed:" + MonoUsedM + "M" + "\n";
		sUserMemory += "AllMemory:" + AllMemory + "M" + "\n";
		sUserMemory += "UnUsedReserved:" + UnityEngine.Profiling.Profiler.GetTotalUnusedReservedMemory() / 1000000 + "M" + "\n";


		s = "";
		s += " MonoHeap:" + UnityEngine.Profiling.Profiler.GetMonoHeapSize() / 1000 + "k";
		s += " MonoUsed:" + UnityEngine.Profiling.Profiler.GetMonoUsedSize() / 1000 + "k";
		s += " Allocated:" + UnityEngine.Profiling.Profiler.GetTotalAllocatedMemory() / 1000 + "k";
		s += " Reserved:" + UnityEngine.Profiling.Profiler.GetTotalReservedMemory() / 1000 + "k";
		s += " UnusedReserved:" + UnityEngine.Profiling.Profiler.GetTotalUnusedReservedMemory() / 1000 + "k";
		s += " UsedHeap:" + UnityEngine.Profiling.Profiler.usedHeapSize / 1000 + "k";
	}
}
