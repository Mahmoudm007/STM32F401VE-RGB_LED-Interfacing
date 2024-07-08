/* GPIO Base address */
#define GPIOX_BASE_ADDRESS 0x40000000


/* GPIO portA Registers addresses*/
#define GPIOA_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020000)
#define GPIOA_MODER      (*(unsigned long *)(GPIOA_BASE_ADDR + 0x00))
#define GPIOA_OTYPER     (*(unsigned long *)(GPIOA_BASE_ADDR + 0x04))
#define GPIOA_ODR        (*(unsigned long *)(GPIOA_BASE_ADDR + 0x14))
#define GPIOA_PUPDR      (*(unsigned long *)(GPIOA_BASE_ADDR + 0x0C))
#define GPIOA_IDR        (*(unsigned long *)(GPIOA_BASE_ADDR + 0x10))
#define GPIOA_PUPDR_RESET_VALUE 0x64000000UL


/* GPIO portB Registers addresses*/
#define GPIOB_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020400)
#define GPIOB_MODER      (*(unsigned long *)(GPIOB_BASE_ADDR + 0x00))
#define GPIOB_OTYPER     (*(unsigned long *)(GPIOB_BASE_ADDR + 0x04))
#define GPIOB_ODR        (*(unsigned long *)(GPIOB_BASE_ADDR + 0x14))
#define GPIOB_PUPDR      (*(unsigned long *)(GPIOB_BASE_ADDR + 0x0C))
#define GPIOB_IDR        (*(unsigned long *)(GPIOB_BASE_ADDR + 0x10))
#define GPIOB_PUPDR_RESET_VALUE 0x00000100UL
#define PULL_UP_PORTB           0x00000100UL
#define PULL_DOWN_PORTB         0x00001000UL


/* GPIO portC Registers addresses*/
#define GPIOC_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020800)
#define GPIOC_MODER      (*(unsigned long *)(GPIOC_BASE_ADDR + 0x00))
#define GPIOC_OTYPER     (*(unsigned long *)(GPIOC_BASE_ADDR + 0x04))
#define GPIOC_ODR        (*(unsigned long *)(GPIOC_BASE_ADDR + 0x14))
#define GPIOC_PUPDR      (*(unsigned long *)(GPIOC_BASE_ADDR + 0x0C))
#define GPIOC_IDR        (*(unsigned long *)(GPIOC_BASE_ADDR + 0x10))


/* GPIO portD Registers addresses*/
#define GPIOD_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020C00)
#define GPIOD_MODER      (*(unsigned long *)(GPIOD_BASE_ADDR + 0x00))
#define GPIOD_OTYPER     (*(unsigned long *)(GPIOD_BASE_ADDR + 0x04))
#define GPIOD_ODR        (*(unsigned long *)(GPIOD_BASE_ADDR + 0x14))
#define GPIOD_PUPDR      (*(unsigned long *)(GPIOD_BASE_ADDR + 0x0C))
#define GPIOD_IDR        (*(unsigned long *)(GPIOD_BASE_ADDR + 0x10))


/* GPIO portE Registers addresses*/
#define GPIOE_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00021000)
#define GPIOE_MODER      (*(unsigned long *)(GPIOE_BASE_ADDR + 0x00))
#define GPIOE_OTYPER     (*(unsigned long *)(GPIOE_BASE_ADDR + 0x04))
#define GPIOE_ODR        (*(unsigned long *)(GPIOE_BASE_ADDR + 0x14))
#define GPIOE_PUPDR      (*(unsigned long *)(GPIOE_BASE_ADDR + 0x0C))
#define GPIOE_IDR        (*(unsigned long *)(GPIOE_BASE_ADDR + 0x10))


/* Clock Registers*/
#define RCC_AHB1ENR      (*(unsigned long *)(0x40023800 + 0x30))
#define RCC_CR           (*(unsigned long *)(0x40023800 + 0x00))


