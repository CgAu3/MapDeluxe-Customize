#pragma once
#include "afxwin.h"


// CDlgRomImage �Ի���

class CDlgRomImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgRomImage)

public:
	CDlgRomImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRomImage();

// �Ի�������
	enum { IDD = IDD_ROM_IMAGE };

	u16 rom_image[240*160];
	bool use_rom_image;

	void PaintImage(CDC* pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonImpRomImage();
	virtual BOOL OnInitDialog();
	CButton m_CheckUseImage;
	afx_msg void OnBnClickedCheckUseImage();
};
