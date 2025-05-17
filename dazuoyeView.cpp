// dazuoyeView.cpp: CdazuoyeView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "dazuoye.h"
#endif

#include "dazuoyeDoc.h"
#include "dazuoyeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdazuoyeView

IMPLEMENT_DYNCREATE(CdazuoyeView, CView)

BEGIN_MESSAGE_MAP(CdazuoyeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	// 基本图形绘制
	ON_COMMAND(ID_LINE_BRESENHAM, &CdazuoyeView::OnLineBresenham)
	ON_COMMAND(ID_LINE_DDA, &CdazuoyeView::OnLineDDA)
	ON_COMMAND(ID_CIRCLE_MIDPOINT, &CdazuoyeView::OnCircleMidpoint)
	ON_COMMAND(ID_ELLIPSE_MIDPOINT, &CdazuoyeView::OnEllipseMidpoint)
	ON_COMMAND(ID_POLYGON_DRAW, &CdazuoyeView::OnPolygonDraw)

	// 图形变换
	ON_COMMAND(ID_TRANSFORM_MOVE, &CdazuoyeView::OnTransformMove)
	ON_COMMAND(ID_TRANSFORM_ROTATE, &CdazuoyeView::OnTransformRotate)
	ON_COMMAND(ID_TRANSFORM_SCALE, &CdazuoyeView::OnTransformScale)
	ON_COMMAND(ID_TRANSFORM_SHEAR, &CdazuoyeView::OnTransformShear)
	ON_COMMAND(ID_TRANSFORM_SYMMETRY, &CdazuoyeView::OnTransformSymmetry)
	ON_COMMAND(ID_SCALE_REF_POINT, &CdazuoyeView::OnScaleRefPoint)
	ON_COMMAND(ID_SCALE_REF_LINE, &CdazuoyeView::OnScaleRefLine)
	ON_COMMAND(ID_SYMMETRY_HORIZONTAL, &CdazuoyeView::OnSymmetryHorizontal)
	ON_COMMAND(ID_SYMMETRY_VERTICAL, &CdazuoyeView::OnSymmetryVertical)
	ON_COMMAND(ID_SYMMETRY_ARBITRARY, &CdazuoyeView::OnSymmetryArbitrary)

	// 图形填充
	ON_COMMAND(ID_FILL_SCANLINE, &CdazuoyeView::OnFillScanline)
	ON_COMMAND(ID_FILL_SEED, &CdazuoyeView::OnFillSeed)

	// 图形裁剪
	ON_COMMAND(ID_CLIP_LINE, &CdazuoyeView::OnClipLine)
	ON_COMMAND(ID_CLIP_POLYGON, &CdazuoyeView::OnClipPolygon)

	// 鼠标事件
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CdazuoyeView 构造/析构

CdazuoyeView::CdazuoyeView() noexcept
	: m_bDrawing(false)
	, m_nDrawMode(0)
	, m_nPolygonCount(0)
	, m_bPolygonDrawing(false)
	, m_bBresenhamSelected(false)
	, m_bDDASelected(false)
	, m_bCircleSelected(false)
	, m_bEllipseSelected(false)
	, m_bPolygonSelected(false)
{
	// TODO: 在此处添加构造代码
}

CdazuoyeView::~CdazuoyeView()
{
}

BOOL CdazuoyeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CdazuoyeView 绘图

void CdazuoyeView::OnDraw(CDC* /*pDC*/)
{
	CdazuoyeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CdazuoyeView 打印

BOOL CdazuoyeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CdazuoyeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CdazuoyeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CdazuoyeView 诊断

#ifdef _DEBUG
void CdazuoyeView::AssertValid() const
{
	CView::AssertValid();
}

void CdazuoyeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdazuoyeDoc* CdazuoyeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdazuoyeDoc)));
	return (CdazuoyeDoc*)m_pDocument;
}
#endif //_DEBUG


// CdazuoyeView 消息处理程序

// 基本图形绘制函数实现
void CdazuoyeView::OnLineBresenham()
{
	// 取消其他菜单项的选中状态
	m_bDDASelected = false;
	m_bCircleSelected = false;
	m_bEllipseSelected = false;
	m_bPolygonSelected = false;

	// 切换当前菜单项的选中状态
	m_bBresenhamSelected = !m_bBresenhamSelected;
	
	// 更新菜单项状态
	CMenu* pMenu = AfxGetMainWnd()->GetMenu();
	if (pMenu)
	{
		pMenu->CheckMenuItem(ID_LINE_BRESENHAM, m_bBresenhamSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_LINE_DDA, m_bDDASelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_CIRCLE_MIDPOINT, m_bCircleSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_ELLIPSE_MIDPOINT, m_bEllipseSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_POLYGON_DRAW, m_bPolygonSelected ? MF_CHECKED : MF_UNCHECKED);
	}

	// 设置绘制模式
	m_nDrawMode = m_bBresenhamSelected ? 1 : 0;
}

