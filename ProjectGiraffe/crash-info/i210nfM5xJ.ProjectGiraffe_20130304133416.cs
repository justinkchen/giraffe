S/W Version Information
Model: Emulator
Tizen-Version: 2.0.0
Build-Number: Tizen_EMULATOR_20130215.1451
Build-Date: 2013.02.15 14:51:54

Crash Information
Process Name: /ProjectGiraffe
PID: 2414
Date: 2013-03-04 13:34:16(GMT+0900)
Executable File Path: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe
This process is multi-thread process
pid=2414 tid=2424
Signal: 11
      (SIGSEGV)
      si_code: -6
      signal sent by tkill (sent by pid 2414, uid 5000)
      TIMER: -2

Memory Information
MemTotal: 509660 KB
MemFree: 156032 KB
Buffers:  49244 KB
Cached:   184340 KB

Callstack Information (PID:2414)
Call Stack Count: 7
 0: /usr/lib/osp/libosp-uifw.so.1(_ZNK5Tizen2Ui12_ControlImpl13SendUserEventElPKNS_4Base10Collection5IListE+0x11c) [0xb355160c]
 1: /usr/lib/osp/libosp-uifw.so.1(_ZNK5Tizen2Ui7Control13SendUserEventElPKNS_4Base10Collection5IListE+0x3c) [0xb352c3dc]
 2: /opt/apps/i210nfM5xJ/bin/ProjectGiraffe.exe(+0x5dc7) [0xb3f05dc7]
 3: /usr/lib/osp/libosp-appfw.so(+0x1a584e) [0xb495184e]
 4: /usr/lib/osp/libosp-appfw.so(_ZN5Tizen4Base7Runtime11_ThreadImpl10ThreadProcEPv+0x68) [0xb4949bc8]
 5: /lib/libpthread.so.0(+0x5e09) [0xb75cae09]
 6: /lib/libc.so.6(clone+0x5e) [0xb73afffe]
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
