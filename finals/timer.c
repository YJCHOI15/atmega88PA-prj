#include "peripherals.h"

// 8비트 타이머0 초기화 함수
void Timer0_Init(void) {
    // 타이머 0을 CTC 모드로 설정
    TCCR0 = (1 << WGM01);  // CTC 모드 설정
    OCR0 = 249;            // 비교 일치 값 (249 -> 1ms 타이머 주기, 16MHz 클럭 기준)
    TCCR0 |= (1 << CS00);  // 프리스케일러 1로 설정 (시스템 클럭 직접 사용)
}

// 8비트 타이머0 인터럽트 활성화
void Timer0_EnableInterrupt(void) {
    // 비교 일치 인터럽트 활성화
    TIMSK |= (1 << OCIE0);
    sei();  // 전역 인터럽트 활성화
}

// 16비트 타이머1 초기화 함수
void Timer1_Init(void) {
    // 타이머 1을 CTC 모드로 설정 (16비트)
    TCCR1B = (1 << WGM12);  // CTC 모드 설정
    OCR1A = 15624;          // 비교 일치 값 (15624 -> 1Hz 타이머 주기, 16MHz 클럭, 프리스케일러 1024)
    TCCR1B |= (1 << CS12) | (1 << CS10);  // 프리스케일러 1024 설정
}

// 16비트 타이머1 인터럽트 활성화
void Timer1_EnableInterrupt(void) {
    // 비교 일치 인터럽트 활성화
    TIMSK |= (1 << OCIE1A);
    sei();  // 전역 인터럽트 활성화
}

// 타이머 인터럽트 비활성화
void Timer_DisableInterrupt(void) {
    // 타이머 0 및 1의 인터럽트를 비활성화
    TIMSK &= ~((1 << OCIE0) | (1 << OCIE1A));
}
