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
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.openAllBtn = new System.Windows.Forms.Button();
            this.closeAllBtn = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
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
            this.columnHeader2,
            this.columnHeader3});
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
            this.columnHeader1.Text = "Dør";
            this.columnHeader1.Width = 130;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Status";
            this.columnHeader2.Width = 145;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Toggle";
            this.columnHeader3.Width = 160;
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
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button1.ImageKey = "script.png";
            this.button1.ImageList = this.icons;
            this.button1.Location = new System.Drawing.Point(12, 257);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(93, 42);
            this.button1.TabIndex = 0;
            this.button1.Text = "Åben log";
            this.button1.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.button1.UseVisualStyleBackColor = true;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Alias";
            this.columnHeader4.Width = 120;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(682, 311);
            this.Controls.Add(this.unitList);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.closeAllBtn);
            this.Controls.Add(this.openAllBtn);
            this.Controls.Add(this.logoffBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Prison System";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button logoffBtn;
        private System.Windows.Forms.ListView unitList;
        private System.Windows.Forms.Button openAllBtn;
        private System.Windows.Forms.Button closeAllBtn;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ImageList icons;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ColumnHeader columnHeader4;

    }
}

