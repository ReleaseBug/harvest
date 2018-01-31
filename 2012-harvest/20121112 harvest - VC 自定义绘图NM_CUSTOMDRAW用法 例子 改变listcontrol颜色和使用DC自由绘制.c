void CConfigNVDS::OnNMCustomdrawLcConfigNvds(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�˴�ǿ�ư�ָ����ͳ�Ϊ��LPNMLVCUSTOMDRAW(list view����).ʹ�������ؼ���ɽ���Ϊ��������
	LPNMLVCUSTOMDRAW lpLVCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	int item    = lpLVCustomDraw->nmcd.dwItemSpec;
	int subItem = lpLVCustomDraw->iSubItem;
	int tag;
	switch(lpLVCustomDraw->nmcd.dwDrawStage)
	{
		//case CDDS_ITEMPREPAINT:
		case CDDS_ITEMPREPAINT | CDDS_SUBITEM: //ɸѡ����ǰ�һ���subitemʱ�� ����ǰֻ��������ɫ�ȼ򵥲���
			tag = _tcstol(m_list.GetItemText(item, NVDS_TAG_NUM), NULL, 0);
				
			if (tag <= NVDS_SYS_TAIL_TAG && tag >= NVDS_SYS_BASE_TAG)
			{
				lpLVCustomDraw->clrText = RGB(0,0,255); // �����ı���ɫ
				lpLVCustomDraw->clrTextBk = CLR_DEFAULT; // ���ı�����ɫ
			}
			else 
			{
				lpLVCustomDraw->clrText = CLR_DEFAULT;
				lpLVCustomDraw->clrTextBk = CLR_DEFAULT;
			}
			break;
		case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM: //ɸѡ���ƺ��һ���subitemʱ�����ƺ�������ʲô����ʲô
			if(subItem == 0)
			{
				CDC* pDC = CDC::FromHandle(lpLVCustomDraw->nmcd.hdc); //��ȡDC ���»��ƣ������ͷ�DC
				CString strItemText = _T("  ") + m_list.GetItemText(item, subItem);
		
				CRect rcItem;
				m_list.GetSubItemRect(item, subItem, LVIR_LABEL, rcItem);
				rcItem.left -= 5;
				rcItem.bottom -= 1;
				
				//���Ʊ���
				pDC->FillSolidRect(&rcItem, ::GetSysColor(COLOR_3DFACE)); //��䱳��
				pDC->Draw3dRect(&rcItem, ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DSHADOW));//����3D��ʽ

				//�������ֺ�������ɫ�����ֱ���ģʽ
				pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
				pDC->SetBkMode(TRANSPARENT);//�����������ػ�ʱ�滻����
				pDC->TextOut(rcItem.left, rcItem.top, strItemText);
			}
			break;
		default: 
			break;    
	}

	*pResult = 0;                      //Ĭ��ֵ�� ������շ���Ϊ��ֵ�������Ϣwindow�����ٷ���
	*pResult |= CDRF_NOTIFYITEMDRAW;   //Ҫ�����itemǰ�����ʹ���Ϣ
	*pResult |= CDRF_NOTIFYSUBITEMDRAW;//Ҫ�����subitemǰ�����ʹ���Ϣ
	*pResult |= CDRF_NOTIFYPOSTPAINT;  //���ƽ����󣬷��ʹ���Ϣ
}