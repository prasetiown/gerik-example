const WebSocket = require("ws");

const ws = new WebSocket("ws://127.0.0.1:2014");

ws.on("open", () => {
    console.log("Connected");
});

ws.on("message", (message) => {
    const data = JSON.parse(message);

    console.log("RIGHT:", data.right);
    console.log("LEFT :", data.left);
    console.log("BODY :", data.body);
});

ws.on("close", () => {
    console.log("Disconnected");
});

ws.on("error", (error) => {
    console.error(error);
});