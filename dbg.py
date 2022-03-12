#!/cygdrive/c/Python39/Python.exe

CPP = True

pinList = \
( \
  ("i", "idx", "Index", ""), \
  ("i", "zA", "ZA", ""), \
  ("i", "zB", "ZB", ""), \
  ("i", "xA", "XA", ""), \
  ("i", "xB", "XB", ""), \
  
  ("i", "spEncDir", "ZFLag", ""), \
  ("i", "jogA1", "JogA1", ""), \
  ("i", "jogB1", "JogB1", ""), \
  ("i", "jogA2", "JogA2", ""), \
  ("i", "jogB2", "JogB2", ""), \
  
  ("o", "stpZ", "Step1", ""), \
  ("o", "stpX", "Step2", ""), \
  ("o", "step3", "Step3", ""), \
  ("o", "step4", "Step4", ""), \
  ("o", "step5", "Step5", ""), \
  
  ("o", "dirZ", "Dir1", ""), \
  ("o", "dirX", "Dir2", ""), \
  ("o", "dir3", "Dir3", ""), \
  ("o", "dir4", "Dir4", ""), \
  ("o", "dir5", "Dir5", ""), \
  
  ("o", "pin1", "Pin1", ""), \
  ("o", "pin14", "Pin14", ""), \
  ("o", "pin16", "Pin16", ""), \
  ("o", "pin17", "Pin17", ""), \
  
  ("i", "pin10", "Pin10", ""), \
  ("i", "pin11", "Pin11", ""), \
  ("i", "pin12", "Pin12", ""), \
  ("i", "pin13", "Pin13", ""), \
  ("i", "pin15", "Pin15", ""), \

  ("i", "eStop", "Pin10", ""), \
  ("i", "limit", "Pin11", ""), \
  ("i", "xHome", "Pin12", ""), \

  ("i", "pinA2", "PinA2", ""), \
  ("i", "pinA3", "PinA3", ""), \
  ("i", "pinA4", "PinA4", ""), \
  ("i", "pinA5", "PinA5", ""), \
  ("i", "pinA6", "PinA6", ""), \
  ("i", "pinA7", "PinA7", ""), \
  ("i", "pinA8", "PinA8", ""), \
  ("i", "pinA9", "PinA9", ""), \
  ("i", "pinA10", "PinA10", ""), \
  ("i", "pinA11", "PinA11", ""), \
  ("i", "pinA12", "PinA12", ""), \
  ("i", "pinA13", "PinA13", ""), \
  ("i", "pinA15", "PinA15", ""), \
  
  ("i", "xPosLim", "PinA13", ""), \
  ("i", "xAHome",  "PinA12", ""), \
  ("i", "xNegLim", "PinA11", ""), \

  ("i", "zPosLim", "PinA8", ""), \
  ("i", "zAHome",  "PinA7", ""), \
  ("i", "zNegLim", "PinA6", ""), \

  ("o", "pinA16", "PinA16", ""), \
  ("o", "pinA17", "PinA17", ""), \
  
  ("o", "start", "ZFlag", ""), \
  ("i", "ready", "XFlag", ""), \

  ("i", "xFlagX", "XFlag", ""), \
  ("i", "zFlagX", "ZFlag", ""), \

  ("o", "spFwd", "Pin14", ""), \
  ("o", "spRev", "Pin1", ""), \
  ("o", "chgPump", "Pin17", ""), \

  ("o", "spiSel", "SPI_SEL", ""), \

  ("o", "led1", "Led1", ""), \
  ("o", "led2", "Led2", ""), \
  ("o", "led3", "Led3", ""), \
)

#  ("i", "xHome", "Pin11", ""),

