using System.Diagnostics;
using System.IO.Pipes;
using System.Reflection.Emit;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using BRY;
using Microsoft.VisualBasic.Devices;
using static System.Windows.Forms.DataFormats;

namespace AepInfo
{
	public partial class MainForm : Form
	{
		public Aep Aep = new Aep();
		private string m_FileName = "";
		// ********************************************************************
		private F_Pipe m_Server = new F_Pipe();
		public void StartServer(string pipename)
		{
			m_Server.Server(pipename);
			m_Server.Reception += M_Server_Reception;
		}
		// ********************************************************************
		public void StopServer()
		{
			m_Server.StopServer();
		}
		// ********************************************************************
		private void M_Server_Reception(object sender, ReceptionArg e)
		{
			this.Invoke((Action)(() =>
			{
				PipeData pd = new PipeData(e.Text);
				Command(pd.Args, PIPECALL.PipeExec);
				ForegroundWindow();
			}));
		}
		// ********************************************************************
		public MainForm()
		{
			InitializeComponent();
		}

		// ********************************************************************
		private void Form1_Load(object sender, EventArgs e)
		{
			if ((Control.ModifierKeys & Keys.Shift) == Keys.Shift) return;
			PrefFile pf = new PrefFile(this);
			this.Text = pf.AppName;
			if (pf.Load() == true)
			{
				pf.RestoreForm();
			}
			else
			{
				ToCenter();
			}
			Command(Environment.GetCommandLineArgs().Skip(1).ToArray(), PIPECALL.StartupExec);
		}
		// ********************************************************************
		private void Form1_FormClosed(object sender, FormClosedEventArgs e)
		{
			PrefFile pf = new PrefFile(this);
			pf.StoreForm();
			pf.Save();
		}
		// ********************************************************************
		private void quitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}
		// ********************************************************************
		public void ToCenter()
		{
			Rectangle rct = Screen.PrimaryScreen.Bounds;
			Point p = new Point((rct.Width - this.Width) / 2, (rct.Height - this.Height) / 2);
			this.Location = p;
			ForegroundWindow();
		}
		// ********************************************************************
		public bool Export(string p)
		{
			bool ret = false;
			ForegroundWindow();
			try
			{
				string s = textBox1.Text;
				File.WriteAllText(p, s);
				m_FileName = p;
				this.Text = Path.GetFileName(p);
				ret = true;
			}
			catch
			{
				ret = false;
			}

			return ret;
		}
		// ********************************************************************
		public bool Import(string p)
		{
			bool ret = false;
			ForegroundWindow();
			textBox1.Text = "";
			if (File.Exists(p) == true)
			{
				try
				{
					if (Aep.loadFile(p) == true)
					{
						string s = "";
						if (Aep.FootageCount > 0)
						{
							for (int i = 0; i < Aep.FootageCount; i++)
							{
								if (s != "") s += "\r\n";
								s += Aep.AepFootages[i].Mes;
								s += "// *****************************\r\n";
							}
						}
						if (Aep.FXCount > 0)
						{
							s += "// *****************************\r\n";
							s += "// used FX\r\n";

							for (int i = 0; i < Aep.FXCount; i++)
							{
								s += Aep.AepFxs[i] + "\r\n";
							}
						}
						textBox1.Text = s;
						ret = true;
					}
				}
				catch
				{
					ret = false;
				}
			}

			return ret;
		}
		// ********************************************************************
		public void ForegroundWindow()
		{
			F_W.SetForegroundWindow(this.Handle);
		}
		// ********************************************************************
		public void Command(string[] args, PIPECALL IsPipe = PIPECALL.StartupExec)
		{
			bool QuitFlag = false;

			F_Args _args = new F_Args(args);
			if (_args.OptionCount > 0)
			{
				for (int i = 0; i < _args.OptionCount; i++)
				{
					F_ArgItem? item = _args.Option(i);
					if (item == null) continue;
					switch (item.Option.ToLower())
					{
						case "tocenter":
						case "center":
							this.Invoke((Action)(() =>
							{
								ToCenter();
							}));
							break;
						case "foregroundWindow":
						case "foreground":
							ForegroundWindow();
							break;
						case "load":
						case "ld":
						case "import":
							int idx = item.Index + 1;
							if (idx < _args.Count)
							{
								if (_args[idx].IsOption == false)
								{
									Import(_args[idx].Name);
								}
							}
							break;
						case "save":
						case "sv":
							int idx2 = item.Index + 1;
							if (idx2 < _args.Count)
							{
								if (_args[idx2].IsOption == false)
								{
									Export(_args[idx2].Name);
								}
							}
							break;
						case "exit":
						case "quit":
							if ((_args.Count == 1) && ((IsPipe == PIPECALL.DoubleExec) || (IsPipe == PIPECALL.PipeExec)))
							{
								QuitFlag = true;
							}
							break;
						case "callback":
							string s = textBox1.Text;
							F_Pipe.Client(Program.MyCallBackId, s).Wait();
							break;

					}

				}

			}
			else
			{
				if (_args.Count > 0)
				{
					if (_args.Count == 1)
					{
						Import(_args[0].Name);
					}
				}
			}
			if (QuitFlag) Application.Exit();
		}

		private void MainForm_DragEnter(object sender, DragEventArgs e)
		{
			if (e.Data != null)
			{
				if (e.Data.GetDataPresent(DataFormats.FileDrop))
					e.Effect = DragDropEffects.Copy;
				else
					e.Effect = DragDropEffects.None;
			}
		}

		private void MainForm_DragDrop(object sender, DragEventArgs e)
		{
			if (e.Data != null)
			{
				string[] fileNames = (string[])e.Data.GetData(DataFormats.FileDrop, false);

				foreach (string fileName in fileNames)
				{
					if(Import(fileName)==true)
					{
						break;
					}
				}

			}
		}
		// *******************************************************************************



	}
}