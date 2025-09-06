#include "peripherals.h"

// USART 초기화 함수
void USART_Init(unsigned int baud) {
    // 계산된 UBRR 값을 사용하여 보드레이트 설정
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    
    // UBRR 레지스터에 보드레이트 설정
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)(ubrr);

    // 송신 및 수신 활성화
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // RXEN0 (수신 활성화), TXEN0 (송신 활성화)

    // 비동기 모드, 8비트 데이터, 1비트 스톱 비트, 패리티 없음
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8비트 데이터, 1비트 스톱 비트
}

// 데이터 송신 함수
void USART_Transmit(unsigned char data) {
    // 송신 버퍼가 비어 있을 때까지 대기
    while (!(UCSR0A & (1 << UDRE0))) {
        // UDRE0 (송신 버퍼 비어 있음 플래그)가 설정될 때까지 대기
    }

    // 데이터를 송신 버퍼에 전달
    UDR0 = data;
}

// 데이터 수신 함수
unsigned char USART_Receive(void) {
    // 데이터가 수신될 때까지 대기
    while (!(UCSR0A & (1 << RXC0))) {
        // RXC0 (수신 완료 플래그)가 설정될 때까지 대기
    }

    // 수신된 데이터 반환
    return UDR0;
}

// 전송 완료 대기 함수
void USART_WaitForTransmit(void) {
    // 송신이 완료될 때까지 대기
    while (!(UCSR0A & (1 << TXC0))) {
        // TXC0 (송신 완료 플래그)가 설정될 때까지 대기
    }

    // 송신 완료 플래그 클리어
    UCSR0A |= (1 << TXC0);
}
