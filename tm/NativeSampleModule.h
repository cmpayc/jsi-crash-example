#pragma once

#if __has_include(<React-Codegen/AppSpecsJSI.h>) // CocoaPod headers on Apple
#include <React-Codegen/AppSpecsJSI.h>
#elif __has_include("AppSpecsJSI.h") // CMake headers on Android
#include "AppSpecsJSI.h"
#endif
#include <memory>
#include <string>
#include <thread>
#include <stdio.h>

namespace facebook::react {

typedef std::function<void (std::string res)> TestCallback;

class NativeSampleModule : public NativeSampleModuleCxxSpec<NativeSampleModule> {
 public:
  NativeSampleModule(std::shared_ptr<CallInvoker> jsInvoker);

  std::string reverseString(jsi::Runtime& rt, std::string input, jsi::Object func);
};

} // namespace facebook::react
