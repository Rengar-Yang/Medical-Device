#include "st7789.h"
#include "main.h"
/**
 * @brief Write command to ST7789 controller
 * @param cmd -> command to write
 * @return none
 */
 #define ST7789_SPI_PORT hspi1
extern SPI_HandleTypeDef ST7789_SPI_PORT;

volatile uint8_t IsTransmittingBlock_=0;

static void ST7789_WriteCommand(uint8_t cmd)
{

	HAL_GPIO_WritePin(LCD_DX_GPIO_Port,LCD_DX_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&ST7789_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);

}

/**
 * @brief Write data to ST7789 controller
 * @param buff -> pointer of data buffer
 * @param buff_size -> size of the data buffer
 * @return none
 */
static void ST7789_WriteData(uint8_t *buff, size_t buff_size)
{
	HAL_GPIO_WritePin(LCD_DX_GPIO_Port,LCD_DX_Pin,GPIO_PIN_SET);
	// split data in small chunks because HAL can't send more than 64K at once

		while (buff_size > 0) {
		uint16_t chunk_size = buff_size > 65535 ? 65535 : buff_size;
		HAL_SPI_Transmit(&ST7789_SPI_PORT, buff, chunk_size, HAL_MAX_DELAY);
		buff += chunk_size;
		buff_size -= chunk_size;
	}

}

static void ST7789_WriteData_DMA(uint16_t *buff, size_t buff_size)
{
		HAL_GPIO_WritePin(LCD_DX_GPIO_Port,LCD_DX_Pin,GPIO_PIN_SET);
		for(int i=0;i<buff_size;i++)
				buff[i]=buff[i]>>8|buff[i]<<8;
		HAL_SPI_Transmit_DMA(&ST7789_SPI_PORT, (uint8_t*)buff, 2*buff_size);
}

/**
 * @brief Write data to ST7789 controller, simplify for 8bit data.
 * data -> data to write
 * @return none
 */
static void ST7789_WriteSmallData(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_DX_GPIO_Port,LCD_DX_Pin,GPIO_PIN_SET);
	HAL_SPI_Transmit(&ST7789_SPI_PORT, &data, sizeof(data), HAL_MAX_DELAY);
}

/**
 * @brief Set the rotation direction of the display
 * @param m -> rotation parameter(please refer it in st7789.h)
 * @return none
 */
void ST7789_SetRotation(uint8_t m)
{
	ST7789_WriteCommand(ST7789_MADCTL);	// MADCTL
	switch (m) {
	case 0:
		ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
		break;
	case 1:
		ST7789_WriteSmallData(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	case 2:
		ST7789_WriteSmallData(ST7789_MADCTL_RGB);
		break;
	case 3:
		ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	default:
		break;
	}
}

/**
 * @brief Set address of DisplayWindow
 * @param xi&yi -> coordinates of window
 * @return none
 */
static uint16_t old_x0=0xFFFF, old_x1=0xFFFF, old_y0=0xFFFF, old_y1=0xFFFF;
static void ST7789_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

	/* Column Address set */
	if (x0 != old_x0 || x1 != old_x1)
  {
		uint8_t data[] = {x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF};
		ST7789_WriteCommand(ST7789_CASET); 
		ST7789_WriteData(data, sizeof(data));
		old_x0 = x0;
    old_x1 = x1;
  }
	/* Row Address set */
	  if (y0 != old_y0 || y1 != old_y1)
  {
		uint8_t data[] = {y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF};
		ST7789_WriteCommand(ST7789_RASET);
		ST7789_WriteData(data, sizeof(data));
		old_y0 = y0;
    old_y1 = y1;
	}
	ST7789_WriteCommand(ST7789_RAMWR);
}

/**
 * @brief Fill the DisplayWindow with single color
 * @param color -> color to Fill with
 * @return none
 */
void ST7789_Fill_Color(uint16_t color)
{
	uint16_t i, j;
	ST7789_SetAddressWindow(0, 0, ST7789_WIDTH - 1, ST7789_HEIGHT - 1);
	for (i = 0; i < ST7789_WIDTH; i++)
		for (j = 0; j < ST7789_HEIGHT; j++) {
			uint8_t data[] = {color >> 8, color & 0xFF};
			ST7789_WriteData(data, sizeof(data));
		}
}


