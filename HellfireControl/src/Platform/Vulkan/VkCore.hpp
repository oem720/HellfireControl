#pragma once

#include <Platform/GLCommon.hpp>

#include <HellfireControl/Math/Vector.hpp>

namespace PlatformRenderer {
	/// <summary>
	/// Initializes the renderer using the given parameters
	/// </summary>
	/// <param name="_strAppName: The name of the app being registered. Needed for Instance creation"></param>
	/// <param name="_u32AppVersion: The version of the app being registered. Needed for Instance creation"></param>
	/// <param name="_u64WindowHandle: A handle to the render target window"></param>
	/// <param name="_v4ClearColor: A Vec4F representing the color that the framebuffer defaults to when no pixels are drawn there. Default: Black"></param>
	void InitRenderer(const std::string& _strAppName, uint32_t _u32AppVersion, uint64_t _u64WindowHandle, const Vec4F& _v4ClearColor = Vec4F());

	/// <summary>
	/// Marks the framebuffer as needing to be updated, and Swapchain as needing recreation.
	/// </summary>
	void MarkFramebufferUpdated();

	/// <summary>
	/// Renders the current frame and presents it to the screen.
	/// </summary>
	void RenderFrame();

	/// <summary>
	/// Destroys all allocated objects on the GPU and shuts down the rendering system.
	/// </summary>
	void CleanupRenderer();
}