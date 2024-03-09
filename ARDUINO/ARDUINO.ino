#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#define FIREBASE_USE_PSRAM

const int pinRojo = 21;
const int pinVerde = 22;
const int pinAzul = 23;

// Conectar a una red WiFi 
const char* WIFI_SSID = "red de prueba xd"; // el nombre de la red
const char* WIFI_PASSWORD = "pokedex"; // la contraseña de la red
// Recursos de Firebase
const char* API_KEY = "AIzaSyCADIjF2BEYn4FvZL1FGwVb_Aux9KjWBJ8";
const char* FIREBASE_PROJECT_ID = "pokedexpesantez";
// Configurar un email y contraseña en Authentication de Firebase
const char* USER_EMAIL = "esp32@esp32.com";
const char* USER_PASSWORD = "123456";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  Serial.print("Conectando a Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado con IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION); // Verificamos la version
  setupWiFi(); // Llamamos la funcion de configuración wifi
  setupFirebase(); // Llamamos la funcion de configuración Firebase

  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  String path = "pokemones"; // Ruta de la colección
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      Serial.println("Documentos encontrados:");
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"]; // Nombre del documento
        const char* pokemon_type = document["fields"]["type"]["stringValue"]; // Tipo del Pokémon

        Serial.print("Nombre del documento: ");
        Serial.println(document_name);
        Serial.print("Tipo de Pokémon: ");
        Serial.println(pokemon_type);

        // Establecer el color del LED RGB según el tipo de Pokémon
        if (strstr(pokemon_type, "steel") != nullptr) {
          setColor(183, 183, 206);// Acero (Steel)
          delay(10);
        } else if (strstr(pokemon_type, "water") != nullptr) {
          setColor(36, 129, 240); // Agua (Water)
          delay(10);
        } else if (strstr(pokemon_type, "bug") != nullptr) {
          setColor(166, 185, 26); // Bicho (Bug)
          delay(10);
        } else if (strstr(pokemon_type, "dragon") != nullptr) {
          setColor(111, 53, 252); // Dragón (Dragon)
          delay(10);
        } else if (strstr(pokemon_type, "electric") != nullptr) {
          setColor(255, 255, 0); // Eléctrico (Electric)
          delay(10);
        } else if (strstr(pokemon_type, "ghost") != nullptr) {
          setColor(115, 87, 151); // Fantasma (Ghost)
          delay(10);
        } else if (strstr(pokemon_type, "fire") != nullptr) {
          setColor (255, 0, 0); // Fuego (Fire)
          delay(10);
        } else if (strstr(pokemon_type, "fairy") != nullptr) {
          setColor(239, 112, 240); // Hada (Fairy)
          delay(10);
        } else if (strstr(pokemon_type, "ice") != nullptr) {
          setColor(150, 217, 214); // Hielo (Ice)
          delay(10);
        } else if (strstr(pokemon_type, "fight") != nullptr) {
          setColor(194, 46, 40); // Lucha (Fight)
          delay(10);
        } else if (strstr(pokemon_type, "normal") != nullptr) {
          setColor(168, 167, 122); // Normal (Normal)
          delay(10);
        } else if (strstr(pokemon_type, "grass") != nullptr) {
          setColor(0, 255, 0); // Planta (Grass)
          delay(10);
        } else if (strstr(pokemon_type, "psychic") != nullptr) {
          setColor (249, 85, 135); // Psíquico (Psychic)
          delay(10);
        } else if (strstr(pokemon_type, "rock") != nullptr) {
          setColor (182, 161, 54); // Roca (Rock)
          delay(10);
        } else if (strstr(pokemon_type, "dark") != nullptr) {
          setColor(112, 87, 70); // Siniestro (Dark)
          delay(10);
        } else if (strstr(pokemon_type, "ground") != nullptr) {
          setColor(226, 191, 101); // Tierra (Ground)
          delay(10);
        } else if (strstr(pokemon_type, "poison") != nullptr) {
          setColor(163, 62, 161); // Veneno (Poison)
          delay(10);
        } else if (strstr(pokemon_type, "flying") != nullptr) {
          setColor(169, 143, 243); // Volador (Flying)
          delay(10);
        }
        // Continuar con los demás tipos de Pokémon...

        delay(1000); // Esperar 1 segundo
      }
    } else {
      Serial.println("Error al deserializar JSON");
      Serial.println(error.c_str());
    }
  } else {
    Serial.println("Error al obtener documentos de Firebase");
    Serial.println(fbdo.errorReason());
  }
}

void setColor(int rojo, int verde, int azul) {
  analogWrite(pinRojo, rojo);
  analogWrite(pinVerde, verde);
  analogWrite(pinAzul, azul);
}