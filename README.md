# ControllerWinApp
Application controller for Windows.

The program works in Windows OS. The program controls the uninterrupted operation of the selected application. It checks at a specified period of time that the process is running. If the program does not find the process in running, the program restarts this application. When the program re-launches the application of the temporary check interval is less than standard. If the program launches the application several times in a row, then the time interval begins to increase to the standard. If the application is running, then the next check will take place after the time interval specified by the user.

Use the "tasklist" command to check the running processes. The program starts with command line arguments:

1 - name of the controlled process.

2 - command to start the application in CMD. If you need a few commands, you need to use quotes and operator combining commands.

3 - the time interval between the inspections specified in seconds. This is an optional argument, by default - 10 minutes.



Программа работает в Windows ОС. Программа контролирует постоянную работу указанного пользователем приложения. Она проверяет через указанный промежуток времени, что процесс запущен. Если программа не находит процесс в запущенных, то перезапускает это приложение. Временной интервал проверки меньше, когда программа заново запускает приложение. Если приходится перезапускать приложение несколько проверок подряд, то временной интервал начинает увеличиваться до стандартного. Если приложение работает, то следующая проверка произойдёт через указанный пользователем промежуток времени.

Используйте команду "tasklist" для проверки запущенных процессов. Программа запускается с аргументами командной строки:

1 аргумент - название контролируемого процесса.

2 аргумент - команда для запуска приложения через cmd. Если вам требуется несколько команд, то используйте кавычки и оператор объединения команд.

3 аргумент - временной интервал между проверками заданный в секундах. Это необязательный аргумент, по умолчанию - 10 минут.
