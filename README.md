# SimpleHttpServer

Простой HTTP-сервер написан на Qt 5.15.

Маршруты:
- http://localhost/ - по запросу GET возвращает время
- http://localhost/test - по запросу GET возвращает HTML-страницу
- http://localhost/data - по запросу GET выводит HTML-страницу списка данных (строк)
- http://localhost/data - по запросу POST сохраняет данные в общий список


## Тестирование

### В браузере



### В терминале через curl

curl http://localhost/ - возвращает время

curl http://localhost/test - возвращает html-страницу

curl http://localhost/data - возвращает html-страницу со списком данных

curl http://localhost/data -d "abc" - добавляет данные в список
