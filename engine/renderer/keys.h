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

#ifndef TINKER_KEYS_H
#define TINKER_KEYS_H

typedef enum {
  TINKER_KEY_UKNOWN = -1,
  TINKER_KEY_FIRST = 256,
  TINKER_KEY_ESCAPE = TINKER_KEY_FIRST,
  TINKER_KEY_F1,
  TINKER_KEY_F2,
  TINKER_KEY_F3,
  TINKER_KEY_F4,
  TINKER_KEY_F5,
  TINKER_KEY_F6,
  TINKER_KEY_F7,
  TINKER_KEY_F8,
  TINKER_KEY_F9,
  TINKER_KEY_F10,
  TINKER_KEY_F11,
  TINKER_KEY_F12,
  TINKER_KEY_UP,
  TINKER_KEY_DOWN,
  TINKER_KEY_LEFT,
  TINKER_KEY_RIGHT,
  TINKER_KEY_LSHIFT,
  TINKER_KEY_RSHIFT,
  TINKER_KEY_LCTRL,
  TINKER_KEY_RCTRL,
  TINKER_KEY_LALT,
  TINKER_KEY_RALT,
  TINKER_KEY_TAB,
  TINKER_KEY_ENTER,
  TINKER_KEY_BACKSPACE,
  TINKER_KEY_INSERT,
  TINKER_KEY_DEL,
  TINKER_KEY_PAGEUP,
  TINKER_KEY_PAGEDOWN,
  TINKER_KEY_HOME,
  TINKER_KEY_END,
  TINKER_KEY_KP_0,
  TINKER_KEY_KP_1,
  TINKER_KEY_KP_2,
  TINKER_KEY_KP_3,
  TINKER_KEY_KP_4,
  TINKER_KEY_KP_5,
  TINKER_KEY_KP_6,
  TINKER_KEY_KP_7,
  TINKER_KEY_KP_8,
  TINKER_KEY_KP_9,
  TINKER_KEY_KP_DIVIDE,
  TINKER_KEY_KP_MULTIPLY,
  TINKER_KEY_KP_SUBTRACT,
  TINKER_KEY_KP_ADD,
  TINKER_KEY_KP_DECIMAL,
  TINKER_KEY_KP_EQUAL,
  TINKER_KEY_KP_ENTER,
  TINKER_KEY_MOUSE_LEFT,
  TINKER_KEY_MOUSE_RIGHT,
  TINKER_KEY_MOUSE_MIDDLE,
  TINKER_KEY_JOYSTICK_1,
  TINKER_KEY_JOYSTICK_2,
  TINKER_KEY_JOYSTICK_3,
  TINKER_KEY_JOYSTICK_4,
  TINKER_KEY_JOYSTICK_5,
  TINKER_KEY_JOYSTICK_6,
  TINKER_KEY_JOYSTICK_7,
  TINKER_KEY_JOYSTICK_8,
  TINKER_KEY_JOYSTICK_9,
  TINKER_KEY_JOYSTICK_10,
  TINKER_KEY_JOYSTICK_11,
  TINKER_KEY_JOYSTICK_12,
  TINKER_KEY_JOYSTICK_13,
  TINKER_KEY_JOYSTICK_14,
  TINKER_KEY_JOYSTICK_15,
  TINKER_KEY_JOYSTICK_16,
  TINKER_KEY_JOYSTICK_17,
  TINKER_KEY_JOYSTICK_18,
  TINKER_KEY_JOYSTICK_19,
  TINKER_KEY_JOYSTICK_20,
} tinker_keys_t;

typedef enum {
  TINKER_MOUSE_RELEASED = 0,
  TINKER_MOUSE_PRESSED = 1,
  TINKER_MOUSE_DOUBLECLICK = 2,
} tinker_mouse_state_t;

#endif