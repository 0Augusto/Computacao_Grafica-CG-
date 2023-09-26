import tkinter as tk
from tkinter import Canvas, Entry, Button, Label

# Cohen-Sutherland region codes
INSIDE = 0
LEFT = 1
RIGHT = 2
BOTTOM = 4
TOP = 8

# Clipping window coordinates
X_MIN = 0
X_MAX = 800
Y_MIN = 0
Y_MAX = 600

# Function to calculate region code for a point
def calculate_region_code(x, y):
    code = INSIDE

    if x < X_MIN:
        code |= LEFT
    elif x > X_MAX:
        code |= RIGHT

    if y < Y_MIN:
        code |= BOTTOM
    elif y > Y_MAX:
        code |= TOP

    return code

# Cohen-Sutherland line clipping function
def cohen_sutherland(x1, y1, x2, y2):
    code1 = calculate_region_code(x1, y1)
    code2 = calculate_region_code(x2, y2)
    accept = False

    while True:
        if not (code1 | code2):
            # Both endpoints are inside the clipping window
            accept = True
            break
        elif code1 & code2:
            # Both endpoints are outside on the same side
            break
        else:
            # Some part of the line is inside, clip against the window
            code_out = code1 if code1 else code2
            x, y = 0, 0  # Initialize x and y variables

            if code_out & TOP:
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1)
                y = Y_MAX
            elif code_out & BOTTOM:
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1)
                y = Y_MIN
            elif code_out & RIGHT:
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1)
                x = X_MAX
            elif code_out & LEFT:
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1)
                x = X_MIN

            if code_out == code1:
                x1, y1 = x, y
                code1 = calculate_region_code(x1, y1)
            else:
                x2, y2 = x, y
                code2 = calculate_region_code(x2, y2)

    if accept:
        result_label.config(text=f"Accepted line segment: ({x1},{y1}) to ({x2},{y2})")
    else:
        result_label.config(text=f"Rejected line segment: ({x1},{y1}) to ({x2},{y2})")

# Create a Tkinter window
root = tk.Tk()
root.title("Cohen-Sutherland Line Clipping")

# Create label and entry widgets for user input
x1_label = Label(root, text="x1:")
x1_label.pack()
x1_entry = Entry(root)
x1_entry.pack()

y1_label = Label(root, text="y1:")
y1_label.pack()
y1_entry = Entry(root)
y1_entry.pack()

x2_label = Label(root, text="x2:")
x2_label.pack()
x2_entry = Entry(root)
x2_entry.pack()

y2_label = Label(root, text="y2:")
y2_label.pack()
y2_entry = Entry(root)
y2_entry.pack()

# Create a button to trigger the line clipping
clip_button = Button(root, text="Clip Line", command=lambda: cohen_sutherland(
    int(x1_entry.get()), int(y1_entry.get()), int(x2_entry.get()), int(y2_entry.get())
))
clip_button.pack()

# Create a canvas to display the line (visual representation of clipping)
canvas = Canvas(root, width=800, height=600)
canvas.pack()

# Create a label to display the result
result_label = Label(root, text="", font=("Helvetica", 12))
result_label.pack()

# Run the Tkinter event loop
root.mainloop()
