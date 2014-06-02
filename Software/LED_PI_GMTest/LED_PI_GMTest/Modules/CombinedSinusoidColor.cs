using System;
using System.ComponentModel;

namespace LED_PI_GMTest.Modules
{
    internal class CombinedSinusoidColor : IModule
    {
        private double _step;

        public CombinedSinusoidColor()
        {
            Step = 0.1;

            // Sinesoid1 defaults
            Sinusoid1Period = Math.PI / 7.5;

            // Sinesoid2 defaults
            Sinesoid2Period = Math.PI / 7.5;
            Sinesoid2Vertical = 2;
            Sinesoid2Horizontal = 3;

            // Concentric defaults
            ConcentricScale = 2500;
            ConcentricVertical = 3;
            ConcentricHorizontal = 5;

            ConcentricLissajousA = 2;
            ConcentricLissajousB = 3;
            ConcentricLissajousSigma = Math.PI / 2;
            ConcentricLissajousPreScale = 4;
        }

        public void Draw(ref Color[,] image)
        {
            _step += Step;

            for (int i = 0; i < image.GetLength(0); i++)
            {
                for (int j = 0; j < image.GetLength(1); j++)
                {
                    double sat = GetSaturation(i, j);

                    double r = 0, g = 0, b = 0;
                    switch (Color)
                    {
                        case PlamsaColor.RedGreen:
                            r = Math.Sin(sat*Math.PI);
                            g = Math.Cos(sat*Math.PI);
                            b = 0;
                            break;
                        case PlamsaColor.GreenBlue: 
                            r = 1;
                            g = Math.Cos(sat * Math.PI);
                            b = Math.Sin(sat*Math.PI);
                            break;
                        case PlamsaColor.RGB:
                            r = Math.Sin(sat * Math.PI);
                            g = Math.Sin(sat * 2 * Math.PI / 3);
                            b = Math.Sin(sat * 4 * Math.PI / 3);
                            break;
                        case PlamsaColor.Grey:
                            r= g = b = Math.Cos(sat * 5 * Math.PI);
                            break;
                        default:
                            throw new ArgumentOutOfRangeException();
                    }
                    
                    r = (r + 1)/2;
                    g = (g + 1)/2;
                    b = (b + 1)/2;

                    // r = (r) / 2;
                    // g = (g) / 2;
                    // b = (b) / 2;
                    
                    var color = new Color(r, g, b);

                    if (Invert)
                        image[i, j] = color.Invert();
                    else
                        image[i, j] = color;   
                }
            }
        }

        private double GetSaturation(int i, int j)
        {
            double sat;
            switch (Method)
            {
                case CombiningMethod.Add:
                    sat = (Sinusoid1(i, j) + Sinusoid2(i, j) + Concentric(i, j) + 1) / 2;
                    break;
                case CombiningMethod.Subtract:
                    sat = (1 - Sinusoid1(i, j) - Sinusoid2(i, j) - Concentric(i, j) - 1) / 2;
                    break;
                case CombiningMethod.Multiply:
                    sat = (Sinusoid1(i, j) * Sinusoid2(i, j) * Concentric(i, j) + 1) / 2;
                    break;
                case CombiningMethod.AddFlat:
                    sat = (Math.Abs(Sinusoid1(i, j)) + Math.Abs(Sinusoid2(i, j)) + Math.Abs(Concentric(i, j))) / 3;
                    break;
                case CombiningMethod.Divide:
                    double var1 = Sinusoid1(i, j);
                    double var2 = Sinusoid2(i, j);
                    double var3 = Concentric(i, j);

                    sat = ((var1 == 0 ? 0 : (1 / var1)) * (var2 == 0 ? 0 : (1 / var2)) * (var3 == 0 ? 0 : (1 / var3)) + 1) / 2;
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
            return sat;
        }

        private double Sinusoid1(int x, int y)
        {
            return Math.Sin(x * Sinusoid1Period + _step);
        }

        private double Sinusoid2(int x, int y)
        {
            double calc = x * Math.Sin(_step / Sinesoid2Horizontal) + y * Math.Sin(_step / Sinesoid2Vertical);
            return Math.Sin(calc * Sinesoid2Period + _step);
        }
        
        private double Concentric(int x, int y)
        {
            double cx = x + .5 * Math.Sin(_step / ConcentricHorizontal) -
                        (15 * Math.Sin(ConcentricLissajousA * (_step / ConcentricLissajousPreScale) + ConcentricLissajousSigma) + 15);
            double cy = y + .5 * Math.Cos(_step / ConcentricVertical) -
                        (15 * Math.Sin(ConcentricLissajousB * (_step / ConcentricLissajousPreScale)) + 15);

            return Math.Sin(Math.Sqrt(ConcentricScale + cx*cx + cy*cy + 1) + _step);
        }

        public object GetSettings()
        {
            return this;
        }

        [Category("General"),
         Description("Sets the step withd, wich is added each frame.")]
        public double Step { get; set; }

        public string Name { get { return "Combined Sinusoids Color"; } }

        [Category("Color"),
         Description("Inverts the created colors")]
        public bool Invert { set; get; }

        [Category("Sinesoid 1"),
         Description("Controls the sines period.")]
        public double Sinusoid1Period { get; set; }

        [Category("Sinesoid 2"),
         Description("Sets the vertical influence of the time.")]
        public double Sinesoid2Vertical { get; set; }

        [Category("Sinesoid 2"),
         Description("Sets the horizontal influence of the time.")]
        public double Sinesoid2Horizontal { get; set; }

        [Category("Sinesoid 2"),
         Description("Controls the sines period.")]
        public double Sinesoid2Period { get; set; }

        [Category("Concentric"),
         Description("Sets the vertical influence of the time.")]
        public double ConcentricVertical { get; set; }

        [Category("Concentric"),
         Description("Sets the horizontal influence of the time.")]
        public double ConcentricHorizontal { get; set; }

        [Category("Concentric"),
         Description("Controls sineoids scale.")]
        public double ConcentricScale { get; set; }

        [Category("Concentric"),
         Description("Sets a parameter ofs lissajours curve (A sin(at + sigma))")]
        public double ConcentricLissajousA { get; set; }

        [Category("Concentric"),
         Description("Sets b parameter ofs lissajours curve (B sin(bt))")]
        public double ConcentricLissajousB { get; set; }

        [Category("Concentric"),
         Description("Sets sigma parameter ofs lissajours curve (A sin(at + sigma))")]
        public double ConcentricLissajousSigma { get; set; }

        [Category("Concentric"),
         Description("Sets the time prescale for the movement on the lissajoures curve.")]
        public double ConcentricLissajousPreScale { get; set; }

        [Category("General"),
         Description("Determines how the sinusoids are combined")]
        public CombiningMethod Method { set; get; }

        [Category("General"),
         Description("Determines how the colors are calculated")]
        public PlamsaColor Color { set; get; }
    }

    internal enum PlamsaColor
    {
        RedGreen,
        GreenBlue,
        RGB,
        Grey,
    }
}