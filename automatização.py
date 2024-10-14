# As bibliotecas ficam nas primeiras linhas ao topo do programa
import pyautogui
import time
import pandas

pyautogui.PAUSE = 1

# pyautogui.click (clicar)
# pyautogui.write(escrever um texto)
# pyautogui.press(pressionar uma tecla)
# https://dlp.hashtagtreinamentos.com/python/intensivao/login
# passo 2: fazer login
# passo 3:  importar a base de dados
# passo 4: cadastrar 1 produto
# passo 5: repetir o processo de cadastro ate acabar

# Abre o browser
pyautogui.press("win")
pyautogui.write("chrome")
pyautogui.press("enter")

# entrar no site
link = "https://dlp.hashtagtreinamentos.com/python/intensivao/login"
pyautogui.write(link)
pyautogui.press("enter")

# Dá uma pausa um pouco maior de 0.3 segundos a cada comando
time.sleep(3)

# passo : fazer loguin

pyautogui.click(x=686, y=409)

# passo : preencher email e senha

pyautogui.write("mylena.2144@hotmail.com")
pyautogui.press("tab")
pyautogui.write("1236456")

# clica no botão de loguin

pyautogui.click(x=675, y=557)
time.sleep(3)

# importar base de dados
# pip install pandas numpy openpyxl


tabela = pandas.read_csv(r"C:\Users\User\OneDrive\Documentos\python.aula1\produtos.csv")
print(tabela)

# para cada linha da tabela

for linha in tabela.index:
    pyautogui.click(x=527, y=294)

    pyautogui.write(tabela.loc[linha, "codigo"])
    pyautogui.press("tab")

    pyautogui.write(tabela.loc[linha, "marca"])
    pyautogui.press("tab")

    pyautogui.write(tabela.loc[linha, "tipo"])
    pyautogui.press("tab")

    pyautogui.write(str(tabela.loc[linha, "categoria"]))
    pyautogui.press("tab")

    pyautogui.write(str(tabela.loc[linha, "preco_unitario"]))
    pyautogui.press("tab")

    pyautogui.write(str(tabela.loc[linha, "custo"]))
    pyautogui.press("tab")

    if not pandas.isna(tabela.loc[linha, "obs"]):
        pyautogui.write(tabela.loc[linha, "obs"])
        pyautogui.press("tab")
    pyautogui.press("enter")
    pyautogui.scroll(5000)

# cadastrar um produto
# repetir o processo ate acabar todos os produtos


