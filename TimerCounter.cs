using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text.RegularExpressions;

public class TimerCounter : MonoBehaviour
{
    //カウントダウン
    public float countdown = 0.0f;

    //時間を表示するText型の変数
    public Text timeText;

    //ポーズしているかどうか
    private bool isPose = true;

    private int time;
    private int min;

    private int start = 0;

    //今回の勉強時間
    private int nowtime;

    private IsTimer it;
    private DataSample ds;

    // Start is called before the first frame update
    void Start()
    {
        ds = FindObjectOfType<DataSample>();
        it = FindObjectOfType<IsTimer>();
        timeText.text = "00:00";
    }


    // Update is called once per frame
    void Update()
    {
        time = (int)countdown / 60;
        min = (int)countdown % 60;


        timeText.text = HanToZenNum(time.ToString().PadLeft(2, '0') + " : " + min.ToString().PadLeft(2, '0'));

        //ポーズ中かどうか
        if (isPose==false)
        {
            Timemeasure();
        }

        
    }

    public void Timemeasure()
    {
        if (countdown >= 60)
        {
            time = (int)countdown / 60;
            min = (int)countdown % 60;
        }

        //時間を表示する
        timeText.text = HanToZenNum(time.ToString().PadLeft(2, '0') + " : " + min.ToString().PadLeft(2, '0'));

        //時間をカウントする
        countdown -= Time.deltaTime;

        //countdownが0以下になったとき
        if ((countdown <= 0)&&(Pose==false))
        {
            timeText.text = "時間になりました！";
            ds.Saved += 1;
            Pose = true;
            it.IsPose = true;
            countdown = 0;
        }
    }

    public string HanToZenNum(string s)
    {
        return Regex.Replace(s, "[0-9]", p => ((char)(p.Value[0] - '0' + '０')).ToString());
    }


    public int TimeSet
    {
        get{return (int)countdown;}
        set{
            countdown += value;
            if (countdown <= 0)
            {
                countdown = 0;
            }
        }
    }

    public bool Pose
    {
        get { return isPose; }
        set { isPose = value; }
    }

    public int isStart
    {
        get { 
            return this.start; }
        set { 
            start = value;
            if (start == 1)
            {
                ds.Saved = 0;
                NowTime = (int)countdown;
                Debug.Log(NowTime);
            }
        }
    }

    public int NowTime
    {
        get { return this.nowtime; }
        set { nowtime = value; }
    }
}