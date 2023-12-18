#!/cygdrive/c/Python310/Python.exe

import sys
from collections import namedtuple
TmrCfg = namedtuple('TmrCfg', ('name', 'tmr', 'argType', 'pwm',
                               'isr', 'slave'))
CPP = True

CAP = 0x20
PWM_MASK = 0x7

if CPP:
    defOut = "inline void"
    defIn = "inline "
    if False:
        op = "\n{\n "
        cl = ";\n}\n"
    else:
        op = "{"
        cl = ";}"
else:
    define = "#define"
    argType = ""
    op = ""
    cl = ""

constants = \
(\
 ("auto", "SP_FWD", "1"),
 ("auto", "SP_REV", "-1"),
 ("unsigned int", "STEP_WIDTH", "10"),
)

condConstants = \
(\
 ("spindleTmr == 8",
  ( \
    (None, "DIR_SPIN_PORT", "Dir5_GPIO_Port"), \
    ("uint32_t", "DIR_SPIN_BIT", "Dir5_Pin"))), \
 ("spindleTmr == 3",
  ( \
    (None, "DIR_SPIN_PORT", "Dir3_GPIO_Port"), \
    ("uint32_t", "DIR_SPIN_BIT", "Dir3_Pin"))), \
)

macros = \
(\
 (None, "dirSpinFwd", None, None, "DIR_SPIN_PORT->BSRR = spA.dirFwd"),
 (None, "dirSpinRev", None, None, "DIR_SPIN_PORT->BSRR = spA.dirRev"),
 (None, "dirZFwd",    None, None, "Dir1_GPIO_Port->BSRR = zAxis.dirFwd"),
 (None, "dirZRev",    None, None, "Dir1_GPIO_Port->BSRR = zAxis.dirRev"),
 (None, "dirXFwd",    None, None, "Dir2_GPIO_Port->BSRR = xAxis.dirFwd"),
 (None, "dirXRev",    None, None, "Dir2_GPIO_Port->BSRR = xAxis.dirRev"),
 ("uint32_t", "CALC_STEP_WIDTH", "unsigned int", "x", \
  "(rVar.cfgFcy * x) / 1000000l"),
)

regList = \
( \
  ("ClrIE",  None,  "%s->DIER &= ~TIM_IT_UPDATE"),
  ("SetIE",  None,  "%s->DIER |= TIM_IT_UPDATE"),
  ("TstIE",  "is",  "(%s->DIER & TIM_IT_UPDATE) != 0"),
  ("IF",     "is",  "(%s->SR & TIM_FLAG_UPDATE) != 0"),
  ("ClrIF",  None,  "%s->SR = ~TIM_FLAG_UPDATE"),
  ("Start",  None,  "%s->CR1 |= TIM_CR1_CEN"),
  ("Pulse",  None,  "%s->CR1 |= (TIM_CR1_OPM | TIM_CR1_CEN)"),
  ("Stop",   None,  "%s->CR1 &= ~(TIM_CR1_OPM | TIM_CR1_CEN)"),
  ("Scl",    "y",   "%s->PSC = (y)"),
  ("Upd",    None,  "%s->EGR = TIM_EGR_UG"),
  ("Read",   "i",   "%s->CNT"),
  ("CntClr", None,  "%s->CNT = 0"),
  ("Cnt",    "x",   "%s->CNT = (x)"),
  ("Max",    "x",   "%s->ARR = ((x) - 1)"),
  ("Set",    "x",   "%s->ARR = (x)"),
  ("MaxRead", "i",  "%s->ARR"),
)

pwm1List = \
( \
  ("CCR",       "x",  "%s->CCR1 = (x)"),
  ("PWMMode",   None, "%s->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)"),
  ("PWMEna",    "b",  "%s->CCER |= TIM_CCER_CC1E"),
  ("PWMDis",    None, "%s->CCER &= ~TIM_CCER_CC1E"),
  ("ReadCCR",   "i",  "%s->CCR1"),
  ("ReadCCMR", "is", "%s->CCMR1"),
)

