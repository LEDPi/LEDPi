using System;
using System.Collections.Generic;
using System.Linq;
using System.Globalization;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;


namespace UDP_Test
{
    public partial class UDPTest : Form
    {
        private readonly Sender _sender = new Sender();
        private List<byte> _bytes = new List<byte>();
        private delegate void MethodDelegate(string text,TextBox textbox,String flag);
        private Thread _receiverThread, _timerThread;
        private static UdpClient _tmpSocket;
        private static int counter;
        private static Mutex _mut;
   
        public UDPTest()
        {
            InitializeComponent();

            //Default Sender Values
            _sender.IPAdress = "192.168.1.10";
            _sender.SendingPort = 8000;
            _sender.PortReceiving = 8100;

            tbBoxIPAdress.Text = _sender.IPAdress;
            tbPortSend.Text = _sender.SendingPort.ToString(CultureInfo.InvariantCulture);
            tbPortRecv.Text = _sender.PortReceiving.ToString(CultureInfo.InvariantCulture);

            _mut = new Mutex();
            _receiverThread = new Thread(ReceiverThread);
            _timerThread = new Thread(threadReceivingSpeed);
            _timerThread.Start();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (_bytes != null)
            {
                var useData = new Byte[_bytes.Count];
                Array.Copy(_bytes.ToArray(), 0, useData, 0, _bytes.Count);

                UInt16 tmpFC;
                UInt16.TryParse(tbFunctionCode.Text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out tmpFC);
                var dataToSend = Sender.BuildMessage(tmpFC, useData);

                if (chBoxExpectResponse.Checked)
                {
                    _sender.Send(dataToSend);
                    tbOutput.AppendText("Sent Message: " + BitConverter.ToString(dataToSend).Replace("-", " ") + Environment.NewLine);
                    lblStatus.Text= @"Waiting for response";
                    String receivedMessage = _sender.ReceiveMessageExpected(chBoxCheckReceivedMessages.Checked);

                    if (string.Equals(receivedMessage,"No response"))
                    {
                        tbOutput.AppendText(receivedMessage + Environment.NewLine);                        
                    }
                    else
                    {
                        tbOutput.AppendText("Recieved Message: " + receivedMessage + Environment.NewLine);
                    }    
                    
                }
                else
                { 
                    _sender.Send(dataToSend);
                    tbOutput.AppendText("Sent Message: "+BitConverter.ToString(dataToSend).Replace("-"," ")+ Environment.NewLine);
                }
            }        
        }

        private void UDPTest_Load(object sender, EventArgs e)
        {
// ReSharper disable CoVariantArrayConversion
            cbBoxMessages.Items.AddRange(Enum.GetNames(typeof(Messages)).ToArray());
// ReSharper restore CoVariantArrayConversion
        }

        private void cbBoxMessages_SelectedIndexChanged(object sender, EventArgs e)
        {
            Messages msg;
            if (Enum.TryParse(cbBoxMessages.SelectedItem.ToString(), out msg))
            {
                tbFunctionCode.Text = ((UInt16)msg).ToString("X4");
                tbFunctionCode_Leave(this, EventArgs.Empty);
            }
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            tbOutput.Clear();
            counter = 0; 
        }

        private void tBoxDataInput_Leave(object sender, EventArgs e)
        {
            tbDataInput.Text = ExpandString(tbDataInput.Text);
            String[] bytes;

            if (!string.IsNullOrEmpty(tbDataInput.Text))
                bytes = tbDataInput.Text.Split(' ');
            else
                bytes = new String[] { };

            _bytes = new List<byte>(bytes.Length);

            foreach (string val in bytes)
            {
                byte tmp;
                byte.TryParse(val, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out tmp);
                _bytes.Add(tmp);
            }

            UInt16 tmpFC;
            
            if ( UInt16.TryParse(tbFunctionCode.Text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out tmpFC))
            {
                tbCheckSum.Text = Convert.ToString(((_sender.CalculateChecksum(tmpFC, _bytes))), 16).PadLeft(2, '0'); 
            }
            
        }

        private void tbFunctionCode_Leave(object sender, EventArgs e)
        {
            UInt16 tmpFC;

            if (UInt16.TryParse(tbFunctionCode.Text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out tmpFC))
            {
                tbCheckSum.Text = Convert.ToString(((_sender.CalculateChecksum(tmpFC, _bytes))), 16).PadLeft(2, '0');
            }
        }

        private void btnStartReceive_Click(object sender, EventArgs e)
        {
            if (_receiverThread.ThreadState == ThreadState.Unstarted)
            {
                _receiverThread.Start();
                lblStatus.Text = @"Started Receiving";
            }
            else if(_receiverThread.ThreadState == ThreadState.Suspended)
            {
#pragma warning disable 612,618
                _receiverThread.Resume();
#pragma warning restore 612,618
            }

            btnStartReceive.Enabled = false;
            btnEndReceive.Enabled = true;
            chBoxExpectResponse.Enabled = false;
            chBoxExpectResponse.Checked = false;
        }