// Bit_masking operations
#define SET_BIT(REGISTER, MASK,BIT_POS, CONTROL_BIT)    (REGISTER |= (MASK<<BIT_POS * CONTROL_BIT))
#define CLEAR_BIT(REGISTER, MASK,BIT_POS, CONTROL_BIT)  (REGISTER &= ~(MASK<<BIT_POS * CONTROL_BIT))
#define TOGGLE_BIT(REGISTER, MASK,BIT_POS, CONTROL_BIT) (REGISTER ^= ( MASK<<BIT_POS * CONTROL_BIT ))
#define READ_BIT(REGISTER, MASK,BIT_POS, CONTROL_BIT)   ((REGISTER & (MASK << (BIT_POS * CONTROL_BIT))) >> (BIT_POS * CONTROL_BIT))


// Variables to use /* Change it as you want RECOMMENDED Delay_time = 10000*/
#define Delay_time     1000
volatile unsigned int Status = 1;


void DELAY(unsigned long timeinMILLS){
    volatile unsigned int i = 0;
    volatile unsigned int j = 0;

    for(i = 0; i < timeinMILLS; i++)
        // to avoid the warning of the for loop is not guard
        for(j = 0; j< 2 ; j++);
}


void Clock_Enable_Reg(){
    // PORTA clock enable register
    SET_BIT(RCC_AHB1ENR, 1,0, 1);
    // PORTB clock enable register
    SET_BIT(RCC_AHB1ENR, 1,1, 1);
}


void GPIO_CONFIG(){
    /* SET PORTB PIN5, PIN6, PIN7 as General purpose output mode : 01*/
    SET_BIT(GPIOB_MODER, 1, 5, 2); // BIT 10
//    CLEAR_BIT(GPIOB_MODER, 1, 11, 1); // BIT 11

    SET_BIT(GPIOB_MODER, 1, 6, 2); // BIT 12
//    CLEAR_BIT(GPIOB_MODER, 1, 13, 1); // BIT 13

    SET_BIT(GPIOB_MODER, 1, 7, 2); // BIT 14
//    CLEAR_BIT(GPIOB_MODER, 1, 15, 1); // BIT 15

    /* Set pin3 portB as input --> 00*/
    CLEAR_BIT(GPIOB_MODER,0x03, 3, 2);
//    CLEAR_BIT(GPIOB_MODER,1, 7, 1);

    /* GPIO PORTB PIN3 in  as PULL UP REGISTER*/
    SET_BIT(GPIOB_PUPDR, 1, 6, 1);
//    CLEAR_BIT(GPIOB_PUPDR, 1, 7, 1);

    /* GPIO PORTB PIN 5,6,7 PUSH PULL MODE*/
    CLEAR_BIT(GPIOB_OTYPER, 0x07, 5, 1);
//    CLEAR_BIT(GPIOB_OTYPER, 1, 6, 1);
//    CLEAR_BIT(GPIOB_OTYPER, 1, 7, 1);
}


