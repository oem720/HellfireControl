#include <Platform/Mac/MacTerminal.hpp>
#include <Foundation/Foundation.h>

void PlatformConsole::Print(const std::string& _strMessage, uint8_t _u8Color) {
    NSString* messageStr = [NSString stringWithCString:_strMessage.c_str() encoding:[NSString defaultCStringEncoding]];
    printf("\033[%dm%s\033[0m\n", _u8Color, [messageStr UTF8String]);
}