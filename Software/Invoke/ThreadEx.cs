using System;
using System.Globalization;
using System.Threading;
using System.Windows.Forms;

namespace Invoke
{
    public partial class ThreadEx : Form
    {
        /// <summary>
        /// Delegate needed to pass the function to the invoke method.
        /// </summary>
        /// <param name="text">The text.</param>
        private delegate void MethodDelegate(string text);

        private readonly Thread _backgroundThread;

        /// <summary>
        /// Initializes a new instance of the <see cref="ThreadEx"/> class.
        /// </summary>
        public ThreadEx()
        {
            InitializeComponent();

            _backgroundThread = new Thread(BackgroundThread);
        }

        /// <summary>
        /// Handles the Load event of the ThreadEx control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void ThreadEx_Load(object sender, EventArgs e)
        {
            _backgroundThread.Start();
        }

        /// <summary>
        /// Handles the FormClosing event of the ThreadEx control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="FormClosingEventArgs"/> instance containing the event data.</param>
        private void ThreadEx_FormClosing(object sender, FormClosingEventArgs e)
        {
            _backgroundThread.Abort();
        }

        /// <summary>
        /// Backgrounds thread: writes every second to the gui.
        /// </summary>
        private void BackgroundThread()
        {
            var counter = 1;
            while (true)
            {
                SetText(counter++.ToString(CultureInfo.InvariantCulture) + "s");
                Thread.Sleep(1000);
            }
        }

        /// <summary>
        /// Sets the text threadsafe.
        /// </summary>
        /// <param name="text">The text.</param>
        public void SetText(string text)
        {
            if (InvokeRequired)
            {
                try
                {
                    // Enter any delegate here, with an optional array wich will be passed as
                    // arguments to the delegate function.
                    Invoke(new MethodDelegate(SetText), new object[] {text});
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, ex.Message, @"Error");
                }
            }
            else
            {
                lblSet.Text = text;
            }
        }
    }
}
