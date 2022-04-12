#ifndef TFLUNA_H_INCLUDE
#define TFLUNA_H_INCLUDE

//----- Headers ------------//
#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>
#include "IO_Macros.h"
#include "tfluna_settings.h"
//--------------------------//

//--------------------------//


//----- Prototypes ------------------------------------------------------------//

void tfSetup();
bool getData( int16_t * dist, int16_t * flux, int16_t * temp, uint8_t addr);
// Get data short version
//bool getData( int16_t * dist, uint8_t addr);

// Read From or Write To an I2C register
bool readReg( uint8_t nmbr, uint8_t addr);
bool writeReg( uint8_t nmbr, uint8_t addr, uint8_t data);

void flush(void);

// Explicit Device Commands
//bool Get_Firmware_Version( uint8_t ver[], uint8_t adr);
//bool Get_Frame_Rate( uint16_t &frm, uint8_t adr);
//bool Get_Prod_Code( uint8_t cod[], uint8_t adr);
//bool Get_Time( uint16_t &tim, uint8_t adr);

//bool Set_Frame_Rate( uint16_t &frm, uint8_t adr);
//bool Set_I2C_Addr( uint8_t adrNew, uint8_t adr);
//bool Set_Enable( uint8_t adr);
//bool Set_Disable( uint8_t adr);
//bool Soft_Reset( uint8_t adr);  // Reset and reboot
//bool Hard_Reset( uint8_t adr);  // Restore factory defaults
//bool Save_Settings( uint8_t adr);
//bool Set_Trig_Mode( uint8_t adr);
//bool Set_Cont_Mode( uint8_t adr);
//bool Set_Trigger( uint8_t adr);  // false = continuous

//  For testing purposes: print reply data and status
//void printDataArray();
//void printStatus();
//-----------------------------------------------------------------------------//
#endif