pwm2List = \
( \
  ("CCR",       "x",  "%s->CCR2 = (x)"),
  ("PWMMode",   None, "%s->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)"),
  ("PWMEna",    "b",  "%s->CCER |= TIM_CCER_CC2E"),
  ("PWMDis",    None, "%s->CCER &= ~TIM_CCER_CC2E"),
  ("ReadCCR",   "i",  "%s->CCR2"),
  ("ReadCCMR", "is", "%s->CCMR1"),
)

pwm3List = \
( \
  ("CCR",       "x",  "%s->CCR3 = (x)"),
  ("PWMMode",   None, "%s->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)"),
  ("PWMEna",    "b",  "%s->CCER |= TIM_CCER_CC3E"),
  ("PWMDis",    None, "%s->CCER &= ~TIM_CCER_CC3E"),
  ("ReadCCR",   "i",  "%s->CCR3"),
  ("ReadCCMR", "is", "%s->CCMR2"),
)

pwm4List = \
( \
  ("CCR",       "x",  "%s->CCR4 = (x)"),
  ("PWMMode",   None, "%s->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)"),
  ("PWMEna",    "b",  "%s->CCER |= TIM_CCER_CC4E"),
  ("PWMDis",    None, "%s->CCER &= ~TIM_CCER_CC4E"),
  ("ReadCCR",   "i",  "%s->CCR4"),
  ("ReadCCMR", "is", "%s->CCMR2"),
)

capList = \
( \
  ("Cap1EnaSet", None, "%s->CCER |= TIM_CCER_CC1E"), \
  ("Cap1SetIE",  None, "%s->DIER |= TIM_DIER_CC1IE"), \
  ("Cap1ClrIE",  None, "%s->DIER &= ~TIM_DIER_CC1IE"), \
  ("Cap1IF",     "i",  "(%s->SR & TIM_SR_CC1IF) != 0"), \
  ("Cap1ClrIF",  None, "%s->SR &= ~TIM_SR_CC1IF"), \
  ("Cap1",       "i",  "%s->CCR1"), \

  ("Cap2EnaSet", None, "%s->CCER |= TIM_CCER_CC2E"), \
  ("Cap2SetIE",  None, "%s->DIER |= TIM_DIER_CC2IE"), \
  ("Cap2ClrIE",  None, "%s->DIER &= ~TIM_DIER_CC2IE"), \
  ("Cap2IF",     "i",  "(%s->SR & TIM_SR_CC1IF) != 0"), \
  ("Cap2ClrIF",  None, "%s->SR &= ~TIM_SR_CC1IF"), \
  ("Cap2",       "i",  "%s->CCR2"), \

  ("OCP1Clr",    None, "%s->SR &= ~TIM_SR_CC1OF"), \
  ("OCP2Clr",    None, "%s->SR &= ~TIM_SR_CC2OF"), \
)

pwmList = (pwm1List, pwm2List, pwm3List, pwm4List)

def makeConstant(cons):
    (type, name, val) = cons
    if CPP and type is not None:
        fWrite(f, "constexpr %s %s = %s;\n" % (type, name, val))
    else:
        fWrite(f, "#define %s (%s)\n" % (name, val))

def makeMacro(macro, nameLen=None):
    (rtnType, funcName, arg, argType, body) = macro
    if CPP:
        if rtnType is None:
            funcType = "inline void"
        else:
            funcType = "inline %s" % (rtnType)
            body = "return(" + body + ")"
    else:
        funcType = "#define"
    argList = ""
    if arg is not None:
        if CPP:
            argList = arg + " " + argType
        else:
            argList = arg
    call = "%s(%s)" % (funcName, argList)
    if nameLen is not None:
        pass
    else:
        fWrite(f, "%s %s %s%s%s\n" % \
                (funcType, call, op, body, cl))