void CdazuoyeView::OnLineDDA()
{
	// 取消其他菜单项的选中状态
	m_bBresenhamSelected = false;
	m_bCircleSelected = false;
	m_bEllipseSelected = false;
	m_bPolygonSelected = false;

	// 切换当前菜单项的选中状态
	m_bDDASelected = !m_bDDASelected;
	
	// 更新菜单项状态
	CMenu* pMenu = AfxGetMainWnd()->GetMenu();
	if (pMenu)
	{
		pMenu->CheckMenuItem(ID_LINE_BRESENHAM, m_bBresenhamSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_LINE_DDA, m_bDDASelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_CIRCLE_MIDPOINT, m_bCircleSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_ELLIPSE_MIDPOINT, m_bEllipseSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_POLYGON_DRAW, m_bPolygonSelected ? MF_CHECKED : MF_UNCHECKED);
	}

	// 设置绘制模式
	m_nDrawMode = m_bDDASelected ? 2 : 0;
}

void CdazuoyeView::OnCircleMidpoint()
{
	// 取消其他菜单项的选中状态
	m_bBresenhamSelected = false;
	m_bDDASelected = false;
	m_bEllipseSelected = false;
	m_bPolygonSelected = false;

	// 切换当前菜单项的选中状态
	m_bCircleSelected = !m_bCircleSelected;
	
	// 更新菜单项状态
	CMenu* pMenu = AfxGetMainWnd()->GetMenu();
	if (pMenu)
	{
		pMenu->CheckMenuItem(ID_LINE_BRESENHAM, m_bBresenhamSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_LINE_DDA, m_bDDASelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_CIRCLE_MIDPOINT, m_bCircleSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_ELLIPSE_MIDPOINT, m_bEllipseSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_POLYGON_DRAW, m_bPolygonSelected ? MF_CHECKED : MF_UNCHECKED);
	}

	// 设置绘制模式
	m_nDrawMode = m_bCircleSelected ? 3 : 0;
}

void CdazuoyeView::OnEllipseMidpoint()
{
	// 取消其他菜单项的选中状态
	m_bBresenhamSelected = false;
	m_bDDASelected = false;
	m_bCircleSelected = false;
	m_bPolygonSelected = false;

	// 切换当前菜单项的选中状态
	m_bEllipseSelected = !m_bEllipseSelected;
	
	// 更新菜单项状态
	CMenu* pMenu = AfxGetMainWnd()->GetMenu();
	if (pMenu)
	{
		pMenu->CheckMenuItem(ID_LINE_BRESENHAM, m_bBresenhamSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_LINE_DDA, m_bDDASelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_CIRCLE_MIDPOINT, m_bCircleSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_ELLIPSE_MIDPOINT, m_bEllipseSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_POLYGON_DRAW, m_bPolygonSelected ? MF_CHECKED : MF_UNCHECKED);
	}

	// 设置绘制模式
	m_nDrawMode = m_bEllipseSelected ? 4 : 0;
}

void CdazuoyeView::OnPolygonDraw()
{
	// 取消其他菜单项的选中状态
	m_bBresenhamSelected = false;
	m_bDDASelected = false;
	m_bCircleSelected = false;
	m_bEllipseSelected = false;

	// 切换当前菜单项的选中状态
	m_bPolygonSelected = !m_bPolygonSelected;
	
	// 更新菜单项状态
	CMenu* pMenu = AfxGetMainWnd()->GetMenu();
	if (pMenu)
	{
		pMenu->CheckMenuItem(ID_LINE_BRESENHAM, m_bBresenhamSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_LINE_DDA, m_bDDASelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_CIRCLE_MIDPOINT, m_bCircleSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_ELLIPSE_MIDPOINT, m_bEllipseSelected ? MF_CHECKED : MF_UNCHECKED);
		pMenu->CheckMenuItem(ID_POLYGON_DRAW, m_bPolygonSelected ? MF_CHECKED : MF_UNCHECKED);
	}

	// 设置绘制模式
	m_nDrawMode = m_bPolygonSelected ? 5 : 0;
	m_bPolygonDrawing = m_bPolygonSelected;
	if (m_bPolygonSelected)
	{
		m_nPolygonCount = 0;
	}
}

// 图形变换函数实现
void CdazuoyeView::OnTransformMove()
{
	// TODO: 实现图形平移
}

