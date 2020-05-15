#include "gfx.h"
#include "lib/util/src/log.h"
#include "lib/util/src/os.h"
#include "vulkan/vulkan.h"

#define LIB_FUNC(name) PFN_##name name = (PFN_##name)GetProcAddress(LIBVK, #name)
#define VK_MSG(name) case name: msg = #name; break;

struct Vulkan {
	HMODULE LIBVK = LoadLibrary(L"vulkan-1.dll");
	LIB_FUNC(vkCreateInstance);
} VULKAN;

struct Gfx {
	VkInstance instance;
};

void vkVerify(VkResult result) {
	if (result) {
		const char* msg;
		switch (result) {
			VK_MSG(VK_SUCCESS)
			VK_MSG(VK_NOT_READY)
			VK_MSG(VK_TIMEOUT)
			VK_MSG(VK_EVENT_SET)
			VK_MSG(VK_EVENT_RESET)
			VK_MSG(VK_INCOMPLETE)
			VK_MSG(VK_ERROR_OUT_OF_HOST_MEMORY)
			VK_MSG(VK_ERROR_OUT_OF_DEVICE_MEMORY)
			VK_MSG(VK_ERROR_INITIALIZATION_FAILED)
			VK_MSG(VK_ERROR_DEVICE_LOST)
			VK_MSG(VK_ERROR_MEMORY_MAP_FAILED)
			VK_MSG(VK_ERROR_LAYER_NOT_PRESENT)
			VK_MSG(VK_ERROR_EXTENSION_NOT_PRESENT)
			VK_MSG(VK_ERROR_FEATURE_NOT_PRESENT)
			VK_MSG(VK_ERROR_INCOMPATIBLE_DRIVER)
			VK_MSG(VK_ERROR_TOO_MANY_OBJECTS)
			VK_MSG(VK_ERROR_FORMAT_NOT_SUPPORTED)
			VK_MSG(VK_ERROR_FRAGMENTED_POOL)
			VK_MSG(VK_ERROR_OUT_OF_POOL_MEMORY)
			VK_MSG(VK_ERROR_INVALID_EXTERNAL_HANDLE)
			VK_MSG(VK_ERROR_SURFACE_LOST_KHR)
			VK_MSG(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR)
			VK_MSG(VK_SUBOPTIMAL_KHR)
			VK_MSG(VK_ERROR_OUT_OF_DATE_KHR)
			VK_MSG(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR)
			VK_MSG(VK_ERROR_VALIDATION_FAILED_EXT)
			VK_MSG(VK_ERROR_INVALID_SHADER_NV)
			VK_MSG(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT)
			VK_MSG(VK_ERROR_FRAGMENTATION_EXT)
			VK_MSG(VK_ERROR_NOT_PERMITTED_EXT)
			VK_MSG(VK_ERROR_INVALID_DEVICE_ADDRESS_EXT)
			VK_MSG(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT)
		}
		DIE(msg);
	}
}

Gfx* ngCreateGfx(const char* appName, u32 appVersion) {
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = appName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "nIce Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	VkInstance instance;
	vkVerify(VULKAN.vkCreateInstance(&createInfo, nullptr, &instance));

	return new Gfx { instance };
}

void ngDestroyGfx(Gfx* gfx) {
	delete gfx;
}
