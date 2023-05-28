
// spin_fansDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "spin_fans.h"
#include "spin_fansDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CspinfansDlg 对话框



CspinfansDlg::CspinfansDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPIN_FANS_DIALOG, pParent)
	, Target_speed(0)
	, position(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	expected_speed = 0;
	speed = 0;
}

void CspinfansDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editBox);
	//  DDX_Control(pDX, IDC_EDIT3, Target_speed);
	DDX_Text(pDX, IDC_EDIT3, Target_speed);
	DDX_Text(pDX, IDC_EDIT4, position);
}

BEGIN_MESSAGE_MAP(CspinfansDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CspinfansDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CspinfansDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CspinfansDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CspinfansDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CspinfansDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CspinfansDlg 消息处理程序

BOOL CspinfansDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	rotate_direction = -1;
	expected_speed = 1;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CspinfansDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CspinfansDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect clientRect;
	GetClientRect(&clientRect);
	m_center = CPoint(clientRect.Width() / 2, clientRect.Height() / 2);

	const double lineLength = 100.0;  // 直线长度
	const double angleIncrement = 72.0;  // 直线之间的角度增量

	for (int i = 0; i < 5; ++i) {
		double angle = (i * angleIncrement + m_rotationAngle) * 3.14159265358979323846 / 180.0;
		int x = m_center.x + static_cast<int>(lineLength * cos(angle));
		int y = m_center.y - static_cast<int>(lineLength * sin(angle));

		dc.MoveTo(m_center);
		dc.LineTo(CPoint(x, y));
	}
	const double rotationSpeed = m_currentSpeed;
	CString speedText;
	speedText.Format(_T("%.2f"), rotationSpeed);
	m_editBox.SetWindowText(speedText);

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CspinfansDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CspinfansDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_targetSpeed = 0.0;    // 初始目标速度
	m_currentSpeed = 0.0;   // 初始当前速度
	m_acceleration = 0.08 + (rand() % 4) * 0.01;   // 加速度 随机数模拟受机械状况、天气等影响
	m_deceleration = 0.18 + (rand() % 4) * 0.01;   // 减速度 随机数模拟受机械状况、天气等影响
	m_isAccelerating = false;   // 初始状态为非加速状态
	m_isDecelerating = false;   // 初始状态为非减速状态
	position = "正转";
	SetTimer(1, 50, nullptr);
	return 0;
}


void CspinfansDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	const double maxSpeed = 40; // 最大速度
	double speedDiff = m_targetSpeed - m_currentSpeed;
	double step;

	if (m_isAccelerating) {
		// 加速阶段
		step = m_acceleration;

		// 如果当前速度接近目标速度，切换到减速状态
		if (abs(speedDiff) <= 0.12) {
			step = speedDiff;
			m_isAccelerating = false;
		}
	}
	else if (m_isDecelerating) {
		// 减速阶段
		step = -m_deceleration;

		// 如果当前速度接近目标速度，停止减速
		if (abs(speedDiff) <= 0.22) {
			step = speedDiff;
			m_isDecelerating = false;
		}
	}
	else {
		// 保持恒定速度
		step = 0;
	}


	// 更新当前速度
	m_currentSpeed += step;

	// 限制速度在最大速度范围内
	if (m_currentSpeed > maxSpeed) {
		m_currentSpeed = maxSpeed;
	}
	else if (m_currentSpeed < -maxSpeed) {
		m_currentSpeed = -maxSpeed;
	}

	// 更新旋转角度
	m_rotationAngle += m_currentSpeed * rotate_direction;

	if (m_targetSpeed > m_currentSpeed) {
		m_isAccelerating = true;
	}
	else {
		m_isAccelerating = false;
	}
	// 重新绘制窗口
	Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}



void CspinfansDlg::OnBnClickedButton2()
{
	ASSERT(m_currentSpeed == 0);
	rotate_direction = 1;
	UpdateData(TRUE);
	position = "反转";
	UpdateData(FALSE);
}




void CspinfansDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ASSERT(m_currentSpeed == 0);
	rotate_direction = -1;
	UpdateData(TRUE);
	position = "正转";
	UpdateData(FALSE);

}


void CspinfansDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isAccelerating = false;
	m_isDecelerating = true;
	m_targetSpeed = 0;
}


void CspinfansDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	newTargetSpeed = Target_speed;
	if (newTargetSpeed > m_targetSpeed) {
		// 加速
		m_isAccelerating = true;
		m_isDecelerating = false;
	}
	else if (newTargetSpeed < m_targetSpeed) {
		// 减速
		m_isAccelerating = false;
		m_isDecelerating = true;
	}
	else {
		// 保持恒定速度
		m_isAccelerating = false;
		m_isDecelerating = false;
	}	
	m_targetSpeed = Target_speed;
	UpdateData(FALSE);
	ASSERT(Target_speed >= 0);
}



void CspinfansDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	m_isAccelerating = true;
	m_isDecelerating = false;
	m_targetSpeed = 40;
}
