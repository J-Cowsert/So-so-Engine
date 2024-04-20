#pragma once

#include "core.h"
#include "Events/Event.h"
#include "Window.h"

namespace soso {

	class SOSO_API Application
	{

	public:
		Application();
		virtual ~Application();
		 
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication(); 

}