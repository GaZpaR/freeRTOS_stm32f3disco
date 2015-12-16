#include "stm32f30x.h"

#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_usart.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_ALL(void);
void send_str(char *str);
