
// spin_fansDlg.h: 头文件
//

#pragma once


// CspinfansDlg 对话框
class CspinfansDlg : public CDialogEx
{
// 构造
public:
	CspinfansDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPIN_FANS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CPoint m_center;         // 中心点坐标
	double m_rotationAngle;  // 当前旋转角度
	double m_rotationSpeed;    // 当前旋转速度
	double m_rotationAccel;    // 旋转加速度
	int m_accelerationCounter; // 加速计数器
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int rotate_direction;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	CEdit m_editBox;
//	CEdit Target_speed;
	double Target_speed;
	afx_msg void OnBnClickedButton4();
	int expected_speed;
	int speed;
	double m_targetSpeed;    // 目标速度
	double m_currentSpeed;   // 当前速度
	double m_acceleration;   // 加速度
	double m_deceleration;   // 减速度
	bool m_isAccelerating;   // 是否正在加速
	bool m_isDecelerating;   // 是否正在减速
	int newTargetSpeed;
	CString position;
	afx_msg void OnBnClickedButton5();
};
