#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Baby Cradle";  // WiFi Name (No Password)
  // Made By raja 11thc

ESP8266WebServer server(80);

const int ena = 4;  // D2 (GPIO 4)
const int in1 = 14; // D5 (GPIO 14)
const int in2 = 12; // D6 (GPIO 12)

void setup() {
  Serial.begin(115200);

  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Start WiFi AP Mode
  WiFi.softAP(ssid);
  Serial.println("WiFi AP Started!");
  Serial.println(WiFi.softAPIP()); // Show ESP8266 IP

  // Webpage Routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/stop", handleStop);
  server.on("/speed", handleSpeed);

  server.begin();
}

void loop() {
  server.handleClient();
}

// Webpage
void handleRoot() {
  server.send(200, "text/html", R"rawliteral(

<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Baby Cardle</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #121212;
            color: white;
            margin: 0;
            padding: 20px;
        }
        h1 {
            color: #00c3ff;
        }
        .button {
            background-color: #00c3ff;
            border: none;
            color: white;
            padding: 15px 30px;
            margin: 10px;
            font-size: 20px;
            border-radius: 10px;
            cursor: pointer;
            transition: 0.3s;
        }
        .button:hover {
            background-color: #008acb;
        }
        #speed {
            width: 80%;
            margin-top: 20px;
        }
        .status {
            margin-top: 20px;
            font-size: 18px;
            font-weight: bold;
            color: #00ff6e;
        }
    </style>
</head>
<body>
    <h1>Baby Cradle Class 9th-A</h1>
    <button class="button" onclick="sendRequest('/forward', 'Moving Forward')">Start</button>
    <button class="button" onclick="sendRequest('/stop', 'Stopped')">Stop</button>
    <br>
    <input type="range" min="0" max="255" value="128" id="speed" onchange="setSpeed(this.value)">
    <p class="status" id="statusText">Status: Ready</p>

    <script>
        function sendRequest(url, statusText) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", url, true);
            xhr.send();
            xhr.onload = function() {
                if (xhr.status == 200) {
                    document.getElementById("statusText").innerText = "Status: " + statusText;
                } else {
                    document.getElementById("statusText").innerText = "Status: Error";
                }
            };
        }
        function setSpeed(value) {
            sendRequest('/speed?value=' + value, 'Speed Set: ' + value);
        }
    </script>
</body>
</html>

  )rawliteral");
}

// Motor Forward
void handleForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

// Motor Reverse
void handleReverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  server.send(200, "text/plain", "Moving Reverse");
}

// Motor Stop
void handleStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  server.send(200, "text/plain", "Stopped");
}

// Speed Control
void handleSpeed() {
  if (server.hasArg("value")) {
    int speed = server.arg("value").toInt();
    analogWrite(ena, speed);
    server.send(200, "text/plain", "Speed Set to " + String(speed));
  }
}