def timerInit(name, tmr, timer):
    body = (" \\\n\t__HAL_RCC_TIM%d_CLK_ENABLE(); \\\n"
            "\t%s->CR1 |= TIM_CR1_DIR; \\\n"
            "\t%s->CR1 &= ~TIM_CR1_CEN")
    body = body.replace("%d", str(tmr))
    makeFunc(timer, "Init" , None, body)
    fWrite(f, "\n")

def timerStart(name, timer):
    body = (" \\\n\t%s->EGR = TIM_EGR_UG; \\\n"
            "\t%s->CR1 |= TIM_CR1_CEN")
    makeFunc(timer, "Start" , None, body)
    fWrite(f, "\n")

def timerBDTR(name, tmr, timer):
    if tmr == 1 or tmr == 8:
        body = "%s->BDTR |= TIM_BDTR_MOE"
        makeFunc(timer, "BDTR" , None, body)
        fWrite(f, "\n")

def makeFuncList(timer, lst):
    maxLen = 0
    extra = len(name) + 2
    argLen = len(argType) + 2
    for (funcName, arg, body) in lst:
        l = len(funcName) + extra
        if arg == "x" or arg == "y":
            l += argLen
        if l > maxLen:
            maxLen = l
    # print("maxLen %d" % (maxLen))
    for (funcName, arg, body) in lst:
        makeFunc(timer, funcName, arg, body, nameLen=maxLen)
    fWrite(f, "\n")

def makeFunc(timer, funcName, arg, body, nameLen=None):
    argList = ""
    if CPP:
        if arg == "i":
            define = "inline " + argType
        elif arg == "is":
            define = "inline uint16_t"
        else:
            define = "inline void"
            if arg == "x":
                argList = "%s %s" % (argType, arg)
            elif arg == "y":
                argList = "uint16_t %s" % (arg)
            elif arg == "b":
                if timer == "TIM1" or timer == "TIM8":
                    body = name + "BDTR(); " + body
    else:
        define = "#define"
        if arg == "x" or arg =="y":
            argList = arg
    if body is not None:
        body = body.replace("%s", timer)
    else:
        body = ""
    if arg is not None and arg.startswith("i"):
        body = "(" + body + ")"
        if CPP:
            body = "return" + body
    call = "%s%s(%s)" % (name, funcName, argList)
    if nameLen is not None:
        call = call.ljust(nameLen)
        if CPP:
            define = define.ljust(15)
        body = op + body + cl
        if (len(body) + nameLen + 15) >= 80:
            body = "\\\n\t" + body
        fWrite(f, "%s %s %s\n" % (define, call, body))
    else:
        fWrite(f, "%s %s %s%s%s\n" % \
                (define, call, op, body, cl))

def fWrite(file, txt):
    file.write(txt.encode())

