import tkinter as tk
from view import Dashboard
from model import HTTPClient
from controller import Controller

def main():
    root = tk.Tk()
    model = HTTPClient()
    controller = Controller(model, None)
    view = Dashboard(root, controller)
    controller.view = view
    view.start_updating()
    root.mainloop()

if __name__ == "__main__":
    main()
