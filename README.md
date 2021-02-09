# Arduino-Serial-to-Integer
Read decimal and hexadecimal string that convert it to long integer.

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
