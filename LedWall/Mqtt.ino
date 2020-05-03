void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
//  Serial.println(message);

  if (!processMessage(message)) {
    // Calls the process function and if it fails then we escape here
    return;
  }

  // Maps brightness if it's valid
  if (gCtrl[0] > 20 || gCtrl[0] < 4090) {
    brightness = sigDiff(brightness, map(gCtrl[0], 0, 4095, 0, 255), 5);
  } else {
    brightness = 255;
  }

  // Maps mode to effects
  if (gCtrl[4] < 200) {
    effect = SOLID;

    // Map input to rgb values
    red = sigDiff(red, map(gCtrl[1], 0, 4094, 0, 255), 5);
    green = sigDiff(green, map(gCtrl[2], 0, 4094, 0, 255), 5);
    blue = sigDiff(blue, map(gCtrl[3], 0, 4094, 0, 255), 5);
    
  } else if (gCtrl[4] > 200 && gCtrl[4] < 1000) {
    effect = RAINBOW;
    
  } else if (gCtrl[4] > 1000) {
    effect = BPM;
    bpm = sigDiff(bpm, map(gCtrl[1], 0, 4094, 50, 160), 5);
  }
}

bool processMessage(char* message) {
//  Serial.println(message);

  if (message == "") {
    return false;
  }

  gCtrl[0] = GetCtrlPls(message, '|', 0).toInt(); // brightness
  gCtrl[1] = GetCtrlPls(message, '|', 1).toInt(); // red
  gCtrl[2] = GetCtrlPls(message, '|', 2).toInt(); // green
  gCtrl[3] = GetCtrlPls(message, '|', 3).toInt(); // blue
  gCtrl[4] = GetCtrlPls(message, '|', 4).toInt(); // mode

  return true;
}