dbgList = \
(\
 ("dbgSpIsr",  "0", "spindle isr time"), \
 ("dbgZIsr",   "1", "z isr time"), \
 ("dbgXIsr",   "2", "x isr time"), \
 ("dbgSpCyc",  "", "spindle cycle counter update"), \
 ("dbgZEnc",   "", "z encoder input"), \
 ("dbgZOut",   "", "z encoder output"), \
 ("dbgXEnc",   "", "x encoder"), \
 ("dbgXOut",   "", "x encoder output"), \

 ("dbgIntC",   "", "toggle on compare input"), \
 ("dbgIntP",   "", "toggle on output pulse"), \
 ("dbgCycle",  "", "toggle on input cycle"), \
 ("dbgCycEnd", "", "end of internal pulse cycle"), \
 ("dbgCapIsr", "", "length of capture isr"), \
 ("dbgIntIsr", "", "length of internal isr"), \

 ("dbgZCyc",   "", "z cycle counter update"), \
 ("dbgXCyc",   "", "x cycle counter update"), \
 ("dbgSpStop", "", "spindle accel and decel"), \
 ("dbgZAccel", "", "z accel and decel"), \
 ("dbgXAccel", "", "x accel and decel"), \
 ("dbgXRem",   "", "x remainder"), \
 ("dbgSpRev",  "", "spindle rev counter"), \
 ("dbgRunout", "", "runout start"), \
 ("dbgZTaper", "", "z taper"), \
 ("dbgXTaper", "", "x taper"), \
 ("dbgSlv",    "", "slave start"), \
 ("dbgS2bIsr", "", "step 2b isr"), \
 ("dbgS3Isr",  "", "step 3 isr"), \
 ("dbgS4Isr",  "", "step 4 isr"), \
 ("dbgS5Isr",  "", "step 5 isr"), \

 ("dbgJogIsr",  "6", "jog isr transition put in queue"), \
 ("dbgJogMPG0", "", "jog idle queue checked"), \
 ("dbgJogMPG1", "", "jog moving all cases"), \
 ("dbgJogMPG2", "", "jog moving isr done start again"), \
 ("dbgJogMPG3", "", "jog moving add to current distance"), \

 ("dbgAxisCtl", "", "axis control"), \

 ("dbgXDro",    "", "x dro isr"), \
 ("dbgXStop",   "", "x stop"), \
 ("dbgXDone",   "", "x done"), \
 ("dbgXUpdDro", "", "x move using dro"), \
 ("dbgXFinalDro","", "x dro final"), \

 ("dbgZDro",    "7", "z dro isr"), \
 ("dbgZStop",   "", "z stop"), \
 ("dbgZDone",   "", "z done"), \

 ("dbgArcUpd",  "", "arc update"), \
 ("dbgArcStep", "", "arc step"), \
 ("dbgEncIsr",  "", "encoder isr"), \
 ("dbgRemCmd",  "", "remote command"), \

 ("dbgZPosErr", "3", "z position error"),\
 ("dbgZJogDir", "4", "jog direction change"),\
 ("dbgMpgBackL","5", "jog backlash"),\
 )
 #("","",""), \

dbgPins = ("0", "1", "2", "3", "4", "5", \
           "6", "7", "8", "9", "10", "11", "12", \
           "A0", "A1", "A2", "A3", "A4", "A5", "A6", \
           "A7", "A8", "A9", "A10", "A11", "A12", "A13")

dbgTrk = "1L1"

dbgTrkList = \
(\
 ("1W0", "spindle position when index pulse"), \
 ("1W1", "x jog encoder"), \
 ("1L0", "rpm"), \
 ("1L1", "mpg"), \
 ("2L0", "x and z timers on spindle cyc ctr max"), \
 ("2L1", "z isr tmr at accel end on sync start"), \
 ("2L2", "spare"), \
 ("2L3", "ext motor index period z clocks step"), \
 ("2WL0", "encoder capature"), \
 ("2WL1", "interal capature"), \
)

if CPP:
    dout = "inline void"
    din = "inline uint16_t"
    empty = " {}"
    emptyIn = " {return(0);}"
    op = "{"
    cl = ";}"
    opIn = "{return("
    clIn = ");}"
else:
    dout = "#define"
    din = "#define"
    empty = ""
    emptyIn = ""
    op = ""
    cl = ""
    opIn = ""
    clIn = ""

def fWrite(f, txt):
    f.write(txt.encode())
    
f = open("include/pinDef.h", "wb")
fWrite(f, "#if defined(__STM32F4xx_HAL_H) || defined(__STM32F7xx_HAL_H) || defined(STM32H7xx_HAL_H)\n")
fWrite(f, "#if !defined(__PINDEF_H)\n")
fWrite(f, "#define __PINDEF_H\n\n")