def main(board, cfg, path):
    global f
    global name, tmr, argType, pwm, isr, slave

    try:
        f = open("../" + path + "/Inc/timers.h", "wb")
    except FileNotFoundError:
        sys.exit()

    fWrite(f, "#if defined(__STM32F4xx_HAL_H) || "\
           "defined(__STM32F7xx_HAL_H) || defined(STM32H7xx_HAL_H)\n")
    fWrite(f, "#if !defined(__TIMERS_H)\n")
    fWrite(f, "#define __TIMERS_H\n\n")

    setConfig(board, cfg)

    maxLen = 0
    for tmp in cfg:
        parm = tmp[0]
        if len(parm) > maxLen:
            maxLen = len(parm)
    fWrite(f, "/*\n")
    for tmp in cfg:
        parm = tmp[0]
        val = tmp[1]
        fWrite(f, "%s %s\n" % (parm.ljust(maxLen), str(globals()[parm])))
    fWrite(f, "*/\n\n")

    for tmp in cfg:
        val = tmp[1]
        if len(tmp) > 2:
            symbol = tmp[2]
            fWrite(f, "#define %s%s\n" % (symbol, val))
    fWrite(f, "\n")

    triggers()

    for c in constants:
        makeConstant(c)
    fWrite(f, "\n")

    for (test, constantList) in condConstants:
        cond = eval(test)
        if cond:
            for c in constantList:
                makeConstant(c)
            fWrite(f, "\n")

    for m in macros:
        makeMacro(m)
    fWrite(f, "\n")

    for t in timers:
        name = t.name
        tmr = t.tmr
        argType = t.argType
        pwm = t.pwm & PWM_MASK
        isr = t.isr
        slave = t.slave
        if tmr == 0:
            continue

        timer = "TIM%d" % tmr

        fWrite(f, "/* %s timer %d" % (name, tmr))
        if pwm != 0:
            fWrite(f, " pwm %d" % (pwm))
        fWrite(f, " */\n\n")

        fWrite(f, "#define %s %s\n" % \
               (name.upper().replace("TMR", "_TIMER"), tmr))
        fWrite(f, "#define %s %s\n\n" % \
               (name.upper().replace("TMR", "_TMR"), timer))

        if isr != None and len(isr) != 0:
            fWrite(f, "#define %sISR(x) %s_IRQHandler(x)\n\n" % (name, isr))

        timerInit(name, tmr, timer)
        # timerStart(name, timer)
        timerBDTR(name, tmr, timer)

        makeFuncList(timer, regList)
        if pwm != 0:
            fWrite(f, "/* pwm %d */\n\n" % (pwm))
            fWrite(f, "#define %s_PWM %d\n\n" % \
                    (name.upper().replace("TMR", "_TMR"), pwm))
            makeFuncList(timer, pwmList[pwm - 1])

        if (t.pwm & CAP) != 0:
            makeFuncList(timer, capList)

        if slave:
            # print("slave %d spindle %d" % (tmr, spindleTmr))
            for (slv, trig) in slaveTrig:
                # print("slvx %d" % (slv))
                if tmr == slv:
                    for (i, trigTimer) in enumerate(trig):
                        # print("i %d trigTimer %d" % (i, trigTimer))
                        if spindleTmr == trigTimer:
                            body = timer + "->SMCR = ("
                            if (i & 2) != 0:
                                body += "TIM_SMCR_TS_1 | "
                            if (i & 1) != 0:
                                body += "TIM_SMCR_TS_0 | "
                            body += "\\\n"
                            body += "\tTIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)"
                            fWrite(f, "/* timer %d trigger %d */\n\n" % \
                                   (spindleTmr, i))
                            makeFunc(timer, "SlvEna", None, body)
                            body = timer + "->SMCR = 0"
                            makeFunc(timer, "SlvDis", None, body)
                            fWrite(f, "\n")
                            break

    fWrite(f, "#endif /* __TIMERS_H */\n")
    fWrite(f, "#endif /* __STM32F4xx_HAL_H */\n")
    f.close()
    
disc407 = \
( \
  ("board",      "disc407"),
  ("proc",       "STM32F407"),
  ("step1",      2, "STEP1_TIM"),
  ("step1Pwm",   3, "STEP1_PWM"),
  ("step2",      5, "STEP2_TIM"),
  ("step2Pwm",   2, "STEP2_PWM"),
  ("step3",      3, "STEP3_TIM"),
  ("step3Pwm",   1, "STEP3_PWM"),
  ("step4",      4, "STEP4_TIM"),
  ("step4Pwm",   2, "STEP4_PWM"),
  ("usecTmr",    6, "USEC_TMR_TIM"),
  ("encTestTmr", 7,  "ENC_TMR_TIM"),
  ("spindleTmr", 8,  "SPINDLE_TMR"),
  ("spindlePwm", 4,  "SPINDLE_PWM"),
  ("indexTmr",   10, "INDEX_TMR"),
  ("intTmr",     11, "INT_TMR"),
  ("intTmrPwm",  0,  "INT_TMR_PWM"),
  ("cmpTmr",     9,  "CMP_TMR"),
  ("pwmTmr",     12, "PWM_TMR"),
  ("pwmTmrPwm",  1,  "PWM_TMR_PWM"),
  ("step3Isr",   "TIM4"),
  ("step4Isr",   "TIM3"),
  ("spindleIsr", "TIM8_UP_TIM13"),
  ("indexTmrIsr", "TIM1_TRG_COM_TIM10"),
  ("usecTmrIsr", None),
  ("pwmTmrIsr",  "TIM8_BRK_TIM12"),
)

