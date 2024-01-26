#pragma once

#include <d3d11.h>
#include <dwmapi.h>
#include "../Utils/Math/Math.h"
#include "../Utils/Memory/Memory.h"
#include "../MenuConfig.hpp"
#include "../Entity/Entity.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Shcore.lib")

#define GREEN ImColor(0, 255, 0)
#define RED ImColor(255, 0, 0)
#define BLUE ImColor(0, 0, 255)
#define SKYBLUE ImColor(0, 255, 255)
#define WHITE ImColor(1.f, 1.f, 1.f, 1.f)

namespace Overlay
{

    inline RECT GameSize = {};
   inline  POINT GamePoint = {};

    // Menu
     inline bool ShowMenu = false;


    void m_Menu();

    void Cheat();

    void ToggleButton(const char* str_id, bool* v);

       void ShowRawImage(unsigned char* image, int width, int height);
 
      void Text(std::string Text, Vec2 Pos, ImColor Color, float FontSize = 15, bool KeepCenter = false);

      void MyText(std::string Text, bool isCenter);
   
      void StrokeText(std::string Text, Vec2 Pos, ImColor Color, float FontSize = 15, bool KeepCenter = false);
    
      void Rectangle(Vec2 Pos, Vec2 Size, ImColor Color, float Thickness, float Rounding = 0);
     void RectangleFilled(Vec2 Pos, Vec2 Size, ImColor Color, float Rounding = 0, int Nums = 15);
     void RectangleFilledGraident(Vec2 Pos, Vec2 Size, ImColor TopColor, ImColor BotColor, float Rounding, int Nums = 15);
    
      void Line(Vec2 From, Vec2 To, ImColor Color, float Thickness);
    
      void Circle(Vec2 Center, float Radius, ImColor Color, float Thickness, int Num = 50);
      void CircleFilled(Vec2 Center, float Radius, ImColor Color, int Num = 50);
   
      void ConnectPoints(std::vector<Vec2> Points, ImColor Color, float Thickness);
    
      void Arc(ImVec2 Center, float Radius, ImColor Color, float Thickness, float Aangle_begin, float Angle_end, float Nums = 15);
   
      void MyCheckBox(const char* str_id, bool* v);
     void MyCheckBox2(const char* str_id, bool* v);
      void MyCheckBox3(const char* str_id, bool* v);
      void MyCheckBox4(const char* str_id, bool* v);
   
     void ShadowRectFilled(Vec2 Pos, Vec2 Size, ImColor RectColor, ImColor ShadowColor, float ShadowThickness, Vec2 ShadowOffset, float Rounding = 0);
   
     void ShadowCircle(Vec2 Pos, float Radius, ImColor CircleColor, ImColor ShadowColor, float ShadowThickness, Vec2 ShadowOffset, int Num = 30);
    
      bool SliderScalarEx1(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
      bool SliderScalarEx2(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);

    
      void OpenWebpage(const char* url);
      void OpenWebpageButton(const char* label, const char* url);

     void MyProgressBar(float fraction, const ImVec2& Size, const char* overlay, ImVec4 Color);
      void SwitchButton(const char* str_id, bool* v);

};

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

static bool IsKeyDown(int VK)
{
    return (GetAsyncKeyState(VK) & 0x8000) != 0;
}

static void LoadStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // Border
    style.WindowBorderSize = 0.f;
    style.FrameBorderSize = 0.f;
    style.ChildBorderSize = 1.f;

    // Roundering
    style.WindowRounding = 6.f;
    style.FrameRounding = 2.f;
    style.ChildRounding = 6.f;
    style.PopupRounding = 3.f;

    style.WindowPadding = ImVec2(12.f, 12.f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.GrabMinSize = 6;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.89f, 0.10f, 0.44f, 1.00f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.50f, 0.92f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.14f);
    colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.17f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.94f, 1.00f, 0.28f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.06f, 0.45f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.f, 0.f, 0.f, 0.f);

    colors[ImGuiCol_Button] = ImVec4(1.00f, 1.00f, 1.00f, 0.01f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.06f, 0.45f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.59f, 0.98f, 1.00f);
}

static void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

static void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

static void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

static bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}
