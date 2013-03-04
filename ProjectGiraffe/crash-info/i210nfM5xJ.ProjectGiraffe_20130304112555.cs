S/W Version Information
Model: Emulator
Tizen-Version: 2.0.0
Build-Number: Tizen_EMULATOR_20130215.1451
Build-Date: 2013.02.15 14:51:54

Crash Information
Process Name: /ProjectGiraffe
PID: 3431
Date: 2013-03-04 11:25:55(GMT+0900)
Executable File Path: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe
Signal: 11
      (SIGSEGV)
      si_code: -6
      signal sent by tkill (sent by pid 3431, uid 5000)
      TIMER: -2

Memory Information
MemTotal: 509660 KB
MemFree: 117572 KB
Buffers:  31104 KB
Cached:   209448 KB

Callstack Information (PID:3431)
Call Stack Count: 29
 0: /usr/lib/osp/libosp-uifw.so.1(+0x54d737) [0xb376d737]
 1: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe.exe(+0xb40e) [0xb3e7c40e]
 2: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe.exe(+0xb641) [0xb3e7c641]
 3: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui12_ControlImpl14CoreTouchEvent15ProcessListenerERKNS0_10_TouchInfoE+0x92b) [0xb34cd4cb]
 4: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui12_ControlImpl18CallOnTouchPressedERKNS0_8_ControlERKNS0_10_TouchInfoE+0x15a) [0xb34c450a]
 5: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui12_ControlImpl29_PropagatedTouchEventListener14OnTouchPressedERKNS0_8_ControlERKNS0_10_TouchInfoE+0x2e) [0xb34cdf5e]
 6: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui13_UiTouchEvent12FireListenerEPKNS0_20_ITouchEventListenerEPKNS0_8_ControlEbRb+0x31c) [0xb353b18c]
 7: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui13_UiTouchEvent17OnEventProcessingERKNS0_8_ControlERb+0xbb) [0xb353b7cb]
 8: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui8_UiEvent12ProcessEventERKNS0_8_ControlERb+0x64) [0xb3529404]
 9: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui15_UiEventManager20ProcessBubblingEventERKNS_4Base10Collection11LinkedListTINS2_8_HandleTINS0_8_ControlEEEEERKNS0_8_UiEventERb+0xac) [0xb352a13c]
10: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui15_UiEventManager12ProcessEventERKNS0_8_UiEventERb+0x2af) [0xb352a4cf]
11: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui15_UiEventManager4FireERKNS0_8_UiEventE+0xe6) [0xb352a6a6]
12: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen2Ui15_UiEventManager9SendEventERKNS0_8_UiEventE+0x24) [0xb352a784]
13: /usr/lib/osp/libosp-uifw.so.1(+0x2f54de) [0xb35154de]
14: /usr/lib/osp/libosp-uifw.so.1(+0x2f85a6) [0xb35185a6]
15: /usr/lib/libecore.so.1(+0x9131) [0xb6d4f131]
16: /usr/lib/libecore.so.1(+0xde8a) [0xb6d53e8a]
17: /usr/lib/libecore.so.1(ecore_main_loop_begin+0x3f) [0xb6d543cf]
18: /usr/lib/libelementary.so.1(elm_run+0x17) [0xb711a987]
19: /usr/lib/libappcore-efl.so.1(appcore_efl_main+0xac) [0xb77498fa]
20: /usr/lib/libcapi-appfw-application.so.0(app_efl_main+0xe8) [0xb4700728]
21: /usr/lib/osp/libosp-appfw.so(_ZN5Tizen3App8_AppImpl7ExecuteEPNS0_9_IAppImplE+0xe9) [0xb480c4e9]
22: /usr/lib/osp/libosp-uifw.so.1(_ZN5Tizen3App5UiApp7ExecuteEPFPS1_vEPKNS_4Base10Collection5IListE+0xa1) [0xb3a4d4e1]
23: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe.exe(OspMain+0x19f) [0xb3e77acf]
24: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe(main+0x8e0) [0xb7206550]
25: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe() [0x804bff6]
26: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe() [0x804d16d]
27: /lib/libc.so.6(__libc_start_main+0xe6) [0xb726ada6]
28: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe() [0x8049ec1]
End of Call Stack

Package Information
Package Name: i210nfM5xJ.ProjectGiraffe
Package ID : i210nfM5xJ
Version: 1.0.0
Package Type: tpk
App Name: ProjectGiraffe
App ID: i210nfM5xJ.ProjectGiraffe
Type: Application
Categories: (NULL)
