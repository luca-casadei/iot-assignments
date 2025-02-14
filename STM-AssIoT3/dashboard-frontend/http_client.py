import http.client
import json

class HTTPClient:
    def __init__(self, base_url):
        self.connection = http.client.HTTPSConnection(base_url)

    def get_system_info(self):
        try:
            self.connection.request("GET", "/info")
            response = self.connection.getresponse()
            if response.status == 200:
                return json.loads(response.read().decode())
            else:
                print(f"Error: {response.status} - {response.reason}")
                return None
        except Exception as e:
            print(f"GET request error: {e}")
            return None

    def set_automatic_mode(self):
        try:
            headers = {'Content-type': 'application/json'}
            self.connection.request("POST", "/set_automatic", "{}", headers)
            response = self.connection.getresponse()
            print(f"Automatic mode set: {response.status} - {response.reason}")
        except Exception as e:
            print(f"POST request error: {e}")

    def set_manual_mode(self):
        try:
            headers = {'Content-type': 'application/json'}
            self.connection.request("POST", "/set_manual", "{}", headers)
            response = self.connection.getresponse()
            print(f"Manual mode set: {response.status} - {response.reason}")
        except Exception as e:
            print(f"POST request error: {e}")

    def reset_alarm(self):
        try:
            headers = {'Content-type': 'application/json'}
            self.connection.request("POST", "/reset_alarm", "{}", headers)
            response = self.connection.getresponse()
            print(f"Alarm reset: {response.status} - {response.reason}")
        except Exception as e:
            print(f"POST request error: {e}")

    def close_connection(self):
        self.connection.close()
