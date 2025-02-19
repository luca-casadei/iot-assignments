import http.client
import json

from config import BACKEND_URL

class HTTPClient:
    def __init__(self):
        self.connection = http.client.HTTPConnection(BACKEND_URL, 8080)

    @staticmethod
    def parse_json(response):
        if not response:
            return {}
        try:
            return json.loads(response)
        except json.JSONDecodeError:
            return {"error": "Invalid JSON data"}

    def get_system_info(self):
        try:
            self.connection.request("GET", "/info")
            response = self.connection.getresponse()
            if response.status == 200:
                return self.parse_json(response.read().decode())
            else:
                print(f"Error: {response.status} - {response.reason}")
                return None
        except Exception as e:
            print(f"GET request error: {e}")
            return None

    def toggle_mode(self, mode):
        try:
            if mode not in ["AUTOMATIC", "MANUAL"]:
                raise ValueError("Mode must be \'AUTOMATIC\' or \'MANUAL\'")

            headers = {'Content-type': 'application/json'}
            body = json.dumps({"mode": mode})
            self.connection.request("POST", "/toggle_mode", body, headers)
            response = self.connection.getresponse()
            print(f"Mode set to {mode}: {response.status} - {response.reason}")
        except Exception as e:
            print(f"POST request error: {e}")

    def reset_alarm(self):
        try:
            headers = {'Content-type': 'application/json'}
            self.connection.request("POST", "/reset", "{}", headers)
            response = self.connection.getresponse()
            print(f"Alarm reset: {response.status} - {response.reason}")
        except Exception as e:
            print(f"POST request error: {e}")

    def close_connection(self):
        self.connection.close()
