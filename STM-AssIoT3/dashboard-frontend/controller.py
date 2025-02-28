import statistics

from config import TEMPERATURE_THRESHOLD

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
        self.max_data_points = 50

    def update_view(self):
        if not self.view:
            return

        data = self.model.get_system_info()
        if data:
            print(data)
            self.state = data["state"]
            self.temperature_data.append(float(data["temperature"]))
            self.mode = data["mode"]
            self.manual_mode = (data["mode"] == "MANUAL")
            if len(self.temperature_data) > self.max_data_points:
                self.temperature_data.pop(0)

            self.view.status_label.config(text=f"{self.mode}: {self.state}")
            self.view.temp_stats_label.config(
                text=f"Min: {data["min"]}°C Max: {data["max"]}°C Avg: {"{:.2f}".format(float(data["avg"]))}°C")
            self.view.window_level_label.config(text=f"Window Opening: {data['window_opening']}%")
            if not self.manual_mode:
                self.view.window_slider.set(int(data['window_opening']))

            self.view.system_mode_btn.config(text="Activate Automatic Mode" if self.manual_mode else "Activate Manual Mode")
            self.view.move_window_btn.config(state="normal" if self.manual_mode else "disabled")

            self.view.alarm_btn.config(state="normal" if self.state == "ALARM" else "disabled")

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
            fixed_threshold = TEMPERATURE_THRESHOLD
            self.view.ax.axhline(fixed_threshold, color="red", linestyle="--", label=f"Threshold: {fixed_threshold}°C")
            self.view.ax.legend()
            self.view.canvas.draw()


    def toggle_mode(self):
        self.model.toggle_mode()
        data = self.model.get_system_info()
        if data:
            self.manual_mode = (data["mode"] == "MANUAL")
            self.view.system_mode_btn.config(text="Activate Automatic Mode" if self.manual_mode else "Activate Manual Mode")
            self.view.move_window_btn.config(state="normal" if self.manual_mode else "disabled")

    def move_window(self):
        self.model.move_window(int(self.view.window_slider.get()))

    def reset_alarm(self):
        self.model.reset_alarm()

    def start_updating(self):
        self.update_data()

    def update_data(self):
        self.update_view()
        self.root.after(1000, self.update_data)
