/*code original par lewdalewda en libre accès donc faites en ce que vous voulez 
checkez mon insta aussi @lewda3dprints
*/




//on ajoute les librairies qui rendent le code des modules plus simple
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <avr/pgmspace.h>

//on donne a l'arduino les dimensions de l'OLED en pixels
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//on crée un objet écran OLED et on lui attache le dimensions et le pin de réinisialiation (ici -1 car il correspond a celui de la carte)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//on crée deux objets de type servo
Servo monservo;
Servo monservo2;

//on crée des variables qui vont contenir les infos suivantes : le pin digital des boutons et l'angle assigné au servos 
int switch1pin = 4;
int switch2pin = 2;
int angle1 = 0;
int angle2 = 0;

//on crée des "strings" de textes stockées dans des variables char en utilisant PROGMEM pour dire a l'arduino de stocker ces informations dans la mémoire programme et non la mémoire dynamique
const char string_0[] PROGMEM = "Charged and ready."; 
const char string_1[] PROGMEM = "Try as you might,you can't Kilowatt...son"; 
const char string_2[] PROGMEM = "The best offense is a strong defense.";
const char string_3[] PROGMEM = "We're just on different sides of the fence. C’est la vie.";
const char string_4[] PROGMEM = "Lights out.";
const char string_5[] PROGMEM = "Adding a bit of… Je Ne Sais Quoi.";
const char string_6[] PROGMEM = "That's a nice fence.";
const char string_7[] PROGMEM = "That's a nice fence.";
const char string_8[] PROGMEM = "That's a happy fence!";
const char string_9[] PROGMEM = "That's a grumpy fence.";
const char string_10[] PROGMEM = "That's an angry fence."; 
const char string_11[] PROGMEM = "That's a funny fence!";
const char string_12[] PROGMEM = "That's a sad fence.";
const char string_13[] PROGMEM = "That's a silly fence!";
const char string_14[] PROGMEM = "That's a scary fence...";
const char string_15[] PROGMEM = "Happy to help.";
const char string_16[] PROGMEM = "All it takes is a single spark.";
const char string_17[] PROGMEM = "Let's break some circuits.";
const char string_18[] PROGMEM = "Let's get to work.";
const char string_19[] PROGMEM = "Time to cut the power.";
const char string_20[] PROGMEM = "note- leave the message in hack";
const char string_21[] PROGMEM = "You're playing in my backyard now.";
const char string_22[] PROGMEM = "oui oui baguette !";
const char string_23[] PROGMEM = "i'm an electrical engineering device, make sense.";
const char string_24[] PROGMEM = "Le Fishe";
const char string_25[] PROGMEM = "shout-out to my boy Zapoyo !!!";
const char string_26[] PROGMEM = "HADUKEN !!!";
const char string_27[] PROGMEM = "SHORYUKEN";
const char string_28[] PROGMEM = "thanks Zack Freedman for the inspiration !";
const char string_29[] PROGMEM = "there's a sussy in my bussy";
const char string_30[] PROGMEM = "i want to die... -lewdalewda";
const char string_31[] PROGMEM = "i don't know how to code";
const char string_32[] PROGMEM = "UWU punish me daddy causthicc !";
const char string_33[] PROGMEM = "thunder kitty best skin u-u";
const char string_34[] PROGMEM = "tf is a Array !!?";
const char string_35[] PROGMEM = "made be @lewda3dprints on instagram";
const char string_36[] PROGMEM = "roblox parkour GOTY";
const char string_37[] PROGMEM = "Burn my BREAAAAAAAAAAD";
const char string_38[] PROGMEM = "how are you seeing this ?";
const char string_39[] PROGMEM = "don't forget that if you want to try smthg GO FOR IT !!!";

//on crée un tableau dans la mémoire programme qui contiens toutes nos strings
const char *const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10, string_11, string_12, string_13, string_14, string_15, string_16, string_17, string_18, string_19, string_20, string_21, string_22, string_23, string_24, string_25, string_26, string_27, string_28, string_29, string_30, string_31, string_32, string_33, string_34, string_35, string_36, string_37, string_38, string_39};

//on donne le nombre maximum de caractères (la longeur de la plus grande string, ici 59 caractères)
char buffer[59];


void setup() {
  
  //on lance le moniteur en série avec 115200 de baudrate
  Serial.begin(115200);
  
  //on vérifie que l'oled est a la bonne adresse IIC (ici 0x3C mais variant en fonction des dimensions de l'écran)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  //on attends 2000 milisecondes ou 2 secondes
  delay(2000);
  
  //on efface tout sur l'écran
  display.clearDisplay();
  
  //on met en place les paramètres de texte sur l'OLED : taille, couleur, position 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  
  //on affiche le texte (ici Hello world)
  display.println("Hello, world!");
  display.display(); //cette fonction doit toujours etre placée après une commande "print" ou "draw"

  //on dit a l'arduino de s'ocuper des résistance pour les boutons sans en mettre dans notre circuit
  pinMode(switch1pin,INPUT_PULLUP);
  pinMode(switch2pin,INPUT_PULLUP);

  //on attache les objets servos crées auparavant a leur pins sur la carte 
  monservo.attach(3);
  monservo2.attach(5);

  //on demande a l'arduino de baser son calcul "random" sur la valeur qu'il lit dans le pin analoge 0 (qui n'est pas utilisé)
  randomSeed(analogRead(0));
}


void loop() {

  //on efface tout sur l'écran
  display.clearDisplay();

  //on met en place les paramètres de texte sur l'OLED : taille, couleur,
  display.setTextSize(1);
  display.setTextColor(WHITE);

   //si le boutton sur pin 4 est appuyé... 
   if (digitalRead(4) == LOW)
  {
   
   //on tire une sting au hasard du tableau créé auparavant
   strcpy_P(buffer, (char *)pgm_read_word(&(string_table[random(39)])));

   //on donne les valeurs pour la variable angle1 et angle2
   (angle1 = 0);
   (angle2 = 0);
   
   //on dit a nos servos d'aller a la valeur d'angle1 et d'angle 2
   monservo.write(angle1);
   monservo2.write(angle2);
   
   //on efface l'écran et y écrit "closed"
   display.clearDisplay();
   display.setCursor(0,0);
   display.println("left button pressed");
   display.display(); 
   
   //on attend 3 secondes
   delay(3000);
   
   //on efface l'écran et y écrit la string choisie aléatoirement
   display.clearDisplay();
   display.setCursor(0,0);
   display.println(buffer);
   display.display();
  }

  //si le boutton sur pin 2 est appuyé
  if (digitalRead(2) == LOW)
  {
    //on tire une sting au hasard du tableau créé auparavant
    strcpy_P(buffer, (char *)pgm_read_word(&(string_table[random(39)])));

    //on donne les valeurs pour la variable angle1 et angle2
    (angle1 = 90);
    (angle2 = 90);
    
    //on dit a nos servos d'aller a la valeur d'angle1 et d'angle 2
    monservo.write(angle1);
    monservo2.write(angle2);
    
    //on efface l'écran et y écrit "opened"
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("right button pressed");
    display.display(); 

    //on attend 3 secondes
    delay(3000);

    //on efface l'écran et y écrit la string choisie aléatoirement
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(buffer);
    display.display(); 
  }
}
