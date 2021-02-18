/*
   [Brief]
   Serial string to decimal integer.
   This function only accepts DEC or HEX strings, otherwise the function will return 0.
   If separated by semicolons, this function also accepts multiple inputs.
   If the prefix is 0x, it will be parsed by the hexadecimal method, otherwise it will be the decimal method.
   
   [Example]
   input=0xA;
   output=10

   input=12;43;100;
   output=
   12
   43
   100

   [Wrong format example]
   input=0xSA; //Because the hexadecimal without 'S'
   output=0 
   input=F1923A; //Because the decimal method is used to parse
   output=0 
*/


const int BAUDRATE = 9600;
const char terminator = ';';
void setup() {
  Serial.begin(BAUDRATE);

}

void loop() {
  if (Serial.available() > 0) {
    Serial.println(func());
  }
}

long func() {

  String data = Serial.readStringUntil(terminator);
  bool flag = true;
  bool isHex = false;
  bool isNeg = false;
  // init
  data.toUpperCase();
  if (data[0] == '0' && data[1] == 'X') {
    data = data.substring(2);
    isHex = true;
  }

  //Check format
  if (isHex) {
    for (int i = 0; i < data.length(); i++) {
      if (!((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'A' && data[i] <= 'F' )) ) {
        flag = false;
        break;
      }
    }
  }
  else {
    int start = 0;
    if (data[0] == '-') {
      isNeg = true;
      data = data.substring(1);
    }

    for (int i = 0; i < data.length(); i++) {
      if (!(data[i] >= '0' && data[i] <= '9')) {
        flag = false;
        break;
      }
    }
  }
  //    Serial.println("Flag:" + (String)flag + " isHex:" + (String)isHex + " Is Neg:" + (String)isNeg);
  //Data process
  if (flag) {
    long result = 0;
    if (isHex) {
      //Hex process
      for (int i = 0; i < data.length(); i++) {
        if (data[i] >= '0' && data[i] <= '9')
          result += (data[i] - '0') * power(16, data.length() - 1 - i);
        else
          result += (data[i] - '7') * power(16, data.length() - 1 - i);
      }
      return result;
    }
    else {
      //Dec process
      for (int i = 0; i < data.length(); i++) {
        result += (data[i] - '0') * power(10, data.length() - 1 - i);
      }
      if (isNeg)
        return result * (-1);
      else
        return result;
    }
  }
  else {
    return 0;
  }
}

long power(int x, int y) {
  // x^y
  long result = 1;
  for (int i = 0; i < y; i++) {
    result *= x;
  }
  return result;
}
