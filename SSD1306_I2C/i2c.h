#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _I2C_MCS_R_Err_Stat  { I2COK, I2CERROR } TransmissionStatus;

TransmissionStatus I2C_Start_Transmission(unsigned const char byte,
                                          unsigned const char address);

TransmissionStatus I2C_Transmit_Byte(unsigned const char byte);

TransmissionStatus I2C_Stop_Transmission(void);

TransmissionStatus I2C_Send_Byte(unsigned const char byte, 
								 unsigned const char address);

TransmissionStatus I2C_Send_Bytes(unsigned const char* buffer,
                                  unsigned long        n_Bytes,
                                  unsigned const char  address);
																	
TransmissionStatus I2C_Recive_Byte(unsigned char*       buffer,
                                   unsigned const char  address);

TransmissionStatus I2C_Recive_Bytes(unsigned char*       buffer,
                                    unsigned const char  address);

void I2C_Init(void);

#ifdef __cplusplus
}
#endif

#endif
