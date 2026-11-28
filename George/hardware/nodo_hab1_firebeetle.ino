//#######################################################################################################################################
// Este codigo esta hecho para conectar a la habitacion 1 del proyecto pero se puede  adaptar a cualquiera de los ambientes
// modificando los topicos programados. Tambien es posible activar/ desactivar los sensores y los actuadores en la seccion interruptores.
//########################################################################################################################################
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// =========================================================================
// 1. INTERRUPTORES MÓDULOS (1 = ACTIVO | 0 = DESACTIVADO)
// =========================================================================
#define USAR_SERVO        1   // Actuador Ventana (SG90 en D2 / GPIO 3)
#define USAR_HALL         0   // Sensor Efecto Hall (Confirmación cierre en D3 / GPIO 38)
#define USAR_LUZ          1   // Actuador Luz (LED en D5 / GPIO 7)
#define USAR_CALEFACCION  1   // Actuador Calefacción (LED en D6 / GPIO 18)

#if USAR_SERVO
  #include <ESP32Servo.h>
#endif

// =========================================================================
// 2. CONFIGURACIÓN WIFI Y MQTT
// =========================================================================
const char* ssid        = "Nombre de la red";
const char* password    = "Password de la red";
const char* mqtt_server = "test.mosquitto.org";
const int   mqtt_port   = 1883;

const char* HABITACION  = "hab1";
const char* TOPIC_SUB   = "roomsenseg3/hab1/actuadores";
const char* TOPIC_PUB   = "roomsenseg3/hab1/sensores";

// =========================================================================
// 3. PINES EN TU FIREBEETLE 2 ESP32-S3
// =========================================================================
const int PIN_SERVO       = 3;   // D2
const int PIN_HALL        = 38;  // D3
const int PIN_LUZ         = 7;   // D5
const int PIN_CALEFACCION = 18;  // D6
const int PIN_LED_STATUS  = 21;  // D13 (LED integrado en la placa)

// =========================================================================
// 4. ESTADO DEL NODO
// =========================================================================
struct EstadoNodo {
  String ventana     = "CERRADA";
  String luz         = "OFF";
  String calefaccion = "OFF";
  int    angulo      = 0;
} estado;

WiFiClient espClient;
PubSubClient client(espClient);

#if USAR_SERVO
  Servo servoVentana;
  const int ANGULO_CIERRE   = 0;
  const int ANGULO_APERTURA = 90;
  bool cerrandoVentana      = false;
  bool abriendoVentana      = false;
  unsigned long tPasoServo  = 0;
#endif

#if USAR_HALL
  String ultimoEstadoHall = "";
#endif

unsigned long tUltimaTelemetria = 0;
unsigned long tParpadeoLed      = 0;
bool ledStatusState             = false;

// =========================================================================
// 5. ENVIAR ESTADO A NODE-RED
// =========================================================================
void publicarTelemetria() {
  JsonDocument doc;
  doc["habitacion"] = HABITACION;

  #if USAR_SERVO || USAR_HALL
    doc["ventana"] = estado.ventana;
    doc["angulo"]  = estado.angulo;
  #endif

  #if USAR_LUZ
    doc["luz"] = estado.luz;
  #endif

  #if USAR_CALEFACCION
    doc["calefaccion"] = estado.calefaccion;
  #endif

  char buffer[256];
  serializeJson(doc, buffer);
  client.publish(TOPIC_PUB, buffer);
  Serial.println("[MQTT PUB] " + String(buffer));
}

// =========================================================================
// 6. INICIALIZAR HARDWARE ACTIVO
// =========================================================================
void inicializarModulos() {
  pinMode(PIN_LED_STATUS, OUTPUT);

  #if USAR_HALL
    pinMode(PIN_HALL, INPUT_PULLUP);
  #endif

  #if USAR_SERVO
    ESP32PWM::allocateTimer(0);
    servoVentana.setPeriodHertz(50);
    servoVentana.attach(PIN_SERVO, 500, 2400);
    #if USAR_HALL
      bool cerrado   = (digitalRead(PIN_HALL) == LOW);
      estado.angulo  = cerrado ? ANGULO_CIERRE : ANGULO_APERTURA;
      estado.ventana = cerrado ? "CERRADA" : "ABIERTA";
    #endif
    servoVentana.write(estado.angulo);
  #endif

  #if USAR_LUZ
    pinMode(PIN_LUZ, OUTPUT);
    digitalWrite(PIN_LUZ, LOW);
  #endif

  #if USAR_CALEFACCION
    pinMode(PIN_CALEFACCION, OUTPUT);
    digitalWrite(PIN_CALEFACCION, LOW);
  #endif
}

