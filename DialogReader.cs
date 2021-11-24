using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

[SerializeField]
public struct DialogData
{
    //대화 내용 구조체
    public string Chapter;  //챕터
    public NPCIndex ID;    //해당 대사를 사용하는 오브젝트의 ID
    public string Script;   //대사 내용
    public int ScriptID;    //대사의 ID
    public int IsEnd;   //대화 끝인지 확인용
}

public class JsonClass
{
    public List<DialogData> DailogList { get; set; }
}

[System.Serializable]
public class DialogReader : MonoBehaviour
{
    //private Dictionary<int, DialogReader> DicDialogLoadText;
    
    //private int ID; //오브젝트별로 가지고 있는 ID
    //private int Chapter;    //현재 챕터
    //private string ScriptText;  //대화 지문

    private List<DialogData> DialogList = new List<DialogData>();   //json 파싱 내용 담을 리스트

    public JObject JObejctTest = new JObject();
    


    //private  = new List<DialogData>();

    
    public static DialogReader Instance { get; private set; }   //단일체 선언용 정적 변수

    private void Awake()
    {
        //단일체 선언
        if (null == Instance)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);

            InitDialogData();

            return;
        }
        Destroy(gameObject);
        //단일체 선언 종료
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

        DialogList = JsonConvert.DeserializeObject<List<DialogData>>(TextStack.text);   //리스트에 json 내용 역직렬화하여 담기


        Teststr = File.ReadAllText(Application.dataPath + "/Resources/Data/Dialog.json");
        //StreamReader TestReader = File.OpenText(Teststr);
        //JsonTextReader reader = new JsonTextReader(TestReader);
        JObejctTest = JObject.Parse(Teststr);   //이 새끼는 왜 또 데이터를 못 먹는 건데 죽고 싶네 진짜


        //this.DicDialogLoadText = new Dictionary<int, DialogReader>();


        //var jlist = JsonConvert.DeserializeObject<List<DialogReader>>(oj.text);

        //foreach(var data in jlist)
        //{
        //    this.DicDialogLoadText.Add(data.ID, data);
        //}
    }

    public string GetDialogScript(NPCIndex NPCID, int ScriptID, out int IsEnd)
    {
        DialogData TemporaryStruct = DialogList.Find(x => x.ID == NPCID && x.ScriptID == ScriptID);   //Find에 람다식 쓰까기 겁나 힘드네

        IsEnd = TemporaryStruct.IsEnd;

        return TemporaryStruct.Script;
    }

    //스크립트가 뭔가 이상한 것 같다...
    //아니 이상한 건 나일지도 모른다..
    //아니 이상한 건..
    //진도를 나가질 못해
}
