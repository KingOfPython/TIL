# opencv-shared-debug-mode-lib-error 관련 (mfc)
 ## 환경
 
- visual studio 2019

- c++ / mfc

- oepn cv 4.6.0 32bit

> open cv의 경우, 현재 사용하고자 하는 버전(v4.6.0) 에서는 32bit library를 제공하지 않음.
>
> 직접 source code 빌드 시, 32 bit 사용 가능.
>
> 공정 SW 적용으로, 작업자들이 직접 셋업 또는 업데이트 시 문제 발생 가능성이 있어, shared-lib 방식이 아닌 static-lib로 적용함

---

## 문제점
 - Release 동작 시, 정상 동작
 - Debug 동작 시, 아래의 오류 발생
  ```
0x75EEC3A2(KernelBase.dll)에(Package_Weight_Check_Tool.exe의) 처리되지 않은 예외가 있습니다.
 0xC000041D: 사용자 콜백 중 처리되지 않은 예외가 발생했습니다.
  ```
  ```
  Run-Time Check Failure #0 - The value of ESP was not properly saved across a function call.
    This is usually a result of calling a function declared with one calling convention with a function pointer declared with a different calling convention.
  ```
-  dialog에 임시로 이미지를 띄우기 위해 사용하는 CImage 객체가 delete 시 오류가 발생.
-  메모리 누수 발생

  ---

## 시도한 것 들
 - ~~Visual Studio의 플랫폼 도구 집합을 open cv 플랫폼 도구 집합과 동일한 Visual Studio 2015 (v140)으로 변경 (기존 Visual Studio 2019 (v142))~~
 - ~~빌드 재시도~~
 - ~~기족 static lib 에서, shared lib 환경으로 변경.~~
  
  추가 적으로 작업진행시, 업데이트

---

## 문제 해결 
 - 원인
  
    - Open CV 문제가 아닌 CImage 문제로 확인
    - CImage 에서 DC를 사용후, release() 를 GetDC()를 한만큼 하지 않아서 발생하는 문제였다.
    - 사용하는 다른 비트맵 관련 함수 내부에서 DC를 가져다 쓰고, 반환은 해주지 않는 것으로 확인했고, 직접 release를 해줘야 했다.
    - 에러는 아래의 함수의 	ATLASSUME( m_hDC == NULL ); 에서 null 에 아니기 때문에 발생했다. ATLASSUME 이기 떄문에 Release에서는 발생하지 않은 것으로 보인다.
    - dc를 사용 후에는, 꼭 반환을 확인하도록 해야겠다.
  ```c++
inline HBITMAP CImage::Detach() throw()
{
	HBITMAP hBitmap;

	ATLASSUME( m_hBitmap != NULL );
	ATLASSUME( m_hDC == NULL );

	hBitmap = m_hBitmap;
	m_hBitmap = NULL;
	m_pBits = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nBPP = 0;
	m_nPitch = 0;
	m_iTransparentColor = -1;
	m_clrTransparentColor = (COLORREF)-1;
	m_bHasAlphaChannel = false;
	m_bIsDIBSection = false;

	return( hBitmap );
}
  ```