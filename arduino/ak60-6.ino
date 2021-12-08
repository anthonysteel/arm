#include <SPI.h>

#define CAN_2515

#define P_MIN -12.5f
#define P_MAX 12.5f
#define V_MIN -65.0f
#define V_MAX 65.0f
#define KP_MIN 0.0f
#define KP_MAX 500.0f
#define KD_MIN 0.0f
#define KD_MAX 5.0f
#define T_MIN -18.0f
#define T_MAX 18.0f

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif

#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

// Set values
float p_in = 0.0f;
float v_in = 0.0f;
float kp_in = 20.0f;
float kd_in = 1.0f;
float t_in = 0.0f;
// measured values
float p_out = 0.0f;
float v_out = 0.0f;
float t_out = 0.0f;

void EnterMotorMode() {
  unsigned char buf[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
  CAN.sendMsgBuf(0x01, 0, 8, buf);
}

void ExitMotorMode() {
  unsigned char buf[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd};
  CAN.sendMsgBuf(0x01, 0, 8, buf);
}

void pack_cmd() {
  float p_des = constrain(p_in, P_MIN, P_MAX);
  float v_des = constrain(v_in, V_MIN, V_MAX);
  float kp = constrain(kp_in, KP_MIN, KP_MAX);
  float kd = constrain(kd_in, KD_MIN, KD_MAX);
  float t_ff = constrain(t_in, T_MIN, T_MAX);

  unsigned int p_int = float_to_uint(p_des, P_MIN, P_MAX, 16);
  unsigned int v_int = float_to_uint(v_des, V_MIN, V_MAX, 12);
  unsigned int kp_int = float_to_uint(kp, KP_MIN, KP_MAX, 12);
  unsigned int kd_int = float_to_uint(kd, KD_MIN, KD_MAX, 12);
  unsigned int t_int = float_to_uint(t_ff, T_MIN, T_MAX, 12);

  unsigned char buf[8] = {(p_int >> 8),
                           (p_int & 0xff),
                           (v_int >> 4),
                           (((v_int & 0xf) << 4) | (kp_int >> 8)),
                           (kp_int & 0xff),
                           (kd_int >> 4),
                           (((kd_int & 0xf) << 4) | (t_int >> 8)),
                           (t_int & 0xff)};
  CAN.sendMsgBuf(0x01, 0, 8, buf);
}

void unpack_reply() {
  byte len = 0;
  byte buf[8];
  CAN.readMsgBuf(&len, buf);

  unsigned long canId = CAN.getCanId();
  unsigned int id = buf[0];
  unsigned int p_int = (buf[1] << 8) | buf[2];
  unsigned int v_int = (buf[3] << 4) | (buf[4] >> 4);
  unsigned int i_int = ((buf[4] & 0xf) << 8) | buf[5];

  p_out = uint_to_float(p_int, P_MIN, P_MAX, 16);
  v_out = uint_to_float(v_int, V_MIN, V_MAX, 12);
  t_out = uint_to_float(i_int, -T_MAX, T_MAX, 12);
}


unsigned int float_to_uint(float x, float x_min, float x_max, int bits) {
  /// Converts a float to an unsigned int, given range and number of bits ///
  float span = x_max - x_min;
  float offset = x_min;
  unsigned int pgg = 0;
  if (bits == 12) {
    pgg = (unsigned int) ((x-offset)*4095.0/span);
  }
  if (bits == 16) {
    pgg = (unsigned int) ((x-offset)*65535.0/span);
  }
  return pgg;
}

float uint_to_float(unsigned int x_int, float x_min, float x_max, int bits) {
  float span = x_max - x_min;
  float offset = x_min;
  float pgg = 0;
  if (bits == 12) {
    pgg = ((float) x_int) * span / 4095.0 + offset;
  }
  if (bits == 16) {
    pgg = ((float) x_int) * span / 65535.0 + offset;
  }
  return pgg;
}

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);
    while(!Serial){};

    while (CAN_OK != CAN.begin(CAN_1000KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
    EnterMotorMode();

}

float dir = -1;
void loop() {
    if (p_in <= P_MIN || p_in >= P_MAX) {
      dir *= -1;
    }
    p_in = constrain(p_in + (dir * 0.01), P_MIN, P_MAX);
    delay(10);
    pack_cmd();
    SERIAL_PORT_MONITOR.println("Send p_in:"+String(p_in));
}
