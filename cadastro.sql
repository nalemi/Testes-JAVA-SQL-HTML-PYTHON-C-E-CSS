CREATE DATABASE cadastro;
use cadastro;

CREATE TABLE pessoas(
nome varchar(50),
idade tinyint,
sexo char (1),
peso float,
altura float,
nacionalidade varchar (20)
);

describe pessoas;

INSERT INTO pessoas(nome,idade,sexo,peso,altura,nacionalidade)
VALUES('milena', 22, 'F', 60.00, 1.63, 'Brasileira');

SELECT *FROM pessoas;