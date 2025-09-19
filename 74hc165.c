#include "peripherals.h"

// 74HC165 초기화 함수
void HC165_Init(void)
{
    // DATA_PIN, CLOCK_PIN, LATCH_PIN을 출력으로 설정
    DDRD |= (1 << DATA_PIN) | (1 << CLOCK_PIN) | (1 << LATCH_PIN) | (1 << CLK_INH_PIN);
    
    // CLK_INH_PIN을 HIGH로 설정하여 클럭 신호를 억제
    PORTD |= (1 << CLK_INH_PIN);
}

// 74HC165에서 데이터를 읽어오는 함수
uint8_t HC165_Read(void)
{
    uint8_t data = 0;
    
    // 래치 신호를 LOW로 설정하여 병렬 데이터를 래치
    PORTD &= ~(1 << LATCH_PIN);
    
    // 잠시 지연 (데이터가 래치될 시간을 주기 위해)
    _delay_us(1);
    
    // 래치 신호를 HIGH로 설정하여 시프트 시작
    PORTD |= (1 << LATCH_PIN);
    
    // 데이터를 시프트하여 읽음
    for (uint8_t i = 0; i < 8; i++) {
        // 클럭을 HIGH로 설정하여 데이터를 시프트
        PORTD |= (1 << CLOCK_PIN);
        
        // DATA_PIN에서 비트 읽기 (MSB부터 읽음)
        if (PIND & (1 << DATA_PIN)) {
            data |= (1 << (7 - i));
        }
        
        // 클럭을 LOW로 설정
        PORTD &= ~(1 << CLOCK_PIN);
    }
    
    return data;
}

// 74HC165에 데이터를 시프트 아웃하는 함수
void HC165_ShiftOut(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++) {
        // 데이터를 직렬로 시프트
        if (data & (1 << (7 - i))) {
            PORTD |= (1 << DATA_PIN);  // 1 비트 전송
        } else {
            PORTD &= ~(1 << DATA_PIN); // 0 비트 전송
        }
        
        // 클럭 신호를 HIGH로 설정하여 데이터 전송
        PORTD |= (1 << CLOCK_PIN);
        
        // 클럭 신호를 LOW로 설정하여 데이터 전송 완료
        PORTD &= ~(1 << CLOCK_PIN);
    }
}