        private void ReceiverThread()
        {
            UdpClient receiver = null;
            try
            {
                receiver = new UdpClient(_sender.PortReceiving);
            }catch(SocketException e)
            {
                SetText("Recv Port is occupied", tbOutput, "append");
                return;
            }
            _tmpSocket = receiver;
         
            while (true)
            {
                var remoteIpEndPoint = new IPEndPoint(IPAddress.Any, 0);
                byte[] receivedData = receiver.Receive(ref remoteIpEndPoint);             
                var receivedMessage = "Recv Message: " + String.Join(" ", receivedData.Select(x => x.ToString("X2")).ToArray());
                
                if (chBoxCheckReceivedMessages.Checked)
                {
                    var checkSum = (byte)((receivedData.Take(receivedData.Length-1).Sum(x => x)) % 0xFF);
                    var length = (receivedData[2] << 8) + receivedData[3];

                    if(checkSum != receivedData[receivedData.Length-1])
                    {
                        receivedMessage += " |Checksum Error|";
                    }

                    if (length != (receivedData.Length - 5))
                    {
                        receivedMessage += " |Length Error|";
                    }    
                }

                if (chBoxCounter.Checked)
                {
                    _mut.WaitOne();
                    counter++;
                    _mut.ReleaseMutex();
                    receivedMessage = "Nr: " +counter.ToString("D4",CultureInfo.InvariantCulture) + " " + receivedMessage;
                }

                if (chBoxTimestamp.Checked)
                {
                    DateTime currentTime;
                    currentTime = DateTime.Now;

                    receivedMessage = currentTime.ToString("HH:mm:ss:fff",CultureInfo.InvariantCulture) + " " + receivedMessage;
                }

                SetText(receivedMessage,tbOutput,"append");
            }
        }

        private void SetText(string text,TextBox textbox,String flag)
        {
            if (InvokeRequired)
            {
                try
                {
                    // Enter any delegate here, with an optional array wich will be passed as
                    // arguments to the delegate function.
                    Invoke(new MethodDelegate(SetText), new object[] {text,textbox,flag});
                }
                catch
                {
                }
            }
            else
            {
                if (flag.Equals("append"))
                {
                    textbox.AppendText(text + Environment.NewLine);
                }
                else if (flag.Equals("replace"))
                {
                    textbox.Text = text;
                }
            }
        }

        private void btnEndReceive_Click(object sender, EventArgs e)
        {

            _receiverThread.Abort();
            try
            {
                _tmpSocket.Close();
            }
            catch (NullReferenceException)
            {
            }
            _receiverThread = new Thread(ReceiverThread);
            lblStatus.Text = @"Stopped Receiving";

            btnStartReceive.Enabled = true;
            btnEndReceive.Enabled = false;
            chBoxExpectResponse.Enabled = true;
           
        }

        private static string ExpandString(string str)
        {
            str = str.Replace(" ", "");

            if (str.Length % 2 != 0)
                str = str.Insert(0, "0");

            for (var i = 2; i < str.Length; i += 3)
                str = str.Insert(i, " ");

            return str;
        }

        private void tbBoxesNetwork_Leave(object sender, EventArgs e)
        {
            int senderPort, receiverPort;

            _sender.IPAdress = tbBoxIPAdress.Text;

            if (Int32.TryParse(tbPortSend.Text, out senderPort))
            {
                _sender.SendingPort = senderPort;
            }

            if (Int32.TryParse(tbPortRecv.Text, out receiverPort))
            {
                _sender.PortReceiving = receiverPort;
            }

        }

        private void tbBoxesNetwork_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                tbBoxesNetwork_Leave(sender, e);
            }
        }

        private void btnGraphing_Click(object sender, EventArgs e)
        {
            Graph graph = new Graph();
            graph.Show();
        }



        private void tbDataInput_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter && tbDataInput.Text != "")
            {
                this.tBoxDataInput_Leave(sender, e);
                this.btnSend_Click(sender, e);
            }

        }

        private void threadReceivingSpeed()
        {
            int tempFirst, tempAfter;
            for (; ;)
            {
                _mut.WaitOne();
                tempFirst = counter;
                _mut.ReleaseMutex();
                Thread.Sleep(1000);

                _mut.WaitOne();
                tempAfter = counter;
                _mut.ReleaseMutex();

                SetText((tempAfter - tempFirst).ToString(), tbMessagesSpeed,"replace");
            }
            
        }

        private void UDPTest_FormClosing(object sender, FormClosingEventArgs e)
        {
            _receiverThread.Abort();
            _timerThread.Abort();
            if (_tmpSocket != null) 
                _tmpSocket.Close();
        }

        
    }
}
