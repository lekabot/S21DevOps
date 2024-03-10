# Simple Docker

## Part 1. Ready-made docker

- Возьмём официальный docker-образ с nginx и выкачаем его при помощи команды `docker pull`  

![pull_nginx](./images/part_1/1.png)  

- Удостоверимся в наличии образа через команду `docker images`  

![docker_images](/images/part_1/2.png)  

- Запустим docker-образ через команду `docker run -d [image_id|repository]`  

![docker_run_nginx](/images/part_1/3.png)  

- Удостоверимся, что контейнер успешно запустился через команду `docker ps`  

![docker_ps_1](/images/part_1/4.png)  

- Посмотрим информацию о контейнере через команду `docker inspect [container_id|container_name]`  

![docker_inspect](/images/part_1/5.png)  

- Выведем размер контейнера  

![grep_size](/images/part_1/6.png)  

- Список замапленных портов  

![mapped_ports](/images/part_1/7.png)  

- IP контейнера  

![docker_ipaddress](/images/part_1/8.png)  

- Остановим docker-образ командой `docker stop [container_id|container_name]` и проверим, что образ успешно остановился через уже знакомую команду `docker ps`  

![docker_stop](/images/part_1/9.png)  

- Запустим docker-образ с портами 80:80 и 443:443 чере команду `docker run`  

![docker_run_8080](/images/part_1/10.png)  

- Удостоверимся, что все работает, открыв в браузере страницу по адресу `localhost`  

![docker_localhost](/images/part_1/11.png)  

- Перезапустим контейнер через команду `docker restart [container_id|container_name]` и проверим, что контейнер снова запустился командой `docker ps`  

![docker_restart](/images/part_1/12.png)  

## Part 2. Operations with container

- Прочтем конфигурационный файл `nginx.conf` внутри docker-контейнера через команду `docker exec`  

![docker_restart](/images/part_2/1.png)  

- Создадим локальный файл `nginx.conf` при помощи команды `touch nginx.conf` и настроем в нем выдачу страницы-статуса сервера по пути `/status`  

![docker2_myconf](/images/part_2/2.png)  

- Перенесем созданный файл внутрь docker-образа командой `docker cp`  

![docker2_cp](/images/part_2/3.png)  

- Перезапустим nginx внутри docker-образа командой `docker exec [container_id|container_name] nginx -s reload`  

![docker2_exec_nginx](/images/part_2/4.png)  

- Убедимся, что все работает, проверив страницу по адресу `localhost/status`  

![docker2_new_conf](/images/part_2/5.png)  

- Экспортируем наш контейнер в файл `container.tar` командой `docker export`  

- Удалим образ командой `docker rmi -f [image_id|repository]`, не удаляя перед этим контейнеры  

![docker2_remove_nginx](/images/part_2/6.png)  

- Удалим остановленный контейнер командой `docker rm [container_id|container_name]`  

![docker2_remove_container](/images/part_2/7.png)  

- Импортируем контейнер обратно командой `docker import` и запустим импортированный контейнер уже знакомой командой `dicker run`  

![docker2_import](/images/part_2/8.png)  

- Проверим, что по адресу `localhost/status` выдается страничка со статусом сервера nginx  

![docker2_localhost8080](/images/part_2/9.png)

## Part 3. Mini web server

- Чтобы создать свой мини веб-сервер, необходимо создать .c файл, в котором будет описана логика сервера (в нашем случае - вывод сообщения `Hello World!`), а также конфиг `nginx.conf`, который будет проксировать все запросы с порта 81 на порт 127.0.0.1:8080  

![docker3_server](/images/part_3/1.png)  

![docker3_conf](/images/part_3/2.png)  

- Выкачаем новый docker-образ и на его основе запустим новый контейнер  

![docker3_new_nginx](/images/part_3/3.png)  

- Перекинем конфиг и логику сервера в новый контейнер  

![docker3_copied](/images/part_3/4.png)  

- Установим требуемые утилиты для запуска мини веб-сервера на FastCGI, в частности `spawn-fcgi` и `libfcgi-dev`  

![docker3_install](/images/part_3/5.png)  

- Скомпилируем и запустим наш мини веб-сервер через команду `spawn-fcgi` на порту 8080  

![docker3_start_server](/images/part_3/6.png)  

- Удостовериться, что все работает корректно, проверим, что в браузере по адресу `localhost:81` отдается написанная нами страница  

![docker3_hello_world](/images/part_3/7.png)  

![docker3_kill](/images/part_3/8.png)  

## Part 4. Your own docker

- Напишем свой docker-образ, который собирает исходники 3-й части, запускает на порту `80`, после копирует внутрь написанный нами `nginx.conf` и, наконец, запускает `nginx` (ниже приведены файлы `run.sh` и `Dockerfile`, файлы `nginx.conf` и `server.c` остаются с 3-й части)  

![docker4_runsh](/images/part_4/1.png)  

![docker4_dockerfile](/images/part_4/2.png)  

- Соберем написанный docker-образ через команду `docker build`, при этом указав имя и тэг нашего контейнера  

![docker4_build.png](/images/part_4/3.png)  

- Запустим собранный docker-образ с мапингом порта `81` на порт `80` локальной машины, а также мапингом папки `./nginx` внутрь контейнера по адресу конфигурационных файлов nginx'а, и проверим, что страничка написанного сервера по адресу  

![docker4_run_server.png](/images/part_4/4.png)  

- Добавим в файл `nginx.conf` проксирование странички `/status`, по которой необходимо отдавать статус сервера `nginx  

![docker4_nginx.png](/images/part_4/5.png)  

- Перезапустим `nginx` в своем docker-образе командой `nginx -s reload`  

![docker4_reload_serv.png](/images/part_4/6.png)  

- Проверим, что по адресу `localhost/status` выдается страничка со тсатусом сервера `nginx`  

![docker4_success.png](/images/part_4/7.png)  

## Part 5. Dockle

- Просканируем docker-образ из предыдущего задания на предмет наличия ошибок командой `dockle [image_id|repository]`  

![part5_troubles.png](/images/part_5/1.png)  

- Исправим конфигурационные файлы docker-образа так, чтобы при проверке через утилиту `dockle` не возникало ошибок и предупреждений (для Part5 я создал отдельный контейнер с тэгом `part_5`, куда подгрузил измененные конфиги)  

![part5_new_build.png](/images/part_5/2.png)  

![part5_check_build.png](/images/part_5/3.png)  

![part5_success.png](/images/part_5/4.png)  

## Part6. Basic Docker Compose

- Остановим все запущенные контейнеры командой `docker stop`  

![part6_build.png](/images/part_6/1.png)  

- Создадим ```docker-compose.yaml```

![part6_build.png](/images/part_6/2.png)  

- Теперь сбилдим контейнер командой `docker-compose build`  

![part6_build.png](/images/part_6/3.png)  

- После необходимо поднять сбилженный контейнер командой `docker compose up`  

![part6_dockerup.png](/images/part_6/4.png)  

- В завершение насладимся плодами своей усердной работы, удостоверившись, что по адресу `localhost` отдается страничка с надписью `Hello World!`  

![part6_success.png](/images/part_6/5.png)  
