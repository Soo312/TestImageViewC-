
// MFCTestAppDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTestApp.h"
#include "MFCTestAppDlg.h"
#include "afxdialogex.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <regex>

using namespace std;

//스레드 리턴
#include <future>

using namespace cv;

#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_RBUTTONDOWN()
//	ON_WM_RBUTTONUP()
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCTestAppDlg 대화 상자



CMFCTestAppDlg::CMFCTestAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTESTAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_box);
	DDX_Control(pDX, IDC_SLIDER1, m_slide);
}

BEGIN_MESSAGE_MAP(CMFCTestAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCTestAppDlg::OnBnClickedOk)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_LBN_DBLCLK(IDC_LIST1, &CMFCTestAppDlg::OnDblclk_ListBoxitem)
	ON_WM_HSCROLL()
//	ON_WM_LBUTTONUP()
ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCTestAppDlg 메시지 처리기

BOOL CMFCTestAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_PICCON)->GetClientRect(&picconrect);


	m_slide.SetRange(0, 100);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTestAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTestAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTestAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTestAppDlg::OnDrawImage(bool listselect )
{
	CClientDC dc(GetDlgItem(IDC_PICCON));

	CRect rect;

	GetDlgItem(IDC_PICCON)->GetClientRect(&rect);

	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	//Picture Control DC에 호환되는ㄴ CDC를생성
	memDC.CreateCompatibleDC(&dc);

	// PicCon의 크기와 동일한 비트맵을 생성
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	//임시버퍼에서 방금 생성된 비트맵 선택, 이전 비트맵 저장
	pOldBitmap = memDC.SelectObject(&bitmap);

	//임시버퍼를 검은색으로 채움
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	//임시버퍼에 그리는 동작
	if (!bool_zoomstart)
	{

		//zoomRect를 그릴때 동작 // listselect 는 현재 리스트 선택시 확인하는 플래그bool
		DrawImage(&memDC,listselect); 
		if (drawZoomRect) 
		{
			DrawRect(&memDC);
		}
	}
	else
	{
		//if (m_image != nullptr)


		if(!m_image.empty())
		{
			CRect rect;
			GetDlgItem(IDC_PICCON)->GetClientRect(&rect);
			
			CRect rect2;
			GetDlgItem(IDC_PICCON)->GetWindowRect(&rect2);
			ScreenToClient(&rect2);


			//CRect rect3((drawrect.left )*zoomrate_x, drawrect.top* zoomrate_y, (drawrect.left + drawrect.Width())*zoomrate_x, (drawrect.top+drawrect.Height())* zoomrate_y);

			CRect rect3((drawrect.left) * zoomrate_y, drawrect.top * zoomrate_y, (drawrect.left + drawrect.Width()) * zoomrate_y, (drawrect.top + drawrect.Height()) * zoomrate_y);

			//rect3.left = drawrect.left - rect2.left;
			//rect3.top = drawrect.top - rect2.top;
			//rect3.Width = drawrect.Width;
			//drawrect.Height = drawrect.Height;

			//CRect rect3(500, 500, 2500, 2500);

			int temp;

			if (rect3.left > rect3.right)
			{
				temp = rect3.left;
				rect3.left = rect3.right;
				rect3.right = temp;
			}
			
			if (rect3.top > rect3.bottom)
			{
				temp = rect3.top;
				rect3.top = rect3.bottom;
				rect3.bottom = temp;
			}

			

			SetStretchBltMode(memDC.GetSafeHdc(), COLORONCOLOR);
			//StretchDIBits(memDC.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), rect3.left, m_image.rows-rect3.bottom, 
			//rect3.Width(), rect3.Height(), m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
#if true // test
			int nowindex = 0;
			//int nowcount = m_list_box.GetCount();
			//int nowcursel = m_list_box.;
			nowindex = m_list_box.GetCurSel();
			CString cstring;
			if (nowindex == -1)
			{
				nowindex = 0;
			}
			m_list_box.GetText(nowindex, cstring);
			
			m_image = Mat();
			
			for (int i = 0; i < imagelist.size(); i++)
			{

				Mat result;
				if (( m_image.cols == 0 && m_image.rows == 0 ))
				{
					
					m_image = Mat(imagelist[i].image.rows, imagelist[i].image.cols, imagelist[i].image.type() ,cv::Scalar(0,0,0,0));
					//cv::cvtColor(m_image, m_image, cv::COLOR_BGR2RGBA);
				}

				//addWeighted는 시간이 좀걸리는작업 호출횟수를 줄여야함
				if (imagelist[i].opacity < 1.0)
				{
					//if (isUsingScroll)
					//{
					//	cv::addWeighted(imagelist[i].image, imagelist[i].opacity, m_image, 1.0 - imagelist[i].opacity, 0.0, result);
					//	result.copyTo(m_image);
					//}
					//else
					//{

					//	m_image.copyTo(result);
					//}

					//m_image 가 백그라운드

					//imagelist[i].image가 foreground


					//m_image = 0.3 * m_image + 0.7 * cv::Scalar(0, 0, 0, 255);

					//result = imagelist[i].image * imagelist[i].opacity + (1.0 - imagelist[i].opacity) * m_image;

					int reduce_x = m_image.cols / zoomrate_y;
					int reduce_y = m_image.rows / zoomrate_y;

					//이걸 async로 바꿔야할지 말지 고민중

					//우클릭 드래그시 확대 화면을 출력해야하는데 지금은 출력이안됨
					
					//test 0826
					//drawrect = rect3;

					ImageAlphaBlend_Func(result, imagelist[i], m_image, &memDC, reduce_x, reduce_y, m_pBitmapInfo);
					//줌드로우일때 result가 계산이 덜됨

#if false

					if (투명도사용)
					{
						//되는코드
						result = imagelist[i].image * imagelist[i].opacity + (1.0 - imagelist[i].opacity) * m_image;
						//되는코드
						//cv::addWeighted(imagelist[i].image, imagelist[i].opacity, m_image, 1.0 - imagelist[i].opacity, 0.0, result);

					}
					else
					{
						m_image.copyTo(result);
					}
#endif

					//똑같이 지연됨
					//result = imagelist[i].image * imagelist[i].opacity + (1.0 - imagelist[i].opacity) * m_image;
					//cv::addWeighted(imagelist[i].image, imagelist[i].opacity, m_image, 1.0 - imagelist[i].opacity, 0.0, result);
					
					//ImageAlphaBlend_Func 가 비동기스레드여서 아마 빈화면이 카피될걸로 추정됨
					//result.copyTo(m_image);
					//result.release();


				}
				else
				{
					imagelist[i].image.copyTo(m_image);
				}


				if (cstring == imagelist[i].GetLayerName())
				{
					//이거 이후로 출력안되게해야함
					break;
				}
			}
			int x_startloc = 0 , x_endloc =0;
			int y_startloc = 0, y_endloc = 0;

			//지금 문제가 rect3는 줄이기 이전의 크기 
			//하지만 rect는 줄일 앞으로 줄일 크기여서 rect3의 rect가 계속적으로 클것이다
			//test1 zoomreate곱하기


			//현재 zoomrect를 그린 위치의 좌표구하기
			//rect.Width는 출력될 전체 크기의 Width여서 다른width를 찾아야함(줄인 이미지 크기)
			for (int i = 0; i < 6; i++)
			{
				if (drawrect.left < m_image.cols / zoomrate_y / 6 * (i+1) )
				{
					x_startloc = i  ;
					break;
				}
			}
			for (int i = 0; i < 6; i++)
			{
				//if (drawrect.Width() > rect.Width() / 6)
				//{
					if (drawrect.left + drawrect.Width() < m_image.cols / zoomrate_y / 6 * (i+1))
					{
						//x_endloc = x_startloc + i ;
						x_endloc = i;
						break;
					}
				//}
				//else
			//	{
					//x_endloc = x_startloc;
					//break;
				//}
			}

			for (int j = 0; j < 6; j++)
			{
				if (drawrect.top  < rect.Height() / 6 * (j+1))
				{
					y_startloc = j;
					break;
				}
			}
			for (int j = 0; j < 6; j++)
			{
				//if (drawrect.Height() > rect.Height() / 6)
				//{
					int a = drawrect.top + drawrect.Height();
					int b = rect.Height() / 6 * (j+1);
					if (a < b )
					{
						//y_endloc = y_startloc + j;
						y_endloc = j;
						break;
					}
				//}
				//else
				//{
				//	y_endloc = y_startloc;
				//	break;
				//}
			}
			
			list<int> changearray;
			//이미지 교체
			//목표 : 확대한 이미지에 해상도가 높은 이미지를 집어넣어 확대시 해상도가 높은 이미지만 보이도록
			if (rect.Height() != 0)
			{
				nowzoomrate = (double)drawrect.Height() / (double)rect.Height(); //세로 기준으로 그림을 그리기대문

				int onecols = m_image.cols / 6;
				int onerows = m_image.rows / 6;
				

				

				if (y_startloc != y_endloc)
				{
					if (x_startloc != x_endloc)
					{
						//여러개 선택됬다는 뜻
						for (int y = y_startloc; y < y_endloc + 1; y++)
						{
							for (int x = x_startloc; x < x_endloc + 1; x++)
							{
								//이미지 넘버 획득
								int changenumber = y * 6 + x;
								changearray.push_back(changenumber);
							}
						}
					}
					else
					{
						//세로 여러개
						for (int y = y_startloc; y < y_endloc + 1; y++)
						{
							//이미지 넘버 획득
							int changenumber = y * 6 + x_startloc;
							changearray.push_back(changenumber);
						}
					}
				}
				else
				{
					if (x_startloc != x_endloc)
					{
						//세로 한줄 가로여러개
						for (int x = x_startloc; x < x_endloc + 1; x++)
						{
							//이미지 넘버 획득
							int changenumber = y_startloc * 6 + x;
							changearray.push_back(changenumber);
						}

					}
					else
					{
						//둘다 한개
														//이미지 넘버 획득
						int changenumber = y_startloc * 6 + x_startloc;
						changearray.push_back(changenumber);
					}
				}
				//위의 코드는 변경할 좌표 및 이미지 넘버 계산식

				if (nowzoomrate < 0.5)
				{
					if (nowzoomrate < 0.1)
					{
						//1.0배율 이미지로 교체
						for (int i = 0; i < changearray.size(); i ++ )
						{
							//위치에 이미지를 바꾸는게아니라 m_image를 새로설계해서 그려야함?
							int num = changearray.front();

							for (int j = 0; j < imagelist.size(); j++)
							{

								std::string loadname = directoryPath + '\\';

								CT2CA pszConvertedLayerName(imagelist[j].GetLayerName());
								std::string layername(pszConvertedLayerName);

								int extensionindex = layername.find('.');
								layername = layername.substr(0, extensionindex);

								loadname = loadname + layername;
								loadname = loadname + "_1.0_";
								loadname  = loadname  + to_string(num);
								loadname += ".png";
								cv::Mat loadmat = imread(loadname , IMREAD_UNCHANGED);

							}

							TRACE("%d \n", changearray.front());
							changearray.pop_front();
							

						}
					
					}
					else
					{
						//0.5배율 이미지로 교체
						for (int i = 0; i < changearray.size(); i++)
						{
							

							int num = changearray.front();
							

							TRACE("%d \n", changearray.front());
							changearray.pop_front();

						}

					}
				}
			}
			TRACE("x_startloc %d x_endloc %d,\n y_startloc %d, y_endloc %d\n", x_startloc, x_endloc, y_startloc, y_endloc);
			
			//TRACE("Change image number \n");
			//if (changearray.size() > 0)
			//{
			//	int changearraysize = changearray.size();
			//	for (int i = 0; i < changearraysize ; i++)
			//	{
			//		
			//		TRACE("%d \n",changearray.front());
			//		changearray.pop_front();
			//	}
			//}
			
			//rect3의 크기만큼 이미지를 잘라서 자른 이미지를 확대하여 Rect에 맞추어 출력함
			StretchDIBits(memDC.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), rect3.left, m_image.rows - rect3.bottom,
				rect3.Width(), rect3.Height(), m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
						//imshow("test", m_image);



#endif



			//rect3.top / rect3.bottom =  y가 역 
			//#주의 Mat은 좌표가 역순이다


			/*m_image.Draw(memDC.m_hDC, rect, rect3);*/

			TRACE("left = %d top =%d right = %d bottom = %d\n", rect3.left, rect3.top, rect3.right, rect3.bottom);
			
			TRACE("\nWidth = %d Height = %d \n", rect3.Width(), rect3.Height());
			
			TRACE("bool_zoomstart is true \n");

			
		}
	}
	//임시버퍼를 PICCON에 그림
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	//이전비트맵으로 재설정 (rect그리기전의 비트맵)	
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();

}

