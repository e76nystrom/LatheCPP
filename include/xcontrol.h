#if !defined(XCONTROL_INC)	// <-
#define XCONTROL_INC

void xSynLoad(void);
void xJMoveX(int dir);
void xMoveX(int32_t pos, char cmd);
void xMoveRelX(int32_t dist, char cmd);
void xControlX(void);

#endif  /* XCONTROL_INC */	// ->
