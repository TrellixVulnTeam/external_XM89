// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/app/android_library_loader_hooks.h"

#include "base/android/base_jni_registrar.h"
#include "base/android/jni_android.h"
#include "base/android/jni_registrar.h"
#include "base/android/jni_string.h"
#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/debug/trace_event.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "base/tracked_objects.h"
#include "content/app/android/app_jni_registrar.h"
#include "content/browser/android/browser_jni_registrar.h"
#include "content/child/android/child_jni_registrar.h"
#include "content/common/android/command_line.h"
#include "content/common/android/common_jni_registrar.h"
#include "content/public/common/content_switches.h"
#include "content/public/common/result_codes.h"
#include "jni/LibraryLoader_jni.h"
#include "media/base/android/media_jni_registrar.h"
#include "net/android/net_jni_registrar.h"
#include "ui/android/ui_jni_registrar.h"
#include "ui/gl/android/gl_jni_registrar.h"
#include "ui/shell_dialogs/android/shell_dialogs_jni_registrar.h"
/// M: set logging level by build variant
#include "base/sys_info.h"

namespace content {

namespace {

base::AtExitManager* g_at_exit_manager = NULL;

bool DoJniRegistration(JNIEnv* env) {
  static bool g_jni_init_done = false;

  if (!g_jni_init_done) {
    if (!base::android::RegisterJni(env))
      return false;

    if (!net::android::RegisterJni(env))
      return false;

    if (!ui::android::RegisterJni(env))
      return false;

    if (!ui::gl::android::RegisterJni(env))
      return false;

    if (!ui::shell_dialogs::RegisterJni(env))
      return false;

    if (!content::android::RegisterChildJni(env))
      return false;

    if (!content::android::RegisterCommonJni(env))
      return false;

    if (!content::android::RegisterBrowserJni(env))
      return false;

    if (!content::android::RegisterAppJni(env))
      return false;

    if (!media::RegisterJni(env))
      return false;

    g_jni_init_done = true;
  }

  return true;
}

}  // namespace

static jint LibraryLoaded(JNIEnv* env, jclass clazz,
                          jobjectArray init_command_line) {
  InitNativeCommandLineFromJavaArray(env, init_command_line);

  CommandLine* command_line = CommandLine::ForCurrentProcess();

  if (command_line->HasSwitch(switches::kTraceStartup)) {
    base::debug::CategoryFilter category_filter(
        command_line->GetSwitchValueASCII(switches::kTraceStartup));
    base::debug::TraceLog::GetInstance()->SetEnabled(category_filter,
        base::debug::TraceLog::RECORD_UNTIL_FULL);
  }

  // Can only use event tracing after setting up the command line.
  TRACE_EVENT0("jni", "JNI_OnLoad continuation");

  // Note: because logging is setup here right after copying the command line
  // array from java to native up top of this method, any code that adds the
  // --enable-dcheck switch must do so on the Java side.
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;
  settings.dcheck_state =
      command_line->HasSwitch(switches::kEnableDCHECK) ?
      logging::ENABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS :
      logging::DISABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS;
  logging::InitLogging(settings);
  // To view log output with IDs and timestamps use "adb logcat -v threadtime".
  logging::SetLogItems(false,    // Process ID
                       false,    // Thread ID
                       false,    // Timestamp
                       false);   // Tick count
  VLOG(0) << "Chromium logging enabled: level = " << logging::GetMinLogLevel()
          << ", default verbosity = " << logging::GetVlogVerbosity() << " isUserLoad="<< base::SysInfo::IsUserLoad();

  /// M: set logging level by build variant @{
  if (base::SysInfo::IsUserLoad())
      logging::SetMinLogLevel(logging::LOG_WARNING);
  /// @}

  if (!DoJniRegistration(env))
    return RESULT_CODE_FAILED_TO_REGISTER_JNI;

  return 0;
}

void LibraryLoaderExitHook() {
  if (g_at_exit_manager) {
    delete g_at_exit_manager;
    g_at_exit_manager = NULL;
  }
}

bool RegisterLibraryLoaderEntryHook(JNIEnv* env, bool lazy_jni_registration) {
  // We need the AtExitManager to be created at the very beginning.
  g_at_exit_manager = new base::AtExitManager();

  if (!RegisterNativesImpl(env))
    return false;

  if (!lazy_jni_registration && !DoJniRegistration(env))
    return false;

  return true;
}

}  // namespace content
