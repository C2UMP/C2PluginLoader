#include <Windows.h>
#include <iostream>
#include <filesystem>

extern "C" {
	__declspec(dllexport) HRESULT CreateFX(REFCLSID clsid, IUnknown** pEffect) {
		return NULL;
	}
}

unsigned long main_thread(void* lpParameter) {
#ifdef _DEBUG
	if (!GetConsoleWindow()) {
		AllocConsole();
		FILE* file_pointer{};
		freopen_s(&file_pointer, "CONOUT$", "w", stdout);
	}
#endif

	std::cout << "Chivalry 2 Plugin Loader" << '\n' << '\n';

	auto folder_attributes{ GetFileAttributesA("Plugins") };

	if (folder_attributes == INVALID_FILE_ATTRIBUTES || !(folder_attributes & FILE_ATTRIBUTE_DIRECTORY)) {
		std::cout << "Could not find plugins folder! Creating it for you..." << '\n';
		if (CreateDirectoryA("Plugins", NULL)) std::cout << "Created Plugins folder sucessfully!" << '\n';
		else std::cout << "Failed to create Plugins folder!" << '\n';
	}

	std::cout << "Loading plugins..." << '\n';

	for (const auto& file : std::filesystem::directory_iterator("Plugins")) {
		auto path{ file.path().string() };
		if (path.find(".dll") != std::string::npos) {
			std::cout << "Loading: " << file.path().filename().string() << '\n';
			LoadLibraryA(path.c_str());
		}
	}

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(lpParameter), 0);
	return 0;
}

int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: {
		HANDLE thread_handle{ CreateThread(NULL, 0, main_thread, hModule, 0, NULL) };
		if (thread_handle) CloseHandle(thread_handle);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return 1;
}