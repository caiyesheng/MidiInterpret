SET PATH=D:\uvision\ARM\ARMCC\bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\Java\jdk1.8.0_121\bin;C:\Program Files\Java\jdk1.8.0_121\jre\bin;%CATALINA_HOME%\lib;C:\Users\Administrator\AppData\Local\Programs\Python\Python35\Scripts\;C:\Users\Administrator\AppData\Local\Programs\Python\Python35\
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=TIM3-DEMO
SET CPU_CLOCK=0x007A1200
"D:\uvision\ARM\ARMCC\bin\ArmAsm" --Via "..\output\startup_stm32f10x_hd._ia"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\main.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_it.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\pwm.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\play.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\time_test.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\can.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\usart.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\isdebug.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\util.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\systick.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_gpio.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_rcc.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\misc.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_tim.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_usart.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_can.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\core_cm3.__i"
"D:\uvision\ARM\ARMCC\bin\ArmCC" --Via "..\output\system_stm32f10x.__i"
"D:\uvision\ARM\ARMCC\bin\ArmLink" --Via "..\Output\STM32-DEMO.lnp"