void LED_SetColor(volatile unsigned int button_clicked, unsigned int red, unsigned int green, unsigned int blue) {
    switch (button_clicked) {
		case 0: // BLACK
			/* the value of red, green, blue is for READABILITY only*/
			red = 0;
			green = 0;
			blue = 0;
			CLEAR_BIT(GPIOB_ODR, 0x07, 5, 1);
//			CLEAR_BIT(GPIOB_ODR, 1, 6, 1);
//			CLEAR_BIT(GPIOB_ODR, 1, 7, 1);
			break;

		case 1: //RED
			/* the value of red, green, blue is for READABILITY only*/
			red = 255;
            green = 0;
            blue = 0;
            CLEAR_BIT(GPIOB_ODR,0x03, 6, 1);
//            CLEAR_BIT(GPIOB_ODR, 1,7, 1);
            DELAY(0.5 * Delay_time);
            SET_BIT(GPIOB_ODR, 1, 5, 1);
            break;

        case 2: // GREEN
        	/* the value of red, green, blue is for READABILITY only*/
        	red = 0;
            green = 255;
            blue =0;
        	CLEAR_BIT(GPIOB_ODR, 0x05, 5, 1);
//            CLEAR_BIT(GPIOB_ODR, 1, 7, 1);
            DELAY(0.5 * Delay_time);
            SET_BIT(GPIOB_ODR, 1, 6, 1);
            break;

        case 3: // YELLOW
        	/* the value of red, green, blue is for READABILITY only*/
        	red = 255;
            green = 255;
            blue = 0;
            CLEAR_BIT(GPIOB_ODR, 1,7, 1);
            DELAY(Delay_time);
        	SET_BIT(GPIOB_ODR, 0x03,5, 1);
//        	SET_BIT(GPIOB_ODR, 1,6, 1);
            break;

        case 4: // BLUE
        	/* the value of red, green, blue is for READABILITY only*/
        	red = 0;
			green = 0;
			blue = 255;
        	CLEAR_BIT(GPIOB_ODR, 0x03,5, 1);
//			CLEAR_BIT(GPIOB_ODR, 1,6, 1);
			DELAY(0.5 * Delay_time);
			SET_BIT(GPIOB_ODR,1, 7, 1);
            break;

        case 5: // MAGENTA
        	/* the value of red, green, blue is for READABILITY only*/
        	red = 255;
            green = 0;
            blue = 255;
            CLEAR_BIT(GPIOB_ODR,1, 6, 1);
            DELAY(0.5 * Delay_time);
        	SET_BIT(GPIOB_ODR, 0x05, 5, 1);
//            SET_BIT(GPIOB_ODR, 1,7, 1);
            break;

        case 6:  // CYAN
        	/* the value of red, green, blue is for READABILITY only*/
        	red = 0;
			green = 255;
			blue = 255;
        	CLEAR_BIT(GPIOB_ODR, 1,5, 1);
        	DELAY(0.5 * Delay_time);
        	SET_BIT(GPIOB_ODR, 0x03,6, 1);
//        	SET_BIT(GPIOB_ODR, 1,7, 1);
            break;

        default: // WHITE
            /* the value of red, green, blue is for READABILITY only*/
			red = 255;
			green = 255;
			blue = 255;
        	SET_BIT(GPIOB_ODR, 0x07,5, 1);
//			SET_BIT(GPIOB_ODR, 1,6, 1);
//			SET_BIT(GPIOB_ODR, 1,7, 1);
            break;
    }
}


int main(void) {

    Clock_Enable_Reg();
    GPIO_CONFIG();

    // Variables to store previous and current button state
    unsigned int prevButtonState = 1; // Initial value HIGH --> Active LOW
    unsigned int currentButtonState = 1; // Initial value HIGH --> Active LOW
    int button_clicked = 0; // The counter that toggle the colors

    // Variables to store RGB LED colors for READABILITY only
    unsigned int red = 0;
    unsigned int green = 0;
    unsigned int blue = 0;

    while (Status == 1) {
        // Read current button state
        currentButtonState = READ_BIT(GPIOB_IDR, 1,3, 1);

        // Check for falling edge (button press)
        if (prevButtonState == 1 && currentButtonState == 0) {
            currentButtonState = READ_BIT(GPIOB_IDR, 1,3, 1);
            if (button_clicked == 7) {
                // Reset the counter
                button_clicked = 0;
            }
            else{
            	// Increase button click counter
            	button_clicked++;
            }
        }

        /* This delay means the time which needed for toggle between state you need to press the button for 0.5sec*/
        DELAY(0.5 * Delay_time);
        // Set LED colors
        LED_SetColor(button_clicked, red,green , blue);
        // Update previous button state
        prevButtonState = currentButtonState;
    }

    return 0;
}
