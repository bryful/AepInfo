namespace AepInfo
{
	partial class MainForm
	{
		/// <summary>
		///  Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		///  Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		///  Required method for Designer support - do not modify
		///  the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			components = new System.ComponentModel.Container();
			menuStrip1 = new MenuStrip();
			fileToolStripMenuItem = new ToolStripMenuItem();
			openToolStripMenuItem = new ToolStripMenuItem();
			saveToolStripMenuItem = new ToolStripMenuItem();
			saveAsToolStripMenuItem = new ToolStripMenuItem();
			quitToolStripMenuItem = new ToolStripMenuItem();
			editToolStripMenuItem = new ToolStripMenuItem();
			exec1ToolStripMenuItem = new ToolStripMenuItem();
			exec2ToolStripMenuItem = new ToolStripMenuItem();
			helpToolStripMenuItem = new ToolStripMenuItem();
			aboutToolStripMenuItem = new ToolStripMenuItem();
			statusStrip1 = new StatusStrip();
			textBox1 = new TextBox();
			textBox2 = new TextBox();
			textBox3 = new TextBox();
			button2 = new Button();
			f_ResFont1 = new F_ResFont(components);
			label1 = new Label();
			menuStrip1.SuspendLayout();
			SuspendLayout();
			// 
			// menuStrip1
			// 
			menuStrip1.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, editToolStripMenuItem, helpToolStripMenuItem });
			menuStrip1.Location = new Point(0, 0);
			menuStrip1.Name = "menuStrip1";
			menuStrip1.Padding = new Padding(8, 3, 0, 3);
			menuStrip1.Size = new Size(703, 25);
			menuStrip1.TabIndex = 3;
			menuStrip1.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { openToolStripMenuItem, saveToolStripMenuItem, saveAsToolStripMenuItem, quitToolStripMenuItem });
			fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			fileToolStripMenuItem.Size = new Size(37, 19);
			fileToolStripMenuItem.Text = "File";
			// 
			// openToolStripMenuItem
			// 
			openToolStripMenuItem.Name = "openToolStripMenuItem";
			openToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.O;
			openToolStripMenuItem.Size = new Size(182, 22);
			openToolStripMenuItem.Text = "Open";
			// 
			// saveToolStripMenuItem
			// 
			saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			saveToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.S;
			saveToolStripMenuItem.Size = new Size(182, 22);
			saveToolStripMenuItem.Text = "Save";
			// 
			// saveAsToolStripMenuItem
			// 
			saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
			saveAsToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.Shift | Keys.S;
			saveAsToolStripMenuItem.Size = new Size(182, 22);
			saveAsToolStripMenuItem.Text = "SaveAs";
			// 
			// quitToolStripMenuItem
			// 
			quitToolStripMenuItem.Name = "quitToolStripMenuItem";
			quitToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.Q;
			quitToolStripMenuItem.Size = new Size(182, 22);
			quitToolStripMenuItem.Text = "Quit";
			quitToolStripMenuItem.Click += quitToolStripMenuItem_Click;
			// 
			// editToolStripMenuItem
			// 
			editToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { exec1ToolStripMenuItem, exec2ToolStripMenuItem });
			editToolStripMenuItem.Name = "editToolStripMenuItem";
			editToolStripMenuItem.Size = new Size(39, 19);
			editToolStripMenuItem.Text = "Edit";
			// 
			// exec1ToolStripMenuItem
			// 
			exec1ToolStripMenuItem.Name = "exec1ToolStripMenuItem";
			exec1ToolStripMenuItem.ShortcutKeys = Keys.Control | Keys.E;
			exec1ToolStripMenuItem.Size = new Size(143, 22);
			exec1ToolStripMenuItem.Text = "Exec1";
			// 
			// exec2ToolStripMenuItem
			// 
			exec2ToolStripMenuItem.Name = "exec2ToolStripMenuItem";
			exec2ToolStripMenuItem.Size = new Size(143, 22);
			exec2ToolStripMenuItem.Text = "Exec2";
			// 
			// helpToolStripMenuItem
			// 
			helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { aboutToolStripMenuItem });
			helpToolStripMenuItem.Name = "helpToolStripMenuItem";
			helpToolStripMenuItem.Size = new Size(44, 19);
			helpToolStripMenuItem.Text = "Help";
			// 
			// aboutToolStripMenuItem
			// 
			aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
			aboutToolStripMenuItem.Size = new Size(107, 22);
			aboutToolStripMenuItem.Text = "About";
			// 
			// statusStrip1
			// 
			statusStrip1.Location = new Point(0, 416);
			statusStrip1.Name = "statusStrip1";
			statusStrip1.Size = new Size(703, 22);
			statusStrip1.TabIndex = 4;
			statusStrip1.Text = "statusStrip1";
			// 
			// textBox1
			// 
			textBox1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			textBox1.BackColor = Color.Black;
			textBox1.Font = new Font("Fira Code", 12F, FontStyle.Regular, GraphicsUnit.Point);
			textBox1.ForeColor = Color.White;
			textBox1.Location = new Point(12, 62);
			textBox1.Multiline = true;
			textBox1.Name = "textBox1";
			textBox1.ScrollBars = ScrollBars.Both;
			textBox1.Size = new Size(691, 351);
			textBox1.TabIndex = 5;
			// 
			// textBox2
			// 
			textBox2.Anchor = AnchorStyles.Left | AnchorStyles.Right;
			textBox2.Location = new Point(12, 118);
			textBox2.Multiline = true;
			textBox2.Name = "textBox2";
			textBox2.Size = new Size(608, 102);
			textBox2.TabIndex = 7;
			// 
			// textBox3
			// 
			textBox3.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			textBox3.Location = new Point(9, 226);
			textBox3.Multiline = true;
			textBox3.Name = "textBox3";
			textBox3.Size = new Size(608, 102);
			textBox3.TabIndex = 8;
			// 
			// button2
			// 
			button2.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			button2.Location = new Point(506, 372);
			button2.Name = "button2";
			button2.Size = new Size(90, 41);
			button2.TabIndex = 9;
			button2.Text = "button2";
			button2.UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			label1.AutoSize = true;
			label1.Location = new Point(12, 38);
			label1.Name = "label1";
			label1.Size = new Size(294, 21);
			label1.TabIndex = 6;
			label1.Text = "Aepに含まれるFootageの情報を獲得します。";
			// 
			// MainForm
			// 
			AllowDrop = true;
			AutoScaleDimensions = new SizeF(9F, 21F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(703, 438);
			Controls.Add(label1);
			Controls.Add(textBox1);
			Controls.Add(statusStrip1);
			Controls.Add(menuStrip1);
			Font = new Font("Yu Gothic UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
			FormBorderStyle = FormBorderStyle.SizableToolWindow;
			MainMenuStrip = menuStrip1;
			Margin = new Padding(4);
			Name = "MainForm";
			Text = "AepInfo";
			FormClosed += Form1_FormClosed;
			Load += Form1_Load;
			DragDrop += MainForm_DragDrop;
			DragEnter += MainForm_DragEnter;
			menuStrip1.ResumeLayout(false);
			menuStrip1.PerformLayout();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion
		private MenuStrip menuStrip1;
		private ToolStripMenuItem fileToolStripMenuItem;
		private ToolStripMenuItem quitToolStripMenuItem;
		private StatusStrip statusStrip1;
		private TextBox textBox1;
		private ToolStripMenuItem openToolStripMenuItem;
		private ToolStripMenuItem saveToolStripMenuItem;
		private ToolStripMenuItem saveAsToolStripMenuItem;
		private ToolStripMenuItem editToolStripMenuItem;
		private ToolStripMenuItem exec1ToolStripMenuItem;
		private ToolStripMenuItem exec2ToolStripMenuItem;
		private ToolStripMenuItem helpToolStripMenuItem;
		private ToolStripMenuItem aboutToolStripMenuItem;
		private TextBox textBox2;
		private TextBox textBox3;
		private Button button2;
		private F_ResFont f_ResFont1;
		private Label label1;
	}
}