void CMFCTestAppDlg::DrawRect(CDC* pDC)
{
	CRect rect;
	GetDlgItem(IDC_PICCON)->GetClientRect(&rect);

	//팬 설정
	CPen* pOldPen, pen;
	CBrush* pOldBrush;
	
	pen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	

	pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	pOldPen = pDC->SelectObject(&pen);

	drawrect=CRect(rect_start_position.x, rect_start_position.y, rect_end_position.x, rect_end_position.y);

	pDC->Rectangle(drawrect);
	pDC->SelectObject(pOldPen);

	pen.DeleteObject();

}

void CMFCTestAppDlg::DrawImage(CDC* pDC, bool ListSelect)
{
	CRect rect;
	GetDlgItem(IDC_PICCON)->GetClientRect(&rect);
#if false // m_image가 CImage일때
	if (m_image != nullptr) 
	{
		m_image.Draw(pDC->GetSafeHdc(), rect);
	}
#else
	if (!m_image.empty())
	{
		//원본 비율을 맞춰서 그려야함
		double zoom_x, zoom_y;
		zoom_x = zoomrate_x;
		zoom_y = zoomrate_y;

#if _true
		//지금 이미지가 1개일 경우 이렇게되있음
		SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, m_image.cols / zoom_y, m_image.rows / zoom_y, 0, 0,
			m_image.cols, m_image.rows, m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
#else

		SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);

		if (imagelist.size() > 0)   
		{
			// 모든 이미지들을 순서대로 m_image에 넣거나 덮어써야하는데..
			//냅다 memDC에 그릴경우(지금은 pDC) 추후 m_image에서 확대할때 문제가생겨 m_image에 그려야함
			int max_width = 0;
			int max_height = 0;

			//이미지중에 제일큰거찾기 아마 똑같은크기만 쓸거여서 형식적
			for (int i = 0; i < imagelist.size(); i++)
			{

				if (i > 0 && imagelist[i].GetImage().type() != imagelist[i - 1].GetImage().type())
				{

					TRACE("Warning : createOne failed, different type of images");
					return;
					//return cv::Mat();
				}
				max_height = std::max(max_height, imagelist[i].GetImage().rows);
				max_width = std::max(max_width, imagelist[i].GetImage().cols);

			}
			//ceil 반올림
			int rows = 1;
			int cols = imagelist.size();

			int reduce_x = m_image.cols / zoom_y;
			int reduce_y = m_image.rows / zoom_y;


			//cv::Mat result = cv::Mat::zeros(rows * max_height +	(rows - 1),
			//	cols * max_width + (cols - 1), imagelist[0].GetImage().type());

			//size_t i = 0;
			//int current_height = 0;
			//int current_width = 0;

			//for (int y = 0; y < rows; y++)
			//{
			//	for (int x = 0; x < cols; x++)
			//	{
			//		if (i >= imagelist.size())
			//			return;

			//		cv::Mat to(result,
			//			cv::Range(current_height, current_height + imagelist[i].GetImage().rows),
			//			cv::Range(current_width, current_width + imagelist[i].GetImage().cols)
			//		);
			//		imagelist[i++].GetImage().copyTo(to);
			//		//current_width += max_width;
			//	}

			//	current_width = 0;
			//	//current_height += max_height;


			//}
#if true
			int nowindex = 0;
			//int nowcount = m_list_box.GetCount();
			//int nowcursel = m_list_box.;
			nowindex = m_list_box.GetCurSel();
			if (nowindex == -1)
			{
				nowindex = m_list_box.GetCount() - 1;
				m_list_box.SetCurSel(nowindex);
			}
			CString cstring;
			m_list_box.GetText(nowindex, cstring);

			//m_image = Mat();
			TRACE("used DrawImage\n");
			if (drawZoomRect)
			{
				
			}
			else
			{
				for (int i = 0; i < imagelist.size(); i++)
				{
#if true
					if (i == 0)
					{
						m_image = Mat();
					}
					Mat result;
					if (m_image.cols == 0 && m_image.rows == 0)
					{
						m_image = Mat(imagelist[i].image.rows, imagelist[i].image.cols, imagelist[i].image.type(), cv::Scalar(0, 0, 0, 0));
						//cv::cvtColor(m_image, m_image, cv::COLOR_BGR2RGBA);
					}

					//addWeighted는 시간이 좀걸리는작업 호출횟수를 줄여야함


					if (imagelist[i].opacity < 1.0)
					{
						//bool 식별해야함

						/*Mat result2;

						cv::resize(imagelist[i].image, result, Size(reduce_x, reduce_y));

						cv::resize(m_image, result2, Size(reduce_x, reduce_y));

						result = result * imagelist[i].opacity + (1.0 - imagelist[i].opacity) * result2;*/


						//opacity를 또만들어야하ㄴ
						//test 1 thread로 비동기식 투명화 진행 
						//비동기 + 전역변수 건들이면 좋지않은데.. 

						Image_info aimageinfo = imagelist[i];

						//thread testthread = thread(ImageAlphaBlend, result, aimageinfo,  m_image);

#if false
						std::future<Mat> futureresult = std::async(ImageAlphaBlend,result,aimageinfo,m_image, pDC, reduce_x, reduce_y, m_pBitmapInfo);

						//비동기스레드로 리턴값이 발생할경우 그값을 m_image에 저장을해야함

						

						return;
#else
						//일반thread를 사용시 딜레이가 발생함

						//std::thread blendthread = thread(ImageAlphaBlend_Func, result, imagelist[i], m_image, pDC, reduce_x, reduce_y, m_pBitmapInfo);

						//blendthread.join();

						//더블클릭 , 투명도조절시
						ImageAlphaBlend_Func(result, imagelist[i], m_image, pDC, reduce_x, reduce_y, m_pBitmapInfo);
						
						//result.copyTo(m_image); 여기넣으면 비동기스레드라 빈이미지를 복사해서 문제발생함
						if (i == imagelist.size() - 1)
						{
							//Sleep(1000);
							//break;
							break;
						}

						if (cstring == imagelist[i].GetLayerName())
						{
							//이거 이후로 출력안되게해야함
							break;
						}
						else
							continue;
#endif
						//result = futureresult.get();

						//result = futureresult.get();

//						testthread.join();
								//result = imagelist[i].image * imagelist[i].opacity + (1.0 - imagelist[i].opacity) * m_image;
						/*
						if (투명도사용)
						{
							//되는코드
							result = imagelist[i].image * imagelist[i].opacity + (1.0 - imagelist[i].opacity) * m_image;
							//되는코드
							//cv::addWeighted(imagelist[i].image, imagelist[i].opacity, m_image, 1.0 - imagelist[i].opacity, 0.0, result);

						}
						else
						{

							m_image.copyTo(result);
							break;

							TRACE("");
							//여기가 잘못됨 다음 이미지를 그려야하는데 m_image를 그려서 아무것도 안나오게만듬
							//m_image.copyTo(result);
						}
						*/


					}
					else if (imagelist[i].opacity == 1.0)
					{
						//cv::resize(imagelist[i].image, result, Size(reduce_x, reduce_y));
						imagelist[i].image.copyTo(m_image);
						if (cstring == imagelist[i].GetLayerName())
						{
							//이거 이후로 출력안되게해야함
							break;
						}
						else
						continue;


						//imagelist[i].image.copyTo(result);
					}
					else
					{
						if (cstring == imagelist[i].GetLayerName())
						{
							//이거 이후로 출력안되게해야함
							break;
						}
						else
							continue;

						//m_image.copyTo(result);
						//그냥 m_image 카피가아니라 투명화한 이미지를 위에그려야함

					}
					try
					{
						result.copyTo(m_image);

						result.release();
						//result.copyTo(m_image);
					}
					catch (Exception ex)
					{
						TRACE("%s", ex.msg);
					}
					if (cstring == imagelist[i].GetLayerName())
					{
						//이거 이후로 출력안되게해야함
						break;
					}

#else
					imagelist[i].GetImage().copyTo(m_image);

					if (cstring == imagelist[i].GetLayerName())
					{

						//이거 이후로 출력안되게해야함
						break;
					}
#endif 
				}
			}

			StretchDIBits(pDC->GetSafeHdc(), 0, 0, reduce_x,reduce_y, 0, 0,
				m_image.cols, m_image.rows , m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
				
		
		//imshow("test", m_image);

#else
			if (ListSelect)
			{
				//리스트 선택으로 화면 출력시 작동 Zoom하지 않은채

				int nowindex = 0;
				//int nowcount = m_list_box.GetCount();
				//int nowcursel = m_list_box.;
				nowindex = m_list_box.GetCurSel();
				CString cstring;
				m_list_box.GetText(nowindex, cstring);

				for (int i = 0; i < imagelist.size(); i++)
				{
					StretchDIBits(pDC->GetSafeHdc(), 0, 0, imagelist[i].GetImage().cols / zoom_y, imagelist[i].GetImage().rows / zoom_y, 0, 0,
						imagelist[i].GetImage().cols, imagelist[i].GetImage().rows, imagelist[i].GetImage().data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

					if (cstring == imagelist[i].GetLayerName())
					{
						//이거 이후로 출력안되게해야함
						break;
					}
				}

			}
			else
			{
				for (int i = 0; i < imagelist.size(); i++)
				{
					//result.copyTo(m_image);


					StretchDIBits(pDC->GetSafeHdc(), 0, 0, imagelist[i].GetImage().cols / zoom_y, imagelist[i].GetImage().rows / zoom_y, 0, 0,
						imagelist[i].GetImage().cols, imagelist[i].GetImage().rows, imagelist[i].GetImage().data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
				}
			}
#endif
			/*result.copyTo(m_image);

			StretchDIBits(pDC->GetSafeHdc(), 0, 0, m_image.cols / zoom_y, m_image.rows / zoom_y, 0, 0,
				m_image.cols, m_image.rows, m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);*/
			return;
		}
		else
		{
			//imagelist갯수가 1개이고 m_image가 nullptr이 아닐경우
			
			//SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
			int reduce_x = m_image.cols / zoom_y;
			int reduce_y = m_image.rows / zoom_y;


			StretchDIBits(pDC->GetSafeHdc(), 0, 0, reduce_x, reduce_y, 0, 0,
				m_image.cols, m_image.rows, m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);


			//StretchDIBits(pDC->GetSafeHdc(), 0, 0, m_image.cols / zoom_y, m_image.rows / zoom_y, 0, 0,
			//	m_image.cols, m_image.rows, m_image.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		}
#endif
	}
#endif
}



void CMFCTestAppDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다. fileopen
	CString filter = _T("(*.*)|*.*");
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY, filter);
	CImage loadimage;
	


	if (dlg.DoModal() == IDOK)
	{
		m_image = Mat();

		CString pathname = dlg.GetPathName();
#if true // 처음 열었을때 큰이미지인가 작은이미지인가 판별후 큰이미지일경우 작은이미지로 나누어 화면에 띄우는 코드
		//일단 큰이미지인가 여부는 제외하고 temp폴더 여부 확인후 만들어 이미지 나누기
		int lastslash = pathname.ReverseFind('\\');
		int stringlength = pathname.GetLength();

		CString DirectoryPath = pathname.Left(lastslash);
		DirectoryPath += "\\Temp";


		CT2CA pszConvertedAnsiString(DirectoryPath);
		std::string convert_directorypath(pszConvertedAnsiString);


		directoryPath = convert_directorypath;

		if (GetFileAttributes(DirectoryPath) == -1)
		{
			TRACE("not exist Temp Directory\n %s\n", DirectoryPath);
			CreateDirectory(DirectoryPath, NULL);

		}
		else
		{
			TRACE("exist Temp Directory\n");

		}	
#endif



#if false //Cimage 사용할떄
		//에러 무시하면 잘됨
		m_image.Destroy(); // 추가시 에러발생X


		m_image.Load(pathname);
		
		CRect rect;
		GetDlgItem(IDC_PICCON)->GetClientRect(&rect);

		zoomrate_x = m_image.GetWidth() / rect.Width();
		zoomrate_y = m_image.GetHeight() / rect.Height();


		
#else
		//Mat사용 25000x25662까진잘됨

		CRect rect;
		GetDlgItem(IDC_PICCON)->GetClientRect(&rect);

		CT2CA pszConvertedAnsiString2(pathname);
		std::string s(pszConvertedAnsiString2);


		CString substring = pathname.Right(stringlength - lastslash - 1);

		Image_info aimage_info;

		try
		{



			//임시로 크기 8000제한

			//std::regex re(DirectoryPath + '\\' + "\\d*\\", std::regex::grep | std::regex::icase);

			CFileFind finder;

			//BOOL bWorking = finder.FindFile(DirectoryPath+"\\)

			//if (GetFileAttributes(DirectoryPath+'\\'+"substring\\d*\\") != -1)
			//{
			//	
			//}
			//else
			//{
			//	
			//}

			HANDLE fileSearch;
			WIN32_FIND_DATA wfd;

			int extension_index = substring.ReverseFind('.');

			CString filename_notextension = substring.Left(extension_index);
			CString filepath_not_extension = DirectoryPath + '\\' + filename_notextension + "*";


			// 이미지이름* 이있으면 파일이 다있다고 판단함
			fileSearch = FindFirstFile(filepath_not_extension,&wfd);

			if (fileSearch != INVALID_HANDLE_VALUE)
			{
				TRACE("DirectoryPath not first");

				//파일이 있으니 합쳐서 m_image로 만들기
		
				Mat onelineMat;

				for (int imagecount = 0; imagecount < 36; imagecount++)
				{
					CString openpath;
					CString str;

					std::stringstream ssInt;
					ssInt << imagecount;

					openpath = filepath_not_extension.Left(filepath_not_extension.GetLength() - 1) + _T("_0.2_");
					
					CT2CA pszConvert(openpath);
					std::string openpath_str(pszConvert);
					openpath_str += ssInt.str() + ".png";

					Mat openmat = imread(openpath_str, IMREAD_UNCHANGED);
					//0.2면 이미지 잡아늘리기
					//if (openpath_str.find("0.2") > 0)
					//{
					//	TRACE("IN \n");
					//	//5배로하니까 출력이 검은화면이되버림
					//	cv::resize(openmat, openmat, cv::Size(openmat.cols * 5, openmat.rows * 5));

					//}

					aimage_info.mini_image[imagecount] = openmat;

					if (onelineMat.cols == 0 || onelineMat.rows == 0)
					{
						onelineMat = openmat;
					}
					else
					{
						hconcat(onelineMat, openmat, onelineMat);
						if (imagecount % 6 == 5 )
						{
							if (m_image.cols == 0 || m_image.rows == 0)
							{
								m_image = onelineMat;
							}
							else
							{
								vconcat(m_image, onelineMat, m_image);
							}
							onelineMat = Mat();

						}


					}

				}

				
			}
			else
			{
				//처음 파일을 열어서 이미지를 자르고 따로 저장해주는 코드포함(ImageDivideFunc)


				TRACE("DirectoryPath first");

#if true
				m_image = imread(s, IMREAD_UNCHANGED);

				if (m_image.cols * m_image.rows > 640000000)//640,000,000
				{ 
					//이미지는 6x6으로 해상도 0.2 0.5 1.0으로 조절해서 3단계로 저장후 현재 줌상태에 따라서 3단계로 불러올것이다
				
					filepath_not_extension = DirectoryPath + '\\' + filename_notextension;

					/*thread t1 = thread(ImageDivideFunc, m_image, 1.0, filepath_not_extension);
					thread t2 = thread(ImageDivideFunc, m_image, 0.5, filepath_not_extension);
					thread t3 = thread(ImageDivideFunc, m_image, 0.2, filepath_not_extension);

					t1.join();
					t2.join();
					t3.join();*/

					std::future<Mat> f1 = std::async(ImageDivideFunc, m_image, 0.2 , filepath_not_extension);
					//std::future<Mat> f2 = std::async(ImageDivideFunc, m_image, 0.5, filepath_not_extension);
					//std::future<Mat> f3 = std::async(ImageDivideFunc, m_image, 0.2, filepath_not_extension);
					//std::future<Mat> f2 = std::async(ImageDivideFunc, m_image, 0.5, filepath_not_extension);
					//std::future<Mat> f3 = std::async(ImageDivideFunc, m_image, 1.0, filepath_not_extension);
					thread t2 = thread(ImageDivideFunc, m_image, 0.5, filepath_not_extension);
					thread t3 = thread(ImageDivideFunc, m_image, 1.0, filepath_not_extension);
					t2.join();
					t3.join();


					//큰이미지를 낮은해상도로 나눠 저장한 이미지들을 붙여서 낮은 해상도로 합친후 출력해야함


					m_image = f1.get();


				}
				else
				{

				}

#else
				filepath_not_extension = DirectoryPath + '\\' + filename_notextension;

				thread t1 = thread(ImageDivideFunc, m_image, 1.0, filepath_not_extension);
				thread t2 = thread(ImageDivideFunc, m_image, 0.5, filepath_not_extension);
				thread t3 = thread(ImageDivideFunc, m_image, 0.2, filepath_not_extension);

				t1.join();
				t2.join();
				t3.join();

#endif
				FindClose(fileSearch);
			}

			//if(FindFirstFile(DirectoryPath + '\\' + "substring\\d*\\", ))





			zoomrate_x = (double)m_image.cols / (double)rect.Width();
			//zoomrate_y = zoomrate_x;
			zoomrate_y = (double)m_image.rows / (double)rect.Height();
			//zoomrate_x = zoomrate_y;



		}
		catch (Exception ex)
		{
			TRACE("imread exception");

		}




#endif
		


#if true //0618 문제 이걸 지우니까 오류없음


		




		//m_image를 사용해서 그런거같음 m_image를 복사해서 넣는게 아니라 주소값만 건들이는거 같아서 m_image에를 쓴데에서 다문제가발새아는거가음
		//int resize_cols, resize_rows;

		//if (m_image.cols % 2 == 1)
		//{
		//	resize_cols = m_image.cols + 1;
		//}
		//else
		//{
		//	resize_cols = m_image.cols;
		//}
		//if (m_image.rows % 2 == 1)
		//{
		//	resize_rows = m_image.rows + 1;
		//}
		//else
		//{
		//	resize_rows = m_image.rows;
		//}
		//resize(m_image, m_image, cv::Size(resize_cols, resize_rows));


		CreateBitampInfo(m_image.cols, m_image.rows, m_image.channels() * 8);

		//이게 투명도조절이네
		//m_image = 0.3 * m_image + 0.7 * cv::Scalar(0, 0, 0, 255);


		//m_image.convertTo(m_image, CV_32FC3, 125.0/255); 
		TRACE("\n @@@@@@@@@ MAT TYPE = %d \n", m_image.type() );

		aimage_info.SetValue(global_index++, substring, m_image);
		aimage_info.opacity = 1.0;
		//cv::imshow("test", aimage_info.image);

		//aimage_info.originHeight = m_image.rows * 5; //일단엄청큰 이미지를 잘라서 해상도를 줄여 처음 출력하기 때문에 처음 해상도 크기 *5배가 origin크기가 된다
		//aimage_info.originWidth = m_image.cols * 5;

		aimage_info.originHeight = m_image.rows ; 
		aimage_info.originWidth = m_image.cols ;


		imagelist.push_back(aimage_info);

		m_list_box.AddString(substring);


		m_slide.SetPos(100);

		listcount++;
#endif
		//
		
		//CString substring;
		//int lastslash = pathname.ReverseFind`('\\');
		//int stringlength = pathname.GetLength();
		//substring = pathname.Right(stringlength - lastslash - 1);
		
		
		
		OnDrawImage();


		

	}

	//CDialogEx::OnOK();
}



void CMFCTestAppDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	bool_drawingrect = true;
	CRect rect;
	GetDlgItem(IDC_PICCON)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	bool_zoomstart = false;

	//더블버퍼링시 zoomrect를 그릴까말까 여부
	drawZoomRect = true;

	rect_start_position.x = point.x - rect.left;
	rect_start_position.y = point.y - rect.top;

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CMFCTestAppDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (bool_drawingrect) 
	{
		//CRect rect;
		//GetDlgItem(IDC_PICCON)->GetWindowRect(&rect);
		//ScreenToClient(&rect);

		//rect_end_position.x = point.x - rect.left;
		//rect_end_position.y = point.y - rect.top;

		bool_zoomstart = true;

		OnMouseMove(nFlags, point);
		bool_drawingrect = false;
		int temp;

		//if (drawrect != nullptr)
		//{
		//	if (drawrect.left > drawrect.right)
		//	{
		//		temp = drawrect.right;
		//		drawrect.right = drawrect.left;
		//		drawrect.left = temp;
		//		
		//	}
		//	else
		//	{
		//		//temp = drawrect.left;
		//		//drawrect.left = drawrect.right;
		//		//drawrect.right = temp;
		//	}

		//	if (drawrect.top < drawrect.bottom)
		//	{
		//		temp = drawrect.bottom;
		//		drawrect.bottom = drawrect.top;
		//		drawrect.top = temp;

		//	}
		//}
	}

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CMFCTestAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (bool_drawingrect)
	{
		CRect rect;
		GetDlgItem(IDC_PICCON)->GetWindowRect(&rect);
		ScreenToClient(&rect);


		rect_end_position.x = point.x - rect.left;
		rect_end_position.y = point.y - rect.top;

		OnDrawImage();

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCTestAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCTestAppDlg::DoubleClickEvent()
{

}


void CMFCTestAppDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//왼쪽 더블클릭 인덱스
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	bool_zoomstart = false;
	drawZoomRect = false;
	//여기서 기본 더블클릭시 원래화면 복귀 + ZoomRect를 삭제해야함
	//ZoomRect 삭제하려면 memDC에 그냥 zoomRect없이 새로그려야함
	OnDrawImage();


	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CMFCTestAppDlg::OnDblclk_ListBoxitem()
{
	//doubleclick 리스트 더블클릭
	//리스트박스 더블클릭시 이벤트
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nowindex = 0;
	//int nowcount = m_list_box.GetCount();
	//int nowcursel = m_list_box.;
	nowindex = m_list_box.GetCurSel();
	CString cstring;
	m_list_box.GetText(nowindex,cstring);

	for each (Image_info var in imagelist)
	{
		//if (nowindex == var.GetLayerNum())
		if(cstring == var.GetLayerName())
		{
			//m_image = var.GetImage();
			int Pos = var.opacity * 100;

			m_slide.SetPos(Pos);


			OnDrawImage(true);
			break;
		}

	}

	int now_sel_index = m_list_box.GetCurSel();



	

}

void CMFCTestAppDlg::CreateBitampInfo(int w, int h, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else
		m_pBitmapInfo = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFO)];


	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	//m_pBitmapInfo->bmiHeader.biBitCount = 32;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	//m_pBitmapInfo->bmiHeader.biCompression = 
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;



	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}


void CMFCTestAppDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//slideValue 값 변경 수평
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	isUsingScroll = true;
	
	int nowindex = 0;
	//int nowcount = m_list_box.GetCount();
	//int nowcursel = m_list_box.;
	nowindex = m_list_box.GetCurSel();
	CString cstring;
	if (nowindex == -1)
	{
		CWnd::MessageBox(_T("선택되지 않은 Layer입니다"), _T("System Message"), MB_ICONWARNING);
		return;
	}
	m_list_box.GetText(nowindex, cstring);

	for (int i = 0; i < imagelist.size(); i++)
	{
		if (imagelist[i].GetLayerName() == cstring)
		{
			imagelist[i].opacity = (double)m_slide.GetPos() / 100;
			bool_useopcaity = true;
			
			//0823 test hscoll을 스레드를 이용하여 함수실행

			thread testthread = thread(HscrollThread_func,this);


			testthread.detach();

			//OnDrawImage();
			bool_useopcaity = false;

			break;
		}
	}
	isUsingScroll = false;
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CMFCTestAppDlg::HscrollThread_func(void* pointer)
{
	CMFCTestAppDlg* pThis = reinterpret_cast<CMFCTestAppDlg *>(pointer);
	pThis->OnDrawImage();

	pThis->Invalidate(false); 
}





