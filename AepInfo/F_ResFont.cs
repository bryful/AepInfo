using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AepInfo
{
	public partial class F_ResFont : Component
	{
		[System.Runtime.InteropServices.DllImport("gdi32.dll")]
		private static extern IntPtr AddFontMemResourceEx(IntPtr pbFont, uint cbFont, IntPtr pdv, [System.Runtime.InteropServices.In] ref uint pcFonts);
		public PrivateFontCollection m_MyFonts = new PrivateFontCollection();
		public int FontCount
		{
			get
			{
				int ret = 0;
				if (m_MyFonts != null)
				{
					ret = m_MyFonts.Families.Length;
				}
				return ret;
			}
		}
		public string[] FontNames
		{
			get
			{
				string[] ret = new string[m_MyFonts.Families.Length];
				if (m_MyFonts.Families.Length > 0)
				{
					int idx = 0;
					foreach (FontFamily f in m_MyFonts.Families)
					{
						ret[idx] = f.Name;
						idx++;
					}
				}
				return ret;
			}
		}
		// *******************************************************************************
		public F_ResFont()
		{
			InitializeComponent();
			AddResFonnt(Properties.Resources.SourceHanCodeJP);
			AddResFonnt(Properties.Resources.Myrica);
		}
		public F_ResFont(IContainer container)
		{
			container.Add(this);
			InitializeComponent();
			AddResFonnt(Properties.Resources.SourceHanCodeJP);
			AddResFonnt(Properties.Resources.Myrica);
		}
		public void AddResFonnt(byte[] fontData)
		{
			//SourceHanCodeJP
			//MyricaM
			//Myrica
			//byte[] fontData = Properties.Resources.SourceHanCodeJP;
			IntPtr fontPtr = System.Runtime.InteropServices.Marshal.AllocCoTaskMem(fontData.Length);
			System.Runtime.InteropServices.Marshal.Copy(fontData, 0, fontPtr, fontData.Length);
			uint dummy = 0;
			if (m_MyFonts == null) m_MyFonts = new PrivateFontCollection();
			m_MyFonts.AddMemoryFont(fontPtr, fontData.Length);
			AddFontMemResourceEx(fontPtr, (uint)fontData.Length, IntPtr.Zero, ref dummy);
			System.Runtime.InteropServices.Marshal.FreeCoTaskMem(fontPtr);
		}
		public Font MyFont(int idx, float sz, FontStyle fs)
		{
			Font ret = new Font("System", sz, fs);
			if ((m_MyFonts != null) && (idx >= 0) && (idx < m_MyFonts.Families.Length))
			{
				try
				{
					ret = new Font(m_MyFonts.Families[idx], sz, fs);
				}
				catch
				{
					ret = new Font("System", sz, fs);
				}
			}
			return ret;
		}
	}
}
