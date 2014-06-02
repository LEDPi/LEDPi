namespace LED_PI_GMTest
{
    internal struct Color
    {
        private byte _red;
        private byte _green;
        private byte _blue;

        public Color(byte red, byte green, byte blue) : this()
        {
            Red = red;
            Green = green;
            Blue = blue;
        }

        public Color(double red, double green, double blue)
            : this()
        {
            Red = (byte)(red < 0 ? 0 : red > 1 ? Depth : red * Depth);
            Green = (byte)(green < 0 ? 0 : green > 1 ? Depth : green * Depth);
            Blue = (byte)(blue < 0 ? 0 : blue > 1 ? Depth : blue * Depth);
        }

        public static byte Depth = 255;

        public byte Red   { set { _red   = value > Depth ? Depth : value; } get { return _red;   } }
        public byte Green { set { _green = value > Depth ? Depth : value; } get { return _green; } }
        public byte Blue  { set { _blue  = value > Depth ? Depth : value; } get { return _blue;  } }
        
        public Color Invert()
        {
            Red   = (byte) (Depth - Red  );
            Green = (byte) (Depth - Green);
            Blue  = (byte) (Depth - Blue );

            return this;
        }

        public System.Drawing.Color ToColor()
        {
            return System.Drawing.Color.FromArgb((byte)(Red * (255d / Depth)),
                                                 (byte)(Green * (255d / Depth)),
                                                 (byte)(Blue * (255d / Depth)));
        }
    }
}
