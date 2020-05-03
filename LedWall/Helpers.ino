byte sigDiff(byte originalVal, int newVal, int diff){
  if(abs(originalVal - newVal) > diff) {
    return newVal;
  } else {
    return originalVal;
  }
}

String GetCtrlPls(String StringToSplit, char SplitChar, int StringPartIndex)
{
  // TODO make this quicker !!! 
  
  int cnt = 0;
  int pos = 0;
  for (int il = 0; il < StringToSplit.length(); il++)
  {
    if (cnt == StringPartIndex)
    {
      int bpos = pos;
      while (pos < StringToSplit.length() && StringToSplit[pos] != SplitChar) pos++;
      return StringToSplit.substring(bpos, pos);
    }
    if (StringToSplit[il] == SplitChar)
    {
      pos = il + 1;
      cnt++;
    }
  }
  return "";
}

void showLeds() {
  delay(1);

  FastLED.setBrightness(brightness);  //EXECUTE EFFECT COLOR
  FastLED.show();

  FastLED.delay(1000/FRAMES_PER_SECOND); 
}
