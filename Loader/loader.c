#include "pch.h"

// ��������
#pragma comment(linker, "/EXPORT:DsRoleFreeMemory=_JMP_DsRoleFreeMemory,@1")
#pragma comment(linker, "/EXPORT:DsRoleGetPrimaryDomainInformation=_JMP_DsRoleGetPrimaryDomainInformation,@2")
// �궨��
#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)
#define ALCPP EXPORT NAKED
#define ALSTD  EXPORT NAKED void __stdcall
#define ALCFAST  EXPORT NAKED void __fastcall
#define ALCDECL  NAKED void __cdecl
//ȫ�ֱ���

DWORD dwRetaddress[3];                          //��ŷ��ص�ַ

// �ڲ����� ��ȡ��ʵ������ַ
TCHAR szTemp[MAX_PATH] = { 0 };
FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	//VMProtectBegin("GetAddress");
	FARPROC fpAddress;
	fpAddress = GetProcAddress(g_hDll, pszProcName);
	if (fpAddress == NULL)
	{
		swprintf_s(szTemp, MAX_PATH, L"WC �޷��ҵ����� :%hs �ĵ�ַ ", pszProcName);
		MessageBox(NULL, szTemp, L"����", MB_OK);
		ExitProcess(-2);
	}
	//������ʵ��ַ
	return fpAddress;
	//VMProtectEnd();
}

ALCDECL JMP_DsRoleFreeMemory()
{
	//����ע�;���OD���Եó� ���뻷��:win10 x64 vs2013�� 
			//һ�������������Ϊ����Ϊ   ע���ջƽ��
	GetAddress("DsRoleFreeMemory");
	//��ʱջ�����ֵ��Ƿ��ص�ַ,��Ϊ����ǰ��û���ƻ���ջ
	__asm pop dwRetaddress[1]                       //������������˿�����call,Ϊʲô��call����Ϊ�����ֱ��jmp�Ļ� ���ȡִ�з���ֵ�е�����
		__asm call eax                              //�ѷ��ص�ַ��ջ����ʱ����൱��ԭ���ķ��ص�ַ������call����һ��ָ���ַ��ջ��������ʵ�������غ��������¶�ؿ���Ȩ
		//һ����������������Ϊ����Ϊ  ע���ջƽ��
	__asm jmp dword ptr dwRetaddress[1]         //����ԭ����
}

ALCDECL JMP_DsRoleGetPrimaryDomainInformation()
{
	//����ע�;���OD���Եó� ���뻷��:win10 x64 vs2013�� 
			//һ�������������Ϊ����Ϊ   ע���ջƽ��
	GetAddress("DsRoleGetPrimaryDomainInformation");
	//��ʱջ�����ֵ��Ƿ��ص�ַ,��Ϊ����ǰ��û���ƻ���ջ
	__asm pop dwRetaddress[2]                       //������������˿�����call,Ϊʲô��call����Ϊ�����ֱ��jmp�Ļ� ���ȡִ�з���ֵ�е�����
		__asm call eax                              //�ѷ��ص�ַ��ջ����ʱ����൱��ԭ���ķ��ص�ַ������call����һ��ָ���ַ��ջ��������ʵ�������غ��������¶�ؿ���Ȩ
		//һ����������������Ϊ����Ϊ  ע���ջƽ��
	__asm jmp dword ptr dwRetaddress[2]         //����ԭ����
}