#include "peripherals.h"
#include <util/delay.h>

// 초기화 함수
void hc595_init() {
    // 제어 핀을 출력 모드로 설정
    DDRB |= (1 << DS_PIN) | (1 << SH_CP_PIN) | (1 << ST_CP_PIN) | (1 << OE_PIN) | (1 << MR_PIN);
    
    // 초기 상태 설정
    PORTB &= ~(1 << SH_CP_PIN);  // 시프트 클럭 초기화
    PORTB &= ~(1 << ST_CP_PIN);  // 스토리지 클럭 초기화
    PORTB |= (1 << OE_PIN);      // 출력 비활성화 (OE 핀 HIGH)
    PORTB |= (1 << MR_PIN);      // 리셋 비활성화
}

// 시프트 데이터를 74HC595로 출력하는 함수
void hc595_shiftOut(uint8_t data) {
    // 8비트 데이터를 시프트 레지스터로 전송
    for (uint8_t i = 0; i < 8; i++) {
        if (data & (1 << (7 - i))) {
            PORTB |= (1 << DS_PIN);  // 데이터 핀 HIGH
        } else {
            PORTB &= ~(1 << DS_PIN); // 데이터 핀 LOW
        }

        // 시프트 클럭 펄스 (SH_CP 핀에서 HIGH -> LOW)
        PORTB |= (1 << SH_CP_PIN);
        _delay_us(1);
        PORTB &= ~(1 << SH_CP_PIN);
        _delay_us(1);
    }
}

// 데이터를 래치로 옮기는 함수 (출력에 반영)
void hc595_latch() {
    PORTB |= (1 << ST_CP_PIN);  // 스토리지 클럭 HIGH
    _delay_us(1);
    PORTB &= ~(1 << ST_CP_PIN); // 스토리지 클럭 LOW
}

// 74HC595 리셋 함수
void hc595_reset() {
    PORTB &= ~(1 << MR_PIN);    // 리셋 핀 LOW (모든 출력 초기화)
    _delay_us(1);
    PORTB |= (1 << MR_PIN);     // 리셋 핀 HIGH
}

// 출력 활성화 함수
void hc595_outputEnable(uint8_t enable) {
    if (enable) {
        PORTB &= ~(1 << OE_PIN); // 출력 활성화 (OE 핀 LOW)
    } else {
        PORTB |= (1 << OE_PIN);  // 출력 비활성화 (OE 핀 HIGH)
    }
}
