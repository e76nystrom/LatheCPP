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
 {'L', 'S', 'Y', 'N',}, /* 03   3 sync control reg         F_Ld_Sync_Ctl */
 {'L', 'C', 'F', 'G',}, /* 04   4 config control reg       F_Ld_Cfg_Ctl */
 {'L', 'C', 'L', 'K',}, /* 05   5 clock control reg        F_Ld_Clk_Ctl */
 {'L', 'D', 'O', 'U',}, /* 06   6 output reg               F_Ld_Out_Reg */
 {'L', 'D', 'S', 'P',}, /* 07   7 display reg              F_Ld_Dsp_Reg */
 {'D', 'D', 'B', 'F',}, /* 08   8 debug frequency          F_Dbg_Freq_Base, F_Ld_Dbg_Freq */
 {'D', 'D', 'B', 'C',}, /* 09   9 debug count              F_Dbg_Freq_Base, F_Ld_Dbg_Count */
 {'R', 'I', 'D', 'X',}, /* 0a  10 clocks per index         F_Rd_Idx_Clks */
 {'P', 'M', 'A', 'X',}, /* 0b  11 pwm counter maximum      F_PWM_Base, F_Ld_PWM_Max */
 {'P', 'T', 'R', 'G',}, /* 0c  12 pwm trigger              F_PWM_Base, F_Ld_PWM_Trig */
 {'E', 'L', 'E', 'C',}, /* 0d  13 load encoder cycle       F_Enc_Base, F_Ld_Enc_Cycle */
 {'E', 'L', 'I', 'C',}, /* 0e  14 load internal cycle      F_Enc_Base, F_Ld_Int_Cycle */
 {'E', 'R', 'C', 'C',}, /* 0f  15 read cmp cycle clocks    F_Enc_Base, F_Rd_Cmp_Cyc_C */
 {'H', 'L', 'L', 'N',}, /* 10  16 phase length             F_Phase_Base, F_Ld_Phase_Len */
 {'H', 'R', 'S', 'Y',}, /* 11  17 read phase at sync pulse F_Phase_Base, F_Rd_Phase_Syn */
 {'Z', 'R', 'A', 'S',}, /* 12  18 read axis status         F_ZAxis_Base, F_Rd_Axis_Status */
 {'Z', 'L', 'A', 'C',}, /* 13  19 set axis control reg     F_ZAxis_Base, F_Ld_Axis_Ctl */
 {'Z', 'R', 'A', 'C',}, /* 14  20 read axis control reg    F_ZAxis_Base, F_Rd_Axis_Ctl */
 {'Z', 'L', 'F', 'R',}, /* 15  21 frequency                F_ZAxis_Base, F_Ld_Freq */
 {'Z', 'L', 'I', 'S',}, /* 16  22 axis initial sum         F_ZAxis_Base, F_Sync_Base, F_Ld_D */
 {'Z', 'L', 'I', '1',}, /* 17  23 axis incr1               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'Z', 'L', 'I', '2',}, /* 18  24 axis incr2               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'Z', 'L', 'A', 'V',}, /* 19  25 axis accel value         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'Z', 'L', 'A', 'C',}, /* 1a  26 axis accel count         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'Z', 'R', 'X', ' ',}, /* 1b  27 axis x pos               F_ZAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'Z', 'R', 'Y', ' ',}, /* 1c  28 axis y pos               F_ZAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'Z', 'R', 'S', 'U',}, /* 1d  29 axis sum                 F_ZAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'Z', 'R', 'A', 'S',}, /* 1e  30 axis accel sum           F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'Z', 'R', 'A', 'C',}, /* 1f  31 axis accel counter       F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'Z', 'L', 'D', 'S',}, /* 20  32 axis distance            F_ZAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'Z', 'L', 'M', 'D',}, /* 21  33 jog maximum distance     F_ZAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'Z', 'R', 'D', 'S',}, /* 22  34 read axis distance       F_ZAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'Z', 'R', 'A', 'S',}, /* 23  35 read accel steps         F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'Z', 'L', 'L', 'C',}, /* 24  36 axis location            F_ZAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'Z', 'R', 'L', 'C',}, /* 25  37 read axis location       F_ZAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'Z', 'L', 'D', 'R',}, /* 26  38 axis dro                 F_ZAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'Z', 'L', 'D', 'E',}, /* 27  39 axis dro end             F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'Z', 'L', 'D', 'L',}, /* 28  40 axis dro decel limit     F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'Z', 'R', 'D', 'R',}, /* 29  41 read axis dro            F_ZAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'X', 'R', 'A', 'S',}, /* 2a  42 read axis status         F_XAxis_Base, F_Rd_Axis_Status */
 {'X', 'L', 'A', 'C',}, /* 2b  43 set axis control reg     F_XAxis_Base, F_Ld_Axis_Ctl */
 {'X', 'R', 'A', 'C',}, /* 2c  44 read axis control reg    F_XAxis_Base, F_Rd_Axis_Ctl */
 {'X', 'L', 'F', 'R',}, /* 2d  45 frequency                F_XAxis_Base, F_Ld_Freq */
 {'X', 'L', 'I', 'S',}, /* 2e  46 axis initial sum         F_XAxis_Base, F_Sync_Base, F_Ld_D */
 {'X', 'L', 'I', '1',}, /* 2f  47 axis incr1               F_XAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'X', 'L', 'I', '2',}, /* 30  48 axis incr2               F_XAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'X', 'L', 'A', 'V',}, /* 31  49 axis accel value         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'X', 'L', 'A', 'C',}, /* 32  50 axis accel count         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'X', 'R', 'X', ' ',}, /* 33  51 axis x pos               F_XAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'X', 'R', 'Y', ' ',}, /* 34  52 axis y pos               F_XAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'X', 'R', 'S', 'U',}, /* 35  53 axis sum                 F_XAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'X', 'R', 'A', 'S',}, /* 36  54 axis accel sum           F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'X', 'R', 'A', 'C',}, /* 37  55 axis accel counter       F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'X', 'L', 'D', 'S',}, /* 38  56 axis distance            F_XAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'X', 'L', 'M', 'D',}, /* 39  57 jog maximum distance     F_XAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'X', 'R', 'D', 'S',}, /* 3a  58 read axis distance       F_XAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'X', 'R', 'A', 'S',}, /* 3b  59 read accel steps         F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'X', 'L', 'L', 'C',}, /* 3c  60 axis location            F_XAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'X', 'R', 'L', 'C',}, /* 3d  61 read axis location       F_XAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'X', 'L', 'D', 'R',}, /* 3e  62 axis dro                 F_XAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'X', 'L', 'D', 'E',}, /* 3f  63 axis dro end             F_XAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'X', 'L', 'D', 'L',}, /* 40  64 axis dro decel limit     F_XAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'X', 'R', 'D', 'R',}, /* 41  65 read axis dro            F_XAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'S', 'L', 'C', 'T',}, /* 42  66 spindle control reg      F_Spindle_Base, F_Ld_Sp_Ctl */
 {'S', 'L', 'F', 'R',}, /* 43  67 freq for step spindle    F_Spindle_Base, F_Ld_Sp_Freq */
 {'S', 'J', 'C', 'T',}, /* 44  68 jog control              F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Ctl */
 {'S', 'J', 'I', 'N',}, /* 45  69 jog increment            F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Inc */
 {'S', 'J', 'J', 'B',}, /* 46  70 jog backlash increment   F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Back */
 {'S', 'L', 'I', 'S',}, /* 47  71 axis initial sum         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_D */
 {'S', 'L', 'I', '1',}, /* 48  72 axis incr1               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr1 */
 {'S', 'L', 'I', '2',}, /* 49  73 axis incr2               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr2 */
 {'S', 'L', 'A', 'V',}, /* 4a  74 axis accel value         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Val */
 {'S', 'L', 'A', 'C',}, /* 4b  75 axis accel count         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Count */
 {'S', 'R', 'X', ' ',}, /* 4c  76 axis x pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_XPos */
 {'S', 'R', 'Y', ' ',}, /* 4d  77 axis y pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_YPos */
 {'S', 'R', 'S', 'U',}, /* 4e  78 axis sum                 F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Sum */
 {'S', 'R', 'A', 'S',}, /* 4f  79 axis accel sum           F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Sum */
 {'S', 'R', 'A', 'C',}, /* 50  80 axis accel counter       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Ctr */
 {'S', 'L', 'D', 'S',}, /* 51  81 axis distance            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dist */
 {'S', 'L', 'M', 'D',}, /* 52  82 jog maximum distance     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Max_Dist */
 {'S', 'R', 'D', 'S',}, /* 53  83 read axis distance       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dist */
 {'S', 'R', 'A', 'S',}, /* 54  84 read accel steps         F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Steps */
 {'S', 'L', 'L', 'C',}, /* 55  85 axis location            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Loc */
 {'S', 'R', 'L', 'C',}, /* 56  86 read axis location       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Loc */
 {'S', 'L', 'D', 'R',}, /* 57  87 axis dro                 F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro */
 {'S', 'L', 'D', 'E',}, /* 58  88 axis dro end             F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_End */
 {'S', 'L', 'D', 'L',}, /* 59  89 axis dro decel limit     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_Limit */
 {'S', 'R', 'D', 'R',}, /* 5a  90 read axis dro            F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dro */
};
