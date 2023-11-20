typedef struct S_CHR
{
 char c0;
 char c1;
 char c2;
 char c3;
} T_CH4, *P_CH4;

T_CH4 fpgaOpStr[] =
{
 {'N', 'O', ' ', ' ',}, /* 00   0 reg 0                    F_Noop */
 {'R', 'S', 'T', 'S',}, /* 01   1 status reg               F_Rd_Status */
 {'R', 'I', 'N', 'P',}, /* 02   2 inputs reg               F_Rd_Inputs */
 {'L', 'R', 'U', 'N',}, /* 03   3 set run control reg      F_Ld_Run_Ctl */
 {'R', 'R', 'U', 'N',}, /* 04   4 read run control reg     F_Rd_Run_Ctl */
 {'L', 'S', 'Y', 'N',}, /* 05   5 sync control reg         F_Ld_Sync_Ctl */
 {'L', 'C', 'F', 'G',}, /* 06   6 config control reg       F_Ld_Cfg_Ctl */
 {'L', 'C', 'L', 'K',}, /* 07   7 clock control reg        F_Ld_Clk_Ctl */
 {'L', 'D', 'O', 'U',}, /* 08   8 output reg               F_Ld_Out_Reg */
 {'L', 'D', 'S', 'P',}, /* 09   9 display reg              F_Ld_Dsp_Reg */
 {'C', 'L', 'C', 'D',}, /* 0a  10 load controller data     F_Ctrl_Base, F_Ld_Ctrl_Data */
 {'C', 'C', 'M', 'D',}, /* 0b  11 controller command       F_Ctrl_Base, F_Ctrl_Cmd */
 {'C', 'L', 'S', 'Q',}, /* 0c  12 load sequence            F_Ctrl_Base, F_Ld_Seq */
 {'C', 'R', 'S', 'Q',}, /* 0d  13 read sequence            F_Ctrl_Base, F_Rd_Seq */
 {'C', 'R', 'C', 'T',}, /* 0e  14 read counter             F_Ctrl_Base, F_Rd_Ctr */
 {'R', 'L', 'D', 'R',}, /* 0f  15 load reader data         F_Read_Base, F_Ld_Read_Data */
 {'R', 'R', 'D', ' ',}, /* 10  16 read data                F_Read_Base, F_Read */
 {'D', 'D', 'B', 'F',}, /* 11  17 debug frequency          F_Dbg_Freq_Base, F_Ld_Dbg_Freq */
 {'D', 'D', 'B', 'C',}, /* 12  18 debug count              F_Dbg_Freq_Base, F_Ld_Dbg_Count */
 {'R', 'I', 'D', 'X',}, /* 13  19 clocks per index         F_Rd_Idx_Clks */
 {'P', 'M', 'A', 'X',}, /* 14  20 pwm counter maximum      F_PWM_Base, F_Ld_PWM_Max */
 {'P', 'T', 'R', 'G',}, /* 15  21 pwm trigger              F_PWM_Base, F_Ld_PWM_Trig */
 {'E', 'L', 'E', 'C',}, /* 16  22 load encoder cycle       F_Enc_Base, F_Ld_Enc_Cycle */
 {'E', 'L', 'I', 'C',}, /* 17  23 load internal cycle      F_Enc_Base, F_Ld_Int_Cycle */
 {'E', 'R', 'C', 'C',}, /* 18  24 read cmp cycle clocks    F_Enc_Base, F_Rd_Cmp_Cyc_C */
 {'H', 'L', 'L', 'N',}, /* 19  25 phase length             F_Phase_Base, F_Ld_Phase_Len */
 {'H', 'R', 'S', 'Y',}, /* 1a  26 read phase at sync pulse F_Phase_Base, F_Rd_Phase_Syn */
 {'Z', 'R', 'A', 'S',}, /* 1b  27 read axis status         F_ZAxis_Base, F_Rd_Axis_Status */
 {'Z', 'L', 'A', 'C',}, /* 1c  28 set axis control reg     F_ZAxis_Base, F_Ld_Axis_Ctl */
 {'Z', 'R', 'A', 'C',}, /* 1d  29 read axis control reg    F_ZAxis_Base, F_Rd_Axis_Ctl */
 {'Z', 'L', 'F', 'R',}, /* 1e  30 frequency                F_ZAxis_Base, F_Ld_Freq */
 {'Z', 'L', 'I', 'S',}, /* 1f  31 axis initial sum         F_ZAxis_Base, F_Sync_Base, F_Ld_D */
 {'Z', 'L', 'I', '1',}, /* 20  32 axis incr1               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'Z', 'L', 'I', '2',}, /* 21  33 axis incr2               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'Z', 'L', 'A', 'V',}, /* 22  34 axis accel value         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'Z', 'L', 'A', 'C',}, /* 23  35 axis accel count         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'Z', 'R', 'X', ' ',}, /* 24  36 axis x pos               F_ZAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'Z', 'R', 'Y', ' ',}, /* 25  37 axis y pos               F_ZAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'Z', 'R', 'S', 'U',}, /* 26  38 axis sum                 F_ZAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'Z', 'R', 'A', 'S',}, /* 27  39 axis accel sum           F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'Z', 'R', 'A', 'C',}, /* 28  40 axis accel counter       F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'Z', 'L', 'D', 'S',}, /* 29  41 axis distance            F_ZAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'Z', 'L', 'M', 'D',}, /* 2a  42 jog maximum distance     F_ZAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'Z', 'R', 'D', 'S',}, /* 2b  43 read axis distance       F_ZAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'Z', 'R', 'A', 'S',}, /* 2c  44 read accel steps         F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'Z', 'L', 'L', 'C',}, /* 2d  45 axis location            F_ZAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'Z', 'R', 'L', 'C',}, /* 2e  46 read axis location       F_ZAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'Z', 'L', 'D', 'R',}, /* 2f  47 axis dro                 F_ZAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'Z', 'L', 'D', 'E',}, /* 30  48 axis dro end             F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'Z', 'L', 'D', 'L',}, /* 31  49 axis dro decel limit     F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'Z', 'R', 'D', 'R',}, /* 32  50 read axis dro            F_ZAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'X', 'R', 'A', 'S',}, /* 33  51 read axis status         F_XAxis_Base, F_Rd_Axis_Status */
 {'X', 'L', 'A', 'C',}, /* 34  52 set axis control reg     F_XAxis_Base, F_Ld_Axis_Ctl */
 {'X', 'R', 'A', 'C',}, /* 35  53 read axis control reg    F_XAxis_Base, F_Rd_Axis_Ctl */
 {'X', 'L', 'F', 'R',}, /* 36  54 frequency                F_XAxis_Base, F_Ld_Freq */
 {'X', 'L', 'I', 'S',}, /* 37  55 axis initial sum         F_XAxis_Base, F_Sync_Base, F_Ld_D */
 {'X', 'L', 'I', '1',}, /* 38  56 axis incr1               F_XAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'X', 'L', 'I', '2',}, /* 39  57 axis incr2               F_XAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'X', 'L', 'A', 'V',}, /* 3a  58 axis accel value         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'X', 'L', 'A', 'C',}, /* 3b  59 axis accel count         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'X', 'R', 'X', ' ',}, /* 3c  60 axis x pos               F_XAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'X', 'R', 'Y', ' ',}, /* 3d  61 axis y pos               F_XAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'X', 'R', 'S', 'U',}, /* 3e  62 axis sum                 F_XAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'X', 'R', 'A', 'S',}, /* 3f  63 axis accel sum           F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'X', 'R', 'A', 'C',}, /* 40  64 axis accel counter       F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'X', 'L', 'D', 'S',}, /* 41  65 axis distance            F_XAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'X', 'L', 'M', 'D',}, /* 42  66 jog maximum distance     F_XAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'X', 'R', 'D', 'S',}, /* 43  67 read axis distance       F_XAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'X', 'R', 'A', 'S',}, /* 44  68 read accel steps         F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'X', 'L', 'L', 'C',}, /* 45  69 axis location            F_XAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'X', 'R', 'L', 'C',}, /* 46  70 read axis location       F_XAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'X', 'L', 'D', 'R',}, /* 47  71 axis dro                 F_XAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'X', 'L', 'D', 'E',}, /* 48  72 axis dro end             F_XAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'X', 'L', 'D', 'L',}, /* 49  73 axis dro decel limit     F_XAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'X', 'R', 'D', 'R',}, /* 4a  74 read axis dro            F_XAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'S', 'L', 'C', 'T',}, /* 4b  75 spindle control reg      F_Spindle_Base, F_Ld_Sp_Ctl */
 {'S', 'L', 'F', 'R',}, /* 4c  76 freq for step spindle    F_Spindle_Base, F_Ld_Sp_Freq */
 {'S', 'J', 'C', 'T',}, /* 4d  77 jog control              F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Ctl */
 {'S', 'J', 'I', 'N',}, /* 4e  78 jog increment            F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Inc */
 {'S', 'J', 'J', 'B',}, /* 4f  79 jog backlash increment   F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Back */
 {'S', 'L', 'I', 'S',}, /* 50  80 axis initial sum         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_D */
 {'S', 'L', 'I', '1',}, /* 51  81 axis incr1               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr1 */
 {'S', 'L', 'I', '2',}, /* 52  82 axis incr2               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr2 */
 {'S', 'L', 'A', 'V',}, /* 53  83 axis accel value         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Val */
 {'S', 'L', 'A', 'C',}, /* 54  84 axis accel count         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Count */
 {'S', 'R', 'X', ' ',}, /* 55  85 axis x pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_XPos */
 {'S', 'R', 'Y', ' ',}, /* 56  86 axis y pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_YPos */
 {'S', 'R', 'S', 'U',}, /* 57  87 axis sum                 F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Sum */
 {'S', 'R', 'A', 'S',}, /* 58  88 axis accel sum           F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Sum */
 {'S', 'R', 'A', 'C',}, /* 59  89 axis accel counter       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Ctr */
 {'S', 'L', 'D', 'S',}, /* 5a  90 axis distance            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dist */
 {'S', 'L', 'M', 'D',}, /* 5b  91 jog maximum distance     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Max_Dist */
 {'S', 'R', 'D', 'S',}, /* 5c  92 read axis distance       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dist */
 {'S', 'R', 'A', 'S',}, /* 5d  93 read accel steps         F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Steps */
 {'S', 'L', 'L', 'C',}, /* 5e  94 axis location            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Loc */
 {'S', 'R', 'L', 'C',}, /* 5f  95 read axis location       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Loc */
 {'S', 'L', 'D', 'R',}, /* 60  96 axis dro                 F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro */
 {'S', 'L', 'D', 'E',}, /* 61  97 axis dro end             F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_End */
 {'S', 'L', 'D', 'L',}, /* 62  98 axis dro decel limit     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_Limit */
 {'S', 'R', 'D', 'R',}, /* 63  99 read axis dro            F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dro */
};