void CdazuoyeView::OnTransformRotate()
{
	// TODO: 实现图形旋转
}

void CdazuoyeView::OnTransformScale()
{
	// TODO: 实现图形比例变换
}

void CdazuoyeView::OnTransformShear()
{
	// TODO: 实现图形错切变换
}

void CdazuoyeView::OnTransformSymmetry()
{
	// TODO: 实现图形对称变换
}

void CdazuoyeView::OnScaleRefPoint()
{
	// TODO: 实现相对点的缩放
}

void CdazuoyeView::OnScaleRefLine()
{
	// TODO: 实现相对线的缩放
}

void CdazuoyeView::OnSymmetryHorizontal()
{
	// TODO: 实现水平对称
}

void CdazuoyeView::OnSymmetryVertical()
{
	// TODO: 实现垂直对称
}

void CdazuoyeView::OnSymmetryArbitrary()
{
	// TODO: 实现任意直线对称
}

// 图形填充函数实现
void CdazuoyeView::OnFillScanline()
{
	// TODO: 实现扫描线填充
}

void CdazuoyeView::OnFillSeed()
{
	// TODO: 实现种子填充
}

// 图形裁剪函数实现
void CdazuoyeView::OnClipLine()
{
	// TODO: 实现直线裁剪
}

void CdazuoyeView::OnClipPolygon()
{
	// TODO: 实现多边形裁剪
}

