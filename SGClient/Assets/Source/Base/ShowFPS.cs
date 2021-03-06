using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ShowFPS : MonoBehaviour
{

    public Text m_uiText;
    public float f_UpdateInterval = 0.5F;
    private float f_LastInterval;
    private int i_Frames = 0;
    private float f_Fps;

    void Start()
    {
        f_LastInterval = Time.realtimeSinceStartup;
        i_Frames = 0;
    }

    void Update()
    {
        ++i_Frames;

        if ( Time.realtimeSinceStartup > f_LastInterval + f_UpdateInterval )
        {
            f_Fps = i_Frames / ( Time.realtimeSinceStartup - f_LastInterval );
            i_Frames = 0;
            f_LastInterval = Time.realtimeSinceStartup;
            if ( f_Fps <= 15.0 )
            {
                m_uiText.color = new Color( 1, 0, 0, 1 );
            }
            else if ( f_Fps <= 24.0 )
            {
                m_uiText.color = new Color( 1, 1, 0, 1 );
            }
            else
            {
                m_uiText.color = new Color( 0, 1, 0, 1 );
            }
            m_uiText.text = "FPS:" + f_Fps.ToString( "f2" );
        }
    }
}

