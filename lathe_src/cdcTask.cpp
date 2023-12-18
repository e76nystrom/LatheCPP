//
// Created by Eric on 4/15/2023.

//
// echo to either Serial0 or Serial1
// with Serial0 as all lower case, Serial1 as all upper case

#include "class/cdc/cdc_device.h"
#include "config.h"
#include "serialio.h"
#include "remcmd.h"

#if 1

void cdc_task()
{
 if (tud_cdc_n_available(REM_USB))
 {
  int count = remCtl.rx_count;
  char *buf = remCtl.rx_buffer;
  int rxCount = (int) tud_cdc_n_read(REM_USB, buf + count,
                                     sizeof(remCtl.rx_buffer) - count);
  if (rxCount != 0)
  {
   //printf("cdc_task count %d rxCount %d\n", count, rxCount);
   //prtBuf((unsigned char *) buf + count, rxCount);
   rxCount += count;
   remCtl.rx_count = rxCount;
   //printf("%02x\n", buf[rxCount - 1]);
   //fflush(stdout);
   //flushBuf();
   if (buf[rxCount - 1] == '\r')
   {
    remCtl.rx_emp = 0;
    remCtl.tx_fil = 0;
    remCtl.tx_count = 0;
    remCmd();
    //prtBuf((unsigned char *) remCtl.tx_buffer, remCtl.tx_count);
    //fflush(stdout);
    //flushBuf();
    tud_cdc_n_write(REM_USB, remCtl.tx_buffer, remCtl.tx_count);
    tud_cdc_n_write_flush(REM_USB);
    remCtl.rx_count = 0;
   }
  }
 }
}

#else
static void echo_serial_port(uint8_t itf, uint8_t buf[], uint32_t count)
{
 uint8_t const case_diff = 'a' - 'A';

 for(uint32_t i=0; i<count; i++)
 {
  if (itf == 0)
  {
   // echo back 1st port as lower case
   if (isupper(buf[i])) buf[i] += case_diff;
  }
  else
  {
   // echo back 2nd port as upper case
   if (islower(buf[i])) buf[i] -= case_diff;
  }

  tud_cdc_n_write_char(itf, buf[i]);
 }
 tud_cdc_n_write_flush(itf);
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void)
{
 uint8_t itf;

 for (itf = 0; itf < CFG_TUD_CDC; itf++)
 {
  // connected() check for DTR bit
  // Most but not all terminal client set this when making connection
  // if ( tud_cdc_n_connected(itf) )
  {
   if ( tud_cdc_n_available(itf) )
   {
    uint8_t buf[64];

    uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));

    // echo back to both serial ports
    echo_serial_port(0, buf, count);
    echo_serial_port(1, buf, count);
   }
  }
 }
}
#endif
