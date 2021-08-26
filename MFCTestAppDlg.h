
// MFCTestAppDlg.h: 헤더 파일
//

#pragma once
#include "Image_info.h"
#include <vector>
#include <opencv2/core.hpp>


using namespace cv;


// CMFCTestAppDlg 대화 상자
class CMFCTestAppDlg : public CDialogEx
{
	// 생성입니다.
public:
	CMFCTestAppDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTESTAPP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Mat m_image; //화면에 출력될 이미지


	BITMAPINFO* m_pBitmapInfo;

	CRect picconrect;//윈도우 크기 바뀔때마다 크기를바꿔야함

	CPoint rect_start_position, rect_end_position;

	void OnDrawImage(bool ListSelect = false); // Double Bufferring 그리는 작업
	void DrawRect(CDC* pDC); // Double Buffering 내 Rect를 그리는 작업
	void DrawImage(CDC* pDC, bool ListSelect = false); // Double Bufferring  내 이미지를 그리는 작업
	afx_msg void OnBnClickedOk();

	CRect drawrect;


	double nowzoomrate = 1.0;
	double zoomrate_x = 1.0, zoomrate_y = 1.0;

	bool bool_drawingrect, bool_zoomstart;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//더블클릭 카운트
	int doubleclick_count = 0;

	void DoubleClickEvent();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// listbox변수임
	CListBox m_list_box;
	afx_msg void OnDblclk_ListBoxitem();

	std::vector<Image_info> imagelist;

	int global_index = 0;;
	int listcount = 0;

	void CreateBitampInfo(int w, int h, int bpp);
	// 현재 이미지의 alpha값
	CSliderCtrl m_slide;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	bool drawZoomRect = false;

	void blendImageToMiddle(cv::Mat background, cv::Mat image);

	void overlayImage(const Mat& background, const Mat& foreground,
		Mat& output, Point2i location);

	std::vector<double> opacitylist;

	//지금 Hscroll을 사용하고있는가여부
	bool isUsingScroll = false;

	static Mat ImageDivideFunc(Mat mat, double zoom, CString filename);

	//불러온 이미지의 이름을 전역이나 OndrawImage에 사용해야함 아마 전역이 좋아보임 
	//이유는 지금 OnDrawImage는 매개변수로 받는게 너무많아서 더받을경우 너무 복잡해짐
	//filepath_not_extension 이 완성되고 난 이후에 불러오는게 좋아보임 어짜피 확장자는 png고정

	std::string directoryPath;

	bool bool_useopcaity;

	Mat ImageAlphaBlend_Func(Mat result2, Image_info imagelist, Mat m_image2, CDC* pDC, int reduce_x, int reduce_y, BITMAPINFO* m_pBitmapInfo);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
 	static void TestThreadFunc(Mat result2, CDC* pDC, int reduce_x, 
		int reduce_y, BITMAPINFO* m_pBitmapInfo, Image_info imagelist, int imagecount
	, void *pointer);


	

	// 쓰레드 동작 유무 확인 Bool

	bool thread_bool0 = false;
	bool thread_bool1 = false;
	bool thread_bool2 = false;
	bool thread_bool3 = false;
	bool thread_bool4 = false;
	bool thread_bool5 = false;

	static void HscrollThread_func(void* pointer);

	static void ListDbclickThread_func(void* pointer);

	void refresh(CDC* pDC,Mat m_image,int reduce_x, int reduce_y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

void ProcessWindowMessage();
