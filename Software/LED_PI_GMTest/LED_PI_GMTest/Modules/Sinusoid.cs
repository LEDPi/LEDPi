using System;
using System.ComponentModel;

namespace LED_PI_GMTest.Modules
{
    internal class Sinusoid : IModule
    {
        private double _step;

        public Sinusoid()
        {
            Period = Math.PI / 7.5;
            Step = 0.1;
        }

        public void Draw(ref Color[,] image)
        {
            _step += Step;

            for (int i = 0; i < image.GetLength(0); i++)
            {
                double sat = (Math.Sin(i * Period + _step) + 1) / 2;
                var color = new Color(sat, sat, sat);

                for (int j = 0; j < image.GetLength(1); j++)
                {

                    if (Invert)
                        image[i, j] = color.Invert();
                    else
                        image[i, j] = color;   
                }
            }
        }

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

        public string Name { get { return "Simple Sinusoid"; } }

        [Category("Color"),
         Description("Inverts the created colors") ]
        public bool Invert { set; get; }
    }
}
