#define uart Serial

/* Resultados:
 *  Testes: String normal(objeto), String.c_str() (String convertida para char array), Sequência de if com char, Switch com char. 
 * 
Arduino Mega 2560:String normal é muuito mais lenta, enquanto os demais levam 0ms
ESP8266 ESP-01: Todos levam 0ms

Resultados
Vars:
String txt ="kaka";
char c = 'k';
char cString[]="kaka";
-----------------------------
C String took 7868uS
true
Regular String (with ==)took 13652uS
true
Converted (with .c_str()) String took 7520uS
true
char if took 4uS
false
C string using if chain took 1900uS
true
char switch took 472uS
true
-------- End ----------
Obs.: Comparação de C string usou strcpm. 
      memcpm é mais lento que strcmp, mesmo com menos caracteres
      

*/
long endTime,startTime;

void logTime(){
  if(startTime==-1){
    startTime=micros();
  }
  else if(endTime==-1){
    endTime=micros();
  }
}

void printTime(){
long interval;
interval=endTime-startTime;
startTime=-1;
endTime=-1;
String txt = " took ";
txt+=interval;
 txt+="uS";
  uart.println(txt);
}


void setup() {
  // put your setup code here, to run once:
uart.begin(115200);
}
void loop() {
  //delay(5000);


 stringPerf();

 delay(5000);
 
        
}

void stringPerf(){
 int loopNum = 1000; 
  
  bool test;
  String txt ="kaka";

  char c;
  c='l';
  char cString[]="kaka";


// C string test ---------------------------

logTime();
test=false;
for(int i;i<loopNum;i++){
  if(strcmp(cString,"wifi")==0){
test=true;
}

else if(strcmp("lala",cString)==0){
test=true;
}
else if(strcmp("kaka",cString)==0){
test=true;
}
}
logTime();

  uart.print("C String");
  printTime();
if(test)
  uart.println("true");
  else   uart.println("false");
  


// String object test -------------------------------
  
logTime();
test=false;
    for(int i;i<loopNum;i++){
  if(txt =="wifi"){
test=true;
  }
else if(txt=="lala"){
test=true;
}

else if(txt=="kaka"){
test=true;
}
  
  }
logTime();
 
  uart.print("Regular String");
  printTime();
if(test)
  uart.println("true");
  else   uart.println("false");




//String obj converted to C string test -------------------------------
logTime();
test=false;

    for(int i;i<loopNum;i++){
  if(strcmp(txt.c_str(),"wifi")==0){
test=true;
  }
else if(strcmp(txt.c_str(),"lala")==0){
test=true;

}

else if(strcmp(txt.c_str(),"kaka")==0){
test=true;

}
  
  }
logTime();
  
  uart.print("Converted String");
  printTime();
if(test)
  uart.println("true");
  else   uart.println("false");




// Char if sequence test -------------------------
logTime();
test=false;
   for(int i;i<loopNum;i++){
  if(c == 'w'){
test=false;
  }
  
  else if (c=='k'){
    test=false;
  }

  else if(c=='l'){
test=true;
  }

   }
   
   logTime();
  uart.print("char if");
  printTime();
if(test)
  uart.println("true");
  else   uart.println("false");


//Converted C string using char if chain test

logTime();
test=false;
char tmps[6];
txt.toCharArray(tmps,6);
   for(int i;i<loopNum;i++){
  if(tmps[0] == 'w'){
  test=false;

  }

  else if(tmps[0] == 'm'){
  test=false;

  }


  else if(tmps[0]=='l'){
test=false;

  }

  else if(tmps[0]=='k'){
if(tmps[1]=='a'){
  
   if(tmps[2]=='s'){
   if(tmps[3]=='a'){ //kasa
      test=false;
    }
    else if(tmps[3]=='o'){ //kaso
      test=false;
    }
  }
  else if(tmps[2]=='k'){
    if(tmps[3]=='o'){ //kako
      test=true;
    }
    else if(tmps[3]=='a'){ //kaka
      test=true;
    }
  }
}

}
   }
logTime();

  uart.print("char if chain for C string");
  printTime();
if(test)
  uart.println("true");
  else   uart.println("false");




// Char switch test ------------------------------
logTime();
test=false;

 for(int i;i<loopNum;i++){
switch(c){
  case 'w':
test=true;
   break;
  
  case 'l':
test=true;
  break;
  case 'k':
test=true;
  break;
   }
   }
logTime();
 
  uart.print("char switch");
  printTime();
if(test)
  uart.println("true");
  else   uart.println("false");

uart.println("-------- End ----------");

  
}
