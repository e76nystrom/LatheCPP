#!/cygdrive/c/Python27/Python.exe

from collections import namedtuple
TmrCfg = namedtuple('TmrCfg', ('name', 'tmr', 'argType', 'pwm',
                               'isr', 'slave'))

CPP = True

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

proc = "STM32F407"

step1 = 2
step1Pwm = 3

step2 = 5
step2Pwm = 2

step3 = 3
step3Pwm = 1

step4 = 4
step4Pwm = 2

spindleTimer = 8
spindlePwm = 4

pwmTmr = 12
pwmTmrPwm = 1

usecTmr = 6

indexTmr = 10

cmpTmr = 9

intTmr = 11
intTmrPwm = 0 

encTestTmr = 7

if proc == "STM32F407" or proc == "STM32F446":
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

timers = \
( \
  TmrCfg("zTmr", step1, "uint32_t", step1Pwm, "TIM2", True),
  TmrCfg("xTmr", step2, "uint32_t", step2Pwm, "TIM5", True),
  TmrCfg("spindleTmr", spindleTimer, "uint16_t", spindlePwm, "TIM8_UP_TIM13", None),
  TmrCfg("step3Tmr", step3, "uint16_t", step3Pwm, "TIM4", None),
  TmrCfg("step4Tmr", step4, "uint16_t", step4Pwm, "TIM3", None),
  TmrCfg("pwmTmr", pwmTmr, "uint16_t", pwmTmrPwm, "TIM8_BRK_TIM12", None),
  TmrCfg("usecTmr", usecTmr, "uint16_t", 0, None, None),
  TmrCfg("indexTmr", indexTmr, "uint16_t", 0, "TIM1_TRG_COM_TIM10", None),
  TmrCfg("cmpTmr", cmpTmr, "uint16_t", 0, "TIM1_BRK_TIM9", None),
  TmrCfg("intTmr", intTmr, "uint16_t", 0, "TIM11", None),
  TmrCfg("encTestTmr", encTestTmr, "uint16_t", 0, "TIM7", None),
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
  ("ReaddCMR", "is", "%s->CCMR1"),
)

pwm2List = \
( \
  ("CCR",       "x",  "%s->CCR1 = (x)"),
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

def timerInit(name, tmr, timer):
    body = (" \\\n\t__HAL_RCC_TIM%d_CLK_ENABLE(); \\\n"
            "\t%s->CR1 |= TIM_CR1_DIR; \\\n"
            "\t%s->CR1 &= ~TIM_CR1_CEN")
    body = body.replace("%d", str(tmr))
    makeFunc(timer, "Init" , None, body)
    f.write("\n")
    
def timerStart(name, timer):
    body = (" \\\n\t%s->EGR = TIM_EGR_UG; \\\n"
            "\t%s->CR1 |= TIM_CR1_CEN")
    makeFunc(timer, "Start" , None, body)
    f.write("\n")
    
def timerBDTR(name, tmr, timer):
    if tmr == 1 or tmr == 8:
        body = "%s->BDTR |= TIM_BDTR_MOE"
        makeFunc(timer, "BDTR" , None, body)
        f.write("\n")
    
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
    f.write("\n")

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
        f.write("%s %s %s\n" % (define, call, body))
    else:
        f.write("%s %s %s%s%s\n" % \
                (define, call, op, body, cl))

def main():
    global f
    global name, tmr, argType, pwm, isr, slave
    
    f = open("include/timers.h", "wb")

    for t in timers:
        name = t.name
        tmr = t.tmr
        argType = t.argType
        pwm = t.pwm
        isr = t.isr
        slave = t.slave

        timer = "TIM%d" % tmr

        f.write("/* %s timer %d" % (name, tmr))
        if pwm != 0:
            f.write(" pwm %d" % (pwm))
        f.write(" */\n\n")

        f.write("#define %s %s\n" % (name.upper().replace("TMR", "_TIMER"), tmr))
        f.write("#define %s %s\n\n" % (name.upper().replace("TMR", "_TMR"), timer))

        if isr != None:
            f.write("#define %sISR(x) %s_IRQHandler(x)\n\n" % (name, isr))

        timerInit(name, tmr, timer)
        # timerStart(name, timer)
        timerBDTR(name, tmr, timer)

        makeFuncList(timer, regList)
        if pwm != 0:
            f.write("/* pwm %d */\n\n" % (pwm))
            f.write("#define %s_PWM %d\n\n" % \
                    (name.upper().replace("TMR", "_TMR"), pwm))
            makeFuncList(timer, pwmList[pwm - 1])

        if tmr == cmpTmr:
            makeFuncList(timer, capList)

        if slave:
            # print("slave %d spindle %d" % (tmr, spindleTimer))
            for (slv, trig) in slaveTrig:
                # print("slvx %d" % (slv))
                if tmr == slv:
                    for (i, trigTimer) in enumerate(trig):
                        # print("i %d trigTimer %d" % (i, trigTimer))
                        if spindleTimer == trigTimer:
                            body = timer + "->SMCR = ("
                            if (i & 2) != 0:
                                body += "TIM_SMCR_TS_1 | "
                            if (i & 1) != 0:
                                body += "TIM_SMCR_TS_0 | "
                            body += "\\\n"
                            body += "\tTIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)"
                            f.write("/* timer %d trigger %d */\n\n" % (spindleTimer, i))
                            makeFunc(timer, "SlvEna", None, body)
                            body = timer + "->SMCR = 0"
                            makeFunc(timer, "SlvDis", None, body)
                            f.write("\n")
                            break

    f.close()

main()
