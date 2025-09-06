#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/* SN74HC138 */
#define A_PIN   PC0   // A 입력 핀 
#define B_PIN   PC1   // B 입력 핀 
#define C_PIN   PC2   // C 입력 핀

#define G1_PIN  PC3   // Enable 핀 G1 (활성 HIGH)
#define G2A_PIN PC4   // Enable 핀 G2A (활성 LOW)
#define G2B_PIN PC5   // Enable 핀 G2B (활성 LOW)

void sn74hc138_init();                           // 초기화 함수
void sn74hc138_select_output(uint8_t channel);   // 출력 선택 함수

/* 74HC595 */
#define DS_PIN     PB0   // 데이터 입력 핀
#define SH_CP_PIN  PB1   // 시프트 클럭 핀
#define ST_CP_PIN  PB2   // 스토리지 클럭 핀
#define OE_PIN     PB3   // 출력 활성화 핀 (LOW로 활성화)
#define MR_PIN     PB4   // 리셋 핀 (LOW로 초기화)

void hc595_init();
void hc595_shiftOut(uint8_t data);
void hc595_latch();
void hc595_reset();
void hc595_outputEnable(uint8_t enable);

/* 74HC165 */
#define DATA_PIN    PD0    // Q7 (출력 데이터)
#define CLOCK_PIN   PD1    // 클럭 핀 (Shift Clock)
#define LATCH_PIN   PD2    // 래치 핀 (Shift/Load)
#define CLK_INH_PIN PD3    // 클럭 억제 핀

void HC165_Init(void);
uint8_t HC165_Read(void);
void HC165_ShiftOut(uint8_t data);

/* ADC */
#define ADC_CHANNEL 0

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

/* INTERRUPT */
void Interrupt_Init(void);

ISR(TIMER0_COMPA_vect);
ISR(INT0_vect);

/* USART */
#define F_CPU 16000000UL

void USART_Init(unsigned int baud);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_WaitForTransmit(void);

/* SPI */
#define SPI_MASTER    1
#define SPI_SLAVE     0

void SPI_Init(uint8_t mode);
void SPI_Transmit(uint8_t data);
uint8_t SPI_Receive(void);
uint8_t SPI_TransmitReceive(uint8_t data);

/* TWI */
// TWI 주소
#define TWI_MASTER_ADDR  0x01  // 마스터의 TWI 주소
#define TWI_SLAVE_ADDR   0x10  // 슬레이브의 TWI 주소

// TWI 상태 코드
#define TWI_START_SENT            0x08
#define TWI_REPEATED_START_SENT   0x10
#define TWI_MT_SLA_ACK            0x18
#define TWI_MT_DATA_ACK           0x28
#define TWI_MR_SLA_ACK            0x40
#define TWI_MR_DATA_ACK           0x50
#define TWI_MR_DATA_NACK          0x58

void TWI_Init(void);
uint8_t TWI_Start(uint8_t address);
uint8_t TWI_Write(uint8_t data);
uint8_t TWI_ReadAck(void);
uint8_t TWI_ReadNack(void);
void TWI_Stop(void);

/* TIMER/COUNTER */
void Timer_Init(void);
void Timer0_Init(void);
void Timer0_EnableInterrupt(void);
void Timer1_Init(void);
void Timer1_EnableInterrupt(void);
void Timer_DisableInterrupt(void);

#endif 
