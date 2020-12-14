#include <LiquidCrystal.h>

const int motor = 6;  // Usamos salida PWM en pin D6 
int adc_nuevo = 0 ;     // Usamos entrada ADC en pin A0
int adc_viejo = 0 ;     // Guardamos la última lectura del ADC
int giroder = 10 ; // Pulsador derecho
int giroizq = 7; // Pulsador izquierdo 
int IN1 = 9; // Salida del puente H
int IN2 = 8; // Salida del puente H
// PONEMOS ESTADOS PARA LAS CONDICIONES
int estado = 0;
int estado1 = 0;
int estado0=0;
int estado01=0;
LiquidCrystal lcd (5,4,3,14,15,16);
void setup() {
   
  // Inicializamos el puerto serie
  Serial.begin(9600);

  // Configuramos pwm (MOTOR)como salida
  // CONFIGURAMOS PULSADORES EN ARDUINO 
  pinMode(motor, OUTPUT) ;
  pinMode (IN1, OUTPUT);  //SALE A PUENTE H  
  pinMode (IN2, OUTPUT);// SALE A PUENTE H
  pinMode (giroder,INPUT);// PULSADOR IZQ CONFIGURAMOS COMO ENTRADA
  pinMode (giroizq, INPUT); // PULSADOR DER CONFIGURAMOS COMO ENTRADA

 // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  lcd.begin(16, 2);
  lcd.print(" ");
 
}

void loop() {
 
 
  {
  // Leemos el valor del ADC en el pin A0 
  adc_nuevo  = analogRead(A0) ;  

  // Ajustamos el valor leido en A0 para adaptarlo al rengo
  // del PWM. Se adapta la escala de 0-1023 a 0-255  
  adc_nuevo = (adc_nuevo/4);  

  if (adc_nuevo != adc_viejo) {
    // Actualiza la lectura del ADC
    adc_viejo = adc_nuevo;

    // Envia el valor actual al puerto serie
    Serial.println(adc_nuevo);
    //IMPERIMR LCD
    lcd.setCursor(1,0);
    lcd.print("PWM=");
    lcd.print(adc_nuevo);

    // Envia el valor adaptado al PWM
    analogWrite(motor, adc_nuevo); 
  }
  
  }
// CONDICION PARA apagaR el motor
//LEEMOS PULSADORES Y ASIGNAMOS A LOS ESTADOS  PARA COMPARAR LA COMDICION (SI ESTA 1 O 0)
estado0 = digitalRead (giroder) ;
estado01 = digitalRead (giroizq);

// SI LOS PULSADORES SON IGUALES SE APAGA
if(estado0 == estado01 ){
  
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  // IMPRIMIR LCD
    lcd.setCursor(1,1);
    lcd.print("APAGADO."); 
  }
  
// Envia el giro hacia la derecha

estado = digitalRead (giroder);
if (estado == LOW)
{
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  //IMPRIMIR LCD
    lcd.setCursor(1,1);
    lcd.print("GIRO DER ");
    
}

//Envia el giro hacia a la izquierda
estado1 = digitalRead (giroizq);
if (estado1 == LOW)
{
  digitalWrite (IN2, HIGH);
  digitalWrite (IN1, LOW);
  //IMPRIMIR LCD
     lcd.setCursor(1,1);
     lcd.print("GIRO IZQ");
    
} 
}
