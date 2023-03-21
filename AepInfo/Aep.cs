using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace AepInfo
{
	public class Aep
	{
		public readonly byte [] Als2alas = new byte[] { 0x41, 0x6C, 0x73, 0x32, 0x61, 0x6C, 0x61, 0x73 };
		public readonly byte[] Pefl = new byte[] { 0x50, 0x65, 0x66, 0x6C };
		public readonly byte[] pjef = new byte[] { 0x70, 0x6A, 0x65, 0x66 };
		public readonly byte[] Utf8 = new byte[] { 0x55, 0x74, 0x66, 0x38 };
		//pjef 70 6A 65 66
		private List<FootageInfo> m_AepFootages = new List<FootageInfo>();

		public int FootageCount
		{
			get { return m_AepFootages.Count;}
		}
		public List<FootageInfo> AepFootages
		{
			get { return m_AepFootages;}
		}
		private List<string> m_AepFx = new List<string>();
		public int FXCount
		{
			get { return m_AepFx.Count; }
		}
		public List<string> AepFxs
		{
			get { return m_AepFx; }
		}

		public string FileName { get; set; } = "";

		private byte[] bdata = new byte[0];

		public Aep() 
		{ 
		}
		/// ***************************************************************************
		/// <summary>
		/// aep読み込み
		/// </summary>
		/// <param name="fn">ファイルパス</param>
		/// <returns></returns>
		public bool loadFile(string fn)
		{
			bool ret = false;
			if (File.Exists(fn) == false) return ret;
			try
			{
				bdata = new byte[0];
				m_AepFootages.Clear();
				FileName = "";

				using (FileStream fs = new FileStream(fn, FileMode.Open, FileAccess.Read))
				{
					byte[] bs = new byte[fs.Length];
					int sz = fs.Read(bs, 0, bs.Length);
					if (sz == fs.Length)
					{
						bdata = bs;
						FileName = fn;
						AnalysisFootage();
						AnalysisFx();
						ret = true;
					}
				}
			}
			catch
			{
				ret = false;
			}
			return ret;
		}
		/// ***************************************************************************
		private int FindBytes(byte[] t,int st=0)
		{
			int ret = -1;
			if ((bdata.Length < st)||(t.Length<=0)) return ret;

			int idx = st;
			while (idx< bdata.Length)
			{
				if (bdata[idx] == t[0])
				{
					bool ok = true;
					for(int i = 1; i<t.Length; i++) 
					{
						if (bdata[idx+i] != t[i])
						{
							ok = false;
							break;
						}
					}
					if(ok)
					{
						ret = idx;
						break;
					}
				}
				idx++;
			}


			return ret;

		}
		private int FindAls2alas(int st = 0)
		{
			return FindBytes(Als2alas,st);
		}
		private int FindPefl(int st = 0)
		{
			return FindBytes(Pefl, st);
		}
		/// ***************************************************************************
		private void AnalysisFootage()
		{
			if(bdata.Length<=0) return;
			m_AepFootages.Clear();

			int idx = FindAls2alas(0);
			while(idx>=0)
			{
				FootageInfo inf = GetFootageInfo(idx);
				if(inf.Info!="")
				{
					m_AepFootages.Add(inf);
				}
				idx = FindAls2alas(idx+10);
				if(idx<0) break;
			}

		}
		/// ***************************************************************************
		private void AnalysisFx()
		{
			if (bdata.Length <= 0) return;

			int idx = FindPefl(0);
			if (idx >= 0)
			{
				idx += 4;
				while (idx >= 0)
				{
					string txt = "";
					idx = GetFXpjef(idx, ref txt);
					if((idx>=0)&&(txt!=""))
					{
						m_AepFx.Add(txt);
					}
				}
			}
		}
		/// ***************************************************************************
		private int GetIntValue(int adr)
		{
			int ret = 0;
			ret = ((int)bdata[adr] << 24) | ((int)bdata[adr+1] << 16) | ((int)bdata[adr + 2]<<8) | (int)bdata[adr + 3];
			return ret;
		}
		/// ***************************************************************************
		private string BData2oStr(int adr, int len)
		{
			byte[] data = new byte[len];
			for (int i = 0; i < len; i++)
			{
				if (adr + i < bdata.Length)
				{
					data[i] = bdata[adr + i];
				}
				else
				{
					data[i] = 0x00;
				}
			}
			return Encoding.UTF8.GetString(data);
		}
		/// ***************************************************************************
		private int TypeChunks(int adr)
		{
			int ret = -1;
			if ((bdata[adr] == 0x55)
				&& (bdata[adr + 1] == 0x74)
				&& (bdata[adr + 2] == 0x66)
				&& (bdata[adr + 3] == 0x38))
			{
				ret = 0;
			}else if ((bdata[adr] == 0x6F) // 6F 70 74 69
				&& (bdata[adr + 1] == 0x70)
				&& (bdata[adr + 2] == 0x74)
				&& (bdata[adr + 3] == 0x69))
			{
				int sz = GetIntValue(adr + 4);
				Debug.WriteLine($"{bdata[adr + 4]:X}");
				Debug.WriteLine($"{bdata[adr + 5]:X}");
				Debug.WriteLine($"{bdata[adr + 6]:X}");
				Debug.WriteLine($"{bdata[adr + 7]:X}");
				Debug.WriteLine($"{sz:X}");
				if(sz == 0x0142)
				{
					ret = 1;
				}else if (sz== 0x025A)
				{
					ret = 2;
				}
			}
			return ret;
		}
		/// ***************************************************************************
		private int GetUtf8(int adr, ref string txt)
		{
			int ret = -1;
			txt = "";
			if((bdata[adr]==0x55)
				&& (bdata[adr+1] == 0x74) 
				&& (bdata[adr + 2] == 0x66)
				&& (bdata[adr + 3] == 0x38))
			{
				int len = GetIntValue(adr+4);
				if (len > 0)
				{
					txt = BData2oStr(adr + 8, len);
					ret = adr + 8 + len;
				}
			}
			return ret;
		}
		/// ***************************************************************************
		private int GetFXpjef(int adr, ref string txt)
		{
			int ret = -1;
			int adr2 = FindBytes(pjef, adr);
			txt = "";
			if (adr2 >=0)
			{
				int len = GetIntValue(adr2 + 4);
				if (len > 0)
				{
					txt = BData2oStr(adr2 + 8, len);
					ret = adr2 + 8 + len;
				}
			}
			return ret;
		}
		/// ***************************************************************************

		/// ***************************************************************************
		private FootageInfo GetFootageInfo(int adr)
		{
			FootageInfo ret = new FootageInfo();
			if (bdata.Length <= adr) return ret;
			ret.Adr = adr;
			int len = GetIntValue(adr + 8);
			ret.Info = BData2oStr(adr + 12, len);
			if(ret.Info!="")
			{
				ret.Info = ret.Info.Replace("{", "{\r\n");
				ret.Info = ret.Info.Replace("}", "\r\n}\r\n");
				ret.Info = ret.Info.Replace(",\"", ",\r\n\"");
			}
			int adr2 = adr + 12 + len;
			if (bdata[adr2] == 00) adr2++;

			int vv = TypeChunks(adr2);
			if (vv == 0)
			{
				while (TypeChunks(adr2) == 0)
				{
					string s = "";
					int idx = GetUtf8(adr2, ref s);
					if ((idx >= 0) && (s != ""))
					{
						ret.Texts.Add(s);
						adr2 = idx;
					}
				}
			}
			int adr3 = 0;
			vv = TypeChunks(adr2);
			switch (vv)
			{
				case 1:
					adr3 = adr2 + 0x42;
					break;
				case 2:
					adr3 = adr2 + 0x160;
					break;
			}
			if(adr3>0)
			{
				int l = 0;
				for (int i = 0; i < 512; i++)
				{
					if (bdata[adr3 + i] == 0x00)
					{
						l = i;
						break;
					}
				}
				string s = BData2oStr(adr3, l);
				if(s!="") { ret.Texts.Add(s);}
			}
			return ret;
		}
		/// ***************************************************************************
	}
	public class FootageInfo
	{
		public int Adr { get; set; } = 0;
		public string Info { get; set; } = "";
		public List<string> Texts { get; set; } = new List<string>();

		public FootageInfo()
		{
		}
		public string Mes
		{
			get
			{
				string ret = "";
				ret += $"Adress: 0x{Adr:X}\r\n";
				ret += Info;
				if(Texts.Count>0)
				{
					foreach(string s in Texts)
					{
						ret += s + "\r\n";
					}
				}
				return ret;
			}
		}
	}
}
