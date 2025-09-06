#include "peripheral.h"

// ADC 초기화 함수
void ADC_Init(void) {
    // ADC 활성화 및 프리스케일러 설정 (예: 64로 설정)
    // ATmega88PA의 ADC prescaler는 64로 설정하여 16MHz 클럭에서 ADC가 정상적으로 동작하도록 함
    // 16MHz / 64 = 250kHz, ADC 동작 범위는 50kHz ~ 200kHz 이내
    // 8비트 해상도에서 안정적인 동작을 위해 64 설정
    ADMUX = (1 << REFS0);   // AREF = Vcc (AVCC 핀에서 제공되는 전압)
    ADCSRA = (1 << ADEN)    // ADC 활성화
           | (1 << ADPS2)  // ADC 프리스케일러 64 설정 (16MHz / 64 = 250kHz)
           | (1 << ADPS1)
           | (1 << ADPS0);
}

// ADC 변환 시작 함수
uint16_t ADC_Read(uint8_t channel) {
    // 채널 선택 (MUX3:0)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // 기존 AREF 설정을 유지하고 채널만 변경

    // ADC 변환 시작
    ADCSRA |= (1 << ADSC);  // 시작 비트 설정

    // 변환이 완료될 때까지 대기
    while (ADCSRA & (1 << ADSC));  // ADSC가 0이 될 때까지 대기

    // 변환된 값을 반환 (10비트 결과)
    return ADC;
}
