import tkinter as tk
import subprocess

# Função para executar o código C
def execute_c_code():
    # Obter os valores inseridos pelo usuário
    angle = float(angle_entry.get())
    dx = float(dx_entry.get())
    dy = float(dy_entry.get())
    sx = float(sx_entry.get())
    sy = float(sy_entry.get())
    shx = float(shx_entry.get())
    shy = float(shy_entry.get())

    # Chamar o código C compilado com os valores inseridos
    cmd_compile = "gcc -o UmTrabalho UmTrabalho.c"  # Comando de compilação
    cmd_run = f"./UmTrabalho {angle} {dx} {dy} {sx} {sy} {shx} {shy}"  # Comando de execução
    try:
        # Compilar o código C
        subprocess.run(cmd_compile, shell=True, check=True)
        # Executar o código C compilado
        subprocess.run(cmd_run, shell=True, check=True)
        result_label.config(text="Código C executado com sucesso!")
    except subprocess.CalledProcessError:
        result_label.config(text="Erro ao executar o código C.")

# Função para desenhar uma reta utilizando o algoritmo DDA
def draw_dda():
    # Obter as coordenadas de início e fim da reta inseridas pelo usuário
    x1 = float(x1_entry.get())
    y1 = float(y1_entry.get())
    x2 = float(x2_entry.get())
    y2 = float(y2_entry.get())

    # Desenhar a reta utilizando o algoritmo DDA
    # ...

# Criar a janela da interface gráfica
root = tk.Tk()
root.title("Transformações Geométricas")

# Criar os campos de entrada para as transformações
# ...

# Botão para executar o código C
execute_button = tk.Button(root, text="Compilar e Executar Código C", command=execute_c_code)
execute_button.pack()

# Label para exibir o resultado
result_label = tk.Label(root, text="")
result_label.pack()

# Área para desenhar a reta
canvas = tk.Canvas(root, width=300, height=300, bg="white")
canvas.pack()

# Campos de entrada para as coordenadas da reta
tk.Label(root, text="Coordenadas da Reta (x1, y1, x2, y2):").pack()
x1_entry = tk.Entry(root)
x1_entry.pack()
y1_entry = tk.Entry(root)
y1_entry.pack()
x2_entry = tk.Entry(root)
x2_entry.pack()
y2_entry = tk.Entry(root)
y2_entry.pack()

# Botão para desenhar a reta
draw_button = tk.Button(root, text="Desenhar Reta", command=draw_dda)
draw_button.pack()

# Iniciar a interface gráfica
root.mainloop()

