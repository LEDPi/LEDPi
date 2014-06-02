using System;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;
using TeensyTest.Properties;

namespace TeensyTest
{
    public partial class TeensyTestMain : Form
    {
        private SerialPort _port;

        public TeensyTestMain()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
// ReSharper disable once CoVariantArrayConversion
            cbPort.Items.AddRange( SerialPort.GetPortNames() );
            cbPort.SelectedIndex = 0;
            SetColor();
        }

        private void SetColor()
        {
            pnlColor.BackColor = Color.FromArgb((int)(numRed.Value * 255),
                (int)(numGreen.Value * 255),
                (int)(numBlue.Value * 255));
        }

        private void numBlue_ValueChanged(object sender, EventArgs e)
        {
            SetColor();
            Send();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            Send();
        }

        private void Send()
        {
            try
            {
                if (_port != null && _port.IsOpen)
                {
                    var buffer = new byte[30*30*3];

                    for (int i = 0; i < 900; ++i)
                    {
                        buffer[i*3 + 0] = (byte) (numRed.Value*4);
                        buffer[i*3 + 1] = (byte) (numGreen.Value*4);
                        buffer[i*3 + 2] = (byte) (numBlue.Value*4);
                    }

                    _port.Write(buffer, 0, buffer.Length);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(Resources.TeensyTestMain_Send_Fail__ + ex.Message);
            }
        }

        private void btnColor_Click(object sender, EventArgs e)
        {
            var dlg = new ColorDialog {AllowFullOpen = true};

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                numRed  .Value = (decimal)(dlg.Color.R / (float)255);
                numGreen.Value = (decimal)(dlg.Color.G / (float)255);
                numBlue .Value = (decimal)(dlg.Color.B / (float)255);
            }
        }

        private void cbPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if(_port != null && _port.IsOpen)
                    _port.Close();

                _port = new SerialPort(cbPort.SelectedItem.ToString(), 115200);
                _port.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show(Resources.TeensyTestMain_Send_Fail__ + ex.Message);
            }
        }

        private void TeensyTestMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (_port != null && _port.IsOpen)
                _port.Close();
        }
    }
}