for (direction, name, pin, comment) in pinList:
    if len(comment) != 0:
        fWrite(f, "/* %s */\n" % (comment))

    if direction == 'o':
        fWrite(f, "#ifdef %s_Pin\n" % (pin))
        fWrite(f, "%s %sSet() %s%s_GPIO_Port->BSRR = %s_Pin%s\n" % \
                (dout, name, op, pin, pin, cl))
        fWrite(f, "%s %sClr() "
                "%s%s_GPIO_Port->BSRR = (%s_Pin << 16)%s\n" % \
                (dout, name, op, pin, pin, cl))
        fWrite(f, "%s %sRead() %s(%s_GPIO_Port->ODR & %s_Pin) != 0%s\n" % \
                (din, name, opIn, pin, pin, clIn))
        fWrite(f, "#else\n")
        fWrite(f, "%s %sSet()%s\n" % (dout, name, empty))
        fWrite(f, "%s %sClr()%s\n" % (dout, name, empty))
        fWrite(f, "%s %s()%s\n" % (din, name, emptyIn))
        fWrite(f, "#endif\n\n")
    elif direction == 'i':
        fWrite(f, "#ifdef %s_Pin\n" % (pin))
        if name != pin:
            fWrite(f, "#define %s_Pin\n" % (name))
        fWrite(f, "%s %s() %s(%s_GPIO_Port->IDR & %s_Pin) != 0%s\n" % \
                (din, name, opIn, pin, pin, clIn))
        fWrite(f, "%s %sIsSet() %s(%s_GPIO_Port->IDR & %s_Pin) != 0%s\n" % \
                (din, name, opIn, pin, pin, clIn))
        fWrite(f, "%s %sIsClr() %s(%s_GPIO_Port->IDR & %s_Pin) == 0%s\n" % \
                (din, name, opIn, pin, pin, clIn))
        fWrite(f, "#else\n")
        fWrite(f, "%s %s()%s\n" % (din, name, emptyIn))
        fWrite(f, "%s %sIsSet()%s\n" % (din, name, emptyIn))
        fWrite(f, "%s %sIsClr()%s\n" % (din, name, emptyIn))
        fWrite(f, "#endif\n\n")
    else:
        print("invalid direction\n");

fWrite(f, "#endif /* __PINDEF_H */\n")
fWrite(f, "#endif /* __STM32F4xx_HAL_H */\n")
f.close()

f = open("include/dbg.h", "wb")
f1 = open("include/dbgPin.h", "wb")

fWrite(f, "#if defined(__STM32F4xx_HAL_H) || defined(__STM32F7xx_HAL_H) || defined(STM32H7xx_HAL_H)\n")
fWrite(f, "#if !defined(__DBG_H)\n")
fWrite(f, "#define __DBG_H\n\n")

for pin in dbgPins:
    if CPP:
        fWrite(f, "constexpr auto DBG%s = 1;\n" % (pin))
    else:
        fWrite(f, "#define DBG%s 1\n" % (pin))
fWrite(f, "\n")

for pin in dbgPins:
    fWrite(f, "#ifdef Dbg%s_Pin\n" % (pin))
    fWrite(f, "%s dbg%sIni()%s\n" % (dout, pin, empty))
    fWrite(f, "%s dbg%sSet() %sDbg%s_GPIO_Port->BSRR = Dbg%s_Pin%s\n" % \
            (dout, pin, op, pin, pin, cl))
    fWrite(f, "%s dbg%sClr() %sDbg%s_GPIO_Port->BSRR = "\
           "(Dbg%s_Pin << 16)%s\n" %\
            (dout, pin, op, pin, pin, cl))
    fWrite(f, "#else\n")
    fWrite(f, "%s dbg%sIni()%s\n" % (dout, pin, empty))
    fWrite(f, "%s dbg%sSet()%s\n" % (dout, pin, empty))
    fWrite(f, "%s dbg%sClr()%s\n" % (dout, pin, empty))
    fWrite(f, "#endif\n\n")
    fWrite(f1, "#ifdef Dbg%s_Pin\n" % (pin))
    fWrite(f1, " PIN(Dbg%s, Dbg%s),\n" % (pin, pin))
    fWrite(f1, "#endif\n")

