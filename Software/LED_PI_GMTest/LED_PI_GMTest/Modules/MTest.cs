using System.ComponentModel;

namespace LED_PI_GMTest.Modules
{
    internal class MTest : IModule
    {
        private readonly MTestSettings _settings = new MTestSettings();
        
        public void Draw(ref Color[,] image)
        {
            for (int i = 0; i < image.GetLength(0); i++)
            {
                for (int j = 0; j < image.GetLength(1); j++)
                {
                    if (_settings.Invert)
                        image[i, j] = new Color(_settings.Red, _settings.Green, _settings.Blue).Invert();
                    else
                        image[i, j] = new Color(_settings.Red, _settings.Green, _settings.Blue);   
                }
            }
        }

        public object GetSettings()
        {
            return _settings;
        }

        public string Name { get { return "Test Module"; } }
    }

    internal class MTestSettings
    {
        [Category("Color")]
        public byte Red { set; get; }
        [Category("Color")]
        public byte Green { set; get; }
        [Category("Color")]
        public byte Blue { set; get; }

        [Category("Color"),
         Description("Inverts the created colors")]
        public bool Invert { set; get; }
    }
}
