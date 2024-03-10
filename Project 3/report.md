# Simple Docker  

## Part 1. Ready-made docker  

- Скачиваем официальный образ nginx ```docker pull```

![pull](./images/1.png)  

- Проверяем, что образ скачался ```docker images | grep nginx```  

![images](./images/2.png)  

- Запускаем образ ```docker run -d nginx```  

![images](./images/3.png)  

- Удостоверимся, что контейнер успешно запустился через команду ```docker ps```  

![images](./images/4.png)  

- Посмотрим информацию о контейнере через команду ```docker inspect focused_joliot```  

![images](./images/5.png)  

- Выведем размер контейнера ```docker inspect focused_joliot --size | grep -ie size```  

![images](./images/6.png)  

- Cписок замапленных портов

![images](./images/7.png)  

- IP контейнера  

![images](./images/8.png)  

- Остановим контейнер  

![images](./images/9.png)  

- Проверим, что образ остановился

![images](./images/10.png)  

- Запустим docker-образ с портами 80:80 и 443:443

![images](./images/11.png)  

- Проверим работоспособность

![images](./images/12.png)  

- Перезапустим контейнер ```docekr restart```  

![images](./images/13.png)  

