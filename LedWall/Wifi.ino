void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // mac is 30:AE:A4:9B:FB:78
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  
  while (WiFi.status() != WL_CONNECTED) {
    analogWrite(WIFI_LED_PIN, 0); // Wifi connected led off
    delay(1000);
    Serial.println("🤔..."); 
    WiFi.begin(ssid, password);
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  analogWrite(WIFI_LED_PIN, 60); // Wifi connected led on
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ledwall", mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(ctrlTopic);
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
