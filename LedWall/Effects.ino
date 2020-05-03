void solidEffect() {
  fill_solid(leds, NUM_LEDS, CRGB(red, green, blue));
      
  Serial.println("Filled solid");
  Serial.print("brightness: ");
  Serial.println(brightness);
  Serial.print(" - ");
  Serial.print(red);
  Serial.print(" - ");
  Serial.print(green);
  Serial.print(" - ");
  Serial.println(blue);
}

void rainbowEffect() {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
  
  Serial.println("Rainbowwwww");
}

void bpmEffect() {
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
