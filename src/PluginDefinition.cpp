#include "PluginDefinition.h"
#include "menuCmdID.h"


#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
using namespace std;



HANDLE g_hMod;
CHAR* curJSON = NULL;

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
    g_hMod = hModule;
    //jsonDialog.init((HINSTANCE)g_hMod, nppData._nppHandle);
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(0, TEXT("Hello Notepad++"), hello, NULL, false);
    setCommand(1, TEXT("Hello (with dialog)"), helloDlg, NULL, false);
    setCommand(2, TEXT("regexDialog"), regexDialog, NULL, false);	//����Զ�������
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
    // Don't forget to deallocate your shortcut here
}

//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR* cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey* sk, bool check0nInit)
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void hello()
{
    // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    // Say hello now :
    // Scintilla control has no Unicode mode, so we use (char *) here
    ::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");
}

void helloDlg()
{
    ::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("Notepad++ Plugin Template"), MB_OK);
}

//ʵ���Զ���������
void sugon()
{
    ::MessageBox(NULL, TEXT("Hello, Sugon!"), TEXT("Notepad++ Plugin Template"), MB_OK);
}
void selectAllIfUnselectedAndSetCurJSON(size_t selectedTextLength, HWND curScintilla) {
    if (selectedTextLength == 0) {
        size_t allTextlength = ::SendMessage(curScintilla, SCI_GETLENGTH, 0, (LPARAM)curJSON);
        ::SendMessage(curScintilla, SCI_SETSELECTIONSTART, 0, (LPARAM)curJSON);
        ::SendMessage(curScintilla, SCI_SETSELECTIONEND, allTextlength, (LPARAM)curJSON);
        curJSON = new CHAR[allTextlength + 1];
    }
    else {
        curJSON = new CHAR[selectedTextLength + 1];
    }

    ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)curJSON);
}

// �ַ����ָ�����
vector<string> split(string origin_str, string splitStr) {
    /*string origin_str = "123#ab##cctry.com#";
    vector<string> res_vec;*/
    vector<string> res_vec;
    size_t ipos = 0, epos = 0;

    // ����#���зָ������vector��
    //size_t size = origin_str.find(splitStr, ipos);
    while ((epos = origin_str.find(splitStr, ipos)) != -1L) {
        string str = origin_str.substr(ipos, epos - ipos);
        if (!str.empty()) {
            res_vec.push_back(str);
        }
        ipos = epos + 1;
    }
    string str = origin_str.substr(ipos, epos - ipos);
    res_vec.push_back(str);
    cout << splitStr << "�ָ����ַ�������" << res_vec.size() << endl;
    return res_vec;
}

//ʵ���Զ���������
void regexDialog()
{

    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;

    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
    size_t start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    size_t end = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
    if (end < start)
    {
        size_t tmp = start;
        start = end;
        end = tmp;
    }

    size_t asciiTextLen = end - start;
    selectAllIfUnselectedAndSetCurJSON(asciiTextLen, curScintilla);

    //const char* fJson = "���ڵȵ���"+ curJSON;
    /*curJSON = strcat(curJSON , "������");
    ::SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)curJSON);*/




    //ʾ��1.
    //std::wstring strTest = L"1000001_v2000.csv";
    //std::wsmatch wm;
    //std::wregex wrx(L"(\\d+)_v(\\d+)\\.csv");

    //if (std::regex_match(strTest, wm, wrx))
    //{
    //    for (auto it : wm)
    //        std::wcout << it.str().c_str() << std::endl;
    //}


    /*std::wstring strTest = L"1000001_v2000.csv";
    std::wsmatch wm;
    std::wregex wrx(L"(\\d+)_v(\\d+)\\.csv");

    if (std::regex_match(strTest, wm, wrx))
    {
        for (auto it : wm)
            ::SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)it.str().c_str());
    }*/

    //ʾ��2.
    //string str = "Hello_2018!";
    //regex pattern2("(.{3})(.{2})_(\\d{4})");				//ƥ��3�������ַ�+2�������ַ�+�»���+4������
    //cout << regex_replace(curJSON, pattern2, "$1$3") << endl;	//�����Hel2018�����ַ����滻Ϊ��һ���͵��������ʽƥ�������
    //cout << regex_replace(str, pattern2, "$1$3$2") << endl;	//�����Hel2018lo������λ��˳��
    //string ss = regex_replace(str, pattern2, "$1$3$2");


    //char* pattern1Str = "��(.*)";
    ////pattern1Str.Replace("\\","\$");
    //regex pattern1(pattern1Str);
    //char* pattern2Str = "$1==dddd";
    //regex pattern2(pattern2Str);
    //string ss = regex_replace(curJSON, pattern1,pattern2Str);
    //
    //char* mm = (char*)ss.data();;

    //::SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)mm);


    //ʾ�� �������
    /*wstring str = L"��3��ָ�����	sm_metadata	";
    str.append(L"����һ�º���");
    ::SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)str.c_str());*/


    //��ȡ�ļ���ȡ������ʽ
    //wstring configPath = L".\\regexconfig.txt";
    string configPath = "D:\\Program Files (x86)\\Notepad++\\plugins\\NPPJSONViewer\\regexconfig.txt";

    string pstr1 = "";
    string pstr2 = "";

    string value = "";
    ifstream fi;
    fi.open(configPath);
    if (!fi.is_open()) {
        MessageBox(nppData._nppHandle, TEXT("regexconfig.txt ,�ļ�������"), TEXT("JSON Viewer"), MB_OK);
    }
    cout << fi.is_open() << endl;
    getline(fi, value);
    fi.close();

    vector<string> v = split(value, ";");
    if (v.size() > 1) {
        pstr1 = v[0];
        pstr2 = v[1];
    }
    regex pattern(pstr1);
    string replaceWstr = regex_replace(curJSON, pattern, pstr2);

    /*MessageBox(nppData._nppHandle,
        value, TEXT("JSON Viewer"), MB_OK);*/
    ::SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)replaceWstr.c_str());

    delete[] curJSON;
}