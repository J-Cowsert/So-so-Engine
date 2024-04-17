#pragma once

#include "core.h"

namespace soso {

	class SOSO_API Application
	{

	public:
		Application();
		virtual ~Application();
		 
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication(); 

}