// =========================================================================
// 7. CONTROL DE VENTANA + SENSOR HALL (NO BLOQUEANTE)
// =========================================================================
void actualizarVentanaYHall() {
  bool imanDetectado = false;
  #if USAR_HALL
    imanDetectado = (digitalRead(PIN_HALL) == LOW);
  #endif

  #if USAR_SERVO
    if ((cerrandoVentana || abriendoVentana) && (millis() - tPasoServo >= 25)) {
      tPasoServo = millis();

      if (cerrandoVentana) {
        #if USAR_HALL
          if (imanDetectado) {
            cerrandoVentana = false;
            estado.ventana  = "CERRADA";
            publicarTelemetria();
            return;
          }
        #endif
        if (estado.angulo > ANGULO_CIERRE) {
          estado.angulo--;
          servoVentana.write(estado.angulo);
        } else {
          cerrandoVentana = false;
          #if !USAR_HALL
            estado.ventana = "CERRADA";
            publicarTelemetria();
          #endif
        }
      } else if (abriendoVentana) {
        if (estado.angulo < ANGULO_APERTURA) {
          estado.angulo++;
          servoVentana.write(estado.angulo);
        } else {
          abriendoVentana = false;
          estado.ventana  = "ABIERTA";
          publicarTelemetria();
        }
      }
    }
  #endif

  #if USAR_HALL
    bool servoQuieto = true;
    #if USAR_SERVO
      servoQuieto = (!cerrandoVentana && !abriendoVentana);
    #endif

    if (servoQuieto) {
      String lectHall = imanDetectado ? "CERRADA" : "ABIERTA";
      if (lectHall != ultimoEstadoHall) {
        ultimoEstadoHall = lectHall;
        estado.ventana   = lectHall;
        publicarTelemetria();
      }
    }
  #endif
}

void actualizarLedEstado() {
  bool trabajando = false;
  #if USAR_SERVO
    trabajando = (cerrandoVentana || abriendoVentana);
  #endif

  if (trabajando) {
    if (millis() - tParpadeoLed >= 100) {
      tParpadeoLed   = millis();
      ledStatusState = !ledStatusState;
      digitalWrite(PIN_LED_STATUS, ledStatusState);
    }
  } else {
    digitalWrite(PIN_LED_STATUS, (estado.ventana == "ABIERTA") ? HIGH : LOW);
  }
}

// =========================================================================
// 8. RECIBIR ÓRDENES DESDE TU DASHBOARD / SCADA
// =========================================================================
void callbackMQTT(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  JsonDocument doc;
  if (deserializeJson(doc, msg)) return;

  String act = doc["actuador"] | "";
  String ord = doc["valor"]    | "";
  ord.toUpperCase();

  #if USAR_SERVO
    if (act == "ventana") {
      if (ord == "CERRADA" || ord == "OFF") {
        #if USAR_HALL
          if (digitalRead(PIN_HALL) == HIGH) { cerrandoVentana = true; abriendoVentana = false; }
          else { estado.ventana = "CERRADA"; publicarTelemetria(); }
        #else
          cerrandoVentana = true; abriendoVentana = false;
        #endif
      } else if (ord == "ABIERTA" || ord == "ON") {
        abriendoVentana = true; cerrandoVentana = false;
      }
    }
  #endif

  #if USAR_LUZ
    if (act == "luz") {
      bool on = (ord == "ON" || ord == "ENCENDIDA");
      digitalWrite(PIN_LUZ, on ? HIGH : LOW);
      estado.luz = on ? "ON" : "OFF";
      publicarTelemetria();
    }
  #endif

  #if USAR_CALEFACCION
    if (act == "clima" || act == "calefaccion") {
      bool on = (ord == "ON" || ord == "ENCENDIDA");
      digitalWrite(PIN_CALEFACCION, on ? HIGH : LOW);
      estado.calefaccion = on ? "ON" : "OFF";
      publicarTelemetria();
    }
  #endif
}

// =========================================================================
// 9. CONEXIÓN WIFI / MQTT Y BUCLE PRINCIPAL
// =========================================================================
void asegurarConexion() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi OK! IP: " + WiFi.localIP().toString());
  }
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    String id = "FireBeetleS3-" + String(random(0xffff), HEX);
    if (client.connect(id.c_str())) {
      Serial.println(" OK!");
      client.subscribe(TOPIC_SUB);
    } else {
      Serial.println(" Fallo rc=" + String(client.state()));
      delay(2000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  inicializarModulos();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callbackMQTT);
  asegurarConexion();
}


void loop() {
  asegurarConexion();
  client.loop();

  actualizarVentanaYHall();
  actualizarLedEstado();

  if (millis() - tUltimaTelemetria >= 5000) {
    tUltimaTelemetria = millis();
    publicarTelemetria();
  }
}

