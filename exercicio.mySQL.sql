-- 1. Criar o banco de dados e usar
CREATE DATABASE Exe2;
USE Exe2;

-- 2. Criar a tabela usuarios
CREATE TABLE usuarios (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(100),
    email VARCHAR(100),
    senha VARCHAR(255)
);

-- 3. Criar a procedure para cadastrar usuário
DELIMITER //
CREATE PROCEDURE cadastrar_usuario(
    IN p_nome VARCHAR(100),
    IN p_email VARCHAR(100),
    IN p_senha VARCHAR(255)
)
BEGIN
    INSERT INTO usuarios (nome, email, senha) VALUES (p_nome, p_email, p_senha);
END //
DELIMITER ;

-- 4. Chamar a procedure para cadastrar um usuário
CALL cadastrar_usuario('Milena', 'milena@hotmail.com', 'senha@1');

-- 5. Selecionar todos os usuários
SELECT * FROM usuarios;

-- 6. Criar a função para calcular a idade
DELIMITER //
CREATE FUNCTION calcular_idade(
    p_data_nascimento DATE
) RETURNS INT DETERMINISTIC
BEGIN
    DECLARE idade INT;
    SET idade = YEAR(CURDATE()) - YEAR(p_data_nascimento);
    RETURN idade;
END //
DELIMITER ;

-- 7. Testar a função calcular_idade
SELECT calcular_idade('2001-10-21');

-- 8. Criar a tabela clientes
CREATE TABLE clientes (
    id_cliente INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(100),
    email VARCHAR(100),
    data_modificacao DATETIME
);

-- 9. Criar a tabela pedidos
CREATE TABLE pedidos (
    id_pedido INT PRIMARY KEY AUTO_INCREMENT,
    id_cliente INT,
    data_pedido DATETIME,
    valor DECIMAL(10,2),
    FOREIGN KEY (id_cliente) REFERENCES clientes(id_cliente)
);

-- 10. Criar a trigger para atualizar a data de modificação
DELIMITER //
CREATE TRIGGER atualizar_data_modificacao
AFTER INSERT ON pedidos
FOR EACH ROW
BEGIN
    UPDATE clientes
    SET data_modificacao = NOW()
    WHERE id_cliente = NEW.id_cliente;
END //
DELIMITER ;

INSERT INTO clientes (nome, email, data_modificacao) VALUES ('Milena', 'milena@hotmail.com', NOW());

