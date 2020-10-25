// #include <Arduino.h>
// #include <math.h>
// #include <LinkedList.h>

// #define MOISTURE_READ_PIN A0

// // air - 559
// // dry soil - 502
// // damp soil - 447
// // wet soil - 301
// // water - 282

// long lastPrintTime = 0;

// LinkedList<int> valueList = LinkedList<int>();

// void doCalcs()
// {
//   int sum = 0;
//   for (int i = 0; i < valueList.size(); i++)
//   {
//     sum += valueList.get(i);
//   }

//   double mean = (double)sum / valueList.size();

//   String message = "mean: ";
//   message += mean;
//   Serial.println(message);

//   long sqrSum = 0;
//   int a;
//   for (int i = 0; i < valueList.size(); i++)
//   {
//     a = valueList.get(i) - mean;
//     sqrSum += (long)(a * a);
//   }

//   double stdDev = sqrt((double)(sqrSum / valueList.size()));

//   message = "stdDev: ";
//   message += stdDev;
//   Serial.println(message);
// }

// void setup() 
// {
//   pinMode(MOISTURE_READ_PIN, INPUT);
  
//   Serial.begin(9600);
// }

// void loop() 
// {
//   valueList.add(analogRead(MOISTURE_READ_PIN));

//   if (millis() - lastPrintTime > 5000)
//   {
//     doCalcs();

//     lastPrintTime = millis();
//   }

//   delay(1000);
// }