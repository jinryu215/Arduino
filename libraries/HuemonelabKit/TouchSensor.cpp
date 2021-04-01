/* 
 * Updated By HuemoneLab, April 2019
 * 
 * TouchSensor.cpp - Library for Educational Arduino Kit made by Huemone Lab.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This software is provided "AS IS" only for educational purpose using MAKER'S BOX Kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.
 * 
 * 본 라이브러리는 (주)휴몬랩이 제작한 메이커스 박스 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 * 
 * Copyright (c) 2019 Huemone Lab Co., Ltd - All Rights Reserved. *
 */

#ifndef HUEMONELAB_TOUCH_SENSOR_CPP
#define HUEMONELAB_TOUCH_SENSOR_CPP

#include "HuemonelabKit.h"

/*
 * Touch sensor 세팅
 * - pinMode 설정
 * - count 변수를 0으로 초기화
 */
TouchSensor::TouchSensor(uint8_t pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _count = 0;
}

/*
 * Touch Sensor 값 읽기 
 */
int TouchSensor::read()
{
  return digitalRead(_pin);
}

/*
 * Touch Sensor 값 카운트 세기
 * - 터치센서 값이 HIGH(1)이면 count 1 증가, LOW(0)이면 count 1 감소
 * - count 최소값 : 0, 최대값: maxCount(maxCount의 default: 50)
 * - count 세는 주기 : duration
 */
int TouchSensor::count(int duration, int maxCount)
{
  int value = digitalRead(_pin);
  if (value)
  {
    _count++;
    if (_count > maxCount) // count가 maxCount보다 크면
      _count = maxCount;   // count를 maxCount로 지정
  }
  else
  {
    _count--;
    if (_count < 0) // count가 0보다 작으면
      _count = 0;   // count를 0으로 지정
  }
  delay(duration); // duration 만큼 delay
  return _count;
}

#endif