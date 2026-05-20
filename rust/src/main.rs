use futures_util::StreamExt;
use tokio_tungstenite::connect_async;
use serde_json::Value;

#[tokio::main]
async fn main() {
    let url = "ws://127.0.0.1:2014";

    let (ws_stream, _) = connect_async(url)
        .await
        .expect("Failed to connect");

    println!("Connected");

    let (_, mut read) = ws_stream.split();

    while let Some(message) = read.next().await {
        let message = message.unwrap();

        if message.is_text() {
            let text = message.to_text().unwrap();

            let data: Value =
                serde_json::from_str(text).unwrap();

            println!("RIGHT: {}", data["right"]);
            println!("LEFT : {}", data["left"]);
            println!("BODY : {}", data["body"]);
        }
    }
}