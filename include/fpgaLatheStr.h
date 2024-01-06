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
 {'D', 'D', 'B', 'C',}, /* 09   9 debug clock count        F_Dbg_Freq_Base, F_Ld_Dbg_Count */
 {'D', 'D', 'B', 'S',}, /* 0a  10 debug sync length        F_Dbg_Freq_Base, F_Ld_Sync_Count */
 {'R', 'I', 'D', 'X',}, /* 0b  11 clocks per index         F_Rd_Idx_Clks */
 {'P', 'M', 'A', 'X',}, /* 0c  12 pwm counter maximum      F_PWM_Base, F_Ld_PWM_Max */
 {'P', 'T', 'R', 'G',}, /* 0d  13 pwm trigger              F_PWM_Base, F_Ld_PWM_Trig */
 {'E', 'E', 'P', 'S',}, /* 0e  14 load encoder prescale    F_Enc_Base, F_Ld_Enc_Prescale */
 {'E', 'L', 'E', 'C',}, /* 0f  15 load encoder cycle       F_Enc_Base, F_Ld_Enc_Cycle */
 {'E', 'L', 'I', 'C',}, /* 10  16 load internal cycle      F_Enc_Base, F_Ld_Int_Cycle */
 {'E', 'R', 'C', 'C',}, /* 11  17 read cmp cycle clocks    F_Enc_Base, F_Rd_Cmp_Cyc_Clks */
 {'H', 'L', 'L', 'N',}, /* 12  18 phase length             F_Phase_Base, F_Ld_Phase_Len */
 {'H', 'R', 'S', 'Y',}, /* 13  19 read phase at sync pulse F_Phase_Base, F_Rd_Phase_Syn */
 {'R', 'C', 'T', 'L',}, /* 14  20 runout control reg       F_RunOut_Base, F_Ld_RunOut_Ctl */
 {'R', 'L', 'I', 'M',}, /* 15  21 runout limit             F_RunOut_Base, F_Ld_Run_Limit */
 {'Z', 'R', 'A', 'S',}, /* 16  22 read axis status         F_ZAxis_Base, F_Rd_Axis_Status */
 {'Z', 'L', 'A', 'C',}, /* 17  23 set axis control reg     F_ZAxis_Base, F_Ld_Axis_Ctl */
 {'Z', 'R', 'A', 'C',}, /* 18  24 read axis control reg    F_ZAxis_Base, F_Rd_Axis_Ctl */
 {'Z', 'L', 'F', 'R',}, /* 19  25 frequency                F_ZAxis_Base, F_Ld_Freq */
 {'Z', 'L', 'I', 'S',}, /* 1a  26 axis initial sum         F_ZAxis_Base, F_Sync_Base, F_Ld_D */
 {'Z', 'L', 'I', '1',}, /* 1b  27 axis incr1               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'Z', 'L', 'I', '2',}, /* 1c  28 axis incr2               F_ZAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'Z', 'L', 'A', 'V',}, /* 1d  29 axis accel value         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'Z', 'L', 'A', 'C',}, /* 1e  30 axis accel count         F_ZAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'Z', 'R', 'X', ' ',}, /* 1f  31 axis x pos               F_ZAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'Z', 'R', 'Y', ' ',}, /* 20  32 axis y pos               F_ZAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'Z', 'R', 'S', 'U',}, /* 21  33 axis sum                 F_ZAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'Z', 'R', 'A', 'S',}, /* 22  34 axis accel sum           F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'Z', 'R', 'A', 'C',}, /* 23  35 axis accel counter       F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'Z', 'L', 'D', 'S',}, /* 24  36 axis distance            F_ZAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'Z', 'L', 'M', 'D',}, /* 25  37 jog maximum distance     F_ZAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'Z', 'R', 'D', 'S',}, /* 26  38 read axis distance       F_ZAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'Z', 'R', 'A', 'S',}, /* 27  39 read accel steps         F_ZAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'Z', 'L', 'L', 'C',}, /* 28  40 axis location            F_ZAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'Z', 'R', 'L', 'C',}, /* 29  41 read axis location       F_ZAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'Z', 'L', 'D', 'R',}, /* 2a  42 axis dro                 F_ZAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'Z', 'L', 'D', 'E',}, /* 2b  43 axis dro end             F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'Z', 'L', 'D', 'L',}, /* 2c  44 axis dro decel limit     F_ZAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'Z', 'R', 'D', 'R',}, /* 2d  45 read axis dro            F_ZAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'X', 'R', 'A', 'S',}, /* 2e  46 read axis status         F_XAxis_Base, F_Rd_Axis_Status */
 {'X', 'L', 'A', 'C',}, /* 2f  47 set axis control reg     F_XAxis_Base, F_Ld_Axis_Ctl */
 {'X', 'R', 'A', 'C',}, /* 30  48 read axis control reg    F_XAxis_Base, F_Rd_Axis_Ctl */
 {'X', 'L', 'F', 'R',}, /* 31  49 frequency                F_XAxis_Base, F_Ld_Freq */
 {'X', 'L', 'I', 'S',}, /* 32  50 axis initial sum         F_XAxis_Base, F_Sync_Base, F_Ld_D */
 {'X', 'L', 'I', '1',}, /* 33  51 axis incr1               F_XAxis_Base, F_Sync_Base, F_Ld_Incr1 */
 {'X', 'L', 'I', '2',}, /* 34  52 axis incr2               F_XAxis_Base, F_Sync_Base, F_Ld_Incr2 */
 {'X', 'L', 'A', 'V',}, /* 35  53 axis accel value         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Val */
 {'X', 'L', 'A', 'C',}, /* 36  54 axis accel count         F_XAxis_Base, F_Sync_Base, F_Ld_Accel_Count */
 {'X', 'R', 'X', ' ',}, /* 37  55 axis x pos               F_XAxis_Base, F_Sync_Base, F_Rd_XPos */
 {'X', 'R', 'Y', ' ',}, /* 38  56 axis y pos               F_XAxis_Base, F_Sync_Base, F_Rd_YPos */
 {'X', 'R', 'S', 'U',}, /* 39  57 axis sum                 F_XAxis_Base, F_Sync_Base, F_Rd_Sum */
 {'X', 'R', 'A', 'S',}, /* 3a  58 axis accel sum           F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Sum */
 {'X', 'R', 'A', 'C',}, /* 3b  59 axis accel counter       F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Ctr */
 {'X', 'L', 'D', 'S',}, /* 3c  60 axis distance            F_XAxis_Base, F_Sync_Base, F_Ld_Dist */
 {'X', 'L', 'M', 'D',}, /* 3d  61 jog maximum distance     F_XAxis_Base, F_Sync_Base, F_Ld_Max_Dist */
 {'X', 'R', 'D', 'S',}, /* 3e  62 read axis distance       F_XAxis_Base, F_Sync_Base, F_Rd_Dist */
 {'X', 'R', 'A', 'S',}, /* 3f  63 read accel steps         F_XAxis_Base, F_Sync_Base, F_Rd_Accel_Steps */
 {'X', 'L', 'L', 'C',}, /* 40  64 axis location            F_XAxis_Base, F_Sync_Base, F_Ld_Loc */
 {'X', 'R', 'L', 'C',}, /* 41  65 read axis location       F_XAxis_Base, F_Sync_Base, F_Rd_Loc */
 {'X', 'L', 'D', 'R',}, /* 42  66 axis dro                 F_XAxis_Base, F_Sync_Base, F_Ld_Dro */
 {'X', 'L', 'D', 'E',}, /* 43  67 axis dro end             F_XAxis_Base, F_Sync_Base, F_Ld_Dro_End */
 {'X', 'L', 'D', 'L',}, /* 44  68 axis dro decel limit     F_XAxis_Base, F_Sync_Base, F_Ld_Dro_Limit */
 {'X', 'R', 'D', 'R',}, /* 45  69 read axis dro            F_XAxis_Base, F_Sync_Base, F_Rd_Dro */
 {'S', 'L', 'C', 'T',}, /* 46  70 spindle control reg      F_Spindle_Base, F_Ld_Sp_Ctl */
 {'S', 'L', 'F', 'R',}, /* 47  71 freq for step spindle    F_Spindle_Base, F_Ld_Sp_Freq */
 {'S', 'J', 'C', 'T',}, /* 48  72 jog control              F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Ctl */
 {'S', 'J', 'I', 'N',}, /* 49  73 jog increment            F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Inc */
 {'S', 'J', 'J', 'B',}, /* 4a  74 jog backlash increment   F_Spindle_Base, F_Sp_Jog_Base, F_Ld_Jog_Back */
 {'S', 'L', 'I', 'S',}, /* 4b  75 axis initial sum         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_D */
 {'S', 'L', 'I', '1',}, /* 4c  76 axis incr1               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr1 */
 {'S', 'L', 'I', '2',}, /* 4d  77 axis incr2               F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Incr2 */
 {'S', 'L', 'A', 'V',}, /* 4e  78 axis accel value         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Val */
 {'S', 'L', 'A', 'C',}, /* 4f  79 axis accel count         F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Accel_Count */
 {'S', 'R', 'X', ' ',}, /* 50  80 axis x pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_XPos */
 {'S', 'R', 'Y', ' ',}, /* 51  81 axis y pos               F_Spindle_Base, F_Sp_Sync_Base, F_Rd_YPos */
 {'S', 'R', 'S', 'U',}, /* 52  82 axis sum                 F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Sum */
 {'S', 'R', 'A', 'S',}, /* 53  83 axis accel sum           F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Sum */
 {'S', 'R', 'A', 'C',}, /* 54  84 axis accel counter       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Ctr */
 {'S', 'L', 'D', 'S',}, /* 55  85 axis distance            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dist */
 {'S', 'L', 'M', 'D',}, /* 56  86 jog maximum distance     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Max_Dist */
 {'S', 'R', 'D', 'S',}, /* 57  87 read axis distance       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dist */
 {'S', 'R', 'A', 'S',}, /* 58  88 read accel steps         F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Accel_Steps */
 {'S', 'L', 'L', 'C',}, /* 59  89 axis location            F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Loc */
 {'S', 'R', 'L', 'C',}, /* 5a  90 read axis location       F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Loc */
 {'S', 'L', 'D', 'R',}, /* 5b  91 axis dro                 F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro */
 {'S', 'L', 'D', 'E',}, /* 5c  92 axis dro end             F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_End */
 {'S', 'L', 'D', 'L',}, /* 5d  93 axis dro decel limit     F_Spindle_Base, F_Sp_Sync_Base, F_Ld_Dro_Limit */
 {'S', 'R', 'D', 'R',}, /* 5e  94 read axis dro            F_Spindle_Base, F_Sp_Sync_Base, F_Rd_Dro */
};
