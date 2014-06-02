namespace JPEG_TO_LED
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
            this.btnOpenJPEG = new System.Windows.Forms.Button();
            this.picBox1 = new System.Windows.Forms.PictureBox();
            this.btnDataToText = new System.Windows.Forms.Button();
            this.btnTxtToClipboard = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.picBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOpenJPEG
            // 
            this.btnOpenJPEG.Location = new System.Drawing.Point(13, 13);
            this.btnOpenJPEG.Name = "btnOpenJPEG";
            this.btnOpenJPEG.Size = new System.Drawing.Size(91, 23);
            this.btnOpenJPEG.TabIndex = 0;
            this.btnOpenJPEG.Text = "OpenJPEG";
            this.btnOpenJPEG.UseVisualStyleBackColor = true;
            this.btnOpenJPEG.Click += new System.EventHandler(this.btnOpenJPEG_Click);
            // 
            // picBox1
            // 
            this.picBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.picBox1.Cursor = System.Windows.Forms.Cursors.No;
            this.picBox1.Location = new System.Drawing.Point(110, 12);
            this.picBox1.Name = "picBox1";
            this.picBox1.Size = new System.Drawing.Size(250, 250);
            this.picBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picBox1.TabIndex = 1;
            this.picBox1.TabStop = false;
            // 
            // btnDataToText
            // 
            this.btnDataToText.Location = new System.Drawing.Point(13, 43);
            this.btnDataToText.Name = "btnDataToText";
            this.btnDataToText.Size = new System.Drawing.Size(91, 23);
            this.btnDataToText.TabIndex = 2;
            this.btnDataToText.Text = "DataToText";
            this.btnDataToText.UseVisualStyleBackColor = true;
            this.btnDataToText.Click += new System.EventHandler(this.btnDataToText_Click);
            // 
            // btnTxtToClipboard
            // 
            this.btnTxtToClipboard.Location = new System.Drawing.Point(13, 73);
            this.btnTxtToClipboard.Name = "btnTxtToClipboard";
            this.btnTxtToClipboard.Size = new System.Drawing.Size(91, 23);
            this.btnTxtToClipboard.TabIndex = 3;
            this.btnTxtToClipboard.Text = "TxtToClipboard";
            this.btnTxtToClipboard.UseVisualStyleBackColor = true;
            this.btnTxtToClipboard.Click += new System.EventHandler(this.btnTxtToClipboard_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(391, 284);
            this.Controls.Add(this.btnTxtToClipboard);
            this.Controls.Add(this.btnDataToText);
            this.Controls.Add(this.picBox1);
            this.Controls.Add(this.btnOpenJPEG);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.picBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnOpenJPEG;
        private System.Windows.Forms.PictureBox picBox1;
        private System.Windows.Forms.Button btnDataToText;
        private System.Windows.Forms.Button btnTxtToClipboard;
    }
}