core407 = \
( \
  ("board",      "core407"),
  ("proc",       "STM32F407"),
  ("step1",      2, "STEP1_TIM"),
  ("step1Pwm",   1, "STEP1_PWM"),
  ("step2",      5, "STEP2_TIM"),
  ("step2Pwm",   4, "STEP2_PWM"),
  ("step2B",     1, "STEP2B_TIM"),
  ("step2BPwm",  2, "STEP2B_PWM"),
  ("step3",      4, "STEP3_TIM"),
  ("step3Pwm",   2, "STEP3_PWM"),
  ("step4",      3, "STEP4_TIM"),
  ("step4Pwm",   2, "STEP4_PWM"),
  ("spindleTmr", 8,  "SPINDLE_TMR"),
  ("spindlePwm", 4,  "SPINDLE_PWM"),

  ("usecTmr",    6, "USEC_TMR_TIM"),
  ("encTestTmr", 7,  "ENC_TMR_TIM"),
  ("cmpTmr",     9,  "CMP_TMR"),
  ("indexTmr",   10, "INDEX_TMR"),
  ("intTmr",     11, "INT_TMR"),
  ("intTmrPwm",  0,  "INT_TMR_PWM"),
  ("pwmTmr",     12, "PWM_TMR"),
  ("pwmTmrPwm",  1,  "PWM_TMR_PWM"),

  ("step3Isr",   "TIM4"),
  ("step4Isr",   "TIM3"),
  ("spindleIsr", "TIM8_UP_TIM13"),
  ("indexTmrIsr", "TIM1_TRG_COM_TIM10"),
  ("usecTmrIsr", None),
  ("pwmTmrIsr",  "TIM8_BRK_TIM12"),
)

nuc446 = \
( \
  ("board",      "nuc446"),
  ("proc",       "STM32F446"),
  ("step1",      2, "STEP1_TIM"),
  ("step1Pwm",   1, "STEP1_PWM"),
  ("step2",      5, "STEP2_TIM"),
  ("step2Pwm",   1, "STEP2_PWM"),
  ("step3",      4, "STEP3_TIM"),
  ("step3Pwm",   4, "STEP3_PWM"),
  ("step4",      3, "STEP4_TIM"),
  ("step4Pwm",   3, "STEP4_PWM"),
  ("usecTmr",    6, "USEC_TMR_TIM"),
  ("encTestTmr", 7,  "ENC_TMR_TIM"),
  ("spindleTmr", 8,  "SPINDLE_TMR"),
  ("spindlePwm", 3,  "SPINDLE_PWM"),
  ("indexTmr",   10, "INDEX_TMR"),
  ("intTmr",     11, "INT_TMR"),
  ("intTmrPwm",  0,  "INT_TMR_PWM"),
  ("cmpTmr",     9,  "CMP_TMR"),
  ("pwmTmr",     12, "PWM_TMR"),
  ("pwmTmrPwm",  1,  "PWM_TMR_PWM"),
  ("step3Isr", "TIM4"),
  ("step4Isr", "TIM3"),
  ("spindleIsr", "TIM8_UP_TIM13"),
  ("indexTmrIsr", "TIM1_TRG_COM_TIM10"),
  ("usecTmrIsr", None),
  ("pwmTmrIsr", "TIM8_BRK_TIM12"),
)

