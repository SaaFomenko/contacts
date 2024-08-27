PREPARE insert_person AS
INSERT INTO person (name, surname, email)
VALUES ($1, $2, $3);

PREPARE insert_phone AS
INSERT INTO telephone (number, person_id)
VALUES ($1, $2);

PREPARE update_person AS
UPDATE person
SET name = $1, surname = $2, email = $3
WHERE id = $4;

PREPARE delete_phone AS
DELETE FROM telephone
WHERE number = $1 AND person_id = $2;

PREPARE delete_person AS
DELETE FROM person
WHERE id = $1;

PREPARE find_person AS
SELECT * FROM person
WHERE name = $1 AND surname = $2 AND email = $3;

PREPARE find_phone AS
SELECT p.* FROM person p
JOIN telephone t ON p.id = t.person_id
WHERE t.number = $1;