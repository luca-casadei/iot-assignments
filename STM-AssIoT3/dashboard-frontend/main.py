import tkinter as tk
from gui import DashboardGUI
from http_client import HTTPClient
import config

def main():
    root = tk.Tk()
    http_client = "" # HTTPClient(config.BACKEND_URL) # TODO: da finire questa parte
    DashboardGUI(root, http_client)
    root.mainloop()

if __name__ == "__main__":
    main()
