import tkinter as tk
from math import pi, cos, sin
import matplotlib.pyplot as plt

class TransformationsApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Transformações Geométricas")

        self.angle_label = tk.Label(root, text="Ângulo de rotação (graus):")
        self.angle_label.pack()
        self.angle_entry = tk.Entry(root)
        self.angle_entry.pack()

        # Restante do código para os campos de entrada

        self.transform_button = tk.Button(root, text="Aplicar Transformações", command=self.apply_transformations)
        self.transform_button.pack()

        self.canvas = tk.Canvas(root, width=400, height=400)
        self.canvas.pack()
        self.canvas.bind("<Button-1>", self.on_canvas_click)

        self.points = []

    def apply_transformations(self):
        angle = float(self.angle_entry.get())
        dx = float(self.dx_entry.get())
        dy = float(self.dy_entry.get())
        sx = float(self.sx_entry.get())
        sy = float(self.sy_entry.get())
        shx = float(self.shx_entry.get())
        shy = float(self.shy_entry.get())

        # Resto da função apply_transformations

    def on_canvas_click(self, event):
        x = event.x
        y = event.y
        self.points.append((x, y))
        self.canvas.create_oval(x - 1, y - 1, x + 1, y + 1, fill="black")

        # Verificar se há pelo menos dois pontos capturados para desenhar a reta
        if len(self.points) >= 2:
            # Capturar os dois últimos pontos adicionados
            x1, y1 = self.points[-2]
            x2, y2 = self.points[-1]
            
            # Calcular e desenhar a reta entre os pontos capturados
            line_points = self.dda_line(x1, y1, x2, y2)
            for i in range(len(line_points) - 1):
                x1, y1 = line_points[i]
                x2, y2 = line_points[i + 1]
                self.canvas.create_line(x1, y1, x2, y2, fill="blue")

    def dda_line(self, x1, y1, x2, y2):
        points = []
        dx = x2 - x1
        dy = y2 - y1
        steps = abs(dx) if abs(dx) > abs(dy) else abs(dy)
        x_increment = dx / steps
        y_increment = dy / steps

        x = x1
        y = y1

        for _ in range(steps + 1):
            points.append((int(round(x)), int(round(y))))
            x += x_increment
            y += y_increment

        return points


if __name__ == "__main__":
    root = tk.Tk()
    app = TransformationsApp(root)
    root.mainloop()
