CREATE DATABASE loja;
use loja;

CREATE TABLE loja(
id INT AUTO_INCREMENT PRIMARY KEY,
nome varchar(100),
produtos varchar(100),
quantidade int,
preco DECIMAL(10,2),
email varchar (100)
);

CREATE TABLE clientes(
id INT AUTO_INCREMENT PRIMARY KEY,
nome varchar (100),
email varchar (100)
);

INSERT INTO loja(nome, produtos, quantidade, preco, email )
VALUES ('Deposito', 'Heinekeen', 100, 13.99, 'ias@hotmail.com'),
('Deposito', 'Budwaiser',50, 11.99, 'milena@hotmail.com'),
('Deposito', 'Corona', 90, 14.99, 'mustafa@hotmail.com');

SELECT* FROM loja;