/**
 * @brief Draw an Image on the screen
 * @param x&y -> start point of the Image
 * @param w&h -> width & height of the Image to Draw
 * @param data -> pointer of the Image array
 * @return none
 */


void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
{
	ST7789_SetAddressWindow(x, y, x + w-1, y + h-1);
	ST7789_WriteData_DMA((uint16_t *)data, w * h);
}


/**
 * @brief Open/Close tearing effect line
 * @param tear -> Whether to tear
 * @return none
 */
void ST7789_TearEffect(uint8_t tear)
{

	ST7789_WriteCommand(tear ? 0x35 /* TEON */ : 0x34 /* TEOFF */);

}


/**
 * @brief Initialize ST7789 controller
 * @param none
 * @return none
 */
void ST7789_Init(void)
{
		HAL_Delay(25);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET);
    HAL_Delay(25);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET);
    HAL_Delay(100);
		
    ST7789_WriteCommand(ST7789_COLMOD);		//	Set color mode
    ST7789_WriteSmallData(ST7789_COLOR_MODE_16bit);
  	ST7789_WriteCommand(0xB2);				//	Porch control
	{
		uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
		ST7789_WriteData(data, sizeof(data));
	}
		ST7789_SetRotation(ST7789_ROTATION);	//	MADCTL (Display Rotation)
	
	/* Internal LCD Voltage generator settings */
    ST7789_WriteCommand(0XB7);				//	Gate Control
    ST7789_WriteSmallData(0x35);			//	Default value
    ST7789_WriteCommand(0xBB);				//	VCOM setting
    ST7789_WriteSmallData(0x19);			//	0.725v (default 0.75v for 0x20)
    ST7789_WriteCommand(0xC0);				//	LCMCTRL	
    ST7789_WriteSmallData (0x2C);			//	Default value
    ST7789_WriteCommand (0xC2);				//	VDV and VRH command Enable
    ST7789_WriteSmallData (0x01);			//	Default value
    ST7789_WriteCommand (0xC3);				//	VRH set
    ST7789_WriteSmallData (0x12);			//	+-4.45v (defalut +-4.1v for 0x0B)
    ST7789_WriteCommand (0xC4);				//	VDV set
    ST7789_WriteSmallData (0x20);			//	Default value
    ST7789_WriteCommand (0xC6);				//	Frame rate control in normal mode
    ST7789_WriteSmallData (0x0F);			//	Default value (60HZ)
    ST7789_WriteCommand (0xD0);				//	Power control
    ST7789_WriteSmallData (0xA4);			//	Default value
    ST7789_WriteSmallData (0xA1);			//	Default value
	/**************** Division line ****************/

	ST7789_WriteCommand(0xE0);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
		ST7789_WriteData(data, sizeof(data));
	}

    ST7789_WriteCommand(0xE1);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
		ST7789_WriteData(data, sizeof(data));
	}
    ST7789_WriteCommand (ST7789_INVON);		//	Inversion ON
		ST7789_WriteCommand (ST7789_SLPOUT);	//	Out of sleep mode
  	ST7789_WriteCommand (ST7789_NORON);		//	Normal Display on
  	ST7789_WriteCommand (ST7789_DISPON);	//	Main screen turned on	
}

/**
 * Check if a Frame Buffer Block is beeing transmitted.
 */
int touchgfxDisplayDriverTransmitActive(void)
{
	return IsTransmittingBlock_;
}
/**
 * Check if a Frame Buffer Block ending at bottom may be sent.
 */
int touchgfxDisplayDriverShouldTransferBlock(uint16_t bottom)
{
	return 1;
}
/**
 * Transmit a Frame Buffer Block.
 */
void touchgfxDisplayDriverTransmitBlock(const uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	IsTransmittingBlock_=1;
	ST7789_DrawImage(x,y,w,h,(uint16_t*)pixels);
}

