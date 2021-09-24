using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class IsTimer : MonoBehaviour
{
    public Image isStart;
    private bool isPose = true;

    private string folderPath = "ボタン/ホーム/";

    // Start is called before the first frame update
    void Start()
    {
        isStart = this.GetComponent<Image>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public bool IsPose
    {
        get { return isPose; }
        set { 
            isPose = value;
            if (isPose == false)
            {
                isStart.sprite = Resources.Load<Sprite>(folderPath + "ストップ");
            }
            else
            {
                isStart.sprite = Resources.Load<Sprite>(folderPath + "start");
            }
        }
    }
}
