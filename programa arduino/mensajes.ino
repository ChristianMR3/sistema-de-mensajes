#include <Keypad.h> // libreria del teclado matricial
#include <DHT11.h> //importamos la libreia del del sensor de temperatura y humedad
#include <LiquidCrystal.h> // libreria del lcd
#include <Wire.h>
#include <RTClib.h> //libreria del rtc 
#define ldr 5  //Pin analógico donde colocamos el LDR

/////teclado
const byte  filas = 4;
const byte  columnas = 4;

byte pinfilas[filas]  = {28, 30, 32, 34};
byte pincolumnas[columnas] = {36, 38, 40, 42};

char teclas[filas][columnas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad teclado = Keypad(makeKeymap(teclas), pinfilas, pincolumnas, filas, columnas); /*objeto de tipo Keypad llamado teclado se inicializa
  con el mapeo de los caracteres con los pines de las filas, columnas seguido del numero de filas y columnas
  termina el codigo necesario
*/
char tecla;
int numero;
///fin de teclado

int LDR_val = 0; //Valor bruto obtenido por el LDR [0,1023]
int LDR_escalado = 0; //Variable en la que almacenaremos el escalado, nos interesa un valor [0,100]
int LDR_invertido = 0;

LiquidCrystal lcd(3, 2, 4, 5, 6, 7); // pines del lcd 
float temp, hum;   // variables de tipo flotante para la temperatura y la humadad
int sensor = 22;   // declaramos el pin del sensor de temperatura y humedad
DHT11 dht11(sensor); // declaramos la variable dht11 de tipo DHT11 y le asignamos el pin 
RTC_DS1307 RTC;   //declaramos el tipo de RTC en este caso fue el RTC_DS1307 de tipo RTC

String readString; // leera el estring que se mande por bluetooth 
String m;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Comprobamos si tenemos el RTC conectado
  if (! RTC.begin()) {
    Serial.println("No hay un módulo RTC");
    while (1);
  }
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // put your main code here, to run repeatedly:

  DateTime now = RTC.now(); // obtenemos el tiempo actual en el momento que enviamos el mensaje
  dht11.read(hum, temp);  // leemos los datos del sensor 
  LDR_val = analogRead(ldr); //Escribimos el valor leído por el LDR en la variable "LDR_val" para procesarlo a continuación
  LDR_escalado = map(LDR_val, 0, 1023, 0, 100); //A través de la función "map" convertimos el valor de LDR_val [0,1023] a un valor porcentual [0,100]
  LDR_invertido = (100 - LDR_escalado); //Restamos a [100] el valor obtenido por el escalado ya que nuestra resistencia es Pull-down y lo que nos interesa es medir la cantidad de luz, no de oscuridad.

  tecla = teclado.getKey();


  while (Serial.available()) {
    delay(50);
    char c = Serial.read();
    readString += c;
  }

  if (readString.length() > 0 || tecla != NO_KEY) { 
    Serial.println(readString);
    int tam = readString.length();
    
    if (readString == "Button1" || tecla == '1') { // si el boton presionado desde la aplicaion es el boton 1 o se presiona la tecla 1 del teclado matricial se imprimira el mensaje
      m = "Buen dia!!!";
      mostrarMensaje(m);
      mostrarRTCLCD(); //Se manda a llamar la funcion "mostrarRTCLCD" y despues se espera un tienpo de 1seg
    }

    if (readString == "Button2" || tecla == '2') {
      m = "Bienvenido!!!";
      mostrarMensaje(m);
      mostrarRTCLCD(); //Se manda a llamar la funcion "mostrarRTCLCD" y despues se espera un tienpo de 1seg
    }

    if (readString == "Button3" || tecla == '3') {
      m = "Que tengas un buen dia!!!";
      mostrarMensaje(m);
      //      lcd.scrollDisplayLeft(m);
      mostrarRTCLCD(); //Se manda a llamar la funcion "mostrarRTCLCD" y despues se espera un tienpo de 1seg
    }

    if (readString == "Button4" || tecla == '4') {
      m = "Saludos!!!";
      mostrarMensaje(m);
      mostrarRTCLCD(); //Se manda a llamar la funcion "mostrarRTCLCD" y despues se espera un tienpo de 1seg
    }
    if (readString == "Button5" || tecla == '5') {
      m = "Hola!!!";
      mostrarMensaje(m);
      mostrarRTCLCD(); //Se manda a llamar la funcion "mostrarRTCLCD" y despues se espera un tienpo de 1seg
    }

    

    if (readString != "Button1" && readString != "Button2" && readString != "Button3" && readString != "Button4" && readString != "Button5") {
      mostrarMensaje(readString);
      mostrarRTCLCD(); //Se manda a llamar la funcion "mostrarRTCLCD" y despues se espera un tienpo de 1seg
    }

    if (tam > 140){   // solo se permiten mensajes menores a 140 caracteres
    lcd.setCursor(0, 0);
    lcd.print("supero los 140");
    lcd.setCursor(0, 1);
    lcd.print("Caracteres");
    delay(5000);
    lcd.clear();
    }
   
  }
     readString = "";
}

void mostrarRTCLCD() //Funcion que lee los datos de modulo RTC y despues los imprime en el display
{
  DateTime now = RTC.now(); //obtiene datos del modulo RTC
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fecha "); // se imprime la fecha
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("Hora ");  // se imprime la hora
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  delay(5000);
  lcd.clear();
}

void mostrarMensaje(String mensaje) {
  int tam_texto = mensaje.length();
if(tam_texto > 16){         // si el mensaje tiene mas de 16 caracteres se desplaza hacia la izquierda 
  for (int i = 1 ; i <= tam_texto ; i++)
  {
    String texto = mensaje.substring(i - 1); 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(texto);
    delay(1000);

  }
}else {
  lcd.print(mensaje); // si el mensaje tiene menos de 16 caracteres se queda estatico 
  delay(5000);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");  // se imprime la temperatura
  lcd.print(temp);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");  // se imprime la humedad
  lcd.print(hum);
  lcd.print("%");
  delay(5000);
  lcd.clear();

  lcd.print("Idc. Luminosidad"); //Escribimos la primera línea, sin más :D
  lcd.setCursor(0, 1); //Nos llevamos el cursor al primer caracter de la segunda línea
  lcd.print(LDR_invertido); //Hacemos que nos muestre el valor procentual que hemos procesado previamente
  lcd.print(" %"); //Colocamos el símbolo "%" con el fin de verlo en el LCD
  delay(5000); //Delay para no saturar el sistema y LISTO :DDD
  lcd.clear();
}
