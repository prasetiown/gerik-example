import websocket
import json

def on_message(ws, message):
    data = json.loads(message)

    right = data["right"]
    left = data["left"]
    body = data["body"]

    print("RIGHT:", right)
    print("LEFT :", left)
    print("BODY :", body)

def on_error(ws, error):
    print(f"{ws} error : ", error)

def on_close(ws, close_status_code, close_msg):
    print(f"Disconnected to {ws} | status code : {close_status_code} | message : {close_msg}")

def on_open(ws):
    print(f"Connected to {ws}")

ws = websocket.WebSocketApp(
    "ws://127.0.0.1:2014",
    on_open=on_open,
    on_message=on_message,
    on_error=on_error,
    on_close=on_close
)

ws.run_forever()