using System;
using System.Drawing;
using System.IO.Ports;
using System.Timers;
using System.Windows.Forms;
using LED_PI_GMTest.Modules;

namespace LED_PI_GMTest
{
    public partial class WndMain : Form
    {
        private readonly System.Timers.Timer _timer = new System.Timers.Timer(10000);
        private readonly Bitmap _image = new Bitmap(30, 30);

        private Color[,] _buffer = new Color[30, 30];
        private IModule _module;

        private static readonly IModule[] Modules = new IModule[]
            {
                new MTest(),
                new Sinusoid(), 
                new Sinusoid2(), 
                new ConcentricSinusoid(), 
                new ConcentricSinusoidLissajous(), 
                new CombinedSinusoid(), 
                new CombinedSinusoidColor(), 
                new Balls(), 
            };

        private SerialPort _port;

        public WndMain()
        {
            InitializeComponent();
            _timer.Elapsed += TimerOnElapsed;
            numFPS_ValueChanged(this, EventArgs.Empty);

            foreach (var module in Modules)
            {
                cbModules.Items.Add(module.Name);
            }

            pbWall.Image = _image;

            cbPorts.Items.AddRange(SerialPort.GetPortNames());
            cbPorts.SelectedIndex = 0;

            cbRefresh.Checked = true;

            numDepth.Value = Color.Depth;
        }

        private void TimerOnElapsed(object sender, ElapsedEventArgs elapsedEventArgs)
        {
            if (_module != null) _module.Draw(ref _buffer);

            DrawImage();
            
            if(cbEnable.Checked) SendImage();
        }

        private void SendImage()
        {
            try
            {
                if (_port != null && _port.IsOpen)
                {
                    var buffer = new byte[30 * 30 * 3];

                    for (int i = 0; i < _buffer.GetLength(0); i++)
                    {
                        for (int j = 0; j < _buffer.GetLength(1); j++)
                        {
                            buffer[3 * (30 * i + j) + 0] = _buffer[i, j].Green;
                            buffer[3 * (30 * i + j) + 1] = _buffer[i, j].Blue;
                            buffer[3 * (30 * i + j) + 2] = _buffer[i, j].Red;
                        }
                    }
                    _port.Write(buffer, 0, buffer.Length);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Fail:" +ex.Message);
            }
        }

        private void DrawImage()
        {
            var image = new Bitmap(30, 30);
            for (int i = 0; i < _buffer.GetLength(0); i++)
            {
                for (int j = 0; j < _buffer.GetLength(1); j++)
                {
                    image.SetPixel(i, j, _buffer[i, j].ToColor());
                }
            }

            pbWall.Image = image;
        }

        private void cbRefresh_CheckedChanged(object sender, EventArgs e)
        {
            _timer.Enabled = cbRefresh.Checked;
        }

        private void numFPS_ValueChanged(object sender, EventArgs e)
        {
            _timer.Interval = (int) (1e3 / (double) numFPS.Value);
         }

        private void cbModules_SelectedIndexChanged(object sender, EventArgs e)
        {
            _module = Modules[cbModules.SelectedIndex];
            pgModuleSettings.SelectedObject = _module.GetSettings();
        }

        private void cbEnable_CheckedChanged(object sender, EventArgs e)
        {
            if(cbEnable.Checked)
            try
            {
                if (_port != null && _port.IsOpen)
                    _port.Close();
                _port = new SerialPort(cbPorts.SelectedItem.ToString(), 115200);
                _port.Open();
            }
            catch (Exception ex)
            {
                cbEnable.Checked = false;
                MessageBox.Show("Fail:" + ex.Message);
            }
        }

        private void numDepth_ValueChanged(object sender, EventArgs e)
        {
            Color.Depth = (byte) numDepth.Value;
        }
    }
}