nuc401 = \
( \
  ("board",      "nuc401"),
  ("proc",       "STM32F401"),
  ("step1",      2, "STEP1_TIM"),
  ("step1Pwm",   1, "STEP1_PWM"),
  ("step2",      5, "STEP2_TIM"),
  ("step2Pwm",   1, "STEP2_PWM"),
  ("step3",      4, "STEP3_TIM"),
  ("step3Pwm",   4, "STEP3_PWM"),
  ("step4",      1, "STEP4_TIM"),
  ("step4Pwm",   1, "STEP4_PWM"),
  ("usecTmr",    10, "USEC_TMR_TIM"),
  ("encTestTmr", 0,  "ENC_TMR_TIM"),
  ("spindleTmr", 3,  "SPINDLE_TMR"),
  ("spindlePwm", 3,  "SPINDLE_PWM"),
  ("indexTmr",   10, "INDEX_TMR"),
  ("intTmr",     11, "INT_TMR"),
  ("intTmrPwm",  0,  "INT_TMR_PWM"),
  ("cmpTmr",     9,  "CMP_TMR"),
  ("pwmTmr",     10, "PWM_TMR"),
  ("pwmTmrPwm",  1,  "PWM_TMR_PWM"),
  ("step3Isr",   "TIM4"),
  ("step4Isr",   "TIM1"),
  ("spindleIsr", "TIM3"),
  ("indexTmrIsr", "TIM1_TRG_COM_TIM10"),
  ("usecTmrIsr", None),
  ("pwmTmrIsr",  None),
)

nuc746 = \
( \
  ("board",       "nuc746"),
  ("proc",        "STM32F746"),
  ("step1",       2,  "STEP1_TIM"),
  ("step1Pwm",    3,  "STEP1_PWM"),
  ("step2",       5,  "STEP2_TIM"),
  ("step2Pwm",    3,  "STEP2_PWM"),
  ("step3",       3,  "STEP3_TIM"),
  ("step3Pwm",    2,  "STEP3_PWM"),
  ("step4",       4,  "STEP4_TIM"),
  ("step4Pwm",    3,  "STEP4_PWM"),
  ("spindleTmr",  8,  "SPINDLE_TMR"),
  ("spindlePwm",  1,  "SPINDLE_PWM"),

  ("usecTmr",     6,  "USEC_TMR_TIM"),
  ("encTestTmr",  7,  "ENC_TMR_TIM"),
  ("intTmr",      9,  "INT_TMR"),
  ("intTmrPwm",   0,  "INT_TMR_PWM"),
  ("indexTmr",    10, "INDEX_TMR"),
  ("cmpTmr",      11, "CMP_TMR"),
  ("pwmTmr",      12, "PWM_TMR"),
  ("pwmTmrPwm",   2,  "PWM_TMR_PWM"),

  ("step3Isr",    "TIM4"),
  ("step4Isr",    "TIM3"),
  ("cmpTmrIsr",   "TIM1_TRG_COM_TIM11"),
  ("intTmrIsr",   "TIM1_BRK_TIM9"),
  ("spindleIsr",  "TIM8_UP_TIM13"),
  ("indexTmrIsr", "TIM1_TRG_COM_TIM10"),
  ("usecTmrIsr",  None),
  ("pwmTmrIsr",   "TIM8_BRK_TIM12"),
)

nuch743 = \
( \
  ("board",       "nucH743"),
  ("proc",        "STM32H743"),
  ("step1",       2,  "STEP1_TIM"),
  ("step1Pwm",    3,  "STEP1_PWM"),
  ("step2",       5,  "STEP2_TIM"),
  ("step2Pwm",    4,  "STEP2_PWM"),
  ("step3",       3,  "STEP3_TIM"),
  ("step3Pwm",    2,  "STEP3_PWM"),
  ("step4",       4,  "STEP4_TIM"),
  ("step4Pwm",    3,  "STEP4_PWM"),
  ("spindleTmr",  8,  "SPINDLE_TMR"),
  ("spindlePwm",  1,  "SPINDLE_PWM"),

  ("usecTmr",     6,  "USEC_TMR_TIM"),
  ("encTestTmr",  7,  "ENC_TMR_TIM"),
  ("pwmTmr",      12, "PWM_TMR"),
  ("pwmTmrPwm",   2,  "PWM_TMR_PWM"),
  ("intTmr",      15, "INT_TMR"),
  ("intTmrPwm",   0,  "INT_TMR_PWM"),
  ("indexTmr",    16, "INDEX_TMR"),
  ("cmpTmr",      17, "CMP_TMR"),

  ("step3Isr",    "TIM4"),
  ("step4Isr",    "TIM3"),
  ("pwmTmrIsr",   "TIM8_BRK_TIM12"),
  ("spindleIsr",  "TIM8_UP_TIM13"),
  ("intTmrIsr",   "TIM15"),
  ("indexTmrIsr", "TIM16"),
  ("cmpTmrIsr",   "TIM17"),
  ("usecTmrIsr",  None),
)

