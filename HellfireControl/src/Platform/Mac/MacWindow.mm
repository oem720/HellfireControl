#include <AppKit/AppKit.h>
#include <Platform/Mac/MacWindow.hpp>

@interface AppDelegate : NSObject <NSApplicationDelegate> {
@public NSWindow* window;
}
@end
@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *) aNotification {
    [window makeKeyAndOrderFront:nil];
}
- (void)setWindowPtr:(NSWindow *) to {
    window = to;
}
@end

namespace {
    constexpr NSWindowStyleMask styleMask[] = {
            NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable,
            NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
            NSWindowStyleMaskResizable,
            NSWindowStyleMaskBorderless,
            NSWindowStyleMaskFullScreen
    };
    constexpr uint8_t whatWindowMode(const NSWindowStyleMask& isThis) {
        if ((isThis & styleMask[0]) == styleMask[0]) return 0;
        if ((isThis & styleMask[1]) == styleMask[1]) return 1;
        if ((isThis & styleMask[2]) == styleMask[2]) return 2;
        return 3;
    }
    static AppDelegate* appDelegate;

}

void PlatformWindow::InitWindow(uint64_t& _u64Handle, uint8_t _u8Type, const std::string& _strName, const Vec2F& _v2Size, const Vec2F& _v2Loc) {
    appDelegate = [[AppDelegate alloc] init];
    NSString *name = [NSString stringWithUTF8String:_strName.c_str()];
    NSRect frame = NSMakeRect(_v2Loc.x, _v2Loc.y, _v2Size.x, _v2Size.y);

    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
        styleMask:NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask
        backing: NSBackingStoreBuffered
        defer:NO];
    [window setTitle:name];
    _u64Handle = reinterpret_cast<uint64_t>(window);

    [appDelegate setWindowPtr:window];

    NSApplication *app = [NSApplication sharedApplication];
    [app setDelegate:appDelegate];
    [app run];
}

[[nodiscard]] bool PlatformWindow::SetWindowName(uint64_t _u64Handle, const std::string &_strName) {
    NSString *name = [NSString stringWithUTF8String:_strName.c_str()];
    auto *window = reinterpret_cast<NSWindow*>(_u64Handle);
    [window setTitle:name];
    return true;
}

[[nodiscard]] Vec2F PlatformWindow::GetWindowSize(uint64_t _u64Handle) {
    auto *window = reinterpret_cast<NSWindow *>(_u64Handle);
    NSRect frame = [window frame];
    return Vec2F{frame.size.width, frame.size.height};
}

[[nodiscard]] bool PlatformWindow::SetWindowSize(uint64_t _u64Handle, const Vec2F &_v2Size) {
    auto *window = reinterpret_cast<NSWindow*>(_u64Handle);
    NSRect frame = [window frame];
    frame.size = NSMakeSize(_v2Size.x, _v2Size.y);
    [window setFrame:frame display:YES];
    return true;
}

[[nodiscard]] Vec2F PlatformWindow::GetWindowLocation(uint64_t _u64Handle) {
    auto *window = reinterpret_cast<NSWindow*>(_u64Handle);
    NSRect frame = [window frame];
    return Vec2F(frame.origin.x, frame.origin.y);
}

[[nodiscard]] bool PlatformWindow::SetWindowLocation(uint64_t _u64Handle, const Vec2F &_v2Loc) {
    auto *window = reinterpret_cast<NSWindow*>(_u64Handle);
    NSRect frame = [window frame];
    frame.origin = NSMakePoint(_v2Loc.x, _v2Loc.y);
    [window setFrame:frame display:YES];
    return true;
}

void PlatformWindow::CleanupWindow(uint64_t _u64Handle) {
    auto *window = reinterpret_cast<NSWindow *>(_u64Handle);
    [window close];
    CFRelease(window);
}

[[nodiscard]] uint8_t PlatformWindow::GetWindowParameters(uint64_t _u64Handle) {
    auto *window = reinterpret_cast<NSWindow*>(_u64Handle);
    NSWindowStyleMask mask = [window styleMask];
    return static_cast<uint8_t>(whatWindowMode(mask));
}

[[nodiscard]] bool PlatformWindow::SetWindowStyleParameters(uint64_t _u64Handle, uint8_t _u8Type) {
    auto *window = reinterpret_cast<NSWindow*>(_u64Handle);
    NSWindowStyleMask mask = styleMask[_u8Type];
    [window setStyleMask:mask];
    return true;
}