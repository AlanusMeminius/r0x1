#pragma once
#include "qglobal.h"
//namespace Platform {
//
//}

#ifdef Q_OS_MAC
#include "launchermac.h"
#elif defined Q_OS_UNIX// Q_OS_MAC
#include "launcherLinux.h"
#elif defined Q_OS_WINRT || defined Q_OS_WIN// Q_OS_MAC || Q_OS_UNIX
#include "launcherwin.h"
#endif// Q_OS_MAC || Q_OS_UNIX || Q_OS_WINRT || Q_OS_WIN
