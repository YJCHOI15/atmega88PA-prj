#include "peripherals.h"

// SPI 초기화 함수 (Master 모드, 기본 SPI 설정)
void SPI_Init(uint8_t mode) {
    // MISO, SCK, MOSI 핀 설정
    if (mode == SPI_MASTER) {
        // 마스터 모드 설정
        DDRB |= (1 << PB5) | (1 << PB7);    // MOSI, SCK를 출력으로 설정
        DDRB &= ~(1 << PB6);                 // MISO는 입력으로 설정
        SPCR |= (1 << MSTR);                 // SPI 마스터 모드 설정
    } else {
        // 슬레이브 모드 설정
        DDRB |= (1 << PB6);                  // MISO를 출력으로 설정
        DDRB &= ~((1 << PB5) | (1 << PB7));  // MOSI, SCK는 입력으로 설정
        SPCR &= ~(1 << MSTR);                // SPI 슬레이브 모드 설정
    }

    // SPI 클럭 분주율 설정 (F_CPU / 16 = 1Mbps)
    SPCR |= (1 << SPR0);  // SPI 클럭 분주율 16 설정 (F_CPU / 16)
    
    // SPI 활성화
    SPCR |= (1 << SPE);   // SPI 활성화
}

// SPI 데이터 송신 함수
void SPI_Transmit(uint8_t data) {
    // 데이터를 전송 레지스터에 저장
    SPDR = data;
    
    // 전송이 완료될 때까지 대기
    while (!(SPSR & (1 << SPIF))) {
        // SPIF 플래그가 설정될 때까지 대기
    }
}

// SPI 데이터 수신 함수
uint8_t SPI_Receive(void) {
    // 수신된 데이터 반환
    while (!(SPSR & (1 << SPIF))) {
        // 데이터가 수신될 때까지 대기
    }
    return SPDR;
}

// SPI 데이터 송수신 함수
uint8_t SPI_TransmitReceive(uint8_t data) {
    // 데이터를 전송 레지스터에 저장
    SPDR = data;
    
    // 전송 및 수신 완료 대기
    while (!(SPSR & (1 << SPIF))) {
        // SPIF 플래그가 설정될 때까지 대기
    }
    
    // 수신된 데이터 반환
    return SPDR;
}
