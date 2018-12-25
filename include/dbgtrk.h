#define DBGTRK 1

#if DBGTRK

constexpr auto TRKBUFSIZE = (4*64);
EXT boolean dbgTrk;
EXT int16_t trkidx;
EXT int16_t trkbuf[TRKBUFSIZE];

constexpr auto DBGTRK1W0 = 0;   /* spindle position when index pulse */
constexpr auto DBGTRK1W1 = 0;   /* x jog encoder */
constexpr auto DBGTRK1L0 = 0;   /* rpm */
constexpr auto DBGTRK2L0 = 0;   /* x and z timers on spindle cyc ctr max */
constexpr auto DBGTRK2L1 = 0;   /* z isr tmr at accel end on sync start */
constexpr auto DBGTRK2L2 = 0;   /* spare */
constexpr auto DBGTRK2L3 = 0;   /* ext motor index period z clocks step */
constexpr auto DBGTRK2WL0 = 0;  /* encoder capature */
constexpr auto DBGTRK2WL1 = 1;  /* interal capature */

constexpr auto DBGTRK1W = 0;
inline void dbgTrk1W(uint16_t val1  __attribute__((unused))) {}

constexpr auto DBGTRK1L = 0;
inline void dbgTrk1L(uint32_t val1  __attribute__((unused))) {}

constexpr auto DBGTRK2L = 0;
inline void dbgTrk2L(uint32_t val1  __attribute__((unused)),
	uint32_t val2  __attribute__((unused))) {}

constexpr auto DBGTRK2WL = 1;
inline void dbgTrk2WL(uint16_t val1  __attribute__((unused)),
	uint16_t val2  __attribute__((unused)),
	uint32_t val3  __attribute__((unused))) \
{ \
 int16_t *p = (int16_t *) &trkbuf[trkidx]; \
 *p++ = val1; \
 *p++ = val2; \
 *((int32_t *) p) = val3; \
 trkidx += 4; \
 trkidx &= (TRKBUFSIZE - 1); \
}

#endif /* DBGTRK */
