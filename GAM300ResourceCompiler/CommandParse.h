#pragma once
#include "pch.h"

namespace TDS
{

	struct Command
	{
		std::string m_Commands;
		std::vector<const char*> m_Params;
	};

	template <typename ...Args>
	struct CommandCallBack : public Command
	{
		std::function<void(Args...)> m_CallBack;
	};


	class CommandParser
	{
	public:
		CommandParser();
		~CommandParser();
		static std::shared_ptr<CommandParser> m_Instance;

		inline static std::shared_ptr<CommandParser> GetInstance()
		{
			if (m_Instance == 0)
				m_Instance = std::make_shared<CommandParser>();
			return m_Instance;
		}

		template <typename ...Args>
		void AddCommand(std::function<void(Args...)> CallBack, std::string_view commandName);

		template <typename ...Args>
		void Execute(std::string_view cmdName, Args&&... params);

		void ExecuteDirect(std::string_view cmdName, std::string_view param1, std::string_view param2);
		void checkForCommands();
	private:
		std::unordered_map<std::string, Command*> m_Commands;
		bool is_Running;
	};



	template<typename ...Args>
	void CommandParser::AddCommand(std::function<void(Args...)> CallBack, std::string_view commandName)
	{
		CommandCallBack<Args...>* cmdcb = new CommandCallBack<Args...>();
		cmdcb->m_CallBack = CallBack;
		cmdcb->m_Commands = commandName.data();
		m_Commands[commandName.data()] = cmdcb;
	}

	template<typename ...Args>
	void CommandParser::Execute(std::string_view cmdName, Args&& ...params)
	{
		CommandCallBack<Args...>* cb = reinterpret_cast<CommandCallBack<Args...>*>(m_Commands[cmdName.data()]);
		cb->m_CallBack(std::forward<Args>(params)...);
	}


}