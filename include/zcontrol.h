#if !defined(ZCONTROL_INC)	// <-
#define ZCONTROL_INC

void zSynLoad(void);
void zJMoveX(int dir);
void zMoveX(int32_t pos, char cmd);
void zMoveRelX(int32_t dist, char cmd);
void zControlX(void);

#endif  /* ZCONTROL_INC */	// ->
