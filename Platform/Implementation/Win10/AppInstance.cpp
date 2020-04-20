#include <Platform/AppInstance.hpp>

AppInstance::AppInstance()
    : appHandle(GetModuleHandle(NULL)) {
}
