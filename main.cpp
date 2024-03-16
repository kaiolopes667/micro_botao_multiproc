#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <StreamString.h>
#include <UniversalTelegramBot.h>

#include <WiFiClientSecure.h>
IPAddress dns(8, 8, 8, 8); // Definir o servidor DNS para o Google

#define pino_botao 4
#define LED_R 25
#define LED_G 26
#define LED_B 27

//put function declarations here:
void botao();
void ligar_led(int r, int g, int b);
void telegram();
void task_botao(void *paramenter);

int conver_to_esp(int value);

const char *ssid = "POCO X3 GT"
const char *password = "pocox3gt";
const char *token = "7878952266:AAEMQl9";

WiFiClientSecure client;
UniversalTelegramBot bot(token, client)



void setup() {
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);
	pinMode(pino_botao, INPUT_PULLDOWN);
	Serial.begin(115200);
	
	xTaskCreate(task_botao, "Botao", 10000, NULL, 1, NULL);
	
	//conectar a rede wifi
	WiFi.begin(ssid, password);
	while(WiFi.status()!= WL_CONNECTED){
		delay(1000);
		Serial.println("Conectando ao Wifi...");
	}
	Serial.println("Conectado ao Wifi");
}

void loop() {}

// put function definitions here:

void task_botao(void *paramenter){
	while(true){
		botao();
		delay(100);
	}
}

void ligar_led(int r, int g, int b){
	digitalWrite(LED_R, conver_to_esp(r)};
	digitalWrite(LED_G, conver_to_esp(g)};
	digitalWrite(LED_B, conver_to_esp(b)};
}

int conver_to_esp(int value){

	return(int)((value*1023)/255)
}

void telegram() {
	String chat_id = "5831795865";
	String text = "Botao pressionado no ESP32";
	
	if (bot.sendMessage(chat_id, text, "")) {
		Serial.println("Mensagem enviada com sucesso");
	}	else {
		Serial.println("Falha ao enviar mensagem");
	}

}
