using System;
using System.ComponentModel;

namespace LED_PI_GMTest.Modules
{
    internal class ConcentricSinusoid : IModule
    {
        private double _step;

        public ConcentricSinusoid()
        {
            Scale = 100;
            Step = 0.1;
            Vertical = 3;
            Horizontal = 5;

            OffsetX = 15;
            OffsetY = 15;
        }
        
        public void Draw(ref Color[,] image)
        {
            _step += Step;

            for (int i = 0; i < image.GetLength(0); i++)
            {
                for (int j = 0; j < image.GetLength(1); j++)
                {
                    double cx = i + .5 * Math.Sin(_step / Horizontal) - OffsetX;
                    double cy = j + .5 * Math.Cos(_step / Vertical) - OffsetY;

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

        [Category("Sine"),
         Description("Sets the circels center")]
        public double OffsetY { get; set; }

        [Category("Sine"),
         Description("Sets the circels center")]
        public double OffsetX { get; set; }

        public string Name { get { return "Concentric Sinusoids"; } }

        [Category("Color"),
         Description("Inverts the created colors") ]
        public bool Invert { set; get; }
    }
}