def triggers():
    global slaveTrig
    if (proc == "STM32F407" or proc == "STM32F446" or \
        proc == "STM32F746" or proc == "STM32H743"):
        slaveTrig = \
        (\
        (2, (1, 8, 3, 4)),
        (3, (1, 2, 5, 4)),
        (4, (1, 2, 3, 8)),
        (5, (2, 3, 4, 8)),
        (1, (5, 2, 3, 4)),
        (8, (1, 2, 4, 5)),
        )
    elif proc == "STM32F401":
        slaveTrig = \
        (\
        (2, (1, 0, 3, 4)),
        (3, (1, 2, 5, 4)),
        (4, (1, 2, 3, 0)),
        (5, (2, 3, 4, 0)),
        (1, (5, 2, 3, 4)),
        )

def setConfig(board, cfg):
    global timers
    for tmp in cfg:
        parm = tmp[0]
        val = tmp[1]
        globals()[parm] = val

    timers = \
    [ \
      TmrCfg("zTmr", step1, "uint32_t", step1Pwm, "TIM2", True),
      TmrCfg("xTmr", step2, "uint32_t", step2Pwm, "TIM5", True),
      TmrCfg("step3Tmr", step3, "uint16_t", step3Pwm, step3Isr, None),
      TmrCfg("step4Tmr", step4, "uint16_t", step4Pwm, step4Isr, None),
      TmrCfg("spindleTmr", spindleTmr, "uint16_t", spindlePwm, \
             spindleIsr, None),
      TmrCfg("pwmTmr", pwmTmr, "uint16_t", pwmTmrPwm, pwmTmrIsr, None),
      TmrCfg("usecTmr", usecTmr, "uint16_t", 0, usecTmrIsr, None),
      TmrCfg("indexTmr", indexTmr, "uint16_t", 0, indexTmrIsr, None),
      TmrCfg("encTestTmr", encTestTmr, "uint16_t", 0, "TIM7", None),
    ]
    if board == "nuch743":
        timers.append(TmrCfg("intTmr", intTmr, "uint16_t", 0, "TIM15", None))
        timers.append(TmrCfg("cmpTmr", cmpTmr, "uint16_t", CAP, "TIM17", None))
    else:
        timers.append(TmrCfg("intTmr", intTmr, "uint16_t", 0, None, None))
        timers.append(TmrCfg("cmpTmr", cmpTmr, "uint16_t", CAP, "TIM1_BRK_TIM9", None))

n = 1
cfg = disc407
path = "LatheCPP"
while True:
    if n >= len(sys.argv):
        break
    board = sys.argv[n]
    if board == "disc407":
        cfg = disc407
        path = "LatheCPP"
    elif board == "core407":
        cfg = core407
        path = "LatheCPPD"
    elif board == "core4071":
        cfg = core407
        path = "LatheCPPD1"
    elif board == "nuc446":
        cfg = nuc446
        path = "LatheCPPN"
    elif board == "nuc401":
        cfg = nuc401
        path = "LatheCPPX0"
    elif board == "nuc746":
        cfg = nuc746
        path = "LatheCPP7N"
    elif board == "nuch743":
        cfg = nuch743
        path = "LatheCPP7H"
    elif board == "nuch723":
        cfg = nuch743
        path = "LatheCPP723"
    n += 1

main(board, cfg, path)
