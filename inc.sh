#!/bin/bash

./inc.py src/encoder.cpp include/encoder.h
./inc.py src/i2c.cpp include/i2c.h
./inc.py src/lathe.cpp include/lathe.h
./inc.py src/lathex.cpp include/lathex.h
./inc.py src/lclcmd.cpp include/lclcmd.h
./inc.py src/lclcmdx.cpp include/lclcmdx.h
./inc.py src/remcmd.cpp include/remcmd.h
./inc.py src/serialio.cpp include/serialio.h
./inc.py src/spi.cpp include/spi.h
./inc.py src/xcontrol.cpp include/xcontrol.h
./inc.py src/zcontrol.cpp include/zcontrol.h
