#include "peripherals.h"
#include <avr/io.h>

// 초기화 함수 - 디코더 핀을 출력 모드로 설정하고 Enable 핀을 초기화
void sn74hc138_init() {
    // A, B, C 핀과 Enable 핀을 출력 모드로 설정
    DDRC |= (1 << A_PIN) | (1 << B_PIN) | (1 << C_PIN);    // 입력 핀 A, B, C 설정
    DDRC |= (1 << G1_PIN) | (1 << G2A_PIN) | (1 << G2B_PIN); // Enable 핀 설정

    // 초기 상태 설정: Enable 핀 비활성화
    PORTC &= ~(1 << G1_PIN);  // G1을 LOW로 설정하여 비활성화
    PORTC |= (1 << G2A_PIN) | (1 << G2B_PIN);  // G2A와 G2B를 HIGH로 설정하여 비활성화
}

// 출력 선택 함수 - 0부터 7까지의 채널을 선택하고 해당 채널을 활성화
void sn74hc138_select_output(uint8_t channel) {
    if (channel > 7) return; // 유효하지 않은 채널이면 함수 종료

    // Enable 핀 활성화
    PORTC |= (1 << G1_PIN);   // G1을 HIGH로 설정
    PORTC &= ~((1 << G2A_PIN) | (1 << G2B_PIN)); // G2A와 G2B를 LOW로 설정

    // 입력 핀 (A, B, C) 설정
    PORTC = (PORTC & ~((1 << A_PIN) | (1 << B_PIN) | (1 << C_PIN)))  // A, B, C 초기화
            | ((channel & 0x01) << A_PIN)   // A 핀 설정 (채널의 0번 비트)
            | ((channel & 0x02) << (B_PIN - 1)) // B 핀 설정 (채널의 1번 비트)
            | ((channel & 0x04) << (C_PIN - 2)); // C 핀 설정 (채널의 2번 비트)
}

