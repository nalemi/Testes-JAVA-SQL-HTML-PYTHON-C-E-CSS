# Passo a passo do projeto
#passo 1: entrar no sistema da empresa
#pip install pyautogui
import pyautogui
import time
pyautogui.PAUSE = 1

    Televisao   6   340.0   71.4    


#pyautogui.click (clicar)TESA000108
#pyautogui.write(escrever um teTESA000747   TESA000346Samsungxto)
#pyautogui.press(pressionar uma tecla)
#https://dlp.hashtagtreinamentos.com/python/intensivao/login
#passo 2: fazer login
#passo 3:  importar a base de dados
#passo 4: cadastrar 1 produto
#passo 5: repetir o processo de cadastro ate acabar

pyautogui.press("win")
pyautogui.write("chrome")
pyautogui.press("enter")


#entrar no site
link = "https://dlp.hashtagtreinamentos.com/python/intensivao/login"
pyautogui.write("https://dlp.hashtagtreinamentos.com/python/intensivao/login")
pyautogui.press("enter")


#dar uma pausa um pouco maior de 0.3 segundos a cada comando
time.sleep(5)

#passo : fazer loguin

pyautogui.click(x=686, y=409)

#passo : preencher email e senha

pyautogui.write("mylena.2144@hotmail.com")
pyautogui.press("tab")
pyautogui.write("1236456")

#clica no botão de loguin

pyautogui.click(x=675, y=557)
time.sleep(3)

#importar base de dados
#pip install pandas numpy openpyxl

import pandas
tabela = pandas.read_csv("produtos.csv")
print(tabela)

#para cada linha da tabela

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
    


#cadastrar um produto
#repetir o processo ate acabar todos os produtos

