import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

class Dashboard:
    def __init__(self, root, controller):
        self.controller = controller
        self.root = root
        self.root.title("Smart Temperature Monitoring Dashboard")
        self.root.geometry("900x650")
        self.root.resizable(False, False)
        self.root.configure(bg="#f0f0f0")

        self.create_dashboard()

    def create_dashboard(self):
        main_frame = tk.Frame(self.root, bg="#f0f0f0")
        main_frame.pack(pady=10, padx=10, fill="both", expand=True)

        self.status_label = tk.Label(
            main_frame,
            font=("Arial", 18, "bold"),
            fg="blue",
            bg="#f0f0f0")
        self.status_label.pack(pady=5)

        self.temp_stats_label = tk.Label(
            main_frame,
            font=("Arial", 12),
            bg="#f0f0f0"
        )
        self.temp_stats_label.pack()

        self.window_level_label = tk.Label(
            main_frame,
            text=f"Window Opening: {self.controller.window_percentage}%",
            font=("Arial", 12),
            bg="#f0f0f0")
        self.window_level_label.pack(pady=5)

        self.fig, self.ax = plt.subplots(figsize=(6, 3))
        self.ax.set_title("Temperature Trend", fontsize=12)
        self.ax.set_xlabel("Time", fontsize=10)
        self.ax.set_ylabel("Temperature (°C)", fontsize=10)
        self.ax.grid(True, linestyle="-.", alpha=0.6)
        self.canvas = FigureCanvasTkAgg(self.fig, master=main_frame)
        self.canvas.get_tk_widget().pack(pady=10, fill="both", expand=True)

        control_frame = tk.Frame(main_frame, bg="#f0f0f0")
        control_frame.pack(pady=5, padx=5)

        self.system_mode_btn = ttk.Button(
            control_frame,
            text= "Activate Automatic Mode" if self.controller.manual_mode else "Activate Manual Mode",
            command=self.controller.toggle_mode)
        self.system_mode_btn.grid(row=0, column=0, padx=10, pady=5)

        self.window_slider = ttk.Scale(
            control_frame,
            from_=0, to=100,
            orient="horizontal",
            length=300
        )
        self.window_slider.grid(row=0, column=1, padx=10, pady=5)

        self.move_window_btn = ttk.Button(
            control_frame,
            text="Move Window",
            command=self.controller.move_window,
            state=tk.NORMAL if self.controller.manual_mode else tk.DISABLED)
        self.move_window_btn.grid(row=0, column=2, padx=10, pady=5)

        self.alarm_btn = ttk.Button(
            control_frame,
            text="Reset Alarm",
            command=self.controller.reset_alarm,
            state= tk.NORMAL if self.controller.manual_mode else tk.DISABLED)
        self.alarm_btn.grid(row=0, column=3, padx=15, pady=5)
