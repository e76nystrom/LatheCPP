#if !defined(LCLCMDX_INC)	// <-
#define LCLCMDX_INC

void lclcmdX(int ch);
void readreg(char addr,char *str);
void loadregb(char addr, char val);

extern int16_t addr;

#endif  /* LCLCMDX_INC */	// ->
