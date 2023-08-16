import tkinter as tk
from math import pi, cos, sin

class TransformationsApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Transformações Geométricas")

        self.canvas = tk.Canvas(root, width=400, height=400)
        self.canvas.pack()

        self.canvas.bind("<Button-1>", self.start_drawing)
        self.canvas.bind("<B1-Motion>", self.draw)

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

        self.start_point = None
        self.end_point = None

    def start_drawing(self, event):
        self.start_point = (event.x, event.y)

    def draw(self, event):
        if self.start_point:
            self.end_point = (event.x, event.y)
            self.canvas.delete("line")
            self.canvas.create_line(self.start_point, self.end_point, tags="line")

    def apply_transformations(self):
        angle = float(self.angle_entry.get())
        dx = float(self.dx_entry.get())
        dy = float(self.dy_entry.get())
        sx = float(self.sx_entry.get())
        sy = float(self.sy_entry.get())
        shx = float(self.shx_entry.get())
        shy = float(self.shy_entry.get())

        if self.start_point and self.end_point:
            originalPoint = self.start_point
            rotatedPoint = originalPoint
            translatedPoint = originalPoint
            scaledPoint = originalPoint
            shearedPoint = originalPoint

            # Apply transformations to the starting point
            angle_rad = angle * pi / 180.0
            rotatedPoint = (
                originalPoint[0] * cos(angle_rad) - originalPoint[1] * sin(angle_rad),
                originalPoint[0] * sin(angle_rad) + originalPoint[1] * cos(angle_rad)
            )

            translatedPoint = (rotatedPoint[0] + dx, rotatedPoint[1] + dy)
            scaledPoint = (translatedPoint[0] * sx, translatedPoint[1] * sy)
            shearedPoint = (scaledPoint[0] + scaledPoint[1] * shx, scaledPoint[1] + scaledPoint[0] * shy)

            print("Original:", originalPoint)
            print("Rotacionado:", rotatedPoint)
            print("Transladado:", translatedPoint)
            print("Escalado:", scaledPoint)
            print("Cisalhado:", shearedPoint)

if __name__ == "__main__":
    root = tk.Tk()
    app = TransformationsApp(root)
    root.mainloop()

