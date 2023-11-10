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
 {'L', 'D', 'S', 'P',}, /* 08   8 display reg              F_Ld_Dsp_Reg */
 {'C', 'L', 'C', 'D',}, /* 09   9 load controller data     F_Ctrl_Base, F_Ld_Ctrl_Data */
 {'C', 'C', 'M', 'D',}, /* 0a  10 controller command       F_Ctrl_Base, F_Ctrl_Cmd */
 {'C', 'L', 'S', 'Q',}, /* 0b  11 load sequence            F_Ctrl_Base, F_Ld_Seq */
 {'C', 'R', 'S', 'Q',}, /* 0c  12 read sequence            F_Ctrl_Base, F_Rd_Seq */
 {'C', 'R', 'C', 'T',}, /* 0d  13 read counter             F_Ctrl_Base, F_Rd_Ctr */
 {'R', 'L', 'D', 'R',}, /* 0e  14 load reader data         F_Read_Base, F_Ld_Read_Data */
 {'R', 'R', 'D', ' ',}, /* 0f  15 read data                F_Read_Base, F_Read */
 {'D', 'D', 'B', 'F',}, /* 10  16 debug frequency          F_Dbg_Freq_Base, F_Ld_Dbg_Freq */
 {'D', 'D', 'B', 'C',}, /* 11  17 debug count              F_Dbg_Freq_Base, F_Ld_Dbg_Count */
 {'R', 'I', 'D', 'X',}, /* 12  18 clocks per index         F_Rd_Idx_Clks */
 {'P', 'M', 'A', 'X',}, /* 13  19 pwm counter maximum      F_PWM_Base, F_Ld_PWM_Max */
 {'P', 'T', 'R', 'G',}, /* 13  19 pwm trigger              F_PWM_Base, F_Ld_PWM_Trig */
 {'E', 'L', 'E', 'C',}, /* 15  21 load encoder cycle       F_Enc_Base, F_Ld_Enc_Cycle */
 {'E', 'L', 'I', 'C',}, /* 16  22 load internal cycle      F_Enc_Base, F_Ld_Int_Cycle */
 {'E', 'R', 'C', 'C',}, /* 17  23 read cmp cycle clocks    F_Enc_Base, F_Rd_Cmp_Cyc_C */
 {'H', 'L', 'L', 'N',}, /* 18  24 phase length             F_Phase_Base, F_Ld_Phase_Len */
 {'H', 'R', 'S', 'Y',}, /* 19  25 read phase at sync pulse F_Phase_Base, F_Rd_Phase_Syn */
 {'Z', 'R', 'A', 'S',}, /* 1a  26 read axis status         F_ZAxis_Base, F_Rd_Axis_Status */
 {'Z', 'L', 'A', 'C',}, /* 1b  27 set axis control reg     F_ZAxis_Base, F_Ld_Axis_Ctl */
 {'Z', 'R', 'A', 'C',}, /* 1c  28 read axis control reg    F_ZAxis_Base, F_Rd_Axis_Ctl */
 {'Z', 'L', 'F', 'R',}, /* 1d  29 frequency                F_ZAxis_Base, F_Ld_Freq */
 {'Z', 'L', 'I', 'S',}, /* 1e  30 axis initial sum         F_ZAxis_Base, F_Sync_Base, F_Ld_D */
 {'Z', 'L', 'I', '1',}, /* 1f  31 axis incr1               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'Z', 'L', 'I', '2',}, /* 20  32 axis incr2               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'Z', 'L', 'A', 'V',}, /* 21  33 axis accel value         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'Z', 'L', 'A', 'C',}, /* 22  34 axis accel count         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'Z', 'R', 'X', ' ',}, /* 23  35 axis x pos               F_ZAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'Z', 'R', 'Y', ' ',}, /* 24  36 axis y pos               F_ZAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'Z', 'R', 'S', 'U',}, /* 25  37 axis sum                 F_ZAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'Z', 'R', 'A', 'S',}, /* 26  38 axis accel sum           F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'Z', 'R', 'A', 'C',}, /* 27  39 axis accel counter       F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'Z', 'L', 'D', 'S',}, /* 28  40 axis distance            F_ZAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'Z', 'L', 'M', 'D',}, /* 29  41 jog maximum distance     F_ZAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'Z', 'L', 'B', ' ',}, /* 2a  42 jog backlash             F_ZAxis_Base, F_Sync_Base, F_Ld_Backlash */
 {'Z', 'R', 'D', 'S',}, /* 2b  43 read axis distance       F_ZAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'Z', 'R', 'A', 'S',}, /* 2c  44 read accel steps         F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'Z', 'L', 'L', 'C',}, /* 2d  45 axis location            F_ZAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'Z', 'R', 'L', 'C',}, /* 2e  46 read axis location       F_ZAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'Z', 'L', 'M', 'D',}, /* 2f  47 Mpg delta values         F_ZAxis_Base, F_Sync_Base, F_Ld_Mpg_Delta */
 {'Z', 'L', 'M', 'S',}, /* 30  48 Mpg dist values          F_ZAxis_Base, F_Sync_Base, F_Ld_Mpg_Dist */
 {'Z', 'L', 'M', 'V',}, /* 31  49 Mpg div values           F_ZAxis_Base, F_Sync_Base, F_Ld_Mpg_Div */
 {'Z', 'L', 'D', 'R',}, /* 32  50 axis dro                 F_ZAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'Z', 'L', 'D', 'E',}, /* 33  51 axis dro end             F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'Z', 'L', 'D', 'L',}, /* 34  52 axis dro decel limit     F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'Z', 'R', 'D', 'R',}, /* 35  53 read axis dro            F_ZAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'X', 'R', 'A', 'S',}, /* 36  54 read axis status         F_XAxis_Base, F_Rd_Axis_Status */
 {'X', 'L', 'A', 'C',}, /* 37  55 set axis control reg     F_XAxis_Base, F_Ld_Axis_Ctl */
 {'X', 'R', 'A', 'C',}, /* 38  56 read axis control reg    F_XAxis_Base, F_Rd_Axis_Ctl */
 {'X', 'L', 'F', 'R',}, /* 39  57 frequency                F_XAxis_Base, F_Ld_Freq */
 {'X', 'L', 'I', 'S',}, /* 3a  58 axis initial sum         F_XAxis_Base, F_Sync_Base, F_Ld_D */
 {'X', 'L', 'I', '1',}, /* 3b  59 axis incr1               F_XAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'X', 'L', 'I', '2',}, /* 3c  60 axis incr2               F_XAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'X', 'L', 'A', 'V',}, /* 3d  61 axis accel value         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'X', 'L', 'A', 'C',}, /* 3e  62 axis accel count         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'X', 'R', 'X', ' ',}, /* 3f  63 axis x pos               F_XAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'X', 'R', 'Y', ' ',}, /* 40  64 axis y pos               F_XAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'X', 'R', 'S', 'U',}, /* 41  65 axis sum                 F_XAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'X', 'R', 'A', 'S',}, /* 42  66 axis accel sum           F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'X', 'R', 'A', 'C',}, /* 43  67 axis accel counter       F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'X', 'L', 'D', 'S',}, /* 44  68 axis distance            F_XAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'X', 'L', 'M', 'D',}, /* 45  69 jog maximum distance     F_XAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'X', 'L', 'B', ' ',}, /* 46  70 jog backlash             F_XAxis_Base, F_Sync_Base, F_Ld_Backlash */
 {'X', 'R', 'D', 'S',}, /* 47  71 read axis distance       F_XAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'X', 'R', 'A', 'S',}, /* 48  72 read accel steps         F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'X', 'L', 'L', 'C',}, /* 49  73 axis location            F_XAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'X', 'R', 'L', 'C',}, /* 4a  74 read axis location       F_XAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'X', 'L', 'M', 'D',}, /* 4b  75 Mpg delta values         F_XAxis_Base, F_Sync_Base, F_Ld_Mpg_Delta */
 {'X', 'L', 'M', 'S',}, /* 4c  76 Mpg dist values          F_XAxis_Base, F_Sync_Base, F_Ld_Mpg_Dist */
 {'X', 'L', 'M', 'V',}, /* 4d  77 Mpg div values           F_XAxis_Base, F_Sync_Base, F_Ld_Mpg_Div */
 {'X', 'L', 'D', 'R',}, /* 4e  78 axis dro                 F_XAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'X', 'L', 'D', 'E',}, /* 4f  79 axis dro end             F_XAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'X', 'L', 'D', 'L',}, /* 50  80 axis dro decel limit     F_XAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'X', 'R', 'D', 'R',}, /* 51  81 read axis dro            F_XAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'S', 'L', 'C', 'T',}, /* 52  82 spindle control reg      F_Spindle_Base, F_Ld_Sp_Ctl */
 {'S', 'L', 'F', 'R',}, /* 53  83 freq for step spindle    F_Spindle_Base, F_Ld_Sp_Freq */
 {'S', 'J', 'C', 'T',}, /* 54  84 jog control              F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Ctl */
 {'S', 'J', 'I', 'N',}, /* 55  85 jog increment            F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Inc */
 {'S', 'J', 'J', 'B',}, /* 56  86 jog backlash increment   F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Back */
 {'S', 'L', 'I', 'S',}, /* 57  87 axis initial sum         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_D */
 {'S', 'L', 'I', '1',}, /* 58  88 axis incr1               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr1 */
 {'S', 'L', 'I', '2',}, /* 59  89 axis incr2               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr2 */
 {'S', 'L', 'A', 'V',}, /* 5a  90 axis accel value         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Val */
 {'S', 'L', 'A', 'C',}, /* 5b  91 axis accel count         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Count */
 {'S', 'R', 'X', ' ',}, /* 5c  92 axis x pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_XPos */
 {'S', 'R', 'Y', ' ',}, /* 5d  93 axis y pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_YPos */
 {'S', 'R', 'S', 'U',}, /* 5e  94 axis sum                 F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Sum */
 {'S', 'R', 'A', 'S',}, /* 5f  95 axis accel sum           F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Sum */
 {'S', 'R', 'A', 'C',}, /* 60  96 axis accel counter       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Ctr */
 {'S', 'L', 'D', 'S',}, /* 61  97 axis distance            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dist */
 {'S', 'L', 'M', 'D',}, /* 62  98 jog maximum distance     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Max_Dist */
 {'S', 'L', 'B', ' ',}, /* 63  99 jog backlash             F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Backlash */
 {'S', 'R', 'D', 'S',}, /* 64 100 read axis distance       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dist */
 {'S', 'R', 'A', 'S',}, /* 65 101 read accel steps         F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Steps */
 {'S', 'L', 'L', 'C',}, /* 66 102 axis location            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Loc */
 {'S', 'R', 'L', 'C',}, /* 67 103 read axis location       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Loc */
 {'S', 'L', 'M', 'D',}, /* 68 104 Mpg delta values         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Mpg_Delta */
 {'S', 'L', 'M', 'S',}, /* 69 105 Mpg dist values          F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Mpg_Dist */
 {'S', 'L', 'M', 'V',}, /* 6a 106 Mpg div values           F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Mpg_Div */
 {'S', 'L', 'D', 'R',}, /* 6b 107 axis dro                 F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro */
 {'S', 'L', 'D', 'E',}, /* 6c 108 axis dro end             F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_End */
 {'S', 'L', 'D', 'L',}, /* 6d 109 axis dro decel limit     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_Limit */
 {'S', 'R', 'D', 'R',}, /* 6e 110 read axis dro            F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dro */
};
