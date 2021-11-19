// ControllerWinApp.cpp : программа контролирующая работу заданного приложения в ОС Windows
// Программа проверяет запущен ли процесс,
// если процесс не найден, то запускает приложение.
// И проводит повторную проверку работы этого процесса через уменьшенный интервал времени.
// Интервал повторной проверки возрастает при неработающем процессе несколько раз подряд.
// Аргументы командной строки:
// 1 - "имя процесса", 2 - "команда для cmd", 3 - время между проверками в секундах (по умолчанию 10 минут, опционально)

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <Windows.h>
#include <TlHelp32.h>   // Для работы с Win API поиска процессов Windows
#include <tchar.h>



// Результаты поиска процесса
namespace SR
{
	enum SearchResult
	{
		SUCCESS,
		INVALID_HANDLE,
		INVALID_EXTRACTION,
		FAIL_SEARCH
	};
}

// Возвращает время данного часового пояса
std::string getTime()
{
	// Системное время с точностью до секунды
	auto sysTime = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());

	// Получаем локальное время часового пояса
	auto localTime = std::chrono::zoned_time<std::chrono::seconds>(std::chrono::current_zone(), sysTime);

	std::stringstream ss;
	ss << localTime;

	return ss.str();
}

// Выводит значение ошибок в консоль
void printError(SR::SearchResult result)
{
	// Выводим текущую дату и время в консоль
	std::cout << getTime() << " ";

	// Выводим в консоль результаты поиска
	switch (result)
	{
	case SR::SUCCESS:
		std::cout << "The process has started." << std::endl;
		break;
	case SR::INVALID_HANDLE:
		std::cout << "ERROR: Invalid handle value" << std::endl;
		break;
	case SR::INVALID_EXTRACTION:
		std::cout << "ERROR: Invalid process extraction" << std::endl;
		break;
	case SR::FAIL_SEARCH:
		std::cout << "Fail search! ";
		break;
	default:
		std::cout << "Unknown error" << std::endl;
		break;
	}
}

// Ищет указанный процесс в уже запущенных
SR::SearchResult ProcessSearch(LPCTSTR szProcessName)
{
	// Дескриптор снимка
	HANDLE hSnapshot;
	// Структура снимка
	PROCESSENTRY32 pe = { sizeof(pe) };
	// Делаем снимок
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// Если дескриптор некорректен(отсутствует)
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printError(SR::INVALID_HANDLE);
		return SR::INVALID_HANDLE;
	}

	// Если информацию не удалось извлечь
	if (!Process32First(hSnapshot, &pe))
	{
		printError(SR::INVALID_EXTRACTION);
		return SR::INVALID_EXTRACTION;
	}

	// Перебираем все запущенные процессы
	do
	{
		// Процесс найден, если строки (идентификаторы) равны
		if (!lstrcmpi(pe.szExeFile, szProcessName))
		{
			printError(SR::SUCCESS);
			return SR::SUCCESS;
		}
	} while (Process32Next(hSnapshot, &pe));  // Цикл работает пока не обойдёт все процессы в снимке

	// Если процесс не найден
	printError(SR::FAIL_SEARCH);
	return SR::FAIL_SEARCH;
}


int main(int argc, char* argv[])
{
	// Проверка количества аргументов командной строки
	if (argc < 3)
	{
		std::cerr << "Insufficient number of required arguments.";

		exit(1);
	}

	// Конвертируем имя процесса в тип TCHAR
	size_t sizeProcess = strlen(argv[1]) + 1;
	TCHAR* processName = new TCHAR[sizeProcess];
#pragma warning(suppress : 4996)
	mbstowcs(processName, argv[1], sizeProcess);

	// Команда для cmd
	char* appName = argv[2];

	// Получаем временной отрезок перепроверки в милисекундах
	int millisecond;
	if (argc >= 4)
	{
		std::stringstream sleepTime(argv[3]);

		if (sleepTime >> millisecond)
			millisecond *= 1000; // Конвертируем в миллисекунды
		else // не удалось конвертировать
			millisecond = 600000; // По умолчанию 10 минут
	}
	else // по умолчанию
		millisecond = 600000;

	// Модификатор интервалов проверки (значения: 5-1), когда процесс не найден
	int intervalMode = 5;

	while (1)
	{
		// Ищем процесс
		SR::SearchResult doingProcess = ProcessSearch(processName);

		if (doingProcess == SR::FAIL_SEARCH)
		{
			// Процесс не найден, запускаем его
			std::cout << "Start process!" << std::endl;
			system(appName);

			// Задержка перед следующей проверкой
			Sleep(millisecond / intervalMode);

			// Увеличиваем интервал задержки перед проверкой
			if (intervalMode > 1)
				--intervalMode;
		}
		else if (doingProcess == SR::INVALID_HANDLE || doingProcess == SR::INVALID_EXTRACTION)
		{
			// Проблемы с дескриптором
			break;
		}
		else
		{
			// Процесс работает, задержка перед следующей проверкой
			Sleep(millisecond);

			// Сбрасываем значение модификатора интервалов к исходному
			intervalMode = 5;
		}
	}

	return 0;
}
