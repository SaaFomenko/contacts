/* Задание 2 */
/* 1. название и продолжительность самого длительного трека; */
SELECT name, duration FROM track WHERE duration=(SELECT MAX(duration) FROM track);

/* 2. название треков, продолжительность которых не менее 3,5 минуты; */
SELECT name, duration FROM track WHERE duration >= '3:30';

/* 3. названия сборников, вышедших в период с 2018 по 2020 год включительно; */
SELECT name, publication FROM collection 
	WHERE publication BETWEEN 2018 AND 2020;

/* 4. исполнители, чье имя состоит из 1 слова; */
SELECT name FROM musician WHERE name NOT LIKE '% %';

/* 5. название треков, которые содержат слово "мой"/"my". */
SELECT name FROM track WHERE name SIMILAR TO '%(моё|my )%';

/* Задание 3 */
/* 1. Количество исполнителей в каждом жанре. */
SELECT name, COUNT(musician_id) musician_q FROM genre g
JOIN genre_musician m ON g.id = m.genre_id
GROUP BY f.name;

/* 2. Количество треков, вошедших в альбомы 2019–2020 годов. */
SELECT COUNT(album_id) FROM track t 
JOIN album a ON t.id = a.id
WHERE a.publication BETWEEN 2019 AND 2020;

/* 3. Средняя продолжительность треков по каждому альбому. */
SELECT a.name, AVG(duration) FROM album a
JOIN track t ON a.id = t.id
GROUP BY a.name;

/* 4. Все исполнители, которые не выпустили альбомы в 2020 году. */
SELECT m.name FROM musician m
JOIN musician_album ma ON m.id = ma.musician_id
JOIN album a ON a.id = ma.album_id
WHERE a.publication != 2020
GROUP BY m.name;

/* 5. Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами). */
SELECT c.name FROM collection c
JOIN collection_track ct ON c.id = ct.collection_id
JOIN track t ON t.id = ct.track_id
JOIN album a ON a.id = t.album_id
JOIN musician_album ma ON a.id = ma.album_id
JOIN musician m ON m.id = ma.musician_id
WHERE m.name LIKE "Любе";