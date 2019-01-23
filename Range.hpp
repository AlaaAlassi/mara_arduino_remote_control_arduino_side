/*! 
 * @file Range.hpp
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was written by Jack Cox since the gen tool failed.
 */
#ifndef _SENSOR_MSGS_RANGE_HPP_
#define _SENSOR_MSGS_RANGE_HPP_


#include <topic.hpp>


#include "std_msgs/Header.hpp"

namespace sensor_msgs {

enum RadiationType 
{
    ULTRASOUND = 0,
    INFRARED
};


class Range : public ros2::Topic<Range>
{
public: 
    std_msgs::Header header;
    uint8_t radiation_type;
    float field_of_view;
    float min_range;
    float max_range;
    float range;


  Range():
    Topic("sensor_msgs::msg::dds_::Range_", "Range"),
    header(),
    radiation_type(0), field_of_view(0),
    min_range(0), max_range(0), range(0)
  { 
  }

  bool serialize(void* msg_buf, const Range* topic)
  {
    ucdrBuffer* writer = (ucdrBuffer*)msg_buf;
    (void) header.serialize(writer, &topic->header);
    (void) ucdr_serialize_uint8_t(writer, topic->radiation_type);
    (void) ucdr_serialize_float(writer, topic->field_of_view);
    (void) ucdr_serialize_float(writer, topic->min_range);
    (void) ucdr_serialize_float(writer, topic->max_range);
    (void) ucdr_serialize_float(writer, topic->range);

    return !writer->error;
  }

  bool deserialize(void* msg_buf, Range* topic)
  {
    ucdrBuffer* reader = (ucdrBuffer*)msg_buf;
    (void) header.deserialize(reader, &topic->header);
    (void) ucdr_deserialize_uint8_t(reader, &topic->radiation_type);
    (void) ucdr_deserialize_float(reader, &topic->field_of_view);
    (void) ucdr_deserialize_float(reader, &topic->min_range);
    (void) ucdr_deserialize_float(reader, &topic->max_range);
    (void) ucdr_deserialize_float(reader, &topic->range);

    return !reader->error;
  }

  uint32_t size_of_topic(const Range* topic, uint32_t size)
  {
    uint32_t previousSize = size;

    size += header.size_of_topic(&topic->header, size);

    size += ucdr_alignment(size, 1) + 1;
    size += ucdr_alignment(size, 4) + 4;
    size += ucdr_alignment(size, 4) + 4;
    size += ucdr_alignment(size, 4) + 4;
    size += ucdr_alignment(size, 4) + 4;

    return size - previousSize;
  }

};

} // namespace sensor_msgs


#endif // _SENSOR_MSGS_RANGE_HPP_