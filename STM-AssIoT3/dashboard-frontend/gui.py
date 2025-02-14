import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import statistics

class DashboardGUI:
    def __init__(self, root, http_client):
        self.root = root
        self.root.title("Smart Temperature Monitoring Dashboard")
        self.root.geometry("900x650")
        self.root.resizable(False, False)
        self.root.configure(bg="#f0f0f0")

        self.http_client = http_client
        self.temperature_data = []
        self.max_data_points = 100
        self.temp_min = 0
        self.temp_max = 0
        self.temp_avg = 0
        self.state = ""
        self.window_percentage = 0
        self.manual_mode = False

        self.create_panel()
        # self.update_data()  # TODO: Attivare quando l'API è pronta

    def create_panel(self):
        main_frame = tk.Frame(self.root, bg="#f0f0f0")
        main_frame.pack(pady=10, padx=10, fill="both", expand=True)

        self.status_label = tk.Label(
            main_frame,
            text=f"State: {self.state}",
            font=("Arial", 18, "bold"),
            fg="blue",
            bg="#f0f0f0")
        self.status_label.pack(pady=5)

        self.temp_stats_label = tk.Label(
            main_frame,
            text=f"Min: {self.temp_min}°C \t Max: {self.temp_max}°C \t Avg: {self.temp_avg}°C",
            font=("Arial", 12),
            bg="#f0f0f0"
        )
        self.temp_stats_label.pack()

        self.window_level_label = tk.Label(
            main_frame,
            text=f"Window Opening: {self.window_percentage}%",
            font=("Arial", 12),
            bg="#f0f0f0")
        self.window_level_label.pack(pady=5)

        self.fig, self.ax = plt.subplots(figsize=(6, 3))
        self.ax.set_title("Temperature Trend", fontsize=12)
        self.ax.set_xlabel("Time", fontsize=10)
        self.ax.set_ylabel("Temperature (°C)", fontsize=10)
        self.ax.grid(True, linestyle="--", alpha=0.6)
        self.canvas = FigureCanvasTkAgg(self.fig, master=main_frame)
        self.canvas.get_tk_widget().pack(pady=10, fill="both", expand=True)

        control_frame = tk.Frame(main_frame, bg="#f0f0f0")
        control_frame.pack(pady=5, padx=5)

        self.system_mode_btn = ttk.Button(
            control_frame,
            text= "Activate Automatic Mode" if self.manual_mode else "Activate Manual Mode",
            command=self.toggle_mode)
        self.system_mode_btn.grid(row=0, column=0, padx=10, pady=5)

        self.window_slider = ttk.Scale(
            control_frame,
            from_=0, to=100,
            orient="horizontal",
            length=300,
            command=self.set_window_opening,
            state= tk.ACTIVE if self.manual_mode else tk.DISABLED)
        self.window_slider.grid(row=0, column=1, padx=10, pady=5)

        self.alarm_btn = ttk.Button(
            control_frame,
            text="Reset Alarm",
            command=self.reset_alarm,
            state=tk.DISABLED)
        self.alarm_btn.grid(row=0, column=2, padx=10, pady=5)

    def update_data(self):
        data = self.http_client.get_system_info()

        if data:
            self.status_label.config(text=f"State: {data['state']}", fg=self.get_state_color(data["state"]))

            if data:
                self.temp_min = min(self.temperature_data) if self.temperature_data else 0
                self.temp_max = max(self.temperature_data) if self.temperature_data else 0
                self.temp_avg = round(statistics.mean(self.temperature_data), 2) if self.temperature_data else 0

                self.temp_stats_label.config(
                    text=f"Min: {self.temp_min}°C \t Max: {self.temp_max}°C \t Avg: {self.temp_avg}°C"
                )

            self.temperature_data.append(data["current_temperature"])
            if len(self.temperature_data) > self.max_data_points:
                self.temperature_data.pop(0)

            if self.temperature_data:
                min_temp = min(self.temperature_data)
                max_temp = max(self.temperature_data)
                avg_temp = round(statistics.mean(self.temperature_data), 2)
                self.temp_stats_label.config(
                    text=f"Min: {min_temp}°C \t Max: {max_temp}°C \t Avg: {avg_temp}°C"
                )

            self.window_level_label.config(text=f"Window Opening Percentage: {data['window_opening']}%")
            self.window_slider.set(data["window_opening"])

            self.ax.clear()
            self.ax.grid(True, linestyle="--", alpha=0.6)
            self.ax.plot(self.temperature_data, label="Temperature", color="red", linewidth=2)
            self.ax.legend()
            self.canvas.draw()

            self.alarm_btn.config(state="normal" if data["state"] == "ALARM" else "disabled")

        self.root.after(5000, self.update_data) # Tempo di chiamata al metodo, attualmente è impostato a 5 secondi (quindi 5000ms) => TODO: da decidere quanto mettere.

    def toggle_mode(self):
        # todo: self.http_client.set_automatic_mode() if self.manual_mode else self.http_client.set_manual_mode()
        self.manual_mode = not self.manual_mode
        self.system_mode_btn.config(
            text= "Activate Automatic Mode" if self.manual_mode else "Activate Manual Mode",
        )
        self.window_slider.config(
            state=tk.ACTIVE if self.manual_mode else tk.DISABLED
        )

    def set_window_opening(self, value):
        self.http_client.set_window_opening(int(float(value)))

    def reset_alarm(self):
        self.http_client.reset_alarm()

    def get_state_color(self, state):
        colors = {
            "NORMAL": "green",
            "HOT": "orange",
            "TOO-HOT": "red",
            "ALARM": "darkred"
        }
        return colors.get(state, "black")

