using System;
using System.ComponentModel;

namespace LED_PI_GMTest.Modules
{
    internal class Sinusoid2 : IModule
    {
        private double _step;

        public Sinusoid2()
        {
            Period = Math.PI / 7.5;
            Step = 0.1;
            Vertical = 2;
            Horizontal = 3;
        }

        public void Draw(ref Color[,] image)
        {
            _step += Step;

            for (int i = 0; i < image.GetLength(0); i++)
            {
                for (int j = 0; j < image.GetLength(1); j++)
                {
                    double calc = i*Math.Sin(_step/Horizontal) + j*Math.Sin(_step/Vertical);
                    double sat = (Math.Sin(calc * Period + _step) + 1) / 2;
                    var color = new Color(sat, sat, sat);

                    if (Invert)
                        image[i, j] = color.Invert();
                    else
                        image[i, j] = color;   
                }
            }
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
         Description("Controls the sines period.")]
        public double Period { get; set; }

        public object GetSettings()
        {
            return this;
        }

        public string Name { get { return "2 Sinusoids"; } }

        [Category("Color"),
         Description("Inverts the created colors") ]
        public bool Invert { set; get; }
    }
}
