#pragma once

#include <HellfireControl/Core/Common.hpp>

enum class AppType {
	CONSOLE,
	WINDOWED
};

class Application {
private:
	//TODO: When the memory manager is active, add it here.
	//TODO: When the windowing solution is complete, add it here.

	/// <summary>
	/// The name of the app
	/// </summary>
	std::string m_strApplicationName;

	/// <summary>
	/// The type of app. This is used for window initialization.
	/// </summary>
	AppType m_atType;
public:
	/// <summary>
	/// By default, inits the name of the app to Hellfire Control Engine and defaults to a console app
	/// </summary>
	Application() : m_strApplicationName("Hellfire Control Engine"), m_atType(AppType::CONSOLE) {}

	/// <summary>
	/// Generate a new application with the given name. Future implementation will include projected memory pool (this will help
	/// with initialization, even if not required).
	/// </summary>
	/// <param name="_strName: The name of the application"></param>
	///  <param name="_atType: The type of the application"></param>
	explicit Application(const std::string& _strName, AppType _atType) : m_strApplicationName(_strName), m_atType(_atType) {}

	/// <summary>
	/// The start of the app. Should always perform initialization actions. Base implementation required, as it includes the startup
	/// of the memory and windowing systems.
	/// </summary>
	virtual void Start();

	/// <summary>
	/// The main application system. This is based entirely around the app being built, and as such is left pure virtual.
	/// </summary>
	virtual void Run() = 0;

	/// <summary>
	/// Final cleanup. Should always ensure that no leaks are left over and everything gracefully exits. Base implementation required,
	/// as it performs the shut down procedure for memory and windowing.
	/// </summary>
	virtual void End();
};