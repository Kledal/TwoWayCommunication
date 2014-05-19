namespace prisonSystem
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.logoffBtn = new System.Windows.Forms.Button();
            this.icons = new System.Windows.Forms.ImageList(this.components);
            this.unitList = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.slaveMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.åbenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lukDørToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.opdaterStatusToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openAllBtn = new System.Windows.Forms.Button();
            this.closeAllBtn = new System.Windows.Forms.Button();
            this.openLogBtn = new System.Windows.Forms.Button();
            this.slaveUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.slaveStatusTimer = new System.Windows.Forms.Timer(this.components);
            this.commandQueueTimer = new System.Windows.Forms.Timer(this.components);
            this.slaveMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // logoffBtn
            // 
            this.logoffBtn.ImageKey = "user_delete.png";
            this.logoffBtn.ImageList = this.icons;
            this.logoffBtn.Location = new System.Drawing.Point(12, 12);
            this.logoffBtn.Name = "logoffBtn";
            this.logoffBtn.Size = new System.Drawing.Size(93, 42);
            this.logoffBtn.TabIndex = 0;
            this.logoffBtn.Text = "Log af";
            this.logoffBtn.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.logoffBtn.UseVisualStyleBackColor = true;
            this.logoffBtn.Click += new System.EventHandler(this.logoffBtn_Click);
            // 
            // icons
            // 
            this.icons.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("icons.ImageStream")));
            this.icons.TransparentColor = System.Drawing.Color.Transparent;
            this.icons.Images.SetKeyName(0, "user_delete.png");
            this.icons.Images.SetKeyName(1, "door.png");
            this.icons.Images.SetKeyName(2, "door_open.png");
            this.icons.Images.SetKeyName(3, "script.png");
            // 
            // unitList
            // 
            this.unitList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.unitList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader4,
            this.columnHeader2});
            this.unitList.ContextMenuStrip = this.slaveMenu;
            this.unitList.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.unitList.FullRowSelect = true;
            this.unitList.GridLines = true;
            this.unitList.Location = new System.Drawing.Point(111, 12);
            this.unitList.Name = "unitList";
            this.unitList.Size = new System.Drawing.Size(559, 287);
            this.unitList.TabIndex = 2;
            this.unitList.UseCompatibleStateImageBehavior = false;
            this.unitList.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Adresse";
            this.columnHeader1.Width = 130;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Alias";
            this.columnHeader4.Width = 180;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Status";
            this.columnHeader2.Width = 200;
            // 
            // slaveMenu
            // 
            this.slaveMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.åbenToolStripMenuItem,
            this.lukDørToolStripMenuItem,
            this.opdaterStatusToolStripMenuItem});
            this.slaveMenu.Name = "slaveMenu";
            this.slaveMenu.Size = new System.Drawing.Size(152, 70);
            // 
            // åbenToolStripMenuItem
            // 
            this.åbenToolStripMenuItem.Name = "åbenToolStripMenuItem";
            this.åbenToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.åbenToolStripMenuItem.Text = "Åben dør";
            this.åbenToolStripMenuItem.Click += new System.EventHandler(this.åbenToolStripMenuItem_Click);
            // 
            // lukDørToolStripMenuItem
            // 
            this.lukDørToolStripMenuItem.Name = "lukDørToolStripMenuItem";
            this.lukDørToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.lukDørToolStripMenuItem.Text = "Luk dør";
            this.lukDørToolStripMenuItem.Click += new System.EventHandler(this.lukDørToolStripMenuItem_Click);
            // 
            // opdaterStatusToolStripMenuItem
            // 
            this.opdaterStatusToolStripMenuItem.Name = "opdaterStatusToolStripMenuItem";
            this.opdaterStatusToolStripMenuItem.Size = new System.Drawing.Size(151, 22);
            this.opdaterStatusToolStripMenuItem.Text = "Opdater status";
            this.opdaterStatusToolStripMenuItem.Click += new System.EventHandler(this.opdaterStatusToolStripMenuItem_Click);
            // 
            // openAllBtn
            // 
            this.openAllBtn.ImageKey = "door_open.png";
            this.openAllBtn.ImageList = this.icons;
            this.openAllBtn.Location = new System.Drawing.Point(12, 60);
            this.openAllBtn.Name = "openAllBtn";
            this.openAllBtn.Size = new System.Drawing.Size(93, 42);
            this.openAllBtn.TabIndex = 0;
            this.openAllBtn.Text = "Åben alle";
            this.openAllBtn.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.openAllBtn.UseVisualStyleBackColor = true;
            this.openAllBtn.Click += new System.EventHandler(this.openAllBtn_Click);
            // 
            // closeAllBtn
            // 
            this.closeAllBtn.ImageKey = "door.png";
            this.closeAllBtn.ImageList = this.icons;
            this.closeAllBtn.Location = new System.Drawing.Point(12, 108);
            this.closeAllBtn.Name = "closeAllBtn";
            this.closeAllBtn.Size = new System.Drawing.Size(93, 42);
            this.closeAllBtn.TabIndex = 0;
            this.closeAllBtn.Text = "Luk alle";
            this.closeAllBtn.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.closeAllBtn.UseVisualStyleBackColor = true;
            this.closeAllBtn.Click += new System.EventHandler(this.closeAllBtn_Click);
            // 
            // openLogBtn
            // 
            this.openLogBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.openLogBtn.ImageKey = "script.png";
            this.openLogBtn.ImageList = this.icons;
            this.openLogBtn.Location = new System.Drawing.Point(12, 257);
            this.openLogBtn.Name = "openLogBtn";
            this.openLogBtn.Size = new System.Drawing.Size(93, 42);
            this.openLogBtn.TabIndex = 0;
            this.openLogBtn.Text = "Åben log";
            this.openLogBtn.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.openLogBtn.UseVisualStyleBackColor = true;
            this.openLogBtn.Click += new System.EventHandler(this.openLogBtn_Click);
            // 
            // slaveUpdateTimer
            // 
            this.slaveUpdateTimer.Enabled = true;
            this.slaveUpdateTimer.Tick += new System.EventHandler(this.slaveUpdateTimer_Tick);
            // 
            // slaveStatusTimer
            // 
            this.slaveStatusTimer.Enabled = true;
            this.slaveStatusTimer.Interval = 1000;
            this.slaveStatusTimer.Tick += new System.EventHandler(this.slaveStatusTimer_Tick);
            // 
            // commandQueueTimer
            // 
            this.commandQueueTimer.Enabled = true;
            this.commandQueueTimer.Tick += new System.EventHandler(this.commandQueueTimer_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(682, 311);
            this.Controls.Add(this.unitList);
            this.Controls.Add(this.openLogBtn);
            this.Controls.Add(this.closeAllBtn);
            this.Controls.Add(this.openAllBtn);
            this.Controls.Add(this.logoffBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Prison System";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.slaveMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button logoffBtn;
        private System.Windows.Forms.ListView unitList;
        private System.Windows.Forms.Button openAllBtn;
        private System.Windows.Forms.Button closeAllBtn;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ImageList icons;
        private System.Windows.Forms.Button openLogBtn;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ContextMenuStrip slaveMenu;
        private System.Windows.Forms.ToolStripMenuItem åbenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem lukDørToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem opdaterStatusToolStripMenuItem;
        private System.Windows.Forms.Timer slaveUpdateTimer;
        private System.Windows.Forms.Timer slaveStatusTimer;
        private System.Windows.Forms.Timer commandQueueTimer;

    }
}

