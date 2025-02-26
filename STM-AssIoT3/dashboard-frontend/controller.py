import statistics

class Controller:
    def __init__(self, root, model, view):
        self.root = root
        self.view = view
        self.model = model

        self.mode = ""
        self.state = ""
        self.window_percentage = 0
        self.manual_mode = False

        self.temperature_data = []
        self.max_data_points = 100
        self.temp_min = 0
        self.temp_max = 0
        self.temp_avg = 0

    def update_view(self):
        if not self.view:
            return

        data = self.model.get_system_info()
        if data:
            print(data)
            self.state = data["state"]
            self.temperature_data.append(float(data["temperature"]))
            self.mode = data["mode"]
            self.manual_mode = True if self.mode == "MANUAL" else False
            if len(self.temperature_data) > self.max_data_points:
                self.temperature_data.pop(0)

            self.temp_min = min(self.temperature_data, default=0)
            self.temp_max = max(self.temperature_data, default=0)
            self.temp_avg = round(statistics.mean(self.temperature_data), 2) if self.temperature_data else 0

            self.view.status_label.config(text=f"{self.mode}: {self.state}")
            self.view.temp_stats_label.config(
                text=f"Min: {self.temp_min}°C Max: {self.temp_max}°C Avg: {self.temp_avg}°C")
            self.view.window_level_label.config(text=f"Window Opening: {data['window_opening']}%")
            self.view.window_slider.set(int(data['window_opening']))
            self.view.ax.clear()
            self.view.ax.plot(
                self.temperature_data,
                color="orange",
                linewidth=2,
                markerfacecolor="blue",
                markeredgecolor="blue",
                linestyle="--",
                marker="o",
                markersize=4,
                alpha=0.8
            )

            self.view.canvas.draw()

    def toggle_mode(self):
        self.model.toggle_mode()
        self.manual_mode = not self.manual_mode
        self.update_data()

    def move_window(self):
        self.model.move_window()
        self.view.move_window_btn.state = "normal" if self.manual_mode else "disabled"

    def reset_alarm(self):
        self.model.reset_alarm()

    def start_updating(self):
        self.update_data()

    def update_data(self):
        self.update_view()
        self.root.after(500, self.update_data)