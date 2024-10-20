#include "NativeSampleModule.h"

namespace facebook::react {

NativeSampleModule::NativeSampleModule(std::shared_ptr<CallInvoker> jsInvoker)
    : NativeSampleModuleCxxSpec(std::move(jsInvoker)) {}

std::string NativeSampleModule::reverseString(jsi::Runtime& rt, std::string input, jsi::Object func) {
  std::shared_ptr<jsi::Function> testFunc = std::make_shared<jsi::Function>(func.asFunction(rt));
  
  TestCallback testCallback = [&rt, testFunc](std::string res) -> void {
    jsi::Object result = jsi::Object(rt);
    result.setProperty(rt, "res", jsi::String::createFromUtf8(rt, res));
    testFunc->call(rt, std::move(result));
  };
  
  std::thread([testCallback, &rt]() {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Uncomment to fix the crash
    testCallback("Start");
    
    int i = 1;
    while (i <= 100) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      char buffer[100];
      snprintf(buffer, 100, "Progress %d", i);
      std::string res = buffer;
      testCallback(res);
      i++;
    }
  }).detach();
  
  testCallback("Init");
  
  return std::string(input.rbegin(), input.rend());
}

} // namespace facebook::react
