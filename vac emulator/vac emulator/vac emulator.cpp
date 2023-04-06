#include <stdio.h>
#include <windows.h>

#define IOCTL_CODE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x999, METHOD_NEITHER, FILE_ANY_ACCESS)

DWORD WINAPI bypassVac(LPVOID lpParameter)
{
    HANDLE hDriver = CreateFileW(L"C/Path", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDriver == INVALID_HANDLE_VALUE)
    {
        printf("Failed to open Vac driver\n");
    }


    DWORD dwBytesReturned;
    BYTE buffer[0x10];
    memset(buffer, 0, sizeof(buffer));

    *(DWORD*)(buffer + 0x8) = 0x1337;
    *(DWORD*)(buffer + 0xC) = 0x1337;
    DeviceIoControl(hDriver, IOCTL_CODE, buffer, sizeof(buffer), buffer, sizeof(buffer), &dwBytesReturned, NULL);
    CloseHandle(hDriver);

    return 0;
}

int main()
{
    printf("Stopping Vac!");
    {
        HANDLE hThread = CreateThread(NULL, 0, &bypassVac, NULL, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);

    }

    printf("Vac Stopped!\n");



    return 0;
}
