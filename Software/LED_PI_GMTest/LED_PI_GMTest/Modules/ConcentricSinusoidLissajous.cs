using System;
using System.ComponentModel;

namespace LED_PI_GMTest.Modules
{
    internal class ConcentricSinusoidLissajous  : IModule
    {
        private double _step;

        public ConcentricSinusoidLissajous()
        {
            Scale = 100;
            Step = 0.1;
            Vertical = 3;
            Horizontal = 5;

            LissajousA = 2;
            LissajousB = 3;
            LissajousSigma = Math.PI/2;
            LissajousPreScale = 4;
        }
        
        public void Draw(ref Color[,] image)
        {
            _step += Step;

            for (int i = 0; i < image.GetLength(0); i++)
            {
                for (int j = 0; j < image.GetLength(1); j++)
                {
                    double cx = i + .5 * Math.Sin(_step / Horizontal) -
                        (15 * Math.Sin(LissajousA * (_step / LissajousPreScale) + LissajousSigma) + 15);
                    double cy = j + .5 * Math.Cos(_step / Vertical) -
                        (15 * Math.Sin(LissajousB * (_step / LissajousPreScale)) + 15); 

                    double sat = (Math.Sin(Math.Sqrt(Scale + cx * cx + cy * cy + 1) + _step) + 1) / 2;
                    var color = new Color(sat, sat, sat);

                    if (Invert)
                        image[i, j] = color.Invert();
                    else
                        image[i, j] = color;   
                }
            }
        }

        public object GetSettings()
        {
            return this;
        }

        [Category("Sine"),
         Description("Sets the vertical influence of the time.")]
        public double Vertical { get; set; }

        [Category("Sine"),
         Description("Sets the horizontal influence of the time.")]
        public double Horizontal { get; set; }

        [Category("Sine"),
         Description("Sets the step withd, wich is added each frame.")]
        public double Step { get; set; }

        [Category("Sine"),
         Description("Controls sineoids scale.")]
        public double Scale { get; set; }

        [Category("Lissajous"),
         Description("Sets a parameter ofs lissajours curve (A sin(at + sigma))")]
        public double LissajousA { get; set; }

        [Category("Lissajous"),
         Description("Sets b parameter ofs lissajours curve (B sin(bt))")]
        public double LissajousB { get; set; }

        [Category("Lissajous"),
         Description("Sets sigma parameter ofs lissajours curve (A sin(at + sigma))")]
        public double LissajousSigma { get; set; }

        [Category("Lissajous"),
         Description("Sets the time prescale for the movement on the lissajoures curve.")]
        public double LissajousPreScale { get; set; }

        public string Name { get { return "Concentric Sinusoids Lissajous"; } }

        [Category("Color"),
         Description("Inverts the created colors") ]
        public bool Invert { set; get; }
    }
}
