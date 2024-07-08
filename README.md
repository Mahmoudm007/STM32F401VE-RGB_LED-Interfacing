[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/BC_RZDaD)



# RGB LED controller

The system is consisted of 1 push button and 1 RGB LED. The Push button is connected to PORTB pin 3. The 3 LED pins are connected to port B pins 5, 6 and 7. The Push button is active low, without external pull up resistor.

## Task Description

You are required to write a code that scans the button periodically. At each valid button press, the Software shall change the RGB LED color.
A button press shall be considered valid only when a falling edge is detected on the button pin. Button debouncing feature shall be added. The LED shall provide 8 colors controlled by the enabled colors mix (RED + GREEN + BELOW).

## Code Implementation
Part of macros in the src code:

```c
/* GPIO Base address */
#define GPIOX_BASE_ADDRESS 0x40000000

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
```

Clock enable and GPIOs initialization:

```c

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
```
RGB LED controller using switch case:

```c
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


```
![Alt Text](assets/RGB_LED.gif)

The watch window to see the addresses and values:
![Alt Text](assets/watch_window.gif)


The main function and falling edge detection:

```c

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

```
![Alt Text](assets/falling_edge_check.gif)



the simulation using 3-LEDS:
![Alt Text](assets/three_leds.gif)


# LED Blinking Code

You are required to write a code that performs LED blinking. The LED is connected to PORTA pin 0.

## Task Description

We are required to implement `main` function that performs the needed port initialization actions to control the LED. The function shall contain an infinite loop that performs the following actions in sequence:

1. Set the LED pin to high.
2. Wait for a predefined time.
3. Set the LED pin to Low.
4. Wait for a predefined time.
5. Repeat from step 1.

## Code Implementation

Part of macros in the code:

```c
/* GPIO Base address */
#define GPIOX_BASE_ADDRESS 0x40000000

/* GPIO portA Registers addresses*/
#define GPIOA_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020000)
#define GPIOA_MODER      (*(unsigned long *)(GPIOA_BASE_ADDR + 0x00))
#define GPIOA_OTYPER     (*(unsigned long *)(GPIOA_BASE_ADDR + 0x04))
#define GPIOA_ODR        (*(unsigned long *)(GPIOA_BASE_ADDR + 0x14))
#define GPIOA_PUPDR      (*(unsigned long *)(GPIOA_BASE_ADDR + 0x0C))
#define GPIOA_IDR        (*(unsigned long *)(GPIOA_BASE_ADDR + 0x10))


/* Clock Registers*/
#define RCC_AHB1ENR      (*(unsigned long *)(0x40023800 + 0x30))
#define RCC_CR           (*(unsigned long *)(0x40023800 + 0x00))

// Bit_masking operations
#define SET_BIT(REGISTER, BIT_POS, CONTROL_BIT)    (REGISTER |= (1<<BIT_POS * CONTROL_BIT))
#define CLEAR_BIT(REGISTER, BIT_POS, CONTROL_BIT)  (REGISTER &= ~(1<<BIT_POS * CONTROL_BIT))
#define TOGGLE_BIT(REGISTER, BIT_POS, CONTROL_BIT) (REGISTER ^=(1<<BIT_POS * CONTROL_BIT))
#define READ_BIT(REGISTER, BIT_POS, CONTROL_BIT)   (REGISTER = ((REGISTER &(1<<BIT_POS * CONTROL_BIT)>>(BIT_POS * CONTROL_BIT))))

// Variables to use /* Change it as you want RECOMMENDED Delay_time = 10000*/
#define Delay_time     10000
```

The initialization of GPIOs and enabling the clock:


```c
void Clock_Enable_Reg(){

	SET_BIT(RCC_AHB1ENR, 0, 1);
}


void SET_GPIO_MODES(){
	/* SET PORTA PIN0 as General purpose output mode : 01*/
	SET_BIT(GPIOA_MODER,0,2);
	CLEAR_BIT(GPIOA_MODER, 1, 2);

	/* GPIO PORTA PIN0 PUSH PULL MODE*/
	CLEAR_BIT(GPIOA_OTYPER, 0, 1);
}
```
Simulation:

![Alt Text](assets/led_blink.gif)
