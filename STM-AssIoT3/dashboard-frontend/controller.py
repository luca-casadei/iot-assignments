import statistics

class Controller:
    def __init__(self, model, view):
        self.model = model
        self.view = view

    def update_view(self):
        data = self.model.get_system_info()
        if data:
            self.view.state = data["state"]
            self.view.temperature_data.append(data["current_temperature"])
            if len(self.view.temperature_data) > self.view.max_data_points:
                self.view.temperature_data.pop(0)

            self.view.temp_min = min(self.view.temperature_data, default=0)
            self.view.temp_max = max(self.view.temperature_data, default=0)
            self.view.temp_avg = round(statistics.mean(self.view.temperature_data),
                                       2) if self.view.temperature_data else 0

            self.view.status_label.config(text=f"State: {self.view.state}")
            self.view.temp_stats_label.config(
                text=f"Min: {self.view.temp_min}°C Max: {self.view.temp_max}°C Avg: {self.view.temp_avg}°C")
            self.view.window_level_label.config(text=f"Window Opening: {data['window_opening']}%")
            self.view.window_slider.set(data["window_opening"])

            self.view.ax.clear()
            self.view.ax.plot(self.view.temperature_data, color="red", linewidth=2)
            self.view.canvas.draw()

    def toggle_mode(self):
        mode = "AUTOMATIC" if self.view.manual_mode else "MANUAL"
        self.model.toggle_mode(mode)
        self.view.manual_mode = not self.view.manual_mode

    def set_window_opening(self):
        self.model.set_window_opening()

    def reset_alarm(self):
        self.model.reset_alarm()