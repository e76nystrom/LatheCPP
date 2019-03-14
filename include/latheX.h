#if 1	// <-

#ifdef WIN32
#define DBG_DETAIL 1
#else
#define DBG_DETAIL 0
#endif

int bitSize(int val);

void axisCtlX(void);

void setupX(void);

void spindleStartX(void);		/* start spindle */
void spindleStopX(void);		/* stop spindle */
void spindleSetupX(int rpm);

void zStopX(void);
void zSetupX(void);
void zMoveSetupX(void);
void zSynSetupX(int feedType, float feed);
void zTaperSetupX(void);

void xStopX(void);
void xSetupX(void);
void xMoveSetupX(void);
void xSynSetupX(int feedType, float feed);
void xTaperSetupX(void);

void accelCalcX(P_ACCEL ac);

void turnPitchX(P_ACCEL ac, float pitch);
void threadTPIX(P_ACCEL ac, float tpi);
void threadMetricX(P_ACCEL ac, float pitch);
void turnAccelX(P_ACCEL ac, float accel);
void accelSetupX(P_ACCEL ac);

void taperCalcX(P_ACCEL a0, P_ACCEL a1, float taper);

void zTaperInitX(P_ACCEL ac, char dir);
void xTaperInitX(P_ACCEL ac, char dir);

char *i64toa(long long val, char *buf, int buflen);

int tmp(int x);

#endif	// ->
