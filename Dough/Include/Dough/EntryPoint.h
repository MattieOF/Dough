#pragma once

#ifdef DH_PLATFORM_WINDOWS

extern Dough::Application* Dough::CreateApplication();

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int argc, char** argv)
{
	// TODO: Move this somewhere else
	Dough::Log::Init();
	DH_ENGINE_CRITICAL("Test!");
	DH_INFO("Initialised log!");

	auto app = Dough::CreateApplication();
	app->Run();
	delete app;
}

#endif
