using System;
using System.Net.WebSockets;
using System.Text;
using System.Text.Json;

var client = new ClientWebSocket();

await client.ConnectAsync(
    new Uri("ws://127.0.0.1:2014"),
    CancellationToken.None
);

Console.WriteLine("Connected");

var buffer = new byte[4096];

while (true)
{
    var result = await client.ReceiveAsync(
        new ArraySegment<byte>(buffer),
        CancellationToken.None
    );

    var message = Encoding.UTF8.GetString(
        buffer,
        0,
        result.Count
    );

    using JsonDocument doc = JsonDocument.Parse(message);

    Console.WriteLine(
        "RIGHT: " + doc.RootElement.GetProperty("right")
    );

    Console.WriteLine(
        "LEFT : " + doc.RootElement.GetProperty("left")
    );

    Console.WriteLine(
        "BODY : " + doc.RootElement.GetProperty("body")
    );
}