// DriverController.cpp: определяет точку входа для консольного приложения.
//

#include "Misc.h"
#include "Cdriver.h"


CDriver* g_pDrv = new CDriver();
using namespace std;

DWORD GEtPid(char * name) {
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	if (Process32First(hsnap, &pe)) {
		while (Process32Next(hsnap, &pe)) {
			if (!_stricmp(name, pe.szExeFile)) {
				CloseHandle(hsnap);
				return pe.th32ProcessID;
			}
		}
	}
	CloseHandle(hsnap);

}
BOOL WINAPI CtrlHandle(DWORD dwCtrlType)
{
	g_pDrv->Destroyer();
	g_pDrv->UnloadDriver();
	Sleep(2000);
	system("sc queryex ObRegister.sys");
	Sleep(1000);
	return FALSE;
}
int main()
{
	SetConsoleCtrlHandler(CtrlHandle, true);

	g_pDrv->DriverLoad("ObRegister.sys");
	g_pDrv->OpenDriverDevice("//./p45h3sys");


	int buffer;
	char procname[50];
	int pider = 0;
	int ProcessPid = GEtPid("Game.exe");
	HANDLE Rerquest = 0;
	static int one = 0;
	DWORD retnl = 0;
	int BufferToRW = 1332;
	memadactr memd;


	printf("Game PID: %i\n", ProcessPid);
	
	while (1) {
		if(one != 0)
		system("cls");
		printf("1 - Input proc for precallback operation\n2 - free procfilter of precallback operation\n3 - send struct\n4 - Get HANDLE\n5 - Write Mem\n6 - Read\n7 - Valloc\n8 - Patch EPROCESS (BSOD)\n9 - Unload svc\nType: ");
		scanf_s("%i", &buffer);
		one = 1;


		if (buffer == 1) {
			scanf_s("%s", procname, 50);
			pider = GEtPid(procname);
			g_pDrv->SetupCallback(pider);
		}
		if (buffer == 2) { g_pDrv->FreeProcFilter(); }
			
		if (buffer == 3) {
			memd.i = 1000;
			memd.b = 150;
			g_pDrv->RequestToDriver(IOCTL_SENDSTRUCTTEST, &memd, sizeof(memd), 0, 0, &retnl);
		}

		if (buffer == 4) {
			scanf_s("%s", procname, 50);
			pider = GEtPid(procname);
			g_pDrv->RequestToDriver(IOCTL_OPENPROCESSCTL, &pider, sizeof(pider), &Rerquest, sizeof(Rerquest), &retnl);

			printf("HANDLE: 0x%X\n", Rerquest);
			if (CloseHandle(Rerquest)) printf("Ok\n");
			_getwch();
		}
		
		if (buffer == 5) {
			DWORD adr = 0x0;
			
			string str = "0xDEADDEAD";
			cin >> str;
			istringstream is(&str[2]);
			is >> hex >> adr;
			
			g_pDrv->WriteProcessMem(ProcessPid, &BufferToRW, 4, (DWORD)adr);
		}
		if (buffer == 6) {
			int buf;
			DWORD adr = 0x0;

			string str = "0xDEADDEAD";
			cin >> str;
			istringstream is(&str[2]);
			is >> hex >> adr;
			g_pDrv->ReadProcessMem(ProcessPid, &buf, sizeof(buf), (DWORD)adr);
			printf("Read buffer: %i\n\n", buf);
			system("pause");
		}
		if (buffer == 7) {
			DWORD dw;
			g_pDrv->VirtualAlloc(ProcessPid, 0x0, 200, &dw);
			printf("Allocated adr: 0x%X\n\n", dw);
			system("pause");
		}
		if (buffer == 8) {
			scanf_s("%s", procname, 50);
			pider = GEtPid(procname);
			
			g_pDrv->RequestToDriver(IOCTL_HIDEPROCESS, &pider, sizeof(pider), 0, 0, &retnl);
		}

		if (buffer == 9) {
			g_pDrv->Destroyer();
			g_pDrv->UnloadDriver();
			Sleep(2000);
			system("sc queryex ObRegister.sys");
			goto exit;
		//	break ;
		}
		Sleep(100);
	}


//	UnloadDriver();
	g_pDrv->Destroyer();
	g_pDrv->UnloadDriver();

	//printf("%i - pid\n", GEtPid("32.exe"));
	Sleep(2000);
	system("sc queryex ObRegister.sys");
	//pider = GEtPid("32.exe");
	exit:
	printf("%i - pid\n", pider);
	delete svc;
	delete g_pDrv;
	

	system("pause");
    return 0;
}

