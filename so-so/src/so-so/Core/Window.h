#pragma once

#include "sspch.h"

#include "so-so/Core/core.h"
#include "so-so/Events/Event.h"


namespace soso {

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "So-So Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface 
	class SOSO_API Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}