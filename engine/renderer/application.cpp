/*
Copyright (c) 2012, Lunar Workshop, Inc.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software must
display the following acknowledgement: This product includes software developed
by Lunar Workshop, Inc.
4. Neither the name of the Lunar Workshop nor the names of its contributors may
be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY LUNAR WORKSHOP INC ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL LUNAR WORKSHOP BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "application.h"

#include <OpenGL/OpenGL.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#ifdef __APPLE__
#include <unistd.h>
#endif

#include <common_platform.h>
#include <strutils.h>

#include "renderer.h"

CApplication *CApplication::s_pApplication = NULL;

CApplication::CApplication(int argc, char **argv) {
  s_pApplication = this;

  for (int i = 0; i < argc; i++)
    m_apszCommandLine.push_back(argv[i]);

  m_bIsOpen = false;
  m_bMultisampling = true;

  m_pRenderer = NULL;
  m_pConsole = NULL;

  SetMouseCursorEnabled(true);
  m_flLastMousePress = -1;
}

bool CApplication::OpenWindow(size_t iWidth, size_t iHeight, bool bFullscreen,
                              bool bResizeable) {
  glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);

  int ret = glfwInit();

  if (!ret) {
    printf("glfwInit failed\n");
    exit(1);
  }

  m_bFullscreen = bFullscreen;

  if (HasCommandLineSwitch("--fullscreen"))
    m_bFullscreen = true;

  if (HasCommandLineSwitch("--windowed"))
    m_bFullscreen = false;

  m_iWindowWidth = iWidth;
  m_iWindowHeight = iHeight;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);

  if (m_bMultisampling)
    glfwWindowHint(GLFW_SAMPLES, 4);

  glfwWindowHint(GLFW_DEPTH_BITS, 16);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 8);

  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);

  m_pWindow =
      glfwCreateWindow(iWidth, iHeight, "Math for Game Developers", NULL, NULL);

  if (!m_pWindow) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(m_pWindow);

  int iScreenWidth;
  int iScreenHeight;

  GetScreenSize(iScreenWidth, iScreenHeight);

  glfwSetWindowCloseCallback(m_pWindow, &CApplication::WindowCloseCallback);
  glfwSetWindowSizeCallback(m_pWindow, &CApplication::WindowResizeCallback);
  glfwSetKeyCallback(m_pWindow, &CApplication::KeyEventCallback);
  glfwSetCharCallback(m_pWindow, &CApplication::CharEventCallback);
  glfwSetCursorPosCallback(m_pWindow, &CApplication::MouseMotionCallback);
  glfwSetMouseButtonCallback(m_pWindow, &CApplication::MouseInputCallback);
  glfwSwapInterval(1);
  glfwSetTime(0.0);

  SetMouseCursorEnabled(true);

  gladLoadGL(glfwGetProcAddress);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(1.0);

  m_bIsOpen = true;

  m_pRenderer = CreateRenderer();
  m_pRenderer->Initialize();

  return true;
}

CApplication::~CApplication() { glfwTerminate(); }

void CApplication::SwapBuffers() {
  glfwSwapBuffers(m_pWindow);
  glfwPollEvents();
}

float CApplication::GetTime() { return (float)glfwGetTime(); }

bool CApplication::IsOpen() { return m_bIsOpen; }

void CApplication::Close() { m_bIsOpen = false; }

bool CApplication::HasFocus() {
  return glfwGetWindowAttrib(m_pWindow, GLFW_FOCUSED) == GL_TRUE;
}

void CApplication::Render() {}

void CApplication::WindowClose(GLFWwindow *window) {
  glfwSetWindowShouldClose(window, true);
  m_bIsOpen = false;
}

void CApplication::WindowResize(int w, int h) {
  m_iWindowWidth = w;
  m_iWindowHeight = h;

  if (m_pRenderer)
    m_pRenderer->WindowResize(w, h);

  Render();

  SwapBuffers();
}

void CApplication::MouseMotion(int x, int y){};

bool CApplication::MouseInput(int iButton, tinker_mouse_state_t iState) {
  return false;
}

tinker_keys_t MapKey(int c) {
  switch (c) {
  case GLFW_KEY_ESCAPE:
    return TINKER_KEY_ESCAPE;

  case GLFW_KEY_F1:
    return TINKER_KEY_F1;

  case GLFW_KEY_F2:
    return TINKER_KEY_F2;

  case GLFW_KEY_F3:
    return TINKER_KEY_F3;

  case GLFW_KEY_F4:
    return TINKER_KEY_F4;

  case GLFW_KEY_F5:
    return TINKER_KEY_F5;

  case GLFW_KEY_F6:
    return TINKER_KEY_F6;

  case GLFW_KEY_F7:
    return TINKER_KEY_F7;

  case GLFW_KEY_F8:
    return TINKER_KEY_F8;

  case GLFW_KEY_F9:
    return TINKER_KEY_F9;

  case GLFW_KEY_F10:
    return TINKER_KEY_F10;

  case GLFW_KEY_F11:
    return TINKER_KEY_F11;

  case GLFW_KEY_F12:
    return TINKER_KEY_F12;

  case GLFW_KEY_UP:
    return TINKER_KEY_UP;

  case GLFW_KEY_DOWN:
    return TINKER_KEY_DOWN;

  case GLFW_KEY_LEFT:
    return TINKER_KEY_LEFT;

  case GLFW_KEY_RIGHT:
    return TINKER_KEY_RIGHT;

  case GLFW_KEY_LEFT_SHIFT:
    return TINKER_KEY_LSHIFT;

  case GLFW_KEY_RIGHT_SHIFT:
    return TINKER_KEY_RSHIFT;

  case GLFW_KEY_LEFT_CONTROL:
    return TINKER_KEY_LCTRL;

  case GLFW_KEY_RIGHT_CONTROL:
    return TINKER_KEY_RCTRL;

  case GLFW_KEY_LEFT_ALT:
    return TINKER_KEY_LALT;

  case GLFW_KEY_RIGHT_ALT:
    return TINKER_KEY_RALT;

  case GLFW_KEY_TAB:
    return TINKER_KEY_TAB;

  case GLFW_KEY_ENTER:
    return TINKER_KEY_ENTER;

  case GLFW_KEY_BACKSPACE:
    return TINKER_KEY_BACKSPACE;

  case GLFW_KEY_INSERT:
    return TINKER_KEY_INSERT;

  case GLFW_KEY_DELETE:
    return TINKER_KEY_DEL;

  case GLFW_KEY_PAGE_UP:
    return TINKER_KEY_PAGEUP;

  case GLFW_KEY_PAGE_DOWN:
    return TINKER_KEY_PAGEDOWN;

  case GLFW_KEY_HOME:
    return TINKER_KEY_HOME;

  case GLFW_KEY_END:
    return TINKER_KEY_END;

  case GLFW_KEY_KP_0:
    return TINKER_KEY_KP_0;

  case GLFW_KEY_KP_1:
    return TINKER_KEY_KP_1;

  case GLFW_KEY_KP_2:
    return TINKER_KEY_KP_2;

  case GLFW_KEY_KP_3:
    return TINKER_KEY_KP_3;

  case GLFW_KEY_KP_4:
    return TINKER_KEY_KP_4;

  case GLFW_KEY_KP_5:
    return TINKER_KEY_KP_5;

  case GLFW_KEY_KP_6:
    return TINKER_KEY_KP_6;

  case GLFW_KEY_KP_7:
    return TINKER_KEY_KP_7;

  case GLFW_KEY_KP_8:
    return TINKER_KEY_KP_8;

  case GLFW_KEY_KP_9:
    return TINKER_KEY_KP_9;

  case GLFW_KEY_KP_DIVIDE:
    return TINKER_KEY_KP_DIVIDE;

  case GLFW_KEY_KP_MULTIPLY:
    return TINKER_KEY_KP_MULTIPLY;

  case GLFW_KEY_KP_SUBTRACT:
    return TINKER_KEY_KP_SUBTRACT;

  case GLFW_KEY_KP_ADD:
    return TINKER_KEY_KP_ADD;

  case GLFW_KEY_KP_DECIMAL:
    return TINKER_KEY_KP_DECIMAL;

  case GLFW_KEY_KP_EQUAL:
    return TINKER_KEY_KP_EQUAL;

  case GLFW_KEY_KP_ENTER:
    return TINKER_KEY_KP_ENTER;
  }

  if (c < 256)
    return (tinker_keys_t)TranslateKeyToQwerty(c);

  return TINKER_KEY_UKNOWN;
}

tinker_keys_t MapMouseKey(int c) {
  switch (c) {
  case GLFW_MOUSE_BUTTON_LEFT:
    return TINKER_KEY_MOUSE_LEFT;

  case GLFW_MOUSE_BUTTON_RIGHT:
    return TINKER_KEY_MOUSE_RIGHT;

  case GLFW_MOUSE_BUTTON_MIDDLE:
    return TINKER_KEY_MOUSE_MIDDLE;
  }

  return TINKER_KEY_UKNOWN;
}

tinker_keys_t MapJoystickKey(int c) {
  switch (c) {
  case GLFW_JOYSTICK_1:
    return TINKER_KEY_JOYSTICK_1;

  case GLFW_JOYSTICK_2:
    return TINKER_KEY_JOYSTICK_2;

  case GLFW_JOYSTICK_3:
    return TINKER_KEY_JOYSTICK_3;

  case GLFW_JOYSTICK_4:
    return TINKER_KEY_JOYSTICK_4;

  case GLFW_JOYSTICK_5:
    return TINKER_KEY_JOYSTICK_5;

  case GLFW_JOYSTICK_6:
    return TINKER_KEY_JOYSTICK_6;

  case GLFW_JOYSTICK_7:
    return TINKER_KEY_JOYSTICK_7;

  case GLFW_JOYSTICK_8:
    return TINKER_KEY_JOYSTICK_8;

  case GLFW_JOYSTICK_9:
    return TINKER_KEY_JOYSTICK_9;

  case GLFW_JOYSTICK_10:
    return TINKER_KEY_JOYSTICK_10;
  }

  return TINKER_KEY_UKNOWN;
}

void CApplication::MouseInputCallback(GLFWwindow *window, int a, int b, int c) {
  // TODO: This is a hack to get it to compile.
}

void CApplication::KeyEvent(GLFWwindow *window, int iKey, int iScancode,
                            int iAction, int iMods) {
  if (iAction == GLFW_REPEAT || iAction == GLFW_PRESS) {
    KeyPress(MapKey(iKey));
  } else {
    KeyRelease(MapKey(iKey));
  }
}

void CApplication::CharEvent(GLFWwindow *window, unsigned int c) {
  DoCharPress(c);
}

bool CApplication::KeyPress(int c) {
  if (c == TINKER_KEY_F4 && IsAltDown())
    exit(0);

  return DoKeyPress(c);
}

void CApplication::KeyRelease(int c) { DoKeyRelease(c); }

bool CApplication::IsCtrlDown() {
  return glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) ||
         glfwGetKey(m_pWindow, GLFW_KEY_RIGHT_CONTROL);
}

bool CApplication::IsAltDown() {
  return glfwGetKey(m_pWindow, GLFW_KEY_LEFT_ALT) ||
         glfwGetKey(m_pWindow, GLFW_KEY_RIGHT_ALT);
}

bool CApplication::IsShiftDown() {
  return glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SHIFT) ||
         glfwGetKey(m_pWindow, GLFW_KEY_RIGHT_SHIFT);
}

bool CApplication::IsMouseLeftDown() {
  return glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool CApplication::IsMouseRightDown() {
  return glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

bool CApplication::IsMouseMiddleDown() {
  return glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
}

void CApplication::GetMousePosition(double &x, double &y) {
  glfwGetCursorPos(m_pWindow, &x, &y);
}

void CApplication::SetMouseCursorEnabled(bool bEnabled) {
  if (bEnabled)
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  else
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  m_bMouseEnabled = bEnabled;
}

bool CApplication::IsMouseCursorEnabled() { return m_bMouseEnabled; }

inline class CRenderer *CApplication::CreateRenderer() {
  return new CRenderer(m_iWindowWidth, m_iWindowHeight);
}

bool CApplication::HasCommandLineSwitch(const char *pszSwitch) {
  for (size_t i = 0; i < m_apszCommandLine.size(); i++) {
    if (strcmp(m_apszCommandLine[i], pszSwitch) == 0)
      return true;
  }

  return false;
}

const char *CApplication::GetCommandLineSwitchValue(const char *pszSwitch) {
  // -1 to prevent buffer overrun
  for (size_t i = 0; i < m_apszCommandLine.size() - 1; i++) {
    if (strcmp(m_apszCommandLine[i], pszSwitch) == 0)
      return m_apszCommandLine[i + 1];
  }

  return NULL;
}
