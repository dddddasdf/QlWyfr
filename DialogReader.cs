using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

[SerializeField]
public struct DialogData
{
    //��ȭ ���� ����ü
    public string Chapter;  //é��
    public NPCIndex ID;    //�ش� ��縦 ����ϴ� ������Ʈ�� ID
    public string Script;   //��� ����
    public int ScriptID;    //����� ID
    public int IsEnd;   //��ȭ ������ Ȯ�ο�
}

public class JsonClass
{
    public List<DialogData> DailogList { get; set; }
}

[System.Serializable]
public class DialogReader : MonoBehaviour
{
    //private Dictionary<int, DialogReader> DicDialogLoadText;
    
    //private int ID; //������Ʈ���� ������ �ִ� ID
    //private int Chapter;    //���� é��
    //private string ScriptText;  //��ȭ ����

    private List<DialogData> DialogList = new List<DialogData>();   //json �Ľ� ���� ���� ����Ʈ

    public JObject JObejctTest = new JObject();
    


    //private  = new List<DialogData>();

    
    public static DialogReader Instance { get; private set; }   //����ü ����� ���� ����

    private void Awake()
    {
        //����ü ����
        if (null == Instance)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);

            InitDialogData();

            return;
        }
        Destroy(gameObject);
        //����ü ���� ����
    }


    public void InitDialogData()
    {
        TextAsset TextStack = Resources.Load("Data/Dialog") as TextAsset;
        string Teststr;
        
        if (TextStack == null)
        {
            Debug.Log("Dailog File Load Failed");
            //return;
        }
        else
        {
            Debug.Log("Dailog File Load Success");
        }
        

        //var JsonTmp = JsonConvert.DeserializeObject<List<DialogData>>(TextStack.text);

        DialogList = JsonConvert.DeserializeObject<List<DialogData>>(TextStack.text);   //����Ʈ�� json ���� ������ȭ�Ͽ� ���


        Teststr = File.ReadAllText(Application.dataPath + "/Resources/Data/Dialog.json");
        //StreamReader TestReader = File.OpenText(Teststr);
        //JsonTextReader reader = new JsonTextReader(TestReader);
        JObejctTest = JObject.Parse(Teststr);   //�� ������ �� �� �����͸� �� �Դ� �ǵ� �װ� �ͳ� ��¥


        //this.DicDialogLoadText = new Dictionary<int, DialogReader>();


        //var jlist = JsonConvert.DeserializeObject<List<DialogReader>>(oj.text);

        //foreach(var data in jlist)
        //{
        //    this.DicDialogLoadText.Add(data.ID, data);
        //}
    }

    public string GetDialogScript(NPCIndex NPCID, int ScriptID, out int IsEnd)
    {
        DialogData TemporaryStruct = DialogList.Find(x => x.ID == NPCID && x.ScriptID == ScriptID);   //Find�� ���ٽ� ����� �̳� �����

        IsEnd = TemporaryStruct.IsEnd;

        return TemporaryStruct.Script;
    }

    //��ũ��Ʈ�� ���� �̻��� �� ����...
    //�ƴ� �̻��� �� �������� �𸥴�..
    //�ƴ� �̻��� ��..
    //������ ������ ����
}
