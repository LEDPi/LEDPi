using System.Drawing;

namespace UDP_Test
{
    partial class UDPTest
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UDPTest));
            this.btnSend = new System.Windows.Forms.Button();
            this.chBoxExpectResponse = new System.Windows.Forms.CheckBox();
            this.cbBoxMessages = new System.Windows.Forms.ComboBox();
            this.tbBoxIPAdress = new System.Windows.Forms.TextBox();
            this.tbPortSend = new System.Windows.Forms.TextBox();
            this.labIPAdress = new System.Windows.Forms.Label();
            this.labPortSend = new System.Windows.Forms.Label();
            this.tbPortRecv = new System.Windows.Forms.TextBox();
            this.labPortRecv = new System.Windows.Forms.Label();
            this.labDataToSend = new System.Windows.Forms.Label();
            this.tbDataInput = new System.Windows.Forms.TextBox();
            this.lbFunctionCode = new System.Windows.Forms.Label();
            this.tbCheckSum = new System.Windows.Forms.TextBox();
            this.lbCheckSum = new System.Windows.Forms.Label();
            this.btnClear = new System.Windows.Forms.Button();
            this.lblStatus = new System.Windows.Forms.Label();
            this.tbOutput = new System.Windows.Forms.TextBox();
            this.tbFunctionCode = new System.Windows.Forms.TextBox();
            this.btnStartReceive = new System.Windows.Forms.Button();
            this.btnEndReceive = new System.Windows.Forms.Button();
            this.chBoxCheckReceivedMessages = new System.Windows.Forms.CheckBox();
            this.chBoxCounter = new System.Windows.Forms.CheckBox();
            this.chBoxTimestamp = new System.Windows.Forms.CheckBox();
            this.tbMessagesSpeed = new System.Windows.Forms.TextBox();
            this.lblMessagesPerSecond = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(384, 10);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(75, 23);
            this.btnSend.TabIndex = 0;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // chBoxExpectResponse
            // 
            this.chBoxExpectResponse.AutoSize = true;
            this.chBoxExpectResponse.Location = new System.Drawing.Point(267, 41);
            this.chBoxExpectResponse.Name = "chBoxExpectResponse";
            this.chBoxExpectResponse.Size = new System.Drawing.Size(110, 17);
            this.chBoxExpectResponse.TabIndex = 1;
            this.chBoxExpectResponse.Text = "Expect Response";
            this.chBoxExpectResponse.UseVisualStyleBackColor = true;
            // 
            // cbBoxMessages
            // 
            this.cbBoxMessages.FormattingEnabled = true;
            this.cbBoxMessages.Location = new System.Drawing.Point(11, 57);
            this.cbBoxMessages.Name = "cbBoxMessages";
            this.cbBoxMessages.Size = new System.Drawing.Size(105, 21);
            this.cbBoxMessages.TabIndex = 2;
            this.cbBoxMessages.SelectedIndexChanged += new System.EventHandler(this.cbBoxMessages_SelectedIndexChanged);
            // 
            // tbBoxIPAdress
            // 
            this.tbBoxIPAdress.Location = new System.Drawing.Point(66, 15);
            this.tbBoxIPAdress.Name = "tbBoxIPAdress";
            this.tbBoxIPAdress.Size = new System.Drawing.Size(73, 20);
            this.tbBoxIPAdress.TabIndex = 4;
            this.tbBoxIPAdress.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbBoxesNetwork_KeyDown);
            this.tbBoxIPAdress.Leave += new System.EventHandler(this.tbBoxesNetwork_Leave);
            // 
            // tbPortSend
            // 
            this.tbPortSend.Location = new System.Drawing.Point(205, 15);
            this.tbPortSend.Name = "tbPortSend";
            this.tbPortSend.Size = new System.Drawing.Size(36, 20);
            this.tbPortSend.TabIndex = 5;
            this.tbPortSend.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbBoxesNetwork_KeyDown);
            this.tbPortSend.Leave += new System.EventHandler(this.tbBoxesNetwork_Leave);
            // 
            // labIPAdress
            // 
            this.labIPAdress.AutoSize = true;
            this.labIPAdress.Location = new System.Drawing.Point(8, 15);
            this.labIPAdress.Name = "labIPAdress";
            this.labIPAdress.Size = new System.Drawing.Size(52, 13);
            this.labIPAdress.TabIndex = 6;
            this.labIPAdress.Text = "IP Adress";
            // 
            // labPortSend
            // 
            this.labPortSend.AutoSize = true;
            this.labPortSend.Location = new System.Drawing.Point(145, 15);
            this.labPortSend.Name = "labPortSend";
            this.labPortSend.Size = new System.Drawing.Size(54, 13);
            this.labPortSend.TabIndex = 7;
            this.labPortSend.Text = "Port Send";
            // 
            // tbPortRecv
            // 
            this.tbPortRecv.Location = new System.Drawing.Point(308, 13);
            this.tbPortRecv.Name = "tbPortRecv";
            this.tbPortRecv.Size = new System.Drawing.Size(36, 20);
            this.tbPortRecv.TabIndex = 9;
            this.tbPortRecv.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbBoxesNetwork_KeyDown);
            this.tbPortRecv.Leave += new System.EventHandler(this.tbBoxesNetwork_Leave);
            // 
            // labPortRecv
            // 
            this.labPortRecv.AutoSize = true;
            this.labPortRecv.Location = new System.Drawing.Point(247, 15);
            this.labPortRecv.Name = "labPortRecv";
            this.labPortRecv.Size = new System.Drawing.Size(55, 13);
            this.labPortRecv.TabIndex = 10;
            this.labPortRecv.Text = "Port Recv";
            // 
            // labDataToSend
            // 
            this.labDataToSend.AutoSize = true;
            this.labDataToSend.Location = new System.Drawing.Point(9, 81);
            this.labDataToSend.Name = "labDataToSend";
            this.labDataToSend.Size = new System.Drawing.Size(57, 13);
            this.labDataToSend.TabIndex = 11;
            this.labDataToSend.Text = "Data Input";
            // 
            // tbDataInput
            // 
            this.tbDataInput.Location = new System.Drawing.Point(11, 97);
            this.tbDataInput.Name = "tbDataInput";
            this.tbDataInput.Size = new System.Drawing.Size(552, 20);
            this.tbDataInput.TabIndex = 12;
            this.tbDataInput.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbDataInput_KeyDown);
            this.tbDataInput.Leave += new System.EventHandler(this.tBoxDataInput_Leave);
            // 
            // lbFunctionCode
            // 
            this.lbFunctionCode.AutoSize = true;
            this.lbFunctionCode.Location = new System.Drawing.Point(8, 41);
            this.lbFunctionCode.Name = "lbFunctionCode";
            this.lbFunctionCode.Size = new System.Drawing.Size(73, 13);
            this.lbFunctionCode.TabIndex = 13;
            this.lbFunctionCode.Text = "FunctionCode";
            // 
            // tbCheckSum
            // 
            this.tbCheckSum.Location = new System.Drawing.Point(191, 58);
            this.tbCheckSum.Name = "tbCheckSum";
            this.tbCheckSum.ReadOnly = true;
            this.tbCheckSum.Size = new System.Drawing.Size(59, 20);
            this.tbCheckSum.TabIndex = 14;
            // 
            // lbCheckSum
            // 
            this.lbCheckSum.AutoSize = true;
            this.lbCheckSum.Location = new System.Drawing.Point(188, 41);
            this.lbCheckSum.Name = "lbCheckSum";
            this.lbCheckSum.Size = new System.Drawing.Size(62, 13);
            this.lbCheckSum.TabIndex = 15;
            this.lbCheckSum.Text = "Check Sum";
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(11, 447);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 16;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.Clear_Click);
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Location = new System.Drawing.Point(91, 452);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.lblStatus.Size = new System.Drawing.Size(43, 13);
            this.lblStatus.TabIndex = 17;
            this.lblStatus.Text = "Waiting";
            // 
            // tbOutput
            // 
            this.tbOutput.BackColor = System.Drawing.Color.White;
            this.tbOutput.Location = new System.Drawing.Point(12, 123);
            this.tbOutput.Multiline = true;
            this.tbOutput.Name = "tbOutput";
            this.tbOutput.ReadOnly = true;
            this.tbOutput.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.tbOutput.Size = new System.Drawing.Size(552, 318);
            this.tbOutput.TabIndex = 18;
            this.tbOutput.WordWrap = false;
            // 
            // tbFunctionCode
            // 
            this.tbFunctionCode.Location = new System.Drawing.Point(122, 57);
            this.tbFunctionCode.Name = "tbFunctionCode";
            this.tbFunctionCode.Size = new System.Drawing.Size(59, 20);
            this.tbFunctionCode.TabIndex = 19;
            this.tbFunctionCode.Leave += new System.EventHandler(this.tbFunctionCode_Leave);
            // 
            // btnStartReceive
            // 
            this.btnStartReceive.Location = new System.Drawing.Point(488, 10);
            this.btnStartReceive.Name = "btnStartReceive";
            this.btnStartReceive.Size = new System.Drawing.Size(75, 23);
            this.btnStartReceive.TabIndex = 20;
            this.btnStartReceive.Text = "Start Recv";
            this.btnStartReceive.UseVisualStyleBackColor = true;
            this.btnStartReceive.Click += new System.EventHandler(this.btnStartReceive_Click);
            // 
            // btnEndReceive
            // 
            this.btnEndReceive.Enabled = false;
            this.btnEndReceive.Location = new System.Drawing.Point(488, 41);
            this.btnEndReceive.Name = "btnEndReceive";
            this.btnEndReceive.Size = new System.Drawing.Size(75, 23);
            this.btnEndReceive.TabIndex = 21;
            this.btnEndReceive.Text = "End Recv";
            this.btnEndReceive.UseVisualStyleBackColor = true;
            this.btnEndReceive.Click += new System.EventHandler(this.btnEndReceive_Click);
            // 
            // chBoxCheckReceivedMessages
            // 
            this.chBoxCheckReceivedMessages.AutoSize = true;
            this.chBoxCheckReceivedMessages.Checked = true;
            this.chBoxCheckReceivedMessages.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chBoxCheckReceivedMessages.Location = new System.Drawing.Point(267, 60);
            this.chBoxCheckReceivedMessages.Name = "chBoxCheckReceivedMessages";
            this.chBoxCheckReceivedMessages.Size = new System.Drawing.Size(108, 17);
            this.chBoxCheckReceivedMessages.TabIndex = 22;
            this.chBoxCheckReceivedMessages.Text = "Check Messages";
            this.chBoxCheckReceivedMessages.UseVisualStyleBackColor = true;
            // 
            // chBoxCounter
            // 
            this.chBoxCounter.AutoSize = true;
            this.chBoxCounter.Checked = true;
            this.chBoxCounter.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chBoxCounter.Location = new System.Drawing.Point(384, 41);
            this.chBoxCounter.Name = "chBoxCounter";
            this.chBoxCounter.Size = new System.Drawing.Size(63, 17);
            this.chBoxCounter.TabIndex = 24;
            this.chBoxCounter.Text = "Counter";
            this.chBoxCounter.UseVisualStyleBackColor = true;
            // 
            // chBoxTimestamp
            // 
            this.chBoxTimestamp.AutoSize = true;
            this.chBoxTimestamp.Location = new System.Drawing.Point(384, 61);
            this.chBoxTimestamp.Name = "chBoxTimestamp";
            this.chBoxTimestamp.Size = new System.Drawing.Size(77, 17);
            this.chBoxTimestamp.TabIndex = 25;
            this.chBoxTimestamp.Text = "Timestemp";
            this.chBoxTimestamp.UseVisualStyleBackColor = true;
            // 
            // tbMessagesSpeed
            // 
            this.tbMessagesSpeed.Location = new System.Drawing.Point(462, 450);
            this.tbMessagesSpeed.Name = "tbMessagesSpeed";
            this.tbMessagesSpeed.ReadOnly = true;
            this.tbMessagesSpeed.Size = new System.Drawing.Size(23, 20);
            this.tbMessagesSpeed.TabIndex = 26;
            // 
            // lblMessagesPerSecond
            // 
            this.lblMessagesPerSecond.AutoSize = true;
            this.lblMessagesPerSecond.Location = new System.Drawing.Point(489, 453);
            this.lblMessagesPerSecond.Name = "lblMessagesPerSecond";
            this.lblMessagesPerSecond.Size = new System.Drawing.Size(74, 13);
            this.lblMessagesPerSecond.TabIndex = 27;
            this.lblMessagesPerSecond.Text = "Msgs/Second";
            // 
            // UDPTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(576, 482);
            this.Controls.Add(this.lblMessagesPerSecond);
            this.Controls.Add(this.tbMessagesSpeed);
            this.Controls.Add(this.chBoxTimestamp);
            this.Controls.Add(this.chBoxCounter);
            this.Controls.Add(this.chBoxCheckReceivedMessages);
            this.Controls.Add(this.btnEndReceive);
            this.Controls.Add(this.btnStartReceive);
            this.Controls.Add(this.tbFunctionCode);
            this.Controls.Add(this.tbOutput);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.lbCheckSum);
            this.Controls.Add(this.tbCheckSum);
            this.Controls.Add(this.lbFunctionCode);
            this.Controls.Add(this.tbDataInput);
            this.Controls.Add(this.labDataToSend);
            this.Controls.Add(this.labPortRecv);
            this.Controls.Add(this.tbPortRecv);
            this.Controls.Add(this.labPortSend);
            this.Controls.Add(this.labIPAdress);
            this.Controls.Add(this.tbPortSend);
            this.Controls.Add(this.tbBoxIPAdress);
            this.Controls.Add(this.cbBoxMessages);
            this.Controls.Add(this.chBoxExpectResponse);
            this.Controls.Add(this.btnSend);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "UDPTest";
            this.Text = "UDP Test";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.UDPTest_FormClosing);
            this.Load += new System.EventHandler(this.UDPTest_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.CheckBox chBoxExpectResponse;
        private System.Windows.Forms.ComboBox cbBoxMessages;
        private System.Windows.Forms.TextBox tbBoxIPAdress;
        private System.Windows.Forms.TextBox tbPortSend;
        private System.Windows.Forms.Label labIPAdress;
        private System.Windows.Forms.Label labPortSend;
        private System.Windows.Forms.TextBox tbPortRecv;
        private System.Windows.Forms.Label labPortRecv;
        private System.Windows.Forms.Label labDataToSend;
        private System.Windows.Forms.TextBox tbDataInput;
        private System.Windows.Forms.Label lbFunctionCode;
        private System.Windows.Forms.TextBox tbCheckSum;
        private System.Windows.Forms.Label lbCheckSum;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.TextBox tbOutput;
        private System.Windows.Forms.TextBox tbFunctionCode;
        private System.Windows.Forms.Button btnStartReceive;
        private System.Windows.Forms.Button btnEndReceive;
        private System.Windows.Forms.CheckBox chBoxCheckReceivedMessages;
        private System.Windows.Forms.CheckBox chBoxCounter;
        private System.Windows.Forms.CheckBox chBoxTimestamp;
        private System.Windows.Forms.TextBox tbMessagesSpeed;
        private System.Windows.Forms.Label lblMessagesPerSecond;
    }
}

