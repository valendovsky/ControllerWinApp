# ControllerWinApp

<p align="center">
   <img src="https://img.shields.io/badge/C%2B%2B-20-blue" alt="Standard C++">
   <img src="https://img.shields.io/badge/Windows-10-green" alt="Windows Version">
   <img src="https://img.shields.io/badge/version-1.0-yellow" alt="Version">
   <img src="https://img.shields.io/badge/license-MIT-red" alt="License">
</p>

## Application controller for Windows.

### About
The program works in Windows OS.
The program controls the uninterrupted operation of the selected application.
It checks at a specified period of time that the process is running.
If the program does not find the process in running, the program restarts this application.
When the program re-launches the application of the temporary check interval is less than standard.
If the program launches the application several times in a row, then the time interval begins to increase to the standard.
If the application is running, then the next check will take place after the time interval specified by the user.

### Documentation
Use the `tasklist` command to check the running processes.
The program starts with command line arguments:
1. Name of the controlled process.
2. Command to start the application in CMD. If you need a few commands, you need to use quotes and operator combining commands.
3. The time interval between the inspections specified in seconds. This is an optional argument, by default - 10 minutes.

### Developers
- [Valendovsky](https://github.com/valendovsky)

### License
Project ControllerWinApp is distributed under the MIT license.

---

## Контроллер работы приложений для Windows.

### О проекте
Приложение создано для ОС Windows.
Программа контролирует постоянную работу указанного пользователем приложения.
Через указанные пользователем промежутки времени проводится проверка запущен ли процесс приложения.
Если программа не находит процесс в запущенных, то перезапускает это приложение.
Если программа вынуждена заново запустить процесс, то интервал времени до следующей проверки уменьшается.
Если приходится перезапускать приложение несколько проверок подряд, то временной интервал начинает увеличиваться до достижения стандартного показателя.
Если же процесс запущен, то следующая проверка произойдёт только через указанный пользователем промежуток времени.

### Документация
Используйте команду `tasklist` для проверки запущенных процессов.
Программа запускается с аргументами командной строки:
1. Название контролируемого процесса.
2. Команда для запуска приложения через cmd. Если вам требуется несколько команд, то используйте кавычки и оператор объединения команд.
3. Временной интервал между проверками заданный в секундах. Это необязательный аргумент, по умолчанию - 10 минут.

### Разработчики
- [Valendovsky](https://github.com/valendovsky)

### Лицензия
Проект ControllerWinApp распространяется под лицензией MIT.
