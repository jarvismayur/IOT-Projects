//#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <ThingESP.h> // Include the ThingESP library

SoftwareSerial swSerial(D1, D2); // RX, TX (change pin numbers accordingly)
StaticJsonDocument<200> jsonDoc;

// Initialize the ThingESP object
ThingESP8266 thing("tembharemayur", "ESPWhatsappLeD", "Mayur@12345");


float humidity = 0;
float temperature = 0;
uint16_t rainValue = 0;
uint16_t ldrValue = 0;
uint16_t soilMoisture = 0;

void setup()
{
  Serial.begin(9600);
  swSerial.begin(9600);
  thing.SetWiFi("JARVIS", "J97j(323");
  thing.initDevice();
}

// Custom function to handle the received JSON data
void handleJSONData()
{
  if (swSerial.available()) {
    // Read the incoming data from SoftwareSerial
    String jsonString = swSerial.readStringUntil('\n');

    // Deserialize the JSON data
    DeserializationError error = deserializeJson(jsonDoc, jsonString);

    // Check if the deserialization was successful
    if (error == DeserializationError::Ok) {
      // Retrieve the sensor data from the JSON object
     humidity = jsonDoc["humidity"];
     temperature = jsonDoc["temperature"];
     rainValue = jsonDoc["rainValue"];
     ldrValue = jsonDoc["ldrValue"];
     soilMoisture = jsonDoc["soilMoisture"];

      // Print the received sensor data
      Serial.print("Received Humidity (%): ");
      Serial.println(humidity, 2);

      Serial.print("Received Temperature (C): ");
      Serial.println(temperature, 2);

      Serial.print("Received Rain Drop: ");
      Serial.println(rainValue);

      Serial.print("Received Day Light: ");
      Serial.println(ldrValue);

      Serial.print("Received Soil Moisture: ");
      Serial.println(soilMoisture);

      // Here you can add your code to process or send the data to your IoT platform
      // For example, you can use thing.writeProperties() to send data to the platform
      // You can also use thing.addDebug() to display data on the ThingESP's debug console
    } else {
      Serial.println("Error parsing JSON data!");
    }
  }
}


String HandleResponse(String query)
{
  String jsonString;
  if(query == "weather") {
  
        StaticJsonDocument<200> jsonWeather;
        jsonWeather["humidity"] = humidity;
        jsonWeather["temperature"] = temperature;
        jsonWeather["rainValue"] = rainValue;
        jsonWeather["ldrValue"] = ldrValue;
        jsonWeather["soilMoisture"] = soilMoisture;
      
        // Serialize the JSON object to a string
        
        serializeJson(jsonWeather, jsonString);
        return jsonString;
  
        
        
      
   
     
    
  }else{ return "Your query was invalid..";}
 
}
void loop()
{
  // Call the custom function to handle JSON data
  handleJSONData();

  // Run ThingESP's loop() function to handle IoT platform communication
  thing.Handle();
}
