
// IMPORTAMOS CONTROLADOR DE PANTALLA
#include <LiquidCrystal_I2C.h>

//VARIABLES PARA LOS BOTONES
int boton1 = 0;
int boton2 = 0;
int boton3 = 0;
int boton4 = 0;
int boton5 = 0;
int boton6 = 0;
int boton7 = 0;
int boton8 = 0;
int boton9 = 0;
int boton0 = 0;
int botonDerecha = 0;
int botonIzqda = 0;

//EL "CURSOR" QUE MARCA CUÁNTO DE LA STRING HEMOS ESCRITO
int cursor = 0;

//SUMA QUE SE USA PARA SABER CUANTOS BOTONES HEMOS PULSADO
int suma = 0;

//CONTADOR DE PITIDOS QUE QUEDAN PARA QUE EXPLOTE
int contadorBomba = 0;

//STRING A ESCRIBIR Y STRING ESCRITA POR EL USUARIO
char reto[16];
char respuesta[16];

//CARACTERES QUE ESCRIBE CADA BOTÓN 
char one = '1';
char two = '2';
char three = '3';
char four = '4';
char five = '5';
char six = '6';
char seven = '7';
char eight = '8';
char nine = '9';
char zero = '0';


//INDICA SI LA STRING QUE SE ESTÁ ESCRIBIENDO TIENE LA POSIBILIDAD DE LLEGAR AL FINAL COMO CORRECTA,
//PUES SE VA COMPROBANDO CADA CARACTER INDIVIDUALMENTE
bool ganable = true;

//NIVEL EN EL QUE SE ENCUENTRA EL USUARIO, SE USA PARA QUE EL SISTEMA MUESTRE QUÉ NIVEL SE VA A JUGAR,
//ADEMÁS DE QUE SIRVE COMO SEED DE CADA NIVEL Y COMO DIVISOR DEL TIEMPO ENTRE PITIDOS
int nivel = 1;

//UNIDADES USADAS PARA CALCULAR EL TIEMPO ENTRE PITIDOS, LA OTRA ESTÁ EN EL LOOP
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 1000;

//DECLARACIÓN DE LA PANTALLA
LiquidCrystal_I2C lcd(0x27,16,2);

//SE INICIALIZAN LA PANTALLA, LOS PINES DE LOS BOTONES Y EL BUZZER, ADEMÁS DE MOSTRAR LA PANTALLA DE
//INICIO DEL PRIMER NIVEL. TRAS ESTO SE GENERA EL PRIMER NIVEL Y SE INICIALIZA EL ARRAY DE RESPUESTA
void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    pinMode(12, OUTPUT); //este pin era el altavoz
    lcd.setCursor(0,1);
    lcd.print("nivel ");
    lcd.print(nivel);
    lcd.setCursor(0,0);
    generarReto(reto);
    mostrarArray(0,reto);
    for(int i=0; i<sizeof(reto);i++){
      Serial.print(reto[i]);
      Serial.print(", ");
    }
    Serial.println();
    vaciarArray(respuesta);
    mostrarArray(1, respuesta);
}

