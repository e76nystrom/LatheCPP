#if !defined(LCLCMD_INC)	// <-
#define LCLCMD_INC

#if !defined(EXT)
#define EXT extern
#endif

void lclcmd(int ch);

EXT int16_t addr;
EXT float tpi;
EXT float zTaperDist;
EXT float taper;
EXT int zDist;
//extern int zFlag;
EXT int xDist;

#endif  /* LCLCMD_INC */	// ->
