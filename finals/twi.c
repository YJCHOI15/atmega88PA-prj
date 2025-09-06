#include "peripherals.h"

// TWI 초기화 함수
void TWI_Init(void) {
    // TWI 클럭 속도 설정 (일반적으로 100kHz)
    TWBR = 32;  // TWI 비트 레이트 레지스터
    TWSR = 0x00;  // TWI 상태 레지스터 (프리스케일러 1)
    
    // TWI 인터페이스 활성화
    TWCR = (1 << TWEN) | (1 << TWINT);  // TWI 활성화, 인터럽트 및 클럭 활성화
}

// TWI 시작 조건 생성 함수
uint8_t TWI_Start(uint8_t address) {
    // 시작 조건 생성
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  // 시작 비트와 인터럽트 설정
    
    // TWI 시작이 완료될 때까지 대기
    while (!(TWCR & (1 << TWINT))) {
        // TWI 전송 완료될 때까지 대기
    }
    
    // 주소 송신 (읽기/쓰기)
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);  // 데이터 전송을 위한 클럭 송신
    
    // 주소 송신 후 응답 대기
    while (!(TWCR & (1 << TWINT))) {
        // TWI 전송 완료될 때까지 대기
    }
    
    // 상태 코드 확인
    if ((TWSR & 0xF8) != TWI_MT_SLA_ACK && (TWSR & 0xF8) != TWI_MR_SLA_ACK) {
        return 1;  // 주소 송신 실패
    }
    
    return 0;  // 주소 송신 성공
}

// TWI 데이터 송신 함수
uint8_t TWI_Write(uint8_t data) {
    // 데이터 전송
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);  // 데이터 전송을 위한 클럭 송신
    
    // 전송이 완료될 때까지 대기
    while (!(TWCR & (1 << TWINT))) {
        // TWI 전송 완료될 때까지 대기
    }
    
    // 상태 코드 확인
    if ((TWSR & 0xF8) != TWI_MT_DATA_ACK) {
        return 1;  // 데이터 송신 실패
    }
    
    return 0;  // 데이터 송신 성공
}

// TWI 데이터 수신 함수 (ACK 반환)
uint8_t TWI_ReadAck(void) {
    // ACK 후 데이터 수신
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);  // ACK 후 데이터 읽기
    
    // 수신이 완료될 때까지 대기
    while (!(TWCR & (1 << TWINT))) {
        // TWI 전송 완료될 때까지 대기
    }
    
    return TWDR;  // 수신된 데이터 반환
}

// TWI 데이터 수신 함수 (NACK 반환)
uint8_t TWI_ReadNack(void) {
    // NACK 후 데이터 수신
    TWCR = (1 << TWINT) | (1 << TWEN);  // NACK 후 데이터 읽기
    
    // 수신이 완료될 때까지 대기
    while (!(TWCR & (1 << TWINT))) {
        // TWI 전송 완료될 때까지 대기
    }
    
    return TWDR;  // 수신된 데이터 반환
}

// TWI 종료 함수
void TWI_Stop(void) {
    // STOP 조건 생성
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // STOP 비트 설정
    
    // TWI STOP이 완료될 때까지 대기
    while (TWCR & (1 << TWSTO)) {
        // STOP 조건이 완료될 때까지 대기
    }
}
