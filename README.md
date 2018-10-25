# Instituto tecnológico de león

Sistemas programables

Practica 3

Sistema Sistema Mimetizador Visualizador de Mensajes

# Realizado por:

Christian Moreno Ramirez

Juan Pablo Barroso Hernández


# Descripcion del Proyecto

un sistema para el despliegue de mensajes en una pantalla LCD, el objetivo es que al
llegar un individuo pueda ver en un pequeno tablero electronico una serie de mensajes o notas almacenados.

Cada mensaje tiene las siguientes caracteristicas:
Tienes que mostrar un mensaje, que se entienda, con sólo 140 caracteres de espacio. 
Debe de mostrat fecha y hora en la que fue emitido el mensaje.
Ademas debe de mostrar Un mensaje del estado del tiempo (Temperatura, Humedad, luminosidad)

El sistema debe contener:
Un interfaz de hardware para navegar entre los mensajes.
Una interfaz de software para enviar los mensajes desde la computadora via serial.
La interfaz de software debe permitir agreagr mensajes y/o borrarlos.

# Herramientas de desarrollo

- [Arduino IDE](https://www.arduino.cc/) 

- [App Inventor](http://appinventor.mit.edu/explore/)

- [Fritzing](http://fritzing.org/home/)


# Materiales 
- Protoboard

- Arduino mega 2560

- Cable USB A a B (cable de arduino)

- Pantalla LCD 16x2

- Teclado matricial 4x4

- RTC DS3231

- Sensor de humedad DTH11

- Fotoresistencia

- Sensor LM35

- Modulo Bluetooth HC-05 

- Cables conectores(macho/macho, macho/hembra)

# Librerias
- LiquidCrystal

- DHT11

- Keypad-master

- RTC_DS3231-master

# Manejo del sistema

![interfaz 2](https://user-images.githubusercontent.com/44387203/47502572-c8df3780-d82d-11e8-8496-956e33b5c0db.png)

La conexion con Bluetooth por primera vez debe de ser fuera de la aplicación y dentro de la aplicación. Las siguientes veces te puedes conectar dentro de la aplicación.

En la interfaz de software tu puedes presionar un boton del 1 al 5 y se mostrará el mensaje correspondiente en la pantalla LCD.
Además puedes escribir un mensaje que tu quieras siempre y cuando sea menor o igual a 140 caracteres y al presionar el botón de enviar mensaje se mostrará en la pantalla LCD. Si el mensaje es mayor de 16 caracteres el mensaje se desplazará de derecha a izquierda para que se visualice el mensaje completo.

# Resultados

![20181025_072214](https://user-images.githubusercontent.com/43175659/47503113-f24c9300-d82e-11e8-9004-4a6589a9c3dd.jpg)
> Temperatura y Humedad

![20181025_072219](https://user-images.githubusercontent.com/43175659/47503134-02647280-d82f-11e8-911a-3e6c06e0ee1d.jpg)
> Luminosidad

![20181025_072645](https://user-images.githubusercontent.com/43175659/47503155-0db79e00-d82f-11e8-8e58-3f2d63d05e74.jpg)
> Fecha y Hora
