#include "Gui/overlay.h"
#include <string>
#include <fstream>
#include <streambuf>
#include<shellapi.h>
#include<windows.h>

HWND GameHwnd = nullptr;
HWND OverlayHwnd = nullptr;

void ManagerTH();

int  main()
{

    if (!m.Init())
        return 0;

    if (!gGame.InitAddress())
    {
        std::cout << "[ERROR] Failed to call InitAddress()." << std::endl;
    }


    GameHwnd = FindWindowA(NULL, "Counter-Strike 2");
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    GetClientRect(GameHwnd, &Overlay::GameSize);

    while (Overlay::GameSize.right == 0 && Overlay::GameSize.bottom == 0)
    {
        GetClientRect(GameHwnd, &Overlay::GameSize);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ClientToScreen(GameHwnd, &Overlay::GamePoint);

    // Create Overlay
    WNDCLASSEXA wc = { sizeof(WNDCLASSEXA), 0, WndProc, 0, 0, NULL, NULL, NULL, NULL, "ALBERT", "WND", NULL };
    RegisterClassExA(&wc);
    OverlayHwnd = CreateWindowExA(NULL, wc.lpszClassName, wc.lpszMenuName, WS_POPUP | WS_VISIBLE, Overlay::GamePoint.x, Overlay::GamePoint.y, Overlay::GameSize.right, Overlay::GameSize.bottom, NULL, NULL, wc.hInstance, NULL);
    SetWindowDisplayAffinity(OverlayHwnd, WDA_EXCLUDEFROMCAPTURE); //hide overlay from all screen capture
    SetWindowLong(OverlayHwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
    SetLayeredWindowAttributes(OverlayHwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
    MARGINS margin = { -1 };
    DwmExtendFrameIntoClientArea(OverlayHwnd, &margin);

    if (!CreateDeviceD3D(OverlayHwnd))
    {
        CleanupDeviceD3D();
        UnregisterClassA(wc.lpszClassName, wc.hInstance);
        exit(0);
    }

    ShowWindow(OverlayHwnd, SW_SHOW);
    UpdateWindow(OverlayHwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;



    ImGui_ImplWin32_Init(OverlayHwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);


    ImVec4 clear_color = ImVec4(1.f, 1.f, 1.f, 0.f);



    std::thread(ManagerTH).detach();


    while (MenuConfig::Active)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                MenuConfig::Active = false;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        HWND ForegroundWindow = GetForegroundWindow();
        if (ForegroundWindow == GameHwnd)
        {
            HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
            SetWindowPos(OverlayHwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }

        // Menu
        if (Overlay::ShowMenu)
            Overlay::m_Menu();

        // Cheat
        if (true)
            Overlay::Cheat();

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(OverlayHwnd);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);

    return 0;
}


void ManagerTH()
{
    while (MenuConfig::Active)
    {

        HWND CheckHwnd = FindWindowA(NULL, "Counter-Strike 2");
        if (!CheckHwnd)
            MenuConfig::Active = false;

        // ShowMenu
        static bool menu_key = false;
        if (IsKeyDown(VK_INSERT) && !menu_key)
        {
            Overlay::ShowMenu = !Overlay::ShowMenu;

            if (Overlay::ShowMenu)
                SetWindowLong(OverlayHwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            else
                SetWindowLong(OverlayHwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);

            menu_key = true;
        }
        else if (!IsKeyDown(VK_INSERT) && menu_key)
        {
            menu_key = false;
        }

        RECT TmpRect = {};
        POINT TmpPoint = {};
        GetClientRect(GameHwnd, &TmpRect);
        ClientToScreen(GameHwnd, &TmpPoint);

        // Resizer
        if (TmpRect.left != Overlay::GameSize.left || TmpRect.bottom != Overlay::GameSize.bottom || TmpRect.top != Overlay::GameSize.top || TmpRect.right != Overlay::GameSize.right || TmpPoint.x != Overlay::GamePoint.x || TmpPoint.y != Overlay::GamePoint.y)
        {
            Overlay::GameSize = TmpRect;
            SetWindowPos(OverlayHwnd, nullptr, TmpPoint.x, TmpPoint.y, Overlay::GameSize.right, Overlay::GameSize.bottom, SWP_NOREDRAW);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
