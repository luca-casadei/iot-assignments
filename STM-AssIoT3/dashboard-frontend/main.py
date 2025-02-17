import tkinter as tk
from view import Dashboard
from model import HTTPClient
from controller import Controller
import config

def main():
    root = tk.Tk()
    model = "" # HTTPClient(config.BACKEND_URL) # TODO: da finire questa parte
    controller = Controller(model, None)
    view = Dashboard(root, Controller)
    controller.view = view

    root.mainloop()

if __name__ == "__main__":
    main()
