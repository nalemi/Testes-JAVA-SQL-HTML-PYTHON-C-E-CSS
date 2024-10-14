CREATE DATABASE mercado;
use mercado;

CREATE TABLE nome(
id INT AUTO_INCREMENT PRIMARY KEY,
email varchar(30),
nome varchar (30)
);

CREATE TABLE clientes(
id INT AUTO_INCREMENT PRIMARY KEY,
nome varchar(30),
telefone varchar(20),
endereco varchar(20),
email varchar(30)
);


CREATE TABLE estoque(
id INT AUTO_INCREMENT PRIMARY KEY,
produtos varchar(40),
quantidade int,
preco DECIMAL(10,2)
);

INSERT INTO clientes(nome,endereco,telefone,email)
VALUES('milena','rua jose rocha',71982938517, 'mylena@hotmail.com');

SELECT * FROM clientes;

INSERT INTO estoque(produtos,quantidade,preco)
VALUES('Feijao', 30, 7.00),
('Arroz', 30, 5.99),
('Macarrao', 40, 4.99);

SELECT * FROM estoque;



