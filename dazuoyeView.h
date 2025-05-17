// dazuoyeView.h: CdazuoyeView 类的接口
//

#pragma once


class CdazuoyeView : public CView
{
protected: // 仅从序列化创建
	CdazuoyeView() noexcept;
	DECLARE_DYNCREATE(CdazuoyeView)

// 特性
public:
	CdazuoyeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CdazuoyeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

// 绘制图形所需的成员变量
CPoint m_ptStart;        // 起点
CPoint m_ptEnd;          // 终点
bool m_bDrawing;         // 是否正在绘制
int m_nDrawMode;         // 绘制模式（0:无, 1:Bresenham, 2:DDA, 3:圆, 4:椭圆, 5:多边形）
CPoint m_ptPolygon[100]; // 多边形顶点数组
int m_nPolygonCount;     // 多边形顶点计数
bool m_bPolygonDrawing;  // 是否正在绘制多边形

// 菜单项选中状态
bool m_bBresenhamSelected;
bool m_bDDASelected;
bool m_bCircleSelected;
bool m_bEllipseSelected;
bool m_bPolygonSelected;

// 辅助函数声明
void DrawCircle(CDC& dc, int xc, int yc, int radius);
void DrawEllipse(CDC& dc, int xc, int yc, int rx, int ry);

// 基本图形绘制
public:
	// 基本图形绘制
	afx_msg void OnLineBresenham();
	afx_msg void OnLineDDA();
	afx_msg void OnCircleMidpoint();
	afx_msg void OnEllipseMidpoint();
	afx_msg void OnPolygonDraw();

	// 图形变换
	afx_msg void OnTransformMove();
	afx_msg void OnTransformRotate();
	afx_msg void OnTransformScale();
	afx_msg void OnTransformShear();
	afx_msg void OnTransformSymmetry();
	afx_msg void OnScaleRefPoint();
	afx_msg void OnScaleRefLine();
	afx_msg void OnSymmetryHorizontal();
	afx_msg void OnSymmetryVertical();
	afx_msg void OnSymmetryArbitrary();

	// 鼠标事件处理
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	// 图形填充
	afx_msg void OnFillScanline();
	afx_msg void OnFillSeed();

	// 图形裁剪
	afx_msg void OnClipLine();
	afx_msg void OnClipPolygon();
};

#ifndef _DEBUG  // dazuoyeView.cpp 中的调试版本
inline CdazuoyeDoc* CdazuoyeView::GetDocument() const
   { return reinterpret_cast<CdazuoyeDoc*>(m_pDocument); }
#endif

