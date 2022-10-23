#pragma once

#ifdef DH_PLATFORM_WINDOWS

extern Dough::Application* Dough::CreateApplication();

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int argc, char** argv)
{
	Dough::Init();

	auto app = Dough::CreateApplication();
	app->Run();
	delete app;
}

#endif
