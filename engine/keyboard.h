#ifndef _KEYBOARD_H
#define _KEYBOARD_H

/* нужно прописать все кнопки */
#ifdef __WIN32

#define WE_BACKSPACE    8
#define WE_TAB          9
// ..
#define WE_ENTER        13
#define WE_RSHIFT       16
#define WE_LSHIFT       16
#define WE_RCTRL        17
#define WE_LCTRL        18
// ..
#define WE_CAPS         20
#define WE_ESC          27
// ..
#define WE_SPACE 		32
#define WE_PGUP         33
#define WE_PGDN         34
#define WE_END          35
#define WE_HOME         36
#define WE_LEFT         37
#define WE_UP           38
#define WE_RIGHT        39
#define WE_DOWN         40
// ..
#define WE_DELETE       46
// ..
#define WE_INSERT       45
#define WE_0            48
#define WE_1            49
#define WE_2            50
#define WE_3            51
#define WE_4            52
#define WE_5            53
#define WE_6            54
#define WE_7            55
#define WE_8            56
#define WE_9            57
// ..
#define WE_A            65
#define WE_B            66
#define WE_C            67
#define WE_D            68
#define WE_E            69
#define WE_F            70
#define WE_G            71
#define WE_H            72
#define WE_I            73
#define WE_J            74
#define WE_K            75
#define WE_L            76
#define WE_N            78
#define WE_M            77
#define WE_O            79
#define WE_P            80
#define WE_Q            81
#define WE_R            82
#define WE_S            83
#define WE_T            84
#define WE_U            85
#define WE_V            86
#define WE_W            87
#define WE_X            88
#define WE_Y            89
#define WE_Z            90
// ...
#define WE_LWIN         91
#define WE_RWIN         92
#define WE_MENU         93
// ..
#define WE_F1           112
#define WE_F2           113
#define WE_F3           114
#define WE_F4           115
#define WE_F5           116
#define WE_F6           117
#define WE_F8           118
#define WE_F9           119
#define WE_F10          120
#define WE_F11          121
// ...
#define WE_F12          123
// ...
#define WE_EQ           187
#define WE_LESS         188
#define WE_MINUS        189
#define WE_MORE         190
#define WE_SLASH        191
#define WE_GRAVE        192
// ...
#define WE_BACKSLASH    220

#else

#define WE_ESC         9
#define WE_1           10
#define WE_2           11
#define WE_3           12
#define WE_4           13
#define WE_5           14
#define WE_6           15
#define WE_7           16
#define WE_8           17
#define WE_9           18
#define WE_0           19
#define WE_MINUS       20
#define WE_EQ          21
#define WE_BACKSPACE   22
#define WE_TAB         23
#define WE_Q           24
#define WE_W           25
#define WE_E           26
#define WE_R           27
#define WE_T           28
#define WE_Y           29
#define WE_U           30
#define WE_I           31
#define WE_O           32
#define WE_P           33
#define WE_LBRK        34
#define WE_RBRK        35
#define WE_ENTER       36
#define WE_LCTRL       37
#define WE_A           38
#define WE_S           39
#define WE_D           40
#define WE_F           41
#define WE_G           42
#define WE_H           43
#define WE_J           44
#define WE_K           45
#define WE_L           46
#define WE_SEMICLN     47
#define WE_QUOTES      48
#define WE_GRAVE       49
#define WE_LSHIFT      50
#define WE_BACKSLASH   51
#define WE_Z           52
#define WE_X           53
#define WE_C           54
#define WE_V           55
#define WE_B           56
#define WE_N           57
#define WE_M           58
#define WE_LESS        59
#define WE_MORE        60
#define WE_SLASH       61
#define WE_RSHIFT      62

#define WE_LALT        64
#define WE_SPACE       65
#define WE_CAPS        66
#define WE_F1          67
#define WE_F2          68
#define WE_F3          69
#define WE_F4          70
#define WE_F5          71
#define WE_F6          72
#define WE_F7          73
#define WE_F8          74
#define WE_F9          75
#define WE_F10         76

#define WE_F11         95
#define WE_F12         96

#define WE_RCTRL       105
#define WE_PRINT       107
#define WE_RALT        108

#define WE_HOME        110
#define WE_UP          111
#define WE_PGUP        112
#define WE_LEFT        113
#define WE_RIGHT       114
#define WE_END         115
#define WE_DOWN        116
#define WE_PGDN        117
#define WE_INSERT      118
#define WE_DEL         119

#define WE_PAUSE       127

#define WE_WIN         133

#define WE_MENU        135

#endif

#endif