void loop() {

  //ULTIMA VARIABLE USADA PARA CALCULAR EL TIEMPO ENTRE PITIDOS
  unsigned long tiempoActual = millis();

  //CADENA DE IF/ELSE QUE SE EJECUTA CUANDO EL CURSOR ESTÁ AL FINAL DE LA CADENA, Y DECIDE SI
  //OBLIGAR AL USUARIO A VOLVER A EMPEZAR LA CADENA, SI LE DEJA PASAR AL SIGUIENTE NIVEL O SI
  //HA GANADO EL JUEGO
  if(cursor == 16){
    if(!ganable){
      vaciarArray(respuesta);
      mostrarArray(1, respuesta);
      cursor = 0;
      ganable = true;
    }else if(nivel == 5){
      lcd.clear();
      lcd.print("ENHORABUENA!!!!!");
      lcd.setCursor(0,1);
      lcd.print("BOMBA DESARMADA!");
      while(true){}
    }else{
      nivel++;
      contadorBomba = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ENHORABUENA!!!!!");
      lcd.setCursor(0,1);
      lcd.print("nivel ");
      lcd.print(nivel);
      delay(1000);
      generarReto(reto);
      mostrarArray(0,reto);
      ganable = false;
    }
  }

  //SE EJECUTA CADA INTERVALO DE TIEMPO QUE VARÍA DEPENDIENDO DEL NIVEL, Y CONSISTE EN HACER EL
  //PITIDO Y REINICIAR EL INTERVALO DE TIEMPO
  if(tiempoActual - tiempoAnterior >= intervalo/nivel){
    digitalWrite(3, HIGH);
    delay(100);
    digitalWrite(3, LOW);
    tiempoAnterior = tiempoActual;
    contadorBomba++;
  }

  //SECUENCIA DE DERROTA, SI EL SISTEMA HACE 50 PITIDOS LA BOMBA "EXPLOTA" Y PIERDES EL JUEGO,
  //QUEDÁNDOTE EN UN BUCLE INFINITO
  if(contadorBomba == 50){
    lcd.clear();
    lcd.print("BOOOOOM!!!!!!!!!");
    digitalWrite(3, HIGH);
    delay(10000);
    digitalWrite(3, LOW);
    while(true){}
  }

  //ESTA SECCIÓN SE EJECUTA CADA LOOP Y CONSISTE EN UNA LECTURA DE BOTONES Y UN RECUENTO DE
  //CUÁNTOS SE ESTÁN PULSANDO SIMULTÁNEAMENTE
  boton1 = digitalRead(2);
  boton2 = digitalRead(3);
  boton3 = digitalRead(4);
  boton4 = digitalRead(5);
  boton5 = digitalRead(6);
  boton6 = digitalRead(7);
  boton7 = digitalRead(8);
  boton8 = digitalRead(9);
  boton9 = digitalRead(10);
  boton0 = digitalRead(11);
  suma = boton1+boton2+boton3+boton4+boton5+boton6+boton7+boton8+boton9+boton0;

  //SI SE DETECTA QUE SOLO SE ESTÁ PULSANDO UN BOTÓN, SE LOGEA LA RESPUESTA Y SE COMPRUEBA SI
  //ES INCORRECTA, EN CUYO CASO EL CURSOR SE PONE A 15 Y, COMO AL FINAL DE ESTE IF SE AUMENTA
  //EL CURSOR, EL SIGUIENTE LOOP INICIARÁ A 16 Y ENTRARÁ A LA SECUENCIA DE REINICIO DE CADENA
  //
  //TAMBIÉN, ESTE LOOP NO DEJA SEGUIR EL PROGRAMA HASTA QUE SE SUELTAN TODOS LOS BOTONES, CON
  //LA INTENCIÓN DE PREVENIR PULSACIONES INDESEADAS
  if(suma == 1){
    respuesta[cursor] = iconoBoton(boton1, boton2, boton3, boton4, boton5, boton6, boton7, boton8, boton9, boton0);
    mostrarArray(1, respuesta);
    compararRespuesta();
    while(suma != 0){
      boton1 = digitalRead(2);
      boton2 = digitalRead(3);
      boton3 = digitalRead(4);
      boton4 = digitalRead(5);
      boton5 = digitalRead(6);
      boton6 = digitalRead(7);
      boton7 = digitalRead(8);
      boton8 = digitalRead(9);
      boton9 = digitalRead(10);
      boton0 = digitalRead(11);
      suma = boton1+boton2+boton3+boton4+boton5+boton6+boton7+boton8+boton9+boton0;
    }
    cursor++;
    delay(20);
  }
}

//MUESTRA LA CADENA QUE SEA EN LA FILA QUE SEA
void mostrarArray(int fila, char array[16]){
  lcd.setCursor(0,fila);
  for(int i = 0; i < 16; i++){
    lcd.print(array[i]);
  }
}

//DEVUELVE EL CARACTER QUE HAYAMOS ASIGNADO A CADA BOTÓN EN LA DECLARACIÓN DE VARIABLES
char iconoBoton(int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9, int b0){
  if(b1 == 1){
    return one;
  }else if(b2 == 1){
    return two;
  }else if(b3 == 1){
    return three;
  }else if(b4 == 1){
    return four;
  }else if(b5 == 1){
    return five;
  }else if(b6 == 1){
    return six;
  }else if(b7 == 1){
    return seven;
  }else if(b8 == 1){
    return eight;
  }else if(b9 == 1){
    return nine;
  }else if(b0 == 1){
    return zero;
  }
  
}

//CONVIERTE TODOS LOS CARACTERES DEL ARRAY EN ' '
void vaciarArray(char array[16]){
  for(int i = 0; i < 16; i++){
    array[i] = ' ';
  }
}

//GENERA UNA CADENA A PARTIR DEL NÚMERO DEL NIVEL MAS UNA SEÑAL SUCIA, PARA ASEGURARNOS
//DE QUE SIEMPRE SON TODAS DISTINTAS
void generarReto(char array[16]){
  int num = 0;
  randomSeed(analogRead(A0) + nivel);
  for(int i = 0; i < 16; i++){
    num = random(9);
    switch(num){
      case 1: array[i]=one;
        break;
      case 2:   array[i]=two;
        break;
      case 3: array[i]=three;
        break;
      case 4: array[i]=four;
        break;
      case 5: array[i]=five;
        break;
      case 6: array[i]=six;
        break;
      case 7: array[i]=seven;
        break;
      case 8: array[i]=eight;
        break;
      case 9: array[i]=nine;
        break;
      case 0: array[i]=zero;
        break;
    }
  }
}

//COMPARA EL CARACTER QUE SE ACABA DE ESCRIBIR CON EL QUE SE SUPONE QUE DEBERÍA HABER
//ESCRITO, Y SI NO ES CORRECTO ASIGNA EL CURSOR A 15 Y PONE LA CONDICIÓN DE VICTORIA
//A FALSO PARA QUE EN EL SIGUIENTE LOOP SE INICIE LA SECUENCIA DE REINICIO DE STRING
void compararRespuesta(){
  if(reto[cursor] != respuesta[cursor]){
    cursor = 15;
    ganable = false;
  }
}

