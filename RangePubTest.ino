#include <ros2arduino.h>
#include <Wire.h>

#include "sensor_msgs/Range.hpp"

#define XRCEDDS_PORT  Serial
#define PUBLISH_FREQUENCY 10 //hz
#define MIN_RANGE 3
#define MAX_RANGE 400 // Maximum distance we want to ping for (in centimeters).
#define ULTRASOUND 0
#define FIELD_OF_VIEW 55 // FOV in degrees



int i2cping()
{
  int reading = 0;
  Wire.beginTransmission(112); // transmit to device #112 (0x70)
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // use 0x50 for inches, use 0x51 for centimeters, use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(90);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(112); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if (2 <= Wire.available())
  { // if two bytes were received
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    //if (reading < MIN_RANGE || reading > MAX_RANGE) return;
    //else return reading;
    return reading;

  }

}
void publishRange(sensor_msgs::Range* msg, void* arg)

{
  (void)(arg);
  int32_t secs = millis() / 1000;
  uint32_t nano = (millis() - (secs * 1000)) * 1000;
  msg->header.stamp.sec = secs;
  msg->header.stamp.nanosec = nano;
  sprintf(msg->header.frame_id, "ultrasonic");
  msg->radiation_type = ULTRASOUND;
  msg->field_of_view = FIELD_OF_VIEW;
  msg->min_range = MIN_RANGE;
  msg->max_range = MAX_RANGE;
  msg->range = i2cping();

}


class RangePub : public ros2::Node
{
  public:
    RangePub()
      : Node()
    {
      ros2::Publisher<sensor_msgs::Range>* publisher_ = this->createPublisher<sensor_msgs::Range>("arduino_ranger");
      this->createWallFreq(PUBLISH_FREQUENCY, (ros2::CallbackFunc)publishRange, NULL, publisher_);
    }
};

void setup()
{
  XRCEDDS_PORT.begin(115200);
  while (!XRCEDDS_PORT);
  ros2::init(&XRCEDDS_PORT);

  Wire.begin();

  Wire.beginTransmission(112); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to range register (0x02)
  Wire.write(byte(0x8C));      // sets max range to 6m (see data sheet for values)
  Wire.endTransmission();      // stop transmitting

}

void loop()
{
  static RangePub RangeNode;

  ros2::spin(&RangeNode);
}
