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
 {'E', 'E', 'P', 'S',}, /* 0d  13 load encoder prescale    F_Enc_Base, F_Ld_Enc_Prescale */
 {'E', 'L', 'E', 'C',}, /* 0e  14 load encoder cycle       F_Enc_Base, F_Ld_Enc_Cycle */
 {'E', 'L', 'I', 'C',}, /* 0f  15 load internal cycle      F_Enc_Base, F_Ld_Int_Cycle */
 {'E', 'R', 'C', 'C',}, /* 10  16 read cmp cycle clocks    F_Enc_Base, F_Rd_Cmp_Cyc_Clks */
 {'H', 'L', 'L', 'N',}, /* 11  17 phase length             F_Phase_Base, F_Ld_Phase_Len */
 {'H', 'R', 'S', 'Y',}, /* 12  18 read phase at sync pulse F_Phase_Base, F_Rd_Phase_Syn */
 {'R', 'C', 'T', 'L',}, /* 13  19 runout control reg       F_RunOut_Base, F_Ld_RunOut_Ctl */
 {'R', 'L', 'I', 'M',}, /* 14  20 runout limit             F_RunOut_Base, F_Ld_Run_Limit */
 {'Z', 'R', 'A', 'S',}, /* 15  21 read axis status         F_ZAxis_Base, F_Rd_Axis_Status */
 {'Z', 'L', 'A', 'C',}, /* 16  22 set axis control reg     F_ZAxis_Base, F_Ld_Axis_Ctl */
 {'Z', 'R', 'A', 'C',}, /* 17  23 read axis control reg    F_ZAxis_Base, F_Rd_Axis_Ctl */
 {'Z', 'L', 'F', 'R',}, /* 18  24 frequency                F_ZAxis_Base, F_Ld_Freq */
 {'Z', 'L', 'I', 'S',}, /* 19  25 axis initial sum         F_ZAxis_Base, F_Sync_Base, F_Ld_D */
 {'Z', 'L', 'I', '1',}, /* 1a  26 axis incr1               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'Z', 'L', 'I', '2',}, /* 1b  27 axis incr2               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'Z', 'L', 'A', 'V',}, /* 1c  28 axis accel value         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'Z', 'L', 'A', 'C',}, /* 1d  29 axis accel count         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'Z', 'R', 'X', ' ',}, /* 1e  30 axis x pos               F_ZAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'Z', 'R', 'Y', ' ',}, /* 1f  31 axis y pos               F_ZAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'Z', 'R', 'S', 'U',}, /* 20  32 axis sum                 F_ZAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'Z', 'R', 'A', 'S',}, /* 21  33 axis accel sum           F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'Z', 'R', 'A', 'C',}, /* 22  34 axis accel counter       F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'Z', 'L', 'D', 'S',}, /* 23  35 axis distance            F_ZAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'Z', 'L', 'M', 'D',}, /* 24  36 jog maximum distance     F_ZAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'Z', 'R', 'D', 'S',}, /* 25  37 read axis distance       F_ZAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'Z', 'R', 'A', 'S',}, /* 26  38 read accel steps         F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'Z', 'L', 'L', 'C',}, /* 27  39 axis location            F_ZAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'Z', 'R', 'L', 'C',}, /* 28  40 read axis location       F_ZAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'Z', 'L', 'D', 'R',}, /* 29  41 axis dro                 F_ZAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'Z', 'L', 'D', 'E',}, /* 2a  42 axis dro end             F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'Z', 'L', 'D', 'L',}, /* 2b  43 axis dro decel limit     F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'Z', 'R', 'D', 'R',}, /* 2c  44 read axis dro            F_ZAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'X', 'R', 'A', 'S',}, /* 2d  45 read axis status         F_XAxis_Base, F_Rd_Axis_Status */
 {'X', 'L', 'A', 'C',}, /* 2e  46 set axis control reg     F_XAxis_Base, F_Ld_Axis_Ctl */
 {'X', 'R', 'A', 'C',}, /* 2f  47 read axis control reg    F_XAxis_Base, F_Rd_Axis_Ctl */
 {'X', 'L', 'F', 'R',}, /* 30  48 frequency                F_XAxis_Base, F_Ld_Freq */
 {'X', 'L', 'I', 'S',}, /* 31  49 axis initial sum         F_XAxis_Base, F_Sync_Base, F_Ld_D */
 {'X', 'L', 'I', '1',}, /* 32  50 axis incr1               F_XAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'X', 'L', 'I', '2',}, /* 33  51 axis incr2               F_XAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'X', 'L', 'A', 'V',}, /* 34  52 axis accel value         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'X', 'L', 'A', 'C',}, /* 35  53 axis accel count         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'X', 'R', 'X', ' ',}, /* 36  54 axis x pos               F_XAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'X', 'R', 'Y', ' ',}, /* 37  55 axis y pos               F_XAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'X', 'R', 'S', 'U',}, /* 38  56 axis sum                 F_XAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'X', 'R', 'A', 'S',}, /* 39  57 axis accel sum           F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'X', 'R', 'A', 'C',}, /* 3a  58 axis accel counter       F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'X', 'L', 'D', 'S',}, /* 3b  59 axis distance            F_XAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'X', 'L', 'M', 'D',}, /* 3c  60 jog maximum distance     F_XAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'X', 'R', 'D', 'S',}, /* 3d  61 read axis distance       F_XAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'X', 'R', 'A', 'S',}, /* 3e  62 read accel steps         F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'X', 'L', 'L', 'C',}, /* 3f  63 axis location            F_XAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'X', 'R', 'L', 'C',}, /* 40  64 read axis location       F_XAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'X', 'L', 'D', 'R',}, /* 41  65 axis dro                 F_XAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'X', 'L', 'D', 'E',}, /* 42  66 axis dro end             F_XAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'X', 'L', 'D', 'L',}, /* 43  67 axis dro decel limit     F_XAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'X', 'R', 'D', 'R',}, /* 44  68 read axis dro            F_XAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'S', 'L', 'C', 'T',}, /* 45  69 spindle control reg      F_Spindle_Base, F_Ld_Sp_Ctl */
 {'S', 'L', 'F', 'R',}, /* 46  70 freq for step spindle    F_Spindle_Base, F_Ld_Sp_Freq */
 {'S', 'J', 'C', 'T',}, /* 47  71 jog control              F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Ctl */
 {'S', 'J', 'I', 'N',}, /* 48  72 jog increment            F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Inc */
 {'S', 'J', 'J', 'B',}, /* 49  73 jog backlash increment   F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Back */
 {'S', 'L', 'I', 'S',}, /* 4a  74 axis initial sum         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_D */
 {'S', 'L', 'I', '1',}, /* 4b  75 axis incr1               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr1 */
 {'S', 'L', 'I', '2',}, /* 4c  76 axis incr2               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr2 */
 {'S', 'L', 'A', 'V',}, /* 4d  77 axis accel value         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Val */
 {'S', 'L', 'A', 'C',}, /* 4e  78 axis accel count         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Count */
 {'S', 'R', 'X', ' ',}, /* 4f  79 axis x pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_XPos */
 {'S', 'R', 'Y', ' ',}, /* 50  80 axis y pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_YPos */
 {'S', 'R', 'S', 'U',}, /* 51  81 axis sum                 F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Sum */
 {'S', 'R', 'A', 'S',}, /* 52  82 axis accel sum           F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Sum */
 {'S', 'R', 'A', 'C',}, /* 53  83 axis accel counter       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Ctr */
 {'S', 'L', 'D', 'S',}, /* 54  84 axis distance            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dist */
 {'S', 'L', 'M', 'D',}, /* 55  85 jog maximum distance     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Max_Dist */
 {'S', 'R', 'D', 'S',}, /* 56  86 read axis distance       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dist */
 {'S', 'R', 'A', 'S',}, /* 57  87 read accel steps         F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Steps */
 {'S', 'L', 'L', 'C',}, /* 58  88 axis location            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Loc */
 {'S', 'R', 'L', 'C',}, /* 59  89 read axis location       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Loc */
 {'S', 'L', 'D', 'R',}, /* 5a  90 axis dro                 F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro */
 {'S', 'L', 'D', 'E',}, /* 5b  91 axis dro end             F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_End */
 {'S', 'L', 'D', 'L',}, /* 5c  92 axis dro decel limit     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_Limit */
 {'S', 'R', 'D', 'R',}, /* 5d  93 read axis dro            F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dro */
};
