using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Globalization;

namespace JPEG_TO_LED
{
    public partial class Form1 : Form
    {
        const int LED_HEIGHT = 30;
        const int LED_WIDTH = 30;
        const string MACRO = "DRAW_VAL";
        static Bitmap readBMP;
        static string filename;

        public Form1()
        {
            InitializeComponent();
        }

        private void btnOpenJPEG_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();

            dialog.InitialDirectory = "c:\\";
            dialog.Filter = "Image files (*.jpg, *.jpeg, *.jpe, *.jfif, *.png) | *.jpg; *.jpeg; *.jpe; *.jfif; *.png";
            dialog.FilterIndex = 2;
            dialog.RestoreDirectory = true;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string directoryPath = dialog.FileName;
                filename = Path.GetFileNameWithoutExtension(directoryPath);
                Image image = Image.FromFile(directoryPath);
                readBMP = new Bitmap(image);

                readBMP = new Bitmap(readBMP, new Size(LED_WIDTH, LED_HEIGHT));
                picBox1.SizeMode = PictureBoxSizeMode.StretchImage;
                picBox1.Image = (Image)readBMP;
            }
        }

        private void btnDataToText_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog();
            saveFile.Filter = "txt files (*.txt)|*.txt"  ;
            saveFile.Title = "Directory to save the Textdatafile";
            saveFile.FileName = filename;  //Default Filename
            saveFile.RestoreDirectory = true ;


            if (saveFile.ShowDialog() == DialogResult.OK)
            {
                
            }

            FileStream fs = new FileStream (saveFile.FileName, FileMode.OpenOrCreate, FileAccess.Write);
            createCodeData(new StreamWriter(fs));

        }

        private void btnTxtToClipboard_Click(object sender, EventArgs e)
        {
            StringWriter sw = new StringWriter();
            createCodeData(sw);
            Clipboard.SetText(sw.ToString());
        }

        private void createCodeData(TextWriter writer)
        {
            float r, g, b;

            writer.WriteLine("draw_buffer_t " + filename + " = ");
            writer.WriteLine("{");

            for (int y = 0; y < LED_HEIGHT; y++)
            {
                writer.Write("  {");

                for (int x = 0; x < LED_WIDTH; x++)
                {
                    r = (float)readBMP.GetPixel(x, y).R / 255;
                    g = (float)readBMP.GetPixel(x, y).G / 255;
                    b = (float)readBMP.GetPixel(x, y).B / 255;
                    writer.Write(MACRO + "(" + r.ToString("0.000", CultureInfo.InvariantCulture) + "f," + g.ToString("0.000", CultureInfo.InvariantCulture) + "f," + b.ToString("0.000", CultureInfo.InvariantCulture) + "f)");

                    if (x != (LED_WIDTH - 1))
                        writer.Write(",");
                }
                if (y != (LED_HEIGHT - 1))
                    writer.WriteLine("},");
            }

            writer.WriteLine("}");
            writer.WriteLine("};");
            writer.Close();
        }

        private void createCodeDataInteger(TextWriter writer)
        {
            int r, g, b;

            writer.WriteLine("draw_buffer_t " + filename + " = ");
            writer.WriteLine("{");

            for (int y = 0; y < LED_HEIGHT; y++)
            {
                writer.Write("  {");

                for (int x = 0; x < LED_WIDTH; x++)
                {
                    r = (readBMP.GetPixel(x, y).R*4)/255;
                    g = (readBMP.GetPixel(x, y).G*4)/255;
                    b = (readBMP.GetPixel(x, y).B*4)/255;
                    writer.Write(MACRO + "(" + r.ToString() + "," + g.ToString() + "," + b.ToString() + ")");

                    if (x != (LED_WIDTH - 1))
                        writer.Write(",");
                }
                if (y != (LED_HEIGHT - 1))
                    writer.WriteLine("},");
            }

            writer.WriteLine("}");
            writer.WriteLine("};");
            writer.Close();
        }

       

    }
}
