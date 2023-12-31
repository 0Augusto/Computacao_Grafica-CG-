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

        self.dx_label = tk.Label(root, text="Componente x da translação:")
        self.dx_label.pack()
        self.dx_entry = tk.Entry(root)
        self.dx_entry.pack()

        self.dy_label = tk.Label(root, text="Componente y da translação:")
        self.dy_label.pack()
        self.dy_entry = tk.Entry(root)
        self.dy_entry.pack()

        self.sx_label = tk.Label(root, text="Fator de escala em x:")
        self.sx_label.pack()
        self.sx_entry = tk.Entry(root)
        self.sx_entry.pack()

        self.sy_label = tk.Label(root, text="Fator de escala em y:")
        self.sy_label.pack()
        self.sy_entry = tk.Entry(root)
        self.sy_entry.pack()

        self.shx_label = tk.Label(root, text="Fator de cisalhamento em x:")
        self.shx_label.pack()
        self.shx_entry = tk.Entry(root)
        self.shx_entry.pack()

        self.shy_label = tk.Label(root, text="Fator de cisalhamento em y:")
        self.shy_label.pack()
        self.shy_entry = tk.Entry(root)
        self.shy_entry.pack()

        self.transform_button = tk.Button(root, text="Aplicar Transformações", command=self.apply_transformations)
        self.transform_button.pack()

    def apply_transformations(self):
        angle = float(self.angle_entry.get())
        dx = float(self.dx_entry.get())
        dy = float(self.dy_entry.get())
        sx = float(self.sx_entry.get())
        sy = float(self.sy_entry.get())
        shx = float(self.shx_entry.get())
        shy = float(self.shy_entry.get())

        originalPoint = (1.0, 1.0)

        angle_rad = angle * pi / 180.0
        rotatedPoint = (originalPoint[0] * cos(angle_rad) - originalPoint[1] * sin(angle_rad),
                        originalPoint[0] * sin(angle_rad) + originalPoint[1] * cos(angle_rad))

        translatedPoint = (rotatedPoint[0] + dx, rotatedPoint[1] + dy)
        scaledPoint = (translatedPoint[0] * sx, translatedPoint[1] * sy)
        shearedPoint = (scaledPoint[0] + scaledPoint[1] * shx, scaledPoint[1] + scaledPoint[0] * shy)

        print("Original:", originalPoint)
        print("Rotacionado:", rotatedPoint)
        print("Transladado:", translatedPoint)
        print("Escalado:", scaledPoint)
        print("Cisalhado:", shearedPoint)

        # Criação do gráfico de dispersão
        plt.figure()

        # Plotar os pontos transformados
        plt.scatter(*zip(originalPoint), label='Original', color='blue')
        plt.scatter(*zip(rotatedPoint), label='Rotacionado', color='green')
        plt.scatter(*zip(translatedPoint), label='Transladado', color='red')
        plt.scatter(*zip(scaledPoint), label='Escalado', color='purple')
        plt.scatter(*zip(shearedPoint), label='Cisalhado', color='orange')

        plt.xlabel('Eixo X')
        plt.ylabel('Eixo Y')
        plt.title('Transformações Geométricas')
        plt.legend()

        # Exibir o gráfico
        plt.show()
    def on_canvas_click(self, event):
        x = event.x
        y = event.y
        self.points.append((x, y))
        self.canvas.create_oval(x - 1, y - 1, x + 1, y + 1, fill="black")

        # Desenhar a linha usando o algoritmo DDA
        if len(self.points) == 2:
            x1, y1 = self.points[0]
            x2, y2 = self.points[1]
            line_points = self.dda_line(x1, y1, x2, y2)
            for point in line_points:
                self.canvas.create_oval(point[0], point[1], point[0], point[1], fill="blue")

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

    def apply_transformations(self):
        # Resto da função apply_transformations
         pass
        

if __name__ == "__main__":
    root = tk.Tk()
    app = TransformationsApp(root)
    root.mainloop()

