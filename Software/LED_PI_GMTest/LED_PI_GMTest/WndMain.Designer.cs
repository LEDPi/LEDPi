namespace LED_PI_GMTest
{
    partial class WndMain
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
            this.splitMain = new System.Windows.Forms.SplitContainer();
            this.label3 = new System.Windows.Forms.Label();
            this.numDepth = new System.Windows.Forms.NumericUpDown();
            this.cbEnable = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cbPorts = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.numFPS = new System.Windows.Forms.NumericUpDown();
            this.cbRefresh = new System.Windows.Forms.CheckBox();
            this.pbWall = new System.Windows.Forms.PictureBox();
            this.pgModuleSettings = new System.Windows.Forms.PropertyGrid();
            this.cbModules = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.splitMain)).BeginInit();
            this.splitMain.Panel1.SuspendLayout();
            this.splitMain.Panel2.SuspendLayout();
            this.splitMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numDepth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numFPS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbWall)).BeginInit();
            this.SuspendLayout();
            // 
            // splitMain
            // 
            this.splitMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitMain.Location = new System.Drawing.Point(0, 0);
            this.splitMain.Name = "splitMain";
            // 
            // splitMain.Panel1
            // 
            this.splitMain.Panel1.Controls.Add(this.label3);
            this.splitMain.Panel1.Controls.Add(this.numDepth);
            this.splitMain.Panel1.Controls.Add(this.cbEnable);
            this.splitMain.Panel1.Controls.Add(this.label2);
            this.splitMain.Panel1.Controls.Add(this.cbPorts);
            this.splitMain.Panel1.Controls.Add(this.label1);
            this.splitMain.Panel1.Controls.Add(this.numFPS);
            this.splitMain.Panel1.Controls.Add(this.cbRefresh);
            this.splitMain.Panel1.Controls.Add(this.pbWall);
            // 
            // splitMain.Panel2
            // 
            this.splitMain.Panel2.Controls.Add(this.pgModuleSettings);
            this.splitMain.Panel2.Controls.Add(this.cbModules);
            this.splitMain.Size = new System.Drawing.Size(612, 398);
            this.splitMain.SplitterDistance = 244;
            this.splitMain.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 254);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Color Depth";
            // 
            // numDepth
            // 
            this.numDepth.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numDepth.Location = new System.Drawing.Point(90, 252);
            this.numDepth.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numDepth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numDepth.Name = "numDepth";
            this.numDepth.Size = new System.Drawing.Size(111, 20);
            this.numDepth.TabIndex = 7;
            this.numDepth.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numDepth.ValueChanged += new System.EventHandler(this.numDepth_ValueChanged);
            // 
            // cbEnable
            // 
            this.cbEnable.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cbEnable.AutoSize = true;
            this.cbEnable.Location = new System.Drawing.Point(182, 369);
            this.cbEnable.Name = "cbEnable";
            this.cbEnable.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.cbEnable.Size = new System.Drawing.Size(59, 17);
            this.cbEnable.TabIndex = 6;
            this.cbEnable.Text = "Enable";
            this.cbEnable.UseVisualStyleBackColor = true;
            this.cbEnable.CheckedChanged += new System.EventHandler(this.cbEnable_CheckedChanged);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 345);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "TEENSY Port";
            // 
            // cbPorts
            // 
            this.cbPorts.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbPorts.FormattingEnabled = true;
            this.cbPorts.Location = new System.Drawing.Point(90, 342);
            this.cbPorts.Name = "cbPorts";
            this.cbPorts.Size = new System.Drawing.Size(151, 21);
            this.cbPorts.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 318);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "FPS: ";
            // 
            // numFPS
            // 
            this.numFPS.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numFPS.Location = new System.Drawing.Point(90, 316);
            this.numFPS.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numFPS.Name = "numFPS";
            this.numFPS.Size = new System.Drawing.Size(82, 20);
            this.numFPS.TabIndex = 2;
            this.numFPS.Value = new decimal(new int[] {
            25,
            0,
            0,
            0});
            this.numFPS.ValueChanged += new System.EventHandler(this.numFPS_ValueChanged);
            // 
            // cbRefresh
            // 
            this.cbRefresh.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cbRefresh.AutoSize = true;
            this.cbRefresh.Location = new System.Drawing.Point(179, 316);
            this.cbRefresh.Name = "cbRefresh";
            this.cbRefresh.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.cbRefresh.Size = new System.Drawing.Size(63, 17);
            this.cbRefresh.TabIndex = 1;
            this.cbRefresh.Text = "Refresh";
            this.cbRefresh.UseVisualStyleBackColor = true;
            this.cbRefresh.CheckedChanged += new System.EventHandler(this.cbRefresh_CheckedChanged);
            // 
            // pbWall
            // 
            this.pbWall.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pbWall.Location = new System.Drawing.Point(3, 3);
            this.pbWall.Name = "pbWall";
            this.pbWall.Size = new System.Drawing.Size(242, 243);
            this.pbWall.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbWall.TabIndex = 0;
            this.pbWall.TabStop = false;
            // 
            // pgModuleSettings
            // 
            this.pgModuleSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pgModuleSettings.Location = new System.Drawing.Point(3, 39);
            this.pgModuleSettings.Name = "pgModuleSettings";
            this.pgModuleSettings.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.pgModuleSettings.Size = new System.Drawing.Size(354, 356);
            this.pgModuleSettings.TabIndex = 1;
            // 
            // cbModules
            // 
            this.cbModules.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbModules.FormattingEnabled = true;
            this.cbModules.Location = new System.Drawing.Point(3, 12);
            this.cbModules.Name = "cbModules";
            this.cbModules.Size = new System.Drawing.Size(353, 21);
            this.cbModules.TabIndex = 0;
            this.cbModules.SelectedIndexChanged += new System.EventHandler(this.cbModules_SelectedIndexChanged);
            // 
            // WndMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(612, 398);
            this.Controls.Add(this.splitMain);
            this.MinimumSize = new System.Drawing.Size(628, 437);
            this.Name = "WndMain";
            this.Text = "LED_PI GM Test";
            this.splitMain.Panel1.ResumeLayout(false);
            this.splitMain.Panel1.PerformLayout();
            this.splitMain.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitMain)).EndInit();
            this.splitMain.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numDepth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numFPS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbWall)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitMain;
        private System.Windows.Forms.CheckBox cbRefresh;
        private System.Windows.Forms.PictureBox pbWall;
        private System.Windows.Forms.NumericUpDown numFPS;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PropertyGrid pgModuleSettings;
        private System.Windows.Forms.ComboBox cbModules;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbPorts;
        private System.Windows.Forms.CheckBox cbEnable;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numDepth;
    }
}

