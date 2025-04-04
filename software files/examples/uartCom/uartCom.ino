#include <Wire.h>
#include <SoftwareSerial.h>

// BNO055 UART haberleşme pinleri
#define PS0_PIN  5     // PS0 pinini Arduino'nun 5. pinine bağlıyoruz
#define PS1_PIN  18    // PS1 pinini Arduino'nun 18. pinine bağlıyoruz
#define RX_PIN   21    // RX pinini SoftwareSerial kullanarak belirliyoruz
#define TX_PIN   22    // TX pinini SoftwareSerial kullanarak belirliyoruz

SoftwareSerial mySerial(RX_PIN, TX_PIN);  // RX, TX pinleri belirleniyor

uint8_t writeByte(uint8_t reg, uint8_t value) {

    uint8_t buffer[5];
    buffer[0] = 0xAA;    // Başlangıç baytı
    buffer[1] = 0x00;    // Yazma komutu (0x00)
    buffer[2] = reg;     // Register adresi
    buffer[3] = 0x01;    // Yazılacak veri uzunluğu (1 bayt)
    buffer[4] = value;   // Yazılacak veri

    for (int i = 0; i < 5; i++) {
        mySerial.write(buffer[i]);
    }

    unsigned long startMillis = millis();
    while (mySerial.available() < 1) {  // Yanıt gelene kadar bekle
        if (millis() - startMillis > 1000) {  // 1 saniye bekleme süresi
            Serial.println("Yazma yaniti alinamadi.");
            return 0;  // Yanit alinamadiği için hata döndür
        }
    }

    uint8_t response = mySerial.read();
    if (response == 0xEE) {
        Serial.println("Yazma işlemi başarili.");
    } else {
        Serial.print("Beklenmeyen yanit: 0x");
        Serial.println(response, HEX);  // Beklenmeyen yanıtı ekrana yazdır
    }

    return value;  // Başarılı yazma durumunda yazılan değeri döndür
}

uint8_t readChipID() {
  uint8_t value = 0;
  uint8_t response = 0;
  uint8_t buffer[6];
  uint8_t count=0;

  buffer[0] = 0xAA;    // Başlangıç baytı
  buffer[1] = 0x01;    // Okuma komutu (0x01)
  buffer[2] = 0x3D;    // CHIP_ID register adresi (örneğin 0x00 olabilir)
  buffer[3] = 0x01;    // 1 bayt veri okunacak
  buffer[4] = 0xBB;
  buffer[5] = 0x01;

  // Komutu UART üzerinden gönder
  for (int i = 0; i < 4; i++) {
    mySerial.write(buffer[i]);
  }

  // Yanıtın gelmesini bekle (1 saniyeye kadar)
  unsigned long startMillis = millis();
  while (mySerial.available() < 1) {
    if (millis() - startMillis > 1000) {
      Serial.println("Yanit alinamadi.");
      return 0;
    }
  }

  response=mySerial.read();
  if (response==0xBB);
    {
      count=mySerial.read();
      for(int i = 0; i < count; i++){ 
        value=mySerial.read(); 
      }
    }
  if (response==0xEE)
    {
    Serial.print(mySerial.read(), HEX);    
    }  

  return value; // Okunan CHIP_ID değerini döndür
}

void setup() {
  pinMode(PS0_PIN, OUTPUT);
  pinMode(PS1_PIN, OUTPUT);

  digitalWrite(PS0_PIN, LOW);   // PS0 = LOW
  digitalWrite(PS1_PIN, HIGH);  // PS1 = HIGH

  Serial.begin(115200);         // Debug için normal Serial başlatma
  mySerial.begin(115200);

}

void loop() {
  //writeByte(0x3D, 0x01);
  //delay(30);
  uint8_t chipID = readChipID();

  // CHIP_ID değerini ekrana yazdır
  Serial.print("CHIP_ID: 0x");
  Serial.println(chipID, HEX);
  //Serial.println(bnoSensor.readByte(0x00));
  delay(250);
}