// 鼠标事件处理函数实现
void CdazuoyeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_nDrawMode > 0)  // 如果选择了绘制模式
	{
		if (m_bPolygonDrawing)
		{
			// 多边形绘制模式
			if (m_nPolygonCount < 100)
			{
				m_ptPolygon[m_nPolygonCount++] = point;
				if (m_nPolygonCount > 1)
				{
					CClientDC dc(this);
					dc.MoveTo(m_ptPolygon[m_nPolygonCount - 2]);
					dc.LineTo(point);
				}
			}
		}
		else
		{
			// 其他图形绘制模式
			m_ptStart = point;
			m_ptEnd = point;
			m_bDrawing = true;
			SetCapture();
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CdazuoyeView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDrawing && !m_bPolygonDrawing)
	{
		CClientDC dc(this);
		// 擦除上一条线
		dc.SetROP2(R2_NOT);
		
		switch (m_nDrawMode)
		{
		case 1:  // Bresenham直线
		case 2:  // DDA直线
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
			m_ptEnd = point;
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
			break;
			
		case 3:  // 圆
			{
				int radius = (int)sqrt(pow(m_ptEnd.x - m_ptStart.x, 2) + pow(m_ptEnd.y - m_ptStart.y, 2));
				dc.Ellipse(m_ptStart.x - radius, m_ptStart.y - radius,
						  m_ptStart.x + radius, m_ptStart.y + radius);
				m_ptEnd = point;
				radius = (int)sqrt(pow(m_ptEnd.x - m_ptStart.x, 2) + pow(m_ptEnd.y - m_ptStart.y, 2));
				dc.Ellipse(m_ptStart.x - radius, m_ptStart.y - radius,
						  m_ptStart.x + radius, m_ptStart.y + radius);
			}
			break;
			
		case 4:  // 椭圆
			{
				int rx = abs(m_ptEnd.x - m_ptStart.x);
				int ry = abs(m_ptEnd.y - m_ptStart.y);
				dc.Ellipse(m_ptStart.x - rx, m_ptStart.y - ry,
						  m_ptStart.x + rx, m_ptStart.y + ry);
				m_ptEnd = point;
				rx = abs(m_ptEnd.x - m_ptStart.x);
				ry = abs(m_ptEnd.y - m_ptStart.y);
				dc.Ellipse(m_ptStart.x - rx, m_ptStart.y - ry,
						  m_ptStart.x + rx, m_ptStart.y + ry);
			}
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CdazuoyeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDrawing && !m_bPolygonDrawing)
	{
		m_bDrawing = false;
		ReleaseCapture();
		
		CClientDC dc(this);
		// 擦除预览
		dc.SetROP2(R2_NOT);
		
		switch (m_nDrawMode)
		{
		case 1:  // Bresenham直线
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
			// 绘制最终直线
			dc.SetROP2(R2_COPYPEN);
			{
				int dx = abs(m_ptEnd.x - m_ptStart.x);
				int dy = abs(m_ptEnd.y - m_ptStart.y);
				int sx = (m_ptStart.x < m_ptEnd.x) ? 1 : -1;
				int sy = (m_ptStart.y < m_ptEnd.y) ? 1 : -1;
				int err = dx - dy;
				
				int x = m_ptStart.x;
				int y = m_ptStart.y;
				
				while (true)
				{
					dc.SetPixel(x, y, RGB(0, 0, 0));
					if (x == m_ptEnd.x && y == m_ptEnd.y) break;
					int e2 = 2 * err;
					if (e2 > -dy)
					{
						err -= dy;
						x += sx;
					}
					if (e2 < dx)
					{
						err += dx;
						y += sy;
					}
				}
			}
			break;
			
		case 2:  // DDA直线
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
			// 绘制最终直线
			dc.SetROP2(R2_COPYPEN);
			{
				float dx = m_ptEnd.x - m_ptStart.x;
				float dy = m_ptEnd.y - m_ptStart.y;
				float steps = max(abs(dx), abs(dy));
				float xIncrement = dx / steps;
				float yIncrement = dy / steps;
				
				float x = m_ptStart.x;
				float y = m_ptStart.y;
				
				for (int i = 0; i <= steps; i++)
				{
					dc.SetPixel(round(x), round(y), RGB(0, 0, 0));
					x += xIncrement;
					y += yIncrement;
				}
			}
			break;
			
		case 3:  // 圆
			{
				int radius = (int)sqrt(pow(m_ptEnd.x - m_ptStart.x, 2) + pow(m_ptEnd.y - m_ptStart.y, 2));
				dc.Ellipse(m_ptStart.x - radius, m_ptStart.y - radius,
						  m_ptStart.x + radius, m_ptStart.y + radius);
				// 绘制最终圆
				dc.SetROP2(R2_COPYPEN);
				DrawCircle(dc, m_ptStart.x, m_ptStart.y, radius);
			}
			break;
			
		case 4:  // 椭圆
			{
				int rx = abs(m_ptEnd.x - m_ptStart.x);
				int ry = abs(m_ptEnd.y - m_ptStart.y);
				dc.Ellipse(m_ptStart.x - rx, m_ptStart.y - ry,
						  m_ptStart.x + rx, m_ptStart.y + ry);
				// 绘制最终椭圆
				dc.SetROP2(R2_COPYPEN);
				DrawEllipse(dc, m_ptStart.x, m_ptStart.y, rx, ry);
			}
			break;
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

// 辅助函数：绘制圆
void CdazuoyeView::DrawCircle(CDC& dc, int xc, int yc, int radius)
{
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;
	while (x <= y)
	{
		dc.SetPixel(xc + x, yc + y, RGB(0, 0, 0));
		dc.SetPixel(xc - x, yc + y, RGB(0, 0, 0));
		dc.SetPixel(xc + x, yc - y, RGB(0, 0, 0));
		dc.SetPixel(xc - x, yc - y, RGB(0, 0, 0));
		dc.SetPixel(xc + y, yc + x, RGB(0, 0, 0));
		dc.SetPixel(xc - y, yc + x, RGB(0, 0, 0));
		dc.SetPixel(xc + y, yc - x, RGB(0, 0, 0));
		dc.SetPixel(xc - y, yc - x, RGB(0, 0, 0));
		if (d < 0)
			d += 4 * x + 6;
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

// 辅助函数：绘制椭圆
void CdazuoyeView::DrawEllipse(CDC& dc, int xc, int yc, int rx, int ry)
{
	int x = 0;
	int y = ry;
	long rx2 = (long)rx * rx;
	long ry2 = (long)ry * ry;
	long p;
	long px = 0;
	long py = 2 * rx2 * y;

	// 区域1
	p = (long)(ry2 - rx2 * ry + 0.25 * rx2);
	while (px < py)
	{
		dc.SetPixel(xc + x, yc + y, RGB(0, 0, 0));
		dc.SetPixel(xc - x, yc + y, RGB(0, 0, 0));
		dc.SetPixel(xc + x, yc - y, RGB(0, 0, 0));
		dc.SetPixel(xc - x, yc - y, RGB(0, 0, 0));
		x++;
		px += 2 * ry2;
		if (p < 0)
			p += ry2 + px;
		else
		{
			y--;
			py -= 2 * rx2;
			p += ry2 + px - py;
		}
	}

	// 区域2
	p = (long)(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
	while (y >= 0)
	{
		dc.SetPixel(xc + x, yc + y, RGB(0, 0, 0));
		dc.SetPixel(xc - x, yc + y, RGB(0, 0, 0));
		dc.SetPixel(xc + x, yc - y, RGB(0, 0, 0));
		dc.SetPixel(xc - x, yc - y, RGB(0, 0, 0));
		y--;
		py -= 2 * rx2;
		if (p > 0)
			p += rx2 - py;
		else
		{
			x++;
			px += 2 * ry2;
			p += rx2 - py + px;
		}
	}
}
