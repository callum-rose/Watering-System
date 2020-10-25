#include <Arduino.h>

class MoistureMotor
{
public:
    MoistureMotor(uint8_t sensorPin, uint16_t motorPin)
    {
        pinMode(sensorPin, INPUT);
        pinMode(motorPin, OUTPUT);
        
        _sensorPin = sensorPin;
        _motorPin = motorPin;
    }

    void Check()
    {
        if (!ShouldRun())
        {
            Serial.println("Motor should not run");
            return;
        }

        int value = analogRead(_sensorPin);

        if (value < _moistureThreadhold)
        {
            Serial.println("Soil moisture content fine");
            SetMotor(false);
        }
        else
        {
            Serial.print("Soil moisture content too dry. Motor on");
            Serial.println(value);
            
            SetMotor(true);

            long startMillis = millis();
            while (millis() - startMillis < 5000)
            {
                value = analogRead(_sensorPin);
                if (value < _moistureThreadhold)
                {
                    Serial.print("Motor stopped early because moisture level reached, ");
                    Serial.println(value);
                    break;
                }

                delay(10);
            }

            SetMotor(false);
        }
    }

private:
    uint8_t _sensorPin;    
    uint8_t _motorPin;

    int _lastValues[];

    const int _moistureThreadhold = 400;
    const long _motorWaitDuration = 10L * 60L * 1000L;

    bool _hasRunEver = false;
    long _lastMotorRunTime;

    bool ShouldRun()
    {
        return !_hasRunEver || millis() - _lastMotorRunTime < _motorWaitDuration;
    }

    void CycleValues(int newValue)
    {
        int tempValue;
    }

    void SetMotor(bool doRun)
    {
        if (doRun)
        {
            _lastMotorRunTime = millis();
            _hasRunEver = true;
        }       

        digitalWrite(_motorPin, doRun);
    }
};

MoistureMotor* plant0;
MoistureMotor* plant1;
MoistureMotor* plant2;

void setup()
{
    plant0 = new MoistureMotor(A0, 11);
    plant1 = new MoistureMotor(A1, 10);
    plant2 = new MoistureMotor(A2, 9);

    Serial.begin(9600);
}

void loop()
{
    Serial.println("Motor 0:");
    plant0->Check();
        
    Serial.println("Motor 1:");
    plant1->Check();

    Serial.println("Motor 2:");
    plant2->Check();

    delay(5*1000);
}