for (name, pin, comment) in dbgList:
    fWrite(f, "/* %s */\n" % (comment))
    if len(pin) != 0:
        fWrite(f, "#ifdef Dbg%s_Pin\n" % (pin))
        fWrite(f, "%s %sSet() %sDbg%s_GPIO_Port->BSRR = Dbg%s_Pin%s\n" % \
                (dout, name, op, pin, pin, cl))
        fWrite(f, "%s %sClr() "
                "%sDbg%s_GPIO_Port->BSRR = (Dbg%s_Pin << 16)%s\n" % \
                (dout, name, op, pin, pin, cl))
        fWrite(f, "%s %sRead() "\
               "%s(Dbg%s_GPIO_Port->IDR & Dbg%s_Pin) != 0)%s\n" % \
               (din, name, opIn, pin, pin, cl))
        fWrite(f, "#else\n")
        fWrite(f, "%s %sSet()%s\n" % (dout, name, empty))
        fWrite(f, "%s %sClr()%s\n" % (dout, name, empty))
        fWrite(f, "%s %sRead()%s\n" % (din, name, emptyIn))
        fWrite(f, "#endif\n\n")

        fWrite(f1, "#ifdef Dbg%s_Pin\n" % (pin))
        fWrite(f1, " PIN(%s, Dbg%s),\n" % (name, pin))
        fWrite(f1, "#endif\n")
    else:
        fWrite(f, "%s %sSet()%s\n" % (dout, name, empty))
        fWrite(f, "%s %sClr()%s\n" % (dout, name, empty))
        fWrite(f, "%s %sRead()%s\n\n" % (din, name, emptyIn))
fWrite(f, "#endif /* __DBG_H */\n")
fWrite(f, "#endif /* __STM32F4xx_HAL_H */\n")
f.close()
f1.close()

dbgTrkCode = \
(\
 ("1W", ("val1",), ("uint16_t",), \
  "{ \\\n" \
  " int16_t *p = (int16_t *) &trkbuf[trkidx]; \\\n" \
  " *p = val1; \\\n" \
  " trkidx += 1; \\\n" \
  " trkidx &= (TRKBUFSIZE - 1); \\\n" \
  "}\n"), \

 ("1L", ("val1",) , ("uint32_t",), \
  "{ \\\n" \
  " int32_t *p = (int32_t *) &trkbuf[trkidx]; \\\n" \
  " *p = val1; \\\n" \
  " trkidx += 2; \\\n" \
  " trkidx &= (TRKBUFSIZE - 1); \\\n" \
  "}\n"), \

 ("2L", ("val1", "val2"), ("uint32_t", "uint32_t"), \
  "{ \\\n" \
  " int32_t *p = (int32_t *) &trkbuf[trkidx]; \\\n" \
  " *p++ = val1; \\\n" \
  " *p = val2; \\\n" \
  " trkidx += 4; \\\n" \
  " trkidx &= (TRKBUFSIZE - 1); \\\n" \
  "}\n"), \

 ("2WL", ("val1", "val2", "val3",), ("uint16_t", "uint16_t", "uint32_t"), \
  "{ \\\n" \
  " int16_t *p = (int16_t *) &trkbuf[trkidx]; \\\n" \
  " *p++ = val1; \\\n" \
  " *p++ = val2; \\\n" \
  " *((int32_t *) p) = val3; \\\n" \
  " trkidx += 4; \\\n" \
  " trkidx &= (TRKBUFSIZE - 1); \\\n" \
  "}\n"), \
)

f = open("include/dbgtrk.h", "wb")

code = dbgTrk[:-1]

if CPP:
    d0 = "constexpr auto"
    d1 = "inline void"
    eq = " ="
    empty = " {}"
    eol = ";"
else:
    d0 = "#define"
    d1 = "#define"
    eq = ""
    empty = ""
    eol = ""

fWrite(f, "#define DBGTRK 1\n\n")

fWrite(f, "#if DBGTRK\n\n")

for (label, comment) in dbgTrkList:
    define = "%s DBGTRK%s%s %d%s" % (d0, label, eq, label == dbgTrk, eol)
    fWrite(f, "%s/* %s */\n" % (define.ljust(32), comment))

fWrite(f, "\n")

for (label, arg, argType, macro) in dbgTrkCode:
    defined = label == code
    fWrite(f, "%s DBGTRK%s%s %d%s\n" % (d0, label, eq, defined, eol))
    fWrite(f, "%s dbgTrk%s(" % (d1, label))
    first = True
    for i in range(len(arg)):
        if first:
            first = False
        else:
            fWrite(f, ",\n\t")
        if CPP:
            fWrite(f, "%s " % (argType[i]))
        fWrite(f, arg[i])
        if CPP:
            fWrite(f, "  __attribute__((unused))");
    fWrite(f, ")")
    if defined:
        fWrite(f, " \\\n%s\n" % (macro))
    else:
        fWrite(f, "%s\n\n" % (empty))
                
fWrite(f, "#endif /* DBGTRK */\n")
f.close()