void CMFCTestAppDlg::blendImageToMiddle(cv::Mat background, cv::Mat image)
{

	int backStartX = background.cols / 2 - image.cols / 2;
	int backStartY = background.cols / 2 - image.rows / 2;

	cv::Mat blendMat = background(cv::Range(backStartY, backStartY  + image.rows),
		cv::Range(backStartX, backStartX + image.cols));

	for (int y = 0; y < image.rows; ++y)
	{
		for (int x = 0; x < image.cols; ++x)
		{
			cv::Vec3b& backgroundPixel = blendMat.at<cv::Vec3b>(y, x);
			cv::Vec4b& imagePixel = image.at<cv::Vec4b>(y, x);

			float alpah = imagePixel[3] / 255;

			backgroundPixel[0] = cv::saturate_cast<uchar>(alpah * imagePixel[0] + (1.0 - alpah) * backgroundPixel[0]);
			backgroundPixel[1] = cv::saturate_cast<uchar>(alpah * imagePixel[1] + (1.0 - alpah) * backgroundPixel[1]);
			backgroundPixel[2] = cv::saturate_cast<uchar>(alpah * imagePixel[2] + (1.0 - alpah) * backgroundPixel[2]);

		
		}
	}

}

void CMFCTestAppDlg::overlayImage(const Mat& background, const Mat& foreground,
	Mat& output, Point2i location)
{
	background.copyTo(output);


	// start at the row indicated by location, or at row 0 if location.y is negative.
	for (int y = std::max(location.y, 0); y < background.rows; ++y)
	{
		int fY = y - location.y; // because of the translation

								 // we are done of we have processed all rows of the foreground image.
		if (fY >= foreground.rows)
			break;

		// start at the column indicated by location, 

		// or at column 0 if location.x is negative.
		for (int x = std::max(location.x, 0); x < background.cols; ++x)
		{
			int fX = x - location.x; // because of the translation.

									 // we are done with this row if the column is outside of the foreground image.
			if (fX >= foreground.cols)
				break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity =
				((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

				/ 255.;


			// and now combine the background and foreground pixel, using the opacity, 

			// but only if opacity > 0.
			for (int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					foreground.data[fY * foreground.step + fX * foreground.channels() + c];
				unsigned char backgroundPx =
					background.data[y * background.step + x * background.channels() + c];
				output.data[y * output.step + output.channels() * x + c] =
					backgroundPx * (1. - opacity) + foregroundPx * opacity;
			}
		}
	}
}

Mat CMFCTestAppDlg::ImageDivideFunc(Mat mat, double zoom, CString filename)
{
	int cols = mat.cols / 6;
	int rows = mat.rows / 6;

	Mat returnMat = Mat();

	for (int i = 0; i < 6; i++)
	{// i = y축
		Mat onelineMat = Mat();

		for (int j = 0; j < 6; j++)
		{//j = x 축
			Mat resultmat = mat(Range(rows * i, rows * (i + 1)), Range(cols*j,cols*(j+1) ));
			resize(resultmat, resultmat, cv::Size(resultmat.cols * zoom, resultmat.rows * zoom));
			cv::String savename;

			Mat outputmat;

			cv::cvtColor(resultmat, outputmat, cv::COLOR_BGR2BGRA);
			cv::Mat abgr(outputmat.size(), outputmat.type());

			//argb > rgba
			int from_to[] = { 0,3, 1,1, 2,2, 3,0 };


			//mixchannels사용한 이유는 24비트일때 cols rows가 홀수일경우 이미지가 깨지는 현상발생
			//그래서 추후 사용될이미지는 32비트로 변환하여 사용
			cv::mixChannels(&outputmat, 1, &abgr, 1, from_to, 4);
			//cv::mixChannels(&onelineMat, 1, &abgr, 1, from_to, 4);
			savename = filename + "_";// +to_string(zoom) + "_" + (i * 6 + j);
			savename += to_string(zoom).substr(0,3) + "_";
			std::stringstream ssInt;
			ssInt << (i * 6 + j);
			savename += ssInt.str() + ".png";

			//imwrite(savename, resultmat);
			if (zoom == 0.2)
			{
				if (onelineMat.cols == 0 || onelineMat.rows == 0)
				{
					outputmat.copyTo(onelineMat);
					//int elemsize = onelineMat.elemSize();
					//int elemsize2 = resultmat.elemSize();
					//int elemsize3 = outputmat.elemSize();
					//cv::mixChannels(&onelineMat, 1, &abgr, 1, from_to, 4);
					//onelineMat = resultmat;
				}
				else
				{
					hconcat(onelineMat, outputmat, onelineMat);

					if (j == 5)
					{
						if (returnMat.cols == 0 || returnMat.rows == 0)
						{
							onelineMat.copyTo(returnMat);
						}
						else
							vconcat(returnMat, onelineMat, returnMat);
					}
				}
			}
			imwrite(savename, outputmat);

		}
	}

	return returnMat;

}

Mat CMFCTestAppDlg::ImageAlphaBlend_Func(Mat result2, Image_info imagelist, Mat m_image2, CDC *pDC, int reduce_x , int reduce_y, BITMAPINFO *m_pBitmapInfo )
{
#if false // test
	result2 = imagelist.image * imagelist.opacity + (1.0 - imagelist.opacity) * m_image2;
	TRACE("AlpahBlend On \n");


	//필요한거 HDC,Mat,BitmapInfo
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, reduce_x, reduce_y, 0, 0,
		result2.cols, result2.rows, result2.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

#else
	//Mat resultmat = mat(Range(rows * i, rows * (i + 1)), Range(cols * j, cols * (j + 1)));

	//test1 조각이미지 다 블랜드후 합치기
	int rows = m_image2.rows / 6;
	int cols = m_image2.cols / 6;


	for (int imagecount = 0; imagecount < 36; imagecount++)
	{
		int i = imagecount / 6;
		int j = imagecount % 6;


		//Mat range_mimage = m_image2(Range(rows * i, rows * (i + 1)), Range(cols * j, cols * (j + 1)));
		//
		//Mat alphablendMat = imagelist.mini_image[imagecount] * imagelist.opacity + (1.0 - imagelist.opacity) * range_mimage;
		////ProcessWindowMessage();
		//Mat change_location_mimage = m_image2(Rect(cols * j, rows * i, cols, rows) );

		//change_location_mimage = alphablendMat;

		//alphablendMat.copyTo(m_image2(cv::Rect(cols * j, rows * i, cols, rows)));

//		if (imagecount != 0 && i == 0) // 1스레드가 6개의 이미지를 처리하도록 변경해야함
		if(imagecount % 6 == 0)
		{
			//thread 완료 식별 bool



			
			std::thread testthread = thread(TestThreadFunc, m_image2,  pDC, reduce_x, reduce_y,
				m_pBitmapInfo, imagelist, imagecount ,this );


			testthread.detach();
			TRACE("Delay ON \n");
			Sleep(100);//150 일때는 4번줄부터 안보였음
		}
	}

	//StretchDIBits(
	//	pDC->GetSafeHdc(), 0, 0, reduce_x, reduce_y, 0, 0,
	//	m_image2.cols, m_image2.rows, m_image2.data,
	//	m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);



#endif
	return result2;
}

void CMFCTestAppDlg::TestThreadFunc(Mat m_image2, CDC* pDC, int reduce_x, int reduce_y, 
	BITMAPINFO* m_pBitmapInfo, Image_info imagelist, int imagecount, void *pointer)
{

	CMFCTestAppDlg* pThis = reinterpret_cast<CMFCTestAppDlg*>(pointer);

	int rows = m_image2.rows / 6;
	int cols = m_image2.cols / 6;

	int i = imagecount / 6;
	int j = imagecount % 6;

	bool thread_bool0 = false;
	bool thread_bool1 = false;
	bool thread_bool2 = false;
	bool thread_bool3 = false;
	bool thread_bool4 = false;
	bool thread_bool5 = false;

	for (; imagecount / 6 != i+1; imagecount++)
	{

		j = imagecount % 6;
		Mat range_mimage = m_image2(Range(rows * i, rows * (i + 1)), Range(cols * j, cols * (j + 1)));

		Mat alphablendMat = imagelist.mini_image[imagecount] * imagelist.opacity + (1.0 - imagelist.opacity) * range_mimage;
		//ProcessWindowMessage();
		Mat change_location_mimage = m_image2(Rect(cols * j, rows * i, cols, rows));

		change_location_mimage = alphablendMat;

		alphablendMat.copyTo(m_image2(cv::Rect(cols * j, rows * i, cols, rows)));
		try 
		{
			//StretchDIBits(
			//	pDC->GetSafeHdc(), 0, 0, reduce_x, reduce_y, 0, 0,
			//	m_image2.cols, m_image2.rows, m_image2.data,
			//	m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			//pThis->Invalidate(false);
			//if (i == 5 && j == 5)
			//{
			//	thread_bool5 = true;
			//	pThis->refresh(pDC, m_image2, reduce_x, reduce_y);
			//}

		}
		catch (Exception ex)
		{
			TRACE("%s", ex.msg);
		}
		TRACE("output image x = %d y = %d\n", i, j);

		//pThis->refresh(pDC, m_image2, reduce_x, reduce_y);


		//여기 딜레이는 의미가 없는것같음

	}
	pThis->refresh(pDC, m_image2, reduce_x, reduce_y);

	//free(&range_mimage);
	//free(&alphablendMat);
	//free(&change_location_mimage);

	//pThis->Invalidate(FALSE);

	
}


void CMFCTestAppDlg::refresh(CDC* pDC, Mat m_image2, int reduce_x, int reduce_y)
{

	//한칸마다 refresh를하네? 스레드 끝나고 다시그리는 함수
	TRACE("CALLED REFRESH_FUNC");
	CClientDC dc(GetDlgItem(IDC_PICCON));

	CRect rect;

	GetDlgItem(IDC_PICCON)->GetClientRect(&rect);

	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	//Picture Control DC에 호환되는ㄴ CDC를생성
	memDC.CreateCompatibleDC(&dc);

	// PicCon의 크기와 동일한 비트맵을 생성
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	//임시버퍼에서 방금 생성된 비트맵 선택, 이전 비트맵 저장
	pOldBitmap = memDC.SelectObject(&bitmap);

	//임시버퍼를 검은색으로 채움
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	SetStretchBltMode(memDC.GetSafeHdc(), COLORONCOLOR);


	if (drawZoomRect)
	{
		//rect3 는 drawrrect 의 크기를 현재 상황에 맞추어 계산한 rect의 크기

		CRect rect3((drawrect.left) * zoomrate_y, drawrect.top * zoomrate_y, (drawrect.left + drawrect.Width()) * zoomrate_y, (drawrect.top + drawrect.Height()) * zoomrate_y);

		int temp;

		if (rect3.left > rect3.right)
		{
			temp = rect3.left;
			rect3.left = rect3.right;
			rect3.right = temp;
		}

		if (rect3.top > rect3.bottom)
		{
			temp = rect3.top;
			rect3.top = rect3.bottom;
			rect3.bottom = temp;
		}

		StretchDIBits(memDC.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), rect3.left, m_image2.rows - rect3.bottom,
			rect3.Width(), rect3.Height(), m_image2.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		
	}
	else
	{
		StretchDIBits(
			memDC.GetSafeHdc(), 0, 0, reduce_x, reduce_y, 0, 0,
			m_image2.cols, m_image2.rows, m_image2.data,
			m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);


	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	//이전비트맵으로 재설정 (rect그리기전의 비트맵)	

	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
}


void ProcessWindowMessage()

{

	MSG msg;

	while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))

	{

		::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);

	}

}


void CMFCTestAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CWnd* pCtrl = GetDlgItem(IDC_PICCON);

	if (!pCtrl) { return; }

	CRect rectCtrl;
	pCtrl->GetWindowRect(&rectCtrl);
	ScreenToClient(&rectCtrl);

	pCtrl->MoveWindow(rectCtrl.left, rectCtrl.top, cx - 2 * rectCtrl.left, cy - rectCtrl.top - rectCtrl.left, TRUE);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
