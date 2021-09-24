using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NCMB;

public class InputName : MonoBehaviour
{
    public InputField inputField;
    public Text text;
    private JsonTest jt;
    private NCMBObject dataManagement;

    // Start is called before the first frame update
    void Start()
    {
        inputField = inputField.GetComponent<InputField>();
        text = text.GetComponent<Text>();
        jt = FindObjectOfType<JsonTest>();
        dataManagement = new NCMBObject("dataManagement");
        SaveData savedata = jt.Load();
        dataManagement.ObjectId = savedata.id;
        dataManagement.FetchAsync((NCMBException e) => {
            if (e != null)
            {
                //エラー処理
            }
            else
            {
                //成功時の処理
                inputField.text = dataManagement["UserName"].ToString();
            }
        });
       
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void InputText()
    {
        text.text = inputField.text;
        SaveData sd = jt.Load();
        dataManagement.FetchAsync((NCMBException e) => {
            if (e != null)
            {
                //エラー処理
            }
            else
            {
                //成功時の処理
                dataManagement["UserName"] = inputField.text;
                dataManagement.SaveAsync();
            }
        });
        
        sd.name= inputField.text;
        jt.Save(sd);
    }

}
