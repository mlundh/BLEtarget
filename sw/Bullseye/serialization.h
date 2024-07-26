#ifndef SERIALIZATION_H
#define SERIALIZATION_H
#include <stdint.h>
#include <stddef.h>

class serialization
{
private:
    serialization();

public:
    /**
     * Serialize the value pointed to by value.
     * @param buffer    Pointer to the buffer where the serialized value will be stored.
     * @param size      Pointer to the size of the buffer. This will be updated to reflect
     *                  the remaining size after writing the data.
     * @param value     Pointer to the value to serialize. Used a pointer so that the interface
     *                  is similar for simple and complex types.
     * @return          Pointer to the end of the written data. Use this together with the size
     *                  parameter to continue the serialization.
     */
    static uint8_t* serialize_uint32_t(uint8_t *buffer, uint32_t* size, uint32_t *value);
    static uint8_t* deserialize_uint32_t(uint8_t *buffer, uint32_t* size, uint32_t* value);

    static uint8_t* serialize_int32_t(uint8_t *buffer, uint32_t* size, int32_t *value);
    static uint8_t* deserialize_int32_t(uint8_t *buffer, uint32_t* size, int32_t* value);

    static uint8_t* serialize_uint16_t(uint8_t *buffer, uint32_t* size, uint16_t* value);
    static uint8_t* deserialize_uint16_t(uint8_t *buffer, uint32_t* size, uint16_t* value);

    static uint8_t* serialize_int16_t(uint8_t *buffer, uint32_t* size, int16_t *value);
    static uint8_t* deserialize_int16_t(uint8_t *buffer, uint32_t* size, int16_t* value);

    static uint8_t* serialize_uint8_t(uint8_t *buffer, uint32_t* size, uint8_t *value);
    static uint8_t* deserialize_uint8_t(uint8_t *buffer, uint32_t* size, uint8_t* value);

    static uint8_t* serialize_int8_t(uint8_t *buffer, uint32_t* size, int8_t *value);
    static uint8_t* deserialize_int8_t(uint8_t *buffer, uint32_t* size, int8_t* value);
};

#endif // SERIALIZATION_H
