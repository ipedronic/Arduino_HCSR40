//www.elbrujitocanaio.es 
//Todo el código esta bajo licencia de la Creative Commons.
#define Trig  2                //Definimos como constante
#define Echo 4                 //Definimos como constante
#define PinLed 3               //Define el pin del Led
#define PinSonoro 5            //Define el altavoz
#define AlarmaLed 20           //Define la alarma de luz a 20 centimetros
#define AlarmaSonora 10        //Define sonido a 10 centimetros
#define TonoSonoro 68           //Valores de 31Hz a 65535 Hz 
#define Medida 58              //58 nos da la distancia en centimetro y 148 en pulgadas
 void setup() {
  Serial.begin(9600);          //Define salida serie
  pinMode(Trig,OUTPUT);        //Pin como salida
  pinMode(Echo,INPUT);         //Pin como entrada
  pinMode(PinLed,OUTPUT);      //Pin alarma luminosa.
  pinMode(PinSonoro,OUTPUT);   //Pin altavoz
 
}
//////////////////////////////////////////////
//////////////Funcion que calcula la distancia
//////////////////////////////////////////////
int Calculo_Sensor_Sonido (int trig,int echo){
   /////////////////////////////Mandar la senal
 digitalWrite(trig,LOW);      //Pone bajo el pin
 delayMicroseconds(2);        //Pausa de tiempo
 digitalWrite(trig,HIGH);     //Pone alto el pin
 delayMicroseconds(10);       //Pausa de tiempo
 digitalWrite(trig,LOW);      //Pone bajo el pin
 ///////////////////////////////Resibe la senal
 int duracion = pulseIn(echo,HIGH);//Guarda la senal
 int Retorna_distancia = (duracion/Medida);//Convertimos en centimetros
 if (Retorna_distancia <= 2) Retorna_distancia =2;
 if (Retorna_distancia >= 400) Retorna_distancia =400;
 return Retorna_distancia;
  }
/////////////////////////////////////////////////
//////////////////////////Funcion alarma luminosa
/////////////////////////////////////////////////
void alarma_Luminosa (int alarmaLed,int distanciaLed){
 
  if (distanciaLed <= alarmaLed){
    delayMicroseconds(50);
  digitalWrite(PinLed,HIGH);
  }else{
    digitalWrite(PinLed,LOW);
    }
  }
 /////////////////////////////////////////////////
//////////////////////////Funcion alarma sonora
/////////////////////////////////////////////////
void alarma_Sonora (int alarmaSonora,int dist_sonora ){
  if (dist_sonora <= alarmaSonora){
    delayMicroseconds(50);
    tone(PinSonoro,TonoSonoro);         //TonoSonoro Valores de 31Hz a 65535 Hz
    }else{
      noTone(PinSonoro);
      }
  }
 
 //////////////////////////////////////////////////// 
/////////////////////Funcion que escribe en pantalla  
////////////////////////////////////////////////////
void pantalla (int dist){
  if (Medida == 58){
    Serial.print("Distancia en centimetros ");
    }else{
      Serial.print("Distancia en pulgadas ");
      }
              //Salida por puerto serie
  Serial.println(dist);                  //Dato a mostrar
  delay(100);                            //Un segundo por favor
  }
/////////////////////////////////////////////////////  
void loop() {
 int distancia =Calculo_Sensor_Sonido (Trig,Echo);
 //////////////////////////////////////////Alarmas
  alarma_Luminosa (AlarmaLed,distancia); //Llamada de funcion alarma luminosa
  alarma_Sonora (AlarmaSonora,distancia);//Llamada de funcion alarma sonora
 //////////////////////////////////////////Pantalla 
  pantalla (distancia);                  //Lamada de funcion Imprimo por serial
 
 

}
