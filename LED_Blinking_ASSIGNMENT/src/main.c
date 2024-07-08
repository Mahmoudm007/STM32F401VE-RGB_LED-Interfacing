/* GPIO Base address */
#define GPIOX_BASE_ADDRESS 0x40000000

/* GPIO portA Registers addresses*/
#define GPIOA_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020000)
#define GPIOA_MODER      (*(unsigned long *)(GPIOA_BASE_ADDR + 0x00))
#define GPIOA_OTYPER     (*(unsigned long *)(GPIOA_BASE_ADDR + 0x04))
#define GPIOA_ODR        (*(unsigned long *)(GPIOA_BASE_ADDR + 0x14))
#define GPIOA_PUPDR      (*(unsigned long *)(GPIOA_BASE_ADDR + 0x0C))
#define GPIOA_IDR        (*(unsigned long *)(GPIOA_BASE_ADDR + 0x10))

/* GPIO portB Registers addresses*/
#define GPIOB_BASE_ADDR  (GPIOX_BASE_ADDRESS + 0x00020400)
#define GPIOB_MODER      (*(unsigned long *)(GPIOB_BASE_ADDR + 0x00))
#define GPIOB_OTYPER     (*(unsigned long *)(GPIOB_BASE_ADDR + 0x04))
#define GPIOB_ODR        (*(unsigned long *)(GPIOB_BASE_ADDR + 0x14))
#define GPIOB_PUPDR      (*(unsigned long *)(GPIOB_BASE_ADDR + 0x0C))
#define GPIOB_IDR        (*(unsigned long *)(GPIOB_BASE_ADDR + 0x10))

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
#define SET_BIT(REGISTER, BIT_POS, CONTROL_BIT)    (REGISTER |= (1<<BIT_POS * CONTROL_BIT))
#define CLEAR_BIT(REGISTER, BIT_POS, CONTROL_BIT)  (REGISTER &= ~(1<<BIT_POS * CONTROL_BIT))
#define TOGGLE_BIT(REGISTER, BIT_POS, CONTROL_BIT) (REGISTER ^=(1<<BIT_POS * CONTROL_BIT))
#define READ_BIT(REGISTER, BIT_POS, CONTROL_BIT)   (REGISTER = ((REGISTER &(1<<BIT_POS * CONTROL_BIT)>>(BIT_POS * CONTROL_BIT))))

// Variables to use /* Change it as you want RECOMMENDED Delay_time = 10000*/
#define Delay_time     10000
volatile unsigned int Status = 1;


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

void DELAY(unsigned long timeinMILLS){
	volatile unsigned int i = 0;
	volatile unsigned int j = 0;

	for(i = 0; i < timeinMILLS; i++)
		// to avoid the warning of the for loop is not guard
		for(j = 0; j < 200 ; j++);
}


int main(void){
	// enable the clock
	Clock_Enable_Reg();
	// set the GPIO modes
	SET_GPIO_MODES();
	// Infinite loop to toggle the led infinitely
	while(Status == 1){
		TOGGLE_BIT(GPIOA_ODR, 0, 1);
		DELAY(10000);
	}
	return 0;
}
