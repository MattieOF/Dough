#pragma once

#ifdef DH_PLATFORM_WINDOWS

extern Dough::Application* Dough::CreateApplication();

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int argc, char** argv)
{
	Dough::Init();

	bool keepRunning = true;
	do
	{
		auto app = Dough::CreateApplication();
		keepRunning = app->Run();
		delete app;
	} while (keepRunning);

}

#